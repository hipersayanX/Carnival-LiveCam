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

#include <QLibrary>
#include <QDir>
#include <QDebug>

#include "../../include/driver/driverfactory.h"
#include "../../include/driver/drivermanager.h"

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

            this->driverLoader.setFileName(fileName);

            if (!this->driverLoader.load())
            {
                qDebug() << this->driverLoader.errorString();

                continue;
            }

            QObject *driverInstance = this->driverLoader.instance();

            if (!driverInstance)
                continue;

            DriverFactory *driverFactory = qobject_cast<DriverFactory *>(driverInstance);

            if (!driverFactory)
                continue;

            Driver *driver = driverFactory->driver();

            if (!driver)
                continue;

            this->driversInfo[driver->id()] = DriverInfo(fileName,
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
            this->driverLoader.unload();
        }

        driverDir.cdUp();
    }
}

QStringList DriverManager::captureDrivers()
{
    return this->driversInfo.keys();
}

bool DriverManager::isLoaded(QString id)
{
    return this->activeDrivers.contains(id);
}

Driver *DriverManager::driver(QString id)
{
    return isLoaded(id)? this->activeDrivers[id]: NULL;
}

bool DriverManager::load(QString id)
{
    if (this->activeDrivers.contains(id))
        return false;

    this->driverLoader.setFileName(this->driversInfo[id].fileName);

    if (!this->driverLoader.load())
        return false;

    QObject *driverInstance = this->driverLoader.instance();

    if (!driverInstance)
        return false;

    DriverFactory *driverFactory = qobject_cast<DriverFactory *>(driverInstance);

    if (!driverFactory)
        return false;

    Driver *driver = driverFactory->driver();

    if (!driver)
        return false;

    this->driversInfo[id].isEnabled = true;
    this->activeDrivers[id] = driver;
    driver->begin();

    return true;
}

bool DriverManager::unload(QString id)
{
    if(!this->driversInfo[id].isEnabled)
         return false;

    this->activeDrivers[id]->end();
    delete this->activeDrivers[id];
    this->activeDrivers.remove(id);
    this->driverLoader.setFileName(this->driversInfo[id].fileName);
    this->driversInfo[id].isEnabled = false;
    this->driverLoader.unload();

    return true;
}
