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

#include "plugin/plugininfo.h"

/*!
  \class PluginInfo

  \brief Store plugin information.

  This class stores information provided by the plugins.
 */

/*!
  \fn PluginInfo::PluginInfo(QObject *parent): QObject(parent)

  \param parent Parent widget.
 */
PluginInfo::PluginInfo(QObject *parent): QObject(parent)
{
    this->resetFileName();
    this->resetMetaData();
}

/*!
  \fn PluginInfo::PluginInfo(const PluginInfo &object)

  \param object Another PluginInfo object.
 */
PluginInfo::PluginInfo(const PluginInfo &object):
    QObject(object.parent()),
    m_fileName(object.m_fileName),
    m_metaData(object.m_metaData)
{
}

/*!
  \fn PluginInfo::PluginInfo(QString fileName,
                             QString id,
                             QString name,
                             QString version,
                             QString summary,
                             QString category,
                             QString thumbnail,
                             QString license,
                             QString author,
                             QString website,
                             QString mail,
                             bool isConfigurable)

  \param fileName The path from were the plugin is loaded.
  \param id Unique plugin identifier.
  \param name Human readable plugin name.
  \param version Version of the plugin.
  \param summary Brief human readable description of the plugin.
  \param category The category of the plugin, i.e.: OpenGL, fire, snow, etc..
  \param thumbnail Plugin preview image.
  \param license Lisence of the plugin, i.e.: GPLv3, LGPL, BSD, etc..
  \param author The author of the plugin.
  \param website The website where the plugin is hosted.
  \param mail The mail of the plugin author.
  \param isConfigurable \b true if the plugin has a configuration dialog, \b else false.
 */
PluginInfo::PluginInfo(QString fileName,
                       QMap<QString, QVariant> pluginId):
    m_fileName(fileName),
    m_metaData(pluginId)
{
}

/*!
  \fn PluginInfo& PluginInfo::operator =(const PluginInfo &other)

  \param other Another PluginInfo object.
 */
PluginInfo& PluginInfo::operator =(const PluginInfo &other)
{
    if (this != &other)
    {
        this->m_fileName = other.m_fileName;
        this->m_metaData = other.m_metaData;
    }

    return *this;
}

QMap<QString, QVariant> PluginInfo::toMap()
{
    QMap<QString, QVariant> map(this->m_metaData);

    map["fileName"] = QVariant(this->m_fileName);

    return map;
}

/*!
  \property PluginInfo::fileName

  \brief The path from were the plugin is loaded.
 */
QString PluginInfo::fileName()
{
    return this->m_fileName;
}

/*!
  \property PluginInfo::id

  \brief The unique plugin identifier.
 */
QMap<QString, QVariant> PluginInfo::metaData()
{
    return this->m_metaData;
}

/*!
  \fn void PluginInfo::setFileName(QString value)

  \param value The plugin file name.

  \brief Set the plugin file name.
 */
void PluginInfo::setFileName(QString fileName)
{
    this->m_fileName = fileName;
}

/*!
  \fn void PluginInfo::setId(QString value)

  \param value Unique plugin identifier.

  \brief Set the unique plugin identifier.
 */
void PluginInfo::setMetaData(QMap<QString, QVariant> pluginId)
{
    this->m_metaData = pluginId;
}

/*!
  \fn void PluginInfo::resetFileName()

  \brief Reset PluginInfo::fileName to "".
 */
void PluginInfo::resetFileName()
{
    this->setFileName("");
}

/*!
  \fn void PluginInfo::resetId()

  \brief Reset PluginInfo::id to "".
 */
void PluginInfo::resetMetaData()
{
    this->setMetaData(QMap<QString, QVariant>());
}
