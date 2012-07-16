// Carnival LiveCam, Augmented reality made easy.
// Copyright (C) 2011-2012  Gonzalo Exequiel Pedone
//
// Carnival LiveCam is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Carnival LiveCam is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Carnival LiveCam.  If not, see <http://www.gnu.org/licenses/>.
//
// Email   : hipersayan DOT x AT gmail DOT com
// Web-Site: https://github.com/hipersayanX/Carnival-LiveCam

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

        foreach (QString pluginPath, pluginDir.entryList(QDir::Files, QDir::Name))
        {
            QString fileName = pluginDir.absoluteFilePath(pluginPath);

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
        pluginInfoMap["isConfigurable"] = QVariant(plugin.isConfigurable());
        pluginInfoMap["applyTo"] = QVariant(plugin.applyTo());

        pluginList << pluginInfoMap;
    }

    return pluginList;
}

Plugin *PluginManager::plugin(QString pluginId)
{
    foreach (Plugin *pluginPtr, this->activePlugins)
        if (pluginPtr->id() == pluginId)
            return pluginPtr;

    return NULL;
}

bool PluginManager::setEffect(QString pluginId, QString spaceId, QSize frameSize)
{
    Plugin *plugin;

    if (!this->pluginsInfo[pluginId].applyTo().isEmpty())
        plugin = this->plugin(pluginId);
    else
    {
        this->pluginLoader.setFileName(pluginsInfo[pluginId].fileName());

        QObject *pluginInstance = this->pluginLoader.instance();

        if (!pluginInstance)
            return false;

        plugin = qobject_cast<Plugin *>(pluginInstance);

        if (!plugin)
            return false;

        this->activePlugins << plugin;

        if (this->pluginConfigs.contains(pluginId))
            plugin->setConfigs(this->pluginConfigs[pluginId]);

        plugin->begin();
    }

    plugin->addSpace(spaceId, frameSize);

    if (this->devices.contains(spaceId))
        this->devices[spaceId] << pluginId;
    else
    {
        QStringList devicesList;

        devicesList << pluginId;
        this->devices[spaceId] = devicesList;
    }

    QStringList applyToList = this->pluginsInfo[pluginId].applyTo();

    if (!applyToList.contains(spaceId))
    {
        applyToList << spaceId;
        this->pluginsInfo[pluginId].setApplyTo(applyToList);
    }

    return true;
}

bool PluginManager::unsetEffect(QString pluginId, QString spaceId)
{
    if (this->pluginsInfo[pluginId].applyTo().isEmpty())
        return false;

    Plugin *plugin = this->plugin(pluginId);

    if (!plugin)
        return false;

    if (this->devices.contains(spaceId))
    {
        this->devices[spaceId].removeOne(pluginId);

        if (this->devices[spaceId].isEmpty())
            this->devices.remove(spaceId);
    }

    plugin->removeSpace(spaceId);

    QStringList applyToList = this->pluginsInfo[pluginId].applyTo();

    if (applyToList.contains(spaceId))
    {
        applyToList.removeOne(spaceId);
        this->pluginsInfo[pluginId].setApplyTo(applyToList);
    }

    if (this->pluginsInfo[pluginId].applyTo().isEmpty())
    {
        this->pluginConfigs[pluginId] = plugin->configs();
        plugin->end();
        this->activePlugins.removeOne(plugin);
        this->pluginLoader.setFileName(this->pluginsInfo[pluginId].fileName());
        this->pluginLoader.unload();
    }

    return true;
}

void PluginManager::unsetEffects(QString spaceId)
{
    QStringList activePlugins;

    foreach (Plugin *plugin, this->activePlugins)
        if (this->pluginsInfo[plugin->id()].applyTo().contains(spaceId))
            activePlugins << plugin->id();

    foreach (QString pluginId, activePlugins)
        this->unsetEffect(pluginId, spaceId);
}

/*!
  \fn void PluginManager::configurePlugin(QString id)

  \param id Unique plugin identifier.

  \brief Calls the configuration dialog of the plugin id.
 */
void PluginManager::configurePlugin(QString pluginId)
{
    Plugin *plugin = this->plugin(pluginId);

    if (!plugin)
        return;

    plugin->configure();
}

/*!
  \fn void PluginManager::movePlugin(qint32 from, qint32 to)

  \param from The old index position of the plugin.
  \param to The new index position of the plugin.

  \brief Move a plugin from a index to another.
 */
void PluginManager::movePlugin(QString spaceId, qint32 from, qint32 to)
{
    if (this->devices.contains(spaceId))
        this->devices[spaceId].move(from, to);
}

void PluginManager::mouseDoubleClickEvent(QString spaceId, QMouseEvent *event)
{
    foreach (Plugin *plugin, this->activePlugins)
        if (this->pluginsInfo[plugin->id()].applyTo().contains(spaceId))
            plugin->mouseDoubleClickEvent(spaceId, event);
}

void PluginManager::mouseMoveEvent(QString spaceId, QMouseEvent *event)
{
    foreach (Plugin *plugin, this->activePlugins)
        if (this->pluginsInfo[plugin->id()].applyTo().contains(spaceId))
            plugin->mouseMoveEvent(spaceId, event);
}

void PluginManager::mousePressEvent(QString spaceId, QMouseEvent *event)
{
    foreach (Plugin *plugin, this->activePlugins)
        if (this->pluginsInfo[plugin->id()].applyTo().contains(spaceId))
            plugin->mousePressEvent(spaceId, event);
}

void PluginManager::mouseReleaseEvent(QString spaceId, QMouseEvent *event)
{
    foreach (Plugin *plugin, this->activePlugins)
        if (this->pluginsInfo[plugin->id()].applyTo().contains(spaceId))
            plugin->mouseReleaseEvent(spaceId, event);
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

    if (!this->devices.contains(deviceId))
        return frame;

    foreach (QString pluginId, this->devices[deviceId])
    {
        Plugin *plugin = this->plugin(pluginId);

        if (!plugin)
            continue;

        frame = plugin->render(deviceId, frame);
    }

    return frame;
}
