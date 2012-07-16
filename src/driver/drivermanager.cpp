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

#include <QLibrary>
#include <QDir>
#include <QDebug>

#include "../../include/driver/driverfactory.h"
#include "../../include/driver/drivermanager.h"

/*!
  \class DriverManager

  \brief Low level driver manager class.

  This class is used for load, unload and query info about the drivers.
  A driver can provide and manage many devices.
 */

/*!
  \fn DriverManager::DriverManager(QObject *parent)

  \param parent Parent widget.
 */
DriverManager::DriverManager(QObject *parent): QObject(parent)
{
    QDir driverDir("share/drivers");

    foreach (QString dirext, driverDir.entryList(QDir::AllDirs | QDir::NoDot | QDir::NoDotDot, QDir::Name))
    {
        driverDir.cd(dirext);

        foreach (QString driverFile, driverDir.entryList(QDir::Files, QDir::Name))
        {
            QString fileName = driverDir.absoluteFilePath(driverFile);

            if (!QLibrary::isLibrary(fileName))
                continue;

            qDebug() << "Loading: " << fileName;

            this->m_driverLoader.setFileName(fileName);

            if (!this->m_driverLoader.load())
            {
                qDebug() << this->m_driverLoader.errorString();

                continue;
            }

            QObject *driverInstance = this->m_driverLoader.instance();

            if (!driverInstance)
                continue;

            DriverFactory *driverFactory = qobject_cast<DriverFactory *>(driverInstance);

            if (!driverFactory)
                continue;

            Driver *driver = driverFactory->driver();

            if (!driver)
                continue;

            this->m_driversInfo[driver->id()] = DriverInfo(fileName,
                                                   driver->id(),
                                                   false,
                                                   driver->name(),
                                                   driver->version(),
                                                   driver->summary(),
                                                   driver->type(),
                                                   driver->icon(),
                                                   driver->license(),
                                                   driver->author(),
                                                   driver->website(),
                                                   driver->mail(),
                                                   driver->isConfigurable());

            delete driver;
            this->m_driverLoader.unload();
        }

        driverDir.cdUp();
    }
}

/*!
  \fn QStringList DriverManager::captureDrivers()

  \return A list of unique driver identifiers.

  \brief Returns the available capture drivers.
 */
QStringList DriverManager::captureDrivers()
{
    return this->m_driversInfo.keys();
}

QStringList DriverManager::activeDrivers()
{
    return this->m_activeDrivers.keys();
}

/*!
  \fn bool DriverManager::isLoaded(QString id)

  \param id Unique driver identifier.

  \retval true The driver is loaded.
  \retval false The driver is not loaded.

  \brief Query if driver is loaded.
 */
bool DriverManager::isLoaded(QString driverId)
{
    return this->m_activeDrivers.contains(driverId);
}

/*!
  \fn Driver *DriverManager::driver(QString id)

  \param id Unique driver identifier.

  \return A pointer to the driver object.

  \brief Returns a pointer to the driver object if loaded else returns NULL.
 */
Driver *DriverManager::driver(QString driverId)
{
    return isLoaded(driverId)? this->m_activeDrivers[driverId]: NULL;
}

/*!
  \fn bool DriverManager::load(QString id)

  \param id Unique driver identifier.

  \retval true The driver was loaded.
  \retval false The driver was not loaded.

  \brief Load a driver.
 */
bool DriverManager::load(QString driverId)
{
    if (this->m_activeDrivers.contains(driverId))
        return false;

    this->m_driverLoader.setFileName(this->m_driversInfo[driverId].fileName());

    if (!this->m_driverLoader.load())
        return false;

    QObject *driverInstance = this->m_driverLoader.instance();

    if (!driverInstance)
        return false;

    DriverFactory *driverFactory = qobject_cast<DriverFactory *>(driverInstance);

    if (!driverFactory)
        return false;

    Driver *driver = driverFactory->driver();

    if (!driver)
        return false;

    this->m_driversInfo[driverId].setIsEnabled(true);
    this->m_activeDrivers[driverId] = driver;
    driver->begin();

    return true;
}

/*!
  \fn bool DriverManager::unload(QString id)

  \param id Unique driver identifier.

  \retval true The driver was unloaded.
  \retval false The driver was not unloaded.

  \brief Unload a driver.
 */
bool DriverManager::unload(QString driverId)
{
    if(!this->m_driversInfo[driverId].isEnabled())
         return false;

    this->m_activeDrivers[driverId]->end();
    delete this->m_activeDrivers[driverId];
    this->m_activeDrivers.remove(driverId);
    this->m_driverLoader.setFileName(this->m_driversInfo[driverId].fileName());
    this->m_driversInfo[driverId].setIsEnabled(false);
    this->m_driverLoader.unload();

    return true;
}
