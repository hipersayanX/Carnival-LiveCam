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

    Q_PROPERTY(QStringList activeDevices READ activeDevices WRITE setActiveDevices RESET resetActiveDevices)

    public:
        explicit DeviceManager(QObject *parent = 0);
        ~DeviceManager();
        Q_INVOKABLE QImage captureFrame(QString deviceId);
        Q_INVOKABLE QSize frameSize(QString deviceId);
        Q_INVOKABLE QList<QVariant> devicesInfoList();

        QStringList activeDevices();

    public slots:
        bool deviceEnable(QString deviceId);
        bool deviceDisable(QString deviceId);
        void configure(QString deviceId);
        void setActiveDevices(QStringList value);
        void resetActiveDevices();
        void setEffect(QString deviceId, QString pluginId);
        void unsetEffect(QString deviceId, QString pluginId);

    signals:
        /*!
          \fn void DeviceManager::devicesModified()

          \brief This signal is emited when a device is added or removed.
         */
        void devicesModified();

    private:
        DriverManager driverManager;
        QStringList m_activeDevices;
        QHash<QString, DeviceInfo> devicesInfo;
        QHash<QString, QVariant> driverConfigs;

        void updateDevices();

    private slots:
        void onDevicesModified();
};

#endif // DEVICEMANAGER_H
