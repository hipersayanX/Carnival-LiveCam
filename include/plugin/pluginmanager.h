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
        QImage getFrame(const QImage &image);
        void resize(QSize size);
        QList<QVariant> pluginsToQml();

    public slots:
        bool disablePlugin(QString id);
        bool disablePlugin(int index);
        bool enablePlugin(QString id);
        bool enablePlugin(QString id, int index);
        void configurePlugin(QString id);
        void movePlugin(int from, int to);

    private:
        QSize frameSize;
        QPluginLoader pluginLoader;
        QList<Plugin *> activePlugins;
        QHash<QString, PluginInfo> pluginsInfo;
};

#endif // PLUGINMANAGER_H
