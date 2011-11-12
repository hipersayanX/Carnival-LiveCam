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

#include <QDebug>

#include "../../include/driver/devicemanager.h"

DeviceManager::DeviceManager(QObject *parent): QObject(parent)
{
    updateDevices();
}

DeviceManager::~DeviceManager()
{
    if (this->activeDevice != "")
        this->disableDevice(this->activeDevice);
}

QImage DeviceManager::captureFrame()
{
    if (this->activeDevice != "")
    {
        Driver *driver = this->driverManager.driver(this->devicesInfo[this->activeDevice].driverId);

        if (driver)
            return driver->captureFrame(this->activeDevice);
    }

    QImage frame(1, 1, QImage::Format_RGB888);

    frame.fill(0);

    return frame;
}

QSize DeviceManager::frameSize()
{
    if (this->activeDevice != "")
    {
        Driver *driver = this->driverManager.driver(this->devicesInfo[this->activeDevice].driverId);

        if (!driver)
            return QSize(1, 1);

        return driver->frameSize(this->activeDevice);
    }
    else
        return QSize(1, 1);
}

QList<QVariant> DeviceManager::devicesToQml()
{
    QList<QVariant> deviceList;

    foreach (DeviceInfo device, this->devicesInfo)
    {
        QMap<QString, QVariant> deviceInfoMap;

        deviceInfoMap["deviceId"] = QVariant(device.id);
        deviceInfoMap["driverId"] = QVariant(device.driverId);
        deviceInfoMap["isEnabled"] = QVariant(device.isEnabled);
        deviceInfoMap["summary"] = QVariant(device.summary);
        deviceInfoMap["icon"] = QVariant(device.icon);
        deviceInfoMap["isConfigurable"] = QVariant(device.isConfigurable);

        deviceList << deviceInfoMap;
    }

    return deviceList;
}

bool DeviceManager::setDevice()
{
    return this->setDevice("/dev/video0");
}

bool DeviceManager::setDevice(QString id)
{
    if (this->activeDevice == "")
        this->enableDevice(id);
    else
        if (this->devicesInfo[this->activeDevice].driverId != this->devicesInfo[id].driverId)
        {
            this->disableDevice(this->activeDevice);
            this->enableDevice(id);
        }
        else
        {
            Driver *driver = this->driverManager.driver(this->devicesInfo[id].driverId);

            if (driver)
            {
                driver->disableDevice(this->activeDevice);
                driver->enableDevice(id);
            }
        }

    this->activeDevice = id;

    return true;
}

void DeviceManager::configure(QString id)
{
    if (this->activeDevice != id)
        return;

    Driver *driver = this->driverManager.driver(this->devicesInfo[id].driverId);
    driver->configureDevice(id);
}

void DeviceManager::updateDevices()
{
    QHash<QString, bool> devicesPreStatus;

    foreach(DeviceInfo device, this->devicesInfo)
        devicesPreStatus[device.id] = this->devicesInfo[device.id].isEnabled;

    this->devicesInfo.clear();

    foreach(QString driverId, this->driverManager.captureDrivers())
    {
        this->driverManager.load(driverId);
        Driver *driver = this->driverManager.driver(driverId);

        if (this->driverConfigs.contains(driverId))
            driver->setConfigs(this->driverConfigs[driverId]);

        foreach(QString device, driver->captureDevices())
            this->devicesInfo[device] = DeviceInfo(device,
                                                   driverId,
                                                   devicesPreStatus.contains(device)? devicesPreStatus[device]: false,
                                                   driver->deviceSummary(device),
                                                   driver->icon(),
                                                   driver->isConfigurable());

        this->driverManager.unload(driverId);
    }
}

void DeviceManager::onDevicesModified()
{
    this->disableDevice(this->activeDevice);
    this->updateDevices();

    if (this->devicesInfo.contains(this->activeDevice))
        this->enableDevice(this->activeDevice);
    else
    {
        this->activeDevice = "";
        this->setDevice();
    }

    emit devicesModified();
}

bool DeviceManager::enableDevice(QString id)
{
    if (!this->devicesInfo.contains(id))
        return false;

    this->driverManager.load(this->devicesInfo[id].driverId);
    Driver *driver = this->driverManager.driver(this->devicesInfo[id].driverId);

    if (this->driverConfigs.contains(this->devicesInfo[id].driverId))
        driver->setConfigs(this->driverConfigs[this->devicesInfo[id].driverId]);

    driver->begin();
    driver->enableDevice(id);
    connect(driver, SIGNAL(devicesModified()), this, SLOT(onDevicesModified()));

    return true;
}

bool DeviceManager::disableDevice(QString id)
{
    if (!this->devicesInfo.contains(id))
        return false;

    Driver *driver = this->driverManager.driver(this->devicesInfo[id].driverId);

    if (!driver)
        return false;

    this->driverConfigs[this->devicesInfo[id].driverId] = driver->configs();
    disconnect(driver, SIGNAL(devicesModified()), this, SLOT(onDevicesModified()));
    driver->disableDevice(id);
    driver->end();
    this->driverManager.unload(this->devicesInfo[id].driverId);

    return true;
}
