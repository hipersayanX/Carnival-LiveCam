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

#include "../../include/driver/driverinfo.h"

DriverInfo::DriverInfo(QObject *parent): QObject(parent)
{
}

DriverInfo::DriverInfo(const DriverInfo &object):
    QObject(object.parent()),
    fileName(object.fileName),
    id(object.id),
    isEnabled(object.isEnabled),
    name(object.name),
    version(object.version),
    summary(object.summary),
    type(object.type),
    icon(object.icon),
    license(object.license),
    author(object.author),
    website(object.website),
    mail(object.mail),
    isConfigurable(object.isConfigurable)
{
}

DriverInfo::DriverInfo(QString fileName,
           QString id,
           bool isEnabled,
           QString name,
           QString version,
           QString summary,
           QString type,
           QString icon,
           QString license,
           QString author,
           QString website,
           QString mail,
           bool isConfigurable):
    fileName(fileName),
    id(id),
    isEnabled(isEnabled),
    name(name),
    version(version),
    summary(summary),
    type(type),
    icon(icon),
    license(license),
    author(author),
    website(website),
    mail(mail),
    isConfigurable(isConfigurable)
{
}

DriverInfo& DriverInfo::operator =(const DriverInfo &other)
{
    if (this != &other)
    {
        this->fileName = other.fileName;
        this->id = other.id;
        this->isEnabled = other.isEnabled;
        this->name = other.name;
        this->version = other.version;
        this->summary = other.summary;
        this->type = other.type;
        this->icon = other.icon;
        this->license = other.license;
        this->author = other.author;
        this->website = other.website;
        this->mail = other.mail;
        this->isConfigurable = other.isConfigurable;
    }

    return *this;
}
