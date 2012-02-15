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

#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>
#include <QHash>
#include <QList>
#include <QPluginLoader>
#include <QVariant>

#include "plugin.h"
#include "plugininfo.h"

class PluginManager: public QObject
{
    Q_OBJECT

    public:
        explicit PluginManager(QObject *parent = 0);
        Q_INVOKABLE QImage getFrame(const QImage &image, QString deviceId);
        Q_INVOKABLE void resize(QSize size, QString deviceId);
        Q_INVOKABLE QList<QVariant> pluginsInfoList();
        Q_INVOKABLE void applyTo(QString pluginId, QString deviceId, bool apply);

    public slots:
        bool disablePlugin(QString pluginId);
        bool disablePlugin(qint32 index);
        bool enablePlugin(QString pluginId);
        bool enablePlugin(QString pluginId, qint32 index);
        void configurePlugin(QString pluginId);
        void movePlugin(qint32 from, qint32 to);

    private:
        QSize frameSize;
        QPluginLoader pluginLoader;
        QList<Plugin *> activePlugins;
        QHash<QString, PluginInfo> pluginsInfo;
        QHash<QString, QVariant> pluginConfigs;
};

#endif // PLUGINMANAGER_H
