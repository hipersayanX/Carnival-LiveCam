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

#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include "pluginfactory.h"
#include "plugininfo.h"

class PluginManager: public QObject
{
    Q_OBJECT

    public:
        explicit PluginManager(QObject *parent = 0);
        Q_INVOKABLE QList<QVariant> toList();

    private:
        QPluginLoader m_pluginLoader;
        QHash<QString, Plugin *> m_plugins;
        QHash<QString, PluginInfo> m_pluginsInfo;
        QHash<QString, QVariant> m_pluginConfigs;

        Plugin *plugin(QString pluginId);
        bool isLoaded(QString pluginId);
        bool load(QString pluginId);
        bool unload(QString pluginId);

    public slots:
        void setPipeline(QString pipeline);
};

#endif // PLUGINMANAGER_H
