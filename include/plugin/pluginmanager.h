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
        Q_INVOKABLE QImage render(QString deviceId, const QImage &image);
        Q_INVOKABLE QList<QVariant> pluginsInfoList();

    public slots:
        bool setEffect(QString pluginId, QString spaceId, QSize frameSize);
        bool unsetEffect(QString pluginId, QString spaceId);
        void unsetEffects(QString spaceId);
        void configurePlugin(QString pluginId);
        void movePlugin(QString spaceId, qint32 from, qint32 to);
        void mouseDoubleClickEvent(QString spaceId, QMouseEvent *event);
        void mouseMoveEvent(QString spaceId, QMouseEvent *event);
        void mousePressEvent(QString spaceId, QMouseEvent *event);
        void mouseReleaseEvent(QString spaceId, QMouseEvent *event);

    private:
        QPluginLoader pluginLoader;
        QList<Plugin *> activePlugins;
        QHash<QString, QStringList> devices;
        QHash<QString, PluginInfo> pluginsInfo;
        QHash<QString, QVariant> pluginConfigs;

        Plugin *plugin(QString pluginId);
};

#endif // PLUGINMANAGER_H
