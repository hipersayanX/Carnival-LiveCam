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

#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QObject>
#include <QImage>
#include <QHash>
#include <QList>
#include <QVariant>

#include "deviceinfo.h"
#include "drivermanager.h"

class DeviceManager: public QObject
{
    Q_OBJECT

    public:
        explicit DeviceManager(QObject *parent = 0);
        ~DeviceManager();
        Q_INVOKABLE QImage captureFrame();
        Q_INVOKABLE QSize frameSize();
        Q_INVOKABLE QList<QVariant> devicesToQml();

    public slots:
        bool setDevice();
        bool setDevice(QString id);
        bool enableDevice(QString id);
        bool disableDevice(QString id);
        void configure(QString id);

    signals:
        /*!
          \fn void DeviceManager::devicesModified()

          \brief This signal is emited when a device is added or removed.
         */
        void devicesModified();

    private:
        DriverManager driverManager;
        QString activeDevice;
        QHash<QString, DeviceInfo> devicesInfo;
        QHash<QString, QVariant> driverConfigs;

        void updateDevices();

    private slots:
        void onDevicesModified();
};

#endif // DEVICEMANAGER_H
