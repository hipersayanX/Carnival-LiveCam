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

/*!
  \class DeviceManager

  \brief High level device manager class.

  This class works on top of DriverManager, managin the devices provided by the
  drivers. The devices are any kind of source from were is possible to obtain a
  image frame.
  DeviceManager allow capture from one or many devices at same time.
 */

/*!
  \fn DeviceManager::DeviceManager(QObject *parent)

  \param parent Parent widget.
 */
DeviceManager::DeviceManager(QObject *parent): QObject(parent)
{
    updateDevices();
}

/*!
  \fn DeviceManager::~DeviceManager()
 */
DeviceManager::~DeviceManager()
{
    foreach (QString deviceId, this->m_activeDevices)
        this->deviceDisable(deviceId);
}

/*!
  \fn QImage DeviceManager::captureFrame()

  \return The captured frame.

  \brief Capture a frame from active device.
 */
QImage DeviceManager::captureFrame(QString deviceId)
{
    if (this->devicesInfo.contains(deviceId))
    {
        // Get a reference to the current loaded driver.
        Driver *driver = this->driverManager.driver(this->devicesInfo[deviceId].driverId());

        if (driver)
            // Capture a frame from the current device.
            return driver->captureFrame(deviceId);
    }

    // Else return a 1x1 black image.
    QImage frame(1, 1, QImage::Format_RGB888);

    frame.fill(0);

    return frame;
}

/*!
  \fn QSize DeviceManager::frameSize()

  \return The size of the captured frame.

  \brief Returns the size of the captured frame from active device.
 */
QSize DeviceManager::frameSize(QString deviceId)
{
    if (this->devicesInfo.contains(deviceId))
    {
        Driver *driver = this->driverManager.driver(this->devicesInfo[deviceId].driverId());

        if (!driver)
            return QSize(1, 1);

        return driver->frameSize(deviceId);
    }
    else
        return QSize(1, 1);
}

/*!
  \fn QList<QVariant> DeviceManager::devicesToQml()

  \return The list of devices information in standard format.

  \brief Returns the list of devices information in standard format.
 */
QList<QVariant> DeviceManager::devicesInfoList()
{
    QList<QVariant> deviceList;

    foreach (DeviceInfo device, this->devicesInfo)
    {
        QMap<QString, QVariant> deviceInfoMap;

        deviceInfoMap["deviceId"] = QVariant(device.deviceId());
        deviceInfoMap["driverId"] = QVariant(device.driverId());
        deviceInfoMap["isEnabled"] = QVariant(device.isEnabled());
        deviceInfoMap["summary"] = QVariant(device.summary());
        deviceInfoMap["icon"] = QVariant(device.icon());
        deviceInfoMap["isConfigurable"] = QVariant(device.isConfigurable());
        deviceInfoMap["effects"] = QVariant(device.effects());

        deviceList << deviceInfoMap;
    }

    return deviceList;
}

/*!
  \fn void DeviceManager::configure(QString id)

  \param id Unique device identifier.

  \brief Calls the configuration dialog for the device id.
         the device must be active.
 */
void DeviceManager::configure(QString deviceId)
{
    if (!this->devicesInfo.contains(deviceId))
        return;

    Driver *driver = this->driverManager.driver(this->devicesInfo[deviceId].driverId());
    driver->configureDevice(deviceId);
}

/*!
  \internal

  \fn void DeviceManager::updateDevices()

  \brief Update the devices list.
 */
void DeviceManager::updateDevices()
{
    QHash<QString, bool> devicesPreStatus;

    foreach(DeviceInfo device, this->devicesInfo)
        devicesPreStatus[device.deviceId()] = this->devicesInfo[device.deviceId()].isEnabled();

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
                                                   driver->isConfigurable(),
                                                   QStringList());

        this->driverManager.unload(driverId);
    }
}

/*!
  \internal

  \fn void DeviceManager::onDevicesModified()

  \brief This slot is called when device is added os removed.
 */
void DeviceManager::onDevicesModified()
{
    QStringList activeDevices = this->m_activeDevices;

    foreach (QString deviceId, this->m_activeDevices)
        this->deviceDisable(deviceId);

    this->updateDevices();

    foreach (QString deviceId, activeDevices)
        this->deviceEnable(deviceId);

    emit devicesModified();
}

/*!
  \fn bool DeviceManager::enableDevice(QString id)

  \param id Unique device identifier.

  \retval true if the device is active.
  \retval false if the device is inactive.

  \brief Try to activate the device id.
 */
bool DeviceManager::deviceEnable(QString deviceId)
{
    if (!this->devicesInfo.contains(deviceId))
        return false;

    QString driverId = this->devicesInfo[deviceId].driverId();
    bool firstDevice = !this->driverManager.isLoaded(driverId);

    this->driverManager.load(driverId);
    Driver *driver = this->driverManager.driver(driverId);

    if (firstDevice)
    {
        if (this->driverConfigs.contains(driverId))
            driver->setConfigs(this->driverConfigs[driverId]);

        driver->begin();
    }

    driver->enableDevice(deviceId);

    if (firstDevice)
        connect(driver, SIGNAL(devicesModified()), this, SLOT(onDevicesModified()));

    this->m_activeDevices << deviceId;
    this->devicesInfo[deviceId].setIsEnabled(true);

    return true;
}

/*!
  \fn bool DeviceManager::disableDevice(QString id)

  \param id Unique device identifier.

  \retval true if the device is inactive.
  \retval false if the device is active.

  \brief Try to desactivate the device id.
 */
bool DeviceManager::deviceDisable(QString deviceId)
{
    if (!this->devicesInfo.contains(deviceId))
        return false;

    QString driverId = this->devicesInfo[deviceId].driverId();

    if(!this->driverManager.isLoaded(driverId))
        return false;

    bool lastDevice = this->driverManager.activeDrivers().count() == 1;

    Driver *driver = this->driverManager.driver(driverId);

    if (!driver)
        return false;

    if (lastDevice)
    {
        this->driverConfigs[driverId] = driver->configs();
        disconnect(driver, SIGNAL(devicesModified()), this, SLOT(onDevicesModified()));
    }

    driver->disableDevice(deviceId);

    if (lastDevice)
    {
        driver->end();
        this->driverManager.unload(driverId);
    }

    this->m_activeDevices.removeOne(deviceId);
    this->devicesInfo[deviceId].setIsEnabled(false);

    return true;
}

QStringList DeviceManager::activeDevices()
{
    return this->m_activeDevices;
}

void DeviceManager::setActiveDevices(QStringList value)
{
    this->m_activeDevices = value;
}

void DeviceManager::resetActiveDevices()
{
    this->m_activeDevices.clear();
}

void DeviceManager::setEffect(QString deviceId, QString pluginId)
{
    if (!this->devicesInfo.contains(deviceId))
        return;

    QStringList effects = this->devicesInfo[deviceId].effects();

    if (effects.contains(pluginId))
        return;

    effects << pluginId;
    this->devicesInfo[deviceId].setEffects(effects);
}

void DeviceManager::unsetEffect(QString deviceId, QString pluginId)
{
    if (!this->devicesInfo.contains(deviceId))
        return;

    QStringList effects = this->devicesInfo[deviceId].effects();

    if (!effects.contains(pluginId))
        return;

    effects.removeOne(pluginId);
    this->devicesInfo[deviceId].setEffects(effects);
}
