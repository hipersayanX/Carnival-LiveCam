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

#ifndef SHELLMANAGER_H
#define SHELLMANAGER_H

#include <QVariant>
#include <QPluginLoader>

#include "shell.h"
#include "shellinfo.h"

class ShellManager: public QObject
{
    Q_OBJECT

    public:
        explicit ShellManager(QObject *parent = 0);
        ~ShellManager();
        QList<QVariant> shellsToQml();
        QWidget *widget(QString id = "");

    private:
        QPluginLoader shellLoader;
        QString activeShellId;
        Shell *activeShell;
        QHash<QString, ShellInfo> shellsInfo;

    public slots:
        bool setShell();
        bool setShell(QString id);
        bool enableShell(QString id);
        bool disableShell(QString id);
        void configureShell(QString id);
        void setFrame(const QImage &frame);
        void updateDevices(const QList<QVariant> &devices);
        void updatePlugins(const QList<QVariant> &plugins);

    private slots:
        void onTakePicture();
        void onStartStopRecord();
        void onDeviceSelected(QString deviceId);
        void onPluginActivated(QString pluginId);
        void onPluginDeactivated(QString pluginId);
        void onPluginMoved(int from, int to);
        void onPluginConfigureClicked(QString pluginId);
        void onDeviceConfigureClicked(QString deviceId);
        void onClosed();

    signals:
        void takePicture();
        void startStopRecord();
        void deviceSelected(QString deviceId);
        void pluginActivated(QString pluginId);
        void pluginDeactivated(QString pluginId);
        void pluginMoved(int from, int to);
        void pluginConfigureClicked(QString pluginId);
        void deviceConfigureClicked(QString deviceId);
        void closed();
};

#endif // SHELLMANAGER_H
