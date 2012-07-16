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

#ifndef CORE_H
#define CORE_H

#include <QObject>

#include "../driver/devicemanager.h"
#include "../shell/shellmanager.h"
#include "../plugin/pluginmanager.h"
#include "../space/spacemanager.h"
#include "../streaming/mediastreaming.h"

class Core: public QObject
{
    Q_OBJECT

    public:
        explicit Core(QObject *parent = 0);

    private:
        DeviceManager deviceManager;
        ShellManager shellManager;
        PluginManager pluginManager;
        MediaStreaming mediaStreaming;
        SpaceManager spaceManager;
        QPushButton toggleMaximizedButton;
        QPushButton scaleAndRotateButton;

    private slots:
        void setEffect(QString pluginId, QString spaceId);
        void unsetEffect(QString pluginId, QString spaceId);
        void devicesModified();
        void deviceEnable(QString deviceId);
        void deviceDisable(QString deviceId);
        void captureFrame();
};

#endif // CORE_H
