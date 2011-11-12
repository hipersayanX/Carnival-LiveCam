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

#include "../../include/plugin/plugininfo.h"

PluginInfo::PluginInfo(QObject *parent): QObject(parent)
{
}

PluginInfo::PluginInfo(const PluginInfo &object):
    QObject(object.parent()),
    fileName(object.fileName),
    isEnabled(object.isEnabled),
    author(object.author),
    mail(object.mail),
    website(object.website),
    category(object.category),
    id(object.id),
    license(object.license),
    name(object.name),
    summary(object.summary),
    thumbnail(object.thumbnail),
    is3D(object.is3D),
    version(object.version),
    isConfigurable(object.isConfigurable)
{
}

PluginInfo::PluginInfo(QString fileName,
                       bool isEnabled,
                       QString author,
                       QString mail,
                       QString website,
                       QString category,
                       QString id,
                       QString license,
                       QString name,
                       QString summary,
                       QString thumbnail,
                       bool is3D,
                       QString version,
                       bool isConfigurable):
    fileName(fileName),
    isEnabled(isEnabled),
    author(author),
    mail(mail),
    website(website),
    category(category),
    id(id),
    license(license),
    name(name),
    summary(summary),
    thumbnail(thumbnail),
    is3D(is3D),
    version(version),
    isConfigurable(isConfigurable)
{
}

PluginInfo& PluginInfo::operator =(const PluginInfo &other)
{
    if (this != &other)
    {
        this->fileName = other.fileName;
        this->isEnabled = other.isEnabled;
        this->author = other.author;
        this->mail = other.mail;
        this->website = other.website;
        this->category = other.category;
        this->id = other.id;
        this->license = other.license;
        this->name = other.name;
        this->summary = other.summary;
        this->thumbnail = other.thumbnail;
        this->is3D = other.is3D;
        this->version = other.version;
        this->isConfigurable = other.isConfigurable;
    }

    return *this;
}
