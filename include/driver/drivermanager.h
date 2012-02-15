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

#ifndef DRIVERMANAGER_H
#define DRIVERMANAGER_H

#include <QObject>
#include <QHash>
#include <QList>
#include <QPluginLoader>

#include "driver.h"
#include "driverinfo.h"

class DriverManager: public QObject
{
    Q_OBJECT

    public:
        explicit DriverManager(QObject *parent = 0);
        Q_INVOKABLE QStringList captureDrivers();
        Q_INVOKABLE QStringList activeDrivers();
        Q_INVOKABLE bool isLoaded(QString driverId);
        Q_INVOKABLE Driver *driver(QString driverId);
        Q_INVOKABLE bool load(QString driverId);
        Q_INVOKABLE bool unload(QString driverId);

     private:
        QPluginLoader m_driverLoader;
        QHash<QString, Driver *> m_activeDrivers;
        QHash<QString, DriverInfo> m_driversInfo;
};

#endif // DRIVERMANAGER_H
