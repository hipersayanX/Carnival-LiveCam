/*
 * Carnival LiveCam, Augmented reality made easy.
 * Copyright (C) 2011  Gonzalo Exequiel Pedone
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with This program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Email   : hipersayan DOT x AT gmail DOT com
 * Web-Site: http://hipersayanx.blogspot.com/
 */

#include <QStringList>
#include <QLibrary>
#include <QDir>
#include <QDebug>

#include "../../include/plugin/pluginmanager.h"

/*!
  \class PluginManager

  \brief This class is used for manage plugins.
 */

/*!
  \fn PluginManager::PluginManager(QObject *parent)

  \param parent Parent widget.
 */
PluginManager::PluginManager(QObject *parent): QObject(parent)
{
    QDir pluginDir("share/plugins");

    foreach (QString dirext, pluginDir.entryList(QDir::AllDirs | QDir::NoDot | QDir::NoDotDot, QDir::Name))
    {
        pluginDir.cd(dirext);

        foreach (QString plugin, pluginDir.entryList(QDir::Files, QDir::Name))
        {
            QString fileName = pluginDir.absoluteFilePath(plugin);

            if (!QLibrary::isLibrary(fileName))
                continue;

            this->pluginLoader.setFileName(fileName);

            if (!this->pluginLoader.load())
            {
                qDebug() << this->pluginLoader.errorString();

                continue;
            }

            QObject *pluginInstance = this->pluginLoader.instance();

            if (!pluginInstance)
                continue;

            Plugin *plugin = qobject_cast<Plugin *>(pluginInstance);

            if (!plugin)
                continue;

            qDebug() << "Loading: " << fileName;

            if (this->pluginConfigs.contains(plugin->id()))
                plugin->setConfigs(this->pluginConfigs[plugin->id()]);

            this->pluginsInfo[plugin->id()] = PluginInfo(fileName,
                                                   plugin->id(),
                                                   false,
                                                   plugin->name(),
                                                   plugin->version(),
                                                   plugin->summary(),
                                                   plugin->category(),
                                                   plugin->thumbnail(),
                                                   plugin->license(),
                                                   plugin->author(),
                                                   plugin->website(),
                                                   plugin->mail(),
                                                   plugin->is3D(),
                                                   plugin->isConfigurable());

            this->pluginLoader.unload();
        }

        pluginDir.cdUp();
    }
}

/*!
  \fn QList<QVariant> PluginManager::pluginsToQml()

  \return The list of plugins information in standard format.

  \brief Returns the list of plugins information in standard format.
 */
QList<QVariant> PluginManager::pluginsToQml()
{
    QList<QVariant> pluginList;

    foreach (PluginInfo plugin, this->pluginsInfo)
    {
        QMap<QString, QVariant> pluginInfoMap;

        pluginInfoMap["pluginId"] = QVariant(plugin.id());
        pluginInfoMap["name"] = QVariant(plugin.name());
        pluginInfoMap["version"] = QVariant(plugin.version());
        pluginInfoMap["summary"] = QVariant(plugin.summary());
        pluginInfoMap["category"] = QVariant(plugin.category());
        pluginInfoMap["thumbnail"] = QVariant(plugin.thumbnail());
        pluginInfoMap["is3D"] = QVariant(plugin.is3D());
        pluginInfoMap["license"] = QVariant(plugin.license());
        pluginInfoMap["author"] = QVariant(plugin.author());
        pluginInfoMap["website"] = QVariant(plugin.website());
        pluginInfoMap["mail"] = QVariant(plugin.mail());
        pluginInfoMap["isActivated"] = QVariant(false);
        pluginInfoMap["isConfigurable"] = QVariant(plugin.isConfigurable());

        pluginList << pluginInfoMap;
    }

    return pluginList;
}

/*!
  \fn bool PluginManager::enablePlugin(QString id)

  \param id Unique plugin identifier.

  \retval true if the plugin is active.
  \retval false if the plugin is inactive.

  \brief Try to activate the plugin id.
 */
bool PluginManager::enablePlugin(QString id)
{
    this->pluginLoader.setFileName(pluginsInfo[id].fileName());

    QObject *pluginInstance = this->pluginLoader.instance();

    if (!pluginInstance)
        return false;

    Plugin *plugin = qobject_cast<Plugin *>(pluginInstance);

    if (!plugin)
        return false;

    this->pluginsInfo[id].setIsEnabled(true);
    this->activePlugins << plugin;

    if (this->pluginConfigs.contains(id))
        plugin->setConfigs(this->pluginConfigs[id]);

    plugin->begin();
    plugin->resize(this->frameSize.width(), this->frameSize.height());

    return true;
}

