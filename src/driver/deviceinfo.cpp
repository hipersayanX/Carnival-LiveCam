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

#include "../../include/driver/deviceinfo.h"

DeviceInfo::DeviceInfo(QObject *parent): QObject(parent)
{
}

DeviceInfo::DeviceInfo(const DeviceInfo &object):
    QObject(object.parent()),
    id(object.id),
    driverId(object.driverId),
    isEnabled(object.isEnabled),
    summary(object.summary),
    icon(object.icon),
    isConfigurable(object.isConfigurable)
{
}

DeviceInfo::DeviceInfo(QString id,
           QString driverId,
           bool isEnabled,
           QString summary,
           QString icon,
           bool isConfigurable):
    id(id),
    driverId(driverId),
    isEnabled(isEnabled),
    summary(summary),
    icon(icon),
    isConfigurable(isConfigurable)
{
}

DeviceInfo& DeviceInfo::operator =(const DeviceInfo &other)
{
    if (this != &other)
    {
        this->id = other.id;
        this->driverId = other.driverId;
        this->isEnabled = other.isEnabled;
        this->summary = other.summary;
        this->icon = other.icon;
        this->isConfigurable = other.isConfigurable;
    }

    return *this;
}
