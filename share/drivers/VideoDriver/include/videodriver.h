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
 * Webcam driver for linux
 */

#ifndef VIDEODRIVER_H
#define VIDEODRIVER_H

#include <QHash>

#include <opencv2/opencv.hpp>

#include "driver.h"
#include "config.h"

class VideoDriver: public Driver
{
    Q_OBJECT

    public:
        QString id();
        QString name();
        QString version();
        QString summary();
        QString type();
        QString icon();
        QString license();
        QString author();
        QString website();
        QString mail();
        bool isConfigurable();

        QStringList captureDevices();
        QString deviceSummary(QString id);
        QImage captureFrame(QString id);
        QSize frameSize(QString id);

        void begin();
        void end();
        bool disableDevice(QString id);
        bool enableDevice(QString id);
        bool isActive(QString id);

        void configureDevice(QString id);
        QVariant configs();
        void setConfigs(QVariant configs);

    private:
        Config config;
        QStringList videoDevices;
        QHash<QString, cv::VideoCapture> video;
};

#endif // VIDEODRIVER_H