/*!
  \fn bool PluginManager::enablePlugin(QString id, int index)

  \param id Unique plugin identifier.
  \param index The index to insert the plugin.

  \retval true if the plugin is active.
  \retval false if the plugin is inactive.

  \brief Try to activate the plugin \b id and insert it to \b index.
 */
bool PluginManager::enablePlugin(QString id, int index)
{
    this->pluginLoader.setFileName(this->pluginsInfo[id].fileName());

    if (!this->pluginLoader.load())
        return false;

    QObject *pluginInstance = this->pluginLoader.instance();

    if (!pluginInstance)
        return false;

    Plugin *plugin = qobject_cast<Plugin *>(pluginInstance);

    if (!plugin)
        return false;

    this->pluginsInfo[id].setIsEnabled(true);
    this->activePlugins.insert(index, plugin);

    if (this->pluginConfigs.contains(id))
        plugin->setConfigs(this->pluginConfigs[id]);

    plugin->begin();
    plugin->resize(this->frameSize.width(), this->frameSize.height());

    return true;
}

/*!
  \fn bool PluginManager::disablePlugin(QString id)

  \param id Unique plugin identifier.

  \retval true if the plugin is inactive.
  \retval false if the plugin is active.

  \brief Try to desactivate the device id.
 */
bool PluginManager::disablePlugin(QString id)
{
    bool isEnabled = false;

    for (int i = 0; i < this->activePlugins.size(); i++)
        if (this->activePlugins[i]->id() == id)
        {
            this->pluginConfigs[id] = this->activePlugins[i]->configs();
            this->activePlugins[i]->end();
            this->activePlugins.removeAt(i);
            isEnabled = true;

            break;
        }

    if (!isEnabled)
        return false;

    this->pluginLoader.setFileName(this->pluginsInfo[id].fileName());
    this->pluginsInfo[id].setIsEnabled(false);
    this->pluginLoader.unload();

    return true;
}

/*!
  \fn bool PluginManager::disablePlugin(int index)

  \param index Index of the plugin in the stack.

  \retval true if the plugin is inactive.
  \retval false if the plugin is active.

  \brief Try to desactivate the plugin at \b index.
 */
bool PluginManager::disablePlugin(int index)
{
    if (index < 0 || index >= this->activePlugins.size())
        return false;

    this->pluginConfigs[this->activePlugins[index]->id()] = this->activePlugins[index]->configs();
    this->activePlugins[index]->end();
    this->pluginsInfo[this->activePlugins[index]->id()].setIsEnabled(false);
    this->pluginLoader.setFileName(this->pluginsInfo[activePlugins[index]->id()].fileName());
    this->pluginLoader.unload();
    this->activePlugins.removeAt(index);

    return true;
}

/*!
  \fn void PluginManager::configurePlugin(QString id)

  \param id Unique plugin identifier.

  \brief Calls the configuration dialog of the plugin id.
 */
void PluginManager::configurePlugin(QString id)
{
    for (int i = 0; i < this->activePlugins.size(); i++)
        if (this->activePlugins[i]->id() == id)
        {
            this->activePlugins[i]->configure();

            break;
        }
}

/*!
  \fn void PluginManager::movePlugin(int from, int to)

  \param from The old index position of the plugin.
  \param to The new index position of the plugin.

  \brief Move a plugin from a index to another.
 */
void PluginManager::movePlugin(int from, int to)
{
    this->activePlugins.move(from, to);
}

/*!
  \fn void PluginManager::resize(QSize size)

  \param size The new size of the frame.

  \brief This method updates the frame size for all plugins.
 */
void PluginManager::resize(QSize size)
{
    this->frameSize = size;

    for (int i = 0; i < this->activePlugins.size(); i++)
        this->activePlugins[i]->resize(size.width(), size.height());
}

/*!
  \fn QImage PluginManager::getFrame(const QImage &image)

  \param image The frame to apply the effects.

  \return The processed frame.

  \brief Applies all plugin effects to a frame.
 */
QImage PluginManager::getFrame(const QImage &image)
{
    QImage frame = image;

    for (int currentPlugin = 0; currentPlugin < this->activePlugins.size(); currentPlugin++)
        frame = this->activePlugins[currentPlugin]->render(frame);

    return frame;
}
