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

#ifndef DRIVER_H
#define DRIVER_H

#include <QImage>
#include <QStringList>

class Driver: public QObject
{
    Q_OBJECT

    public:
        virtual QString id() = 0;
        virtual QString name() = 0;
        virtual QString version() = 0;
        virtual QString summary() = 0;
        virtual QString type() = 0;
        virtual QString icon() = 0;
        virtual QString license() = 0;
        virtual QString author() = 0;
        virtual QString website() = 0;
        virtual QString mail() = 0;
        virtual bool isConfigurable() = 0;

        virtual QStringList captureDevices() = 0;
        virtual QString deviceSummary(QString id) = 0;
        virtual QImage captureFrame(QString id) = 0;
        virtual QSize frameSize(QString id) = 0;

        virtual void begin() = 0;
        virtual void end() = 0;
        virtual bool disableDevice(QString id) = 0;
        virtual bool enableDevice(QString id) = 0;
        virtual bool isActive(QString id) = 0;

        virtual void configureDevice(QString id) = 0;
        virtual QVariant configs() = 0;
        virtual void setConfigs(QVariant configs) = 0;

    signals:
        void devicesModified();
};

#endif // DRIVER_H
