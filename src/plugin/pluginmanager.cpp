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

            this->pluginsInfo[plugin->id()] = PluginInfo(fileName,
                                                   false,
                                                   plugin->author(),
                                                   plugin->mail(),
                                                   plugin->website(),
                                                   plugin->category(),
                                                   plugin->id(),
                                                   plugin->license(),
                                                   plugin->name(),
                                                   plugin->summary(),
                                                   plugin->thumbnail(),
                                                   plugin->is3D(),
                                                   plugin->version(),
                                                   plugin->isConfigurable());

            this->pluginLoader.unload();
        }

        pluginDir.cdUp();
    }
}

QList<QVariant> PluginManager::pluginsToQml()
{
    QList<QVariant> pluginList;

    foreach (PluginInfo plugin, this->pluginsInfo)
    {
        QMap<QString, QVariant> pluginInfoMap;

        pluginInfoMap["pluginId"] = QVariant(plugin.id);
        pluginInfoMap["name"] = QVariant(plugin.name);
        pluginInfoMap["version"] = QVariant(plugin.version);
        pluginInfoMap["summary"] = QVariant(plugin.summary);
        pluginInfoMap["category"] = QVariant(plugin.category);
        pluginInfoMap["thumbnail"] = QVariant(plugin.thumbnail);
        pluginInfoMap["is3D"] = QVariant(plugin.is3D);
        pluginInfoMap["license"] = QVariant(plugin.license);
        pluginInfoMap["author"] = QVariant(plugin.author);
        pluginInfoMap["website"] = QVariant(plugin.website);
        pluginInfoMap["mail"] = QVariant(plugin.mail);
        pluginInfoMap["isActivated"] = QVariant(false);
        pluginInfoMap["isConfigurable"] = QVariant(plugin.isConfigurable);

        pluginList << pluginInfoMap;
    }

    return pluginList;
}

bool PluginManager::enablePlugin(QString id)
{
    this->pluginLoader.setFileName(pluginsInfo[id].fileName);

    QObject *pluginInstance = this->pluginLoader.instance();

    if (!pluginInstance)
        return false;

    Plugin *plugin = qobject_cast<Plugin *>(pluginInstance);

    if (!plugin)
        return false;

    this->pluginsInfo[id].isEnabled = true;
    this->activePlugins << plugin;

    plugin->begin();
    plugin->resize(this->frameSize.width(), this->frameSize.height());

    return true;
}

bool PluginManager::enablePlugin(QString id, int index)
{
    this->pluginLoader.setFileName(this->pluginsInfo[id].fileName);

    if (!this->pluginLoader.load())
        return false;

    QObject *pluginInstance = this->pluginLoader.instance();

    if (!pluginInstance)
        return false;

    Plugin *plugin = qobject_cast<Plugin *>(pluginInstance);

    if (!plugin)
        return false;

    this->pluginsInfo[id].isEnabled = true;
    this->activePlugins.insert(index, plugin);

    plugin->begin();
    plugin->resize(this->frameSize.width(), this->frameSize.height());

    return true;
}

bool PluginManager::disablePlugin(QString id)
{
    bool isEnabled = false;

    for (int i = 0; i < this->activePlugins.size(); i++)
        if (this->activePlugins[i]->id() == id)
        {
            this->activePlugins[i]->end();
            this->activePlugins.removeAt(i);
            isEnabled = true;

            break;
        }

    if (!isEnabled)
        return false;

    this->pluginLoader.setFileName(this->pluginsInfo[id].fileName);
    this->pluginsInfo[id].isEnabled = false;
    this->pluginLoader.unload();

    return true;
}

bool PluginManager::disablePlugin(int index)
{
    if (index < 0 || index >= this->activePlugins.size())
        return false;

    this->activePlugins[index]->end();
    this->pluginsInfo[this->activePlugins[index]->id()].isEnabled = false;
    this->pluginLoader.setFileName(this->pluginsInfo[activePlugins[index]->id()].fileName);
    this->pluginLoader.unload();
    this->activePlugins.removeAt(index);

    return true;
}

void PluginManager::configurePlugin(QString id)
{
    for (int i = 0; i < this->activePlugins.size(); i++)
        if (this->activePlugins[i]->id() == id)
        {
            this->activePlugins[i]->configure();

            break;
        }
}

void PluginManager::movePlugin(int from, int to)
{
    this->activePlugins.move(from, to);
}

void PluginManager::resize(QSize size)
{
    this->frameSize = size;

    for (int i = 0; i < this->activePlugins.size(); i++)
        this->activePlugins[i]->resize(size.width(), size.height());
}

QImage PluginManager::getFrame(const QImage &image)
{
    QImage frame = image;

    for (int currentPlugin = 0; currentPlugin < this->activePlugins.size(); currentPlugin++)
        frame = this->activePlugins[currentPlugin]->render(frame);

    return frame;
}
