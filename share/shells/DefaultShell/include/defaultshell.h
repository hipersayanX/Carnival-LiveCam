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
 *
 * QML shell plugin
 */

#ifndef DEFAULTSHELL_H
#define DEFAULTSHELL_H

#include "shell.h"
#include "gui.h"

class DefaultShell: public Shell
{
    Q_OBJECT

    public:
        QString id();
        QString name();
        QString version();
        QString summary();
        QString type();
        QString thumbnail();
        QString license();
        QString author();
        QString website();
        QString mail();
        bool isConfigurable();

        void begin();
        void end();

        void configure();
        QVariant configs();
        void setConfigs(QVariant configs);

        QWidget *widget();

    public slots:
        void setFrame(const QImage &frame);
        void updateDevices(const QList<QVariant> &devices);
        void updatePlugins(const QList<QVariant> &plugins);

    private:
        Gui *gui;

    private slots:
        void onViewPortSizeChanged(QSize size);
        void onMouseDoubleClicked(QMouseEvent *event);
        void onMousePositionChanged(QMouseEvent *event);
        void onMousePressed(QMouseEvent *event);
        void onMouseReleased(QMouseEvent *event);
        void onToggleEditMode();
        void onTakePicture();
        void onStartStopRecord();
        void onDeviceEnable(QString deviceId);
        void onDeviceDisable(QString deviceId);
        void onPluginActivated(QString pluginId);
        void onPluginDeactivated(QString pluginId);
        void onPluginMoved(int from, int to);
        void onPluginConfigureClicked(QString pluginId);
        void onDeviceConfigureClicked(QString deviceId);
        void onClosed();
};

#endif // DEFAULTSHELL_H
