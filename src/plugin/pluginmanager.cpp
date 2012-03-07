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
                                                   plugin->isConfigurable(),
                                                   QStringList());

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
QList<QVariant> PluginManager::pluginsInfoList()
{
    QList<QVariant> pluginList;

    foreach (PluginInfo plugin, this->pluginsInfo)
    {
        QMap<QString, QVariant> pluginInfoMap;

        pluginInfoMap["pluginId"] = QVariant(plugin.pluginId());
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
        pluginInfoMap["applyTo"] = QVariant(plugin.applyTo());

        pluginList << pluginInfoMap;
    }

    return pluginList;
}

// < !!!
void PluginManager::applyTo(QString pluginId, QString deviceId, bool apply)
{
    QStringList applyToList = this->pluginsInfo[pluginId].applyTo();

    if (applyToList.contains(deviceId) && !apply)
        applyToList.removeOne(deviceId);
    else if (!applyToList.contains(deviceId) && apply)
        applyToList << deviceId;

    this->pluginsInfo[pluginId].setApplyTo(applyToList);
}

bool PluginManager::setEffect(QString pluginId, QString spaceId, QSize frameSize)
{
    this->pluginLoader.setFileName(pluginsInfo[pluginId].fileName());

    QObject *pluginInstance = this->pluginLoader.instance();

    if (!pluginInstance)
        return false;

    Plugin *plugin = qobject_cast<Plugin *>(pluginInstance);

    if (!plugin)
        return false;

    this->pluginsInfo[pluginId].setIsEnabled(true);
    this->activePlugins << plugin;

    if (this->pluginConfigs.contains(pluginId))
        plugin->setConfigs(this->pluginConfigs[pluginId]);

    plugin->begin();

    for (qint32 i = 0; i < this->activePlugins.size(); i++)
        if (this->activePlugins[i]->id() == pluginId)
        {
            this->activePlugins[i]->addSpace(pluginId, spaceId, frameSize);
            this->applyTo(pluginId, spaceId, true);

            break;
        }

    return true;
}

bool PluginManager::unsetEffect(QString pluginId, QString spaceId)
{
    bool isEnabled = false;

    for (qint32 i = 0; i < this->activePlugins.size(); i++)
        if (this->activePlugins[i]->id() == pluginId)
        {
            this->pluginConfigs[pluginId] = this->activePlugins[i]->configs();
            this->activePlugins[i]->end();
            this->activePlugins.removeAt(i);
            isEnabled = true;

            break;
        }

    if (!isEnabled)
        return false;

    this->pluginLoader.setFileName(this->pluginsInfo[pluginId].fileName());
    this->pluginsInfo[pluginId].setIsEnabled(false);
    this->pluginLoader.unload();

    for (qint32 i = 0; i < this->activePlugins.size(); i++)
        if (this->activePlugins[i]->id() == pluginId)
        {
            this->activePlugins[i]->removeSpace(pluginId, spaceId, frameSize);
            this->applyTo(pluginId, spaceId, false);

            break;
        }

    return true;
}
// > !!!

/*!
  \fn void PluginManager::configurePlugin(QString id)

  \param id Unique plugin identifier.

  \brief Calls the configuration dialog of the plugin id.
 */
void PluginManager::configurePlugin(QString pluginId)
{
    for (qint32 i = 0; i < this->activePlugins.size(); i++)
        if (this->activePlugins[i]->id() == pluginId)
        {
            this->activePlugins[i]->configure();

            break;
        }
}

/*!
  \fn void PluginManager::movePlugin(qint32 from, qint32 to)

  \param from The old index position of the plugin.
  \param to The new index position of the plugin.

  \brief Move a plugin from a index to another.
 */
void PluginManager::movePlugin(QString spaceId, qint32 from, qint32 to)
{
    this->activePlugins.move(spaceId, from, to);
}

/*!
  \fn QImage PluginManager::getFrame(const QImage &image)

  \param image The frame to apply the effects.

  \return The processed frame.

  \brief Applies all plugin effects to a frame.
 */
QImage PluginManager::render(QString deviceId, const QImage &image)
{
    QImage frame = image;

    for (qint32 plugin = 0; plugin < this->activePlugins.size(); plugin++)
        frame = this->activePlugins[plugin]->render(deviceId, frame);

    return frame;
}
