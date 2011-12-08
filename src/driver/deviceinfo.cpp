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

/*!
  \class DeviceInfo

  \brief Store device information.

  This class stores device information provided by the drivers.
 */

/*!
  \fn DeviceInfo::DeviceInfo(QObject *parent)

  \param parent Parent widget.
 */
DeviceInfo::DeviceInfo(QObject *parent): QObject(parent)
{
    this->m_id = "";
    this->m_driverId = "";
    this->m_isEnabled = false;
    this->m_summary = "";
    this->m_icon = "";
    this->m_isConfigurable = false;
}

/*!
  \fn DeviceInfo::DeviceInfo(const DeviceInfo &object)

  \param object Another DeviceInfo object.
 */
DeviceInfo::DeviceInfo(const DeviceInfo &object):
    QObject(object.parent()),
    m_id(object.m_id),
    m_driverId(object.m_driverId),
    m_isEnabled(object.m_isEnabled),
    m_summary(object.m_summary),
    m_icon(object.m_icon),
    m_isConfigurable(object.m_isConfigurable)
{
}

/*!
  \fn DeviceInfo::DeviceInfo(QString id, QString driverId, bool isEnabled, QString summary, QString icon, bool isConfigurable)

  \param id Unique device identifier.
  \param driverId Unique driver identifier.
  \param isEnabled \b true if the device is enabled, else \b false.
  \param summary Human readable device description.
  \param icon Device icon.
  \param isConfigurable \b true if the device is configurable, else \b false.
 */
DeviceInfo::DeviceInfo(QString id,
                       QString driverId,
                       bool isEnabled,
                       QString summary,
                       QString icon,
                       bool isConfigurable):
    m_id(id),
    m_driverId(driverId),
    m_isEnabled(isEnabled),
    m_summary(summary),
    m_icon(icon),
    m_isConfigurable(isConfigurable)
{
}

/*!
  \fn DeviceInfo& DeviceInfo::operator =(const DeviceInfo &other)

  \param other Another DeviceInfo object.
 */
DeviceInfo& DeviceInfo::operator =(const DeviceInfo &other)
{
    if (this != &other)
    {
        this->m_id = other.m_id;
        this->m_driverId = other.m_driverId;
        this->m_isEnabled = other.m_isEnabled;
        this->m_summary = other.m_summary;
        this->m_icon = other.m_icon;
        this->m_isConfigurable = other.m_isConfigurable;
    }

    return *this;
}

/*!
  \property DeviceInfo::id

  \brief Unique device identifier.
 */
QString DeviceInfo::id()
{
    return this->m_id;
}

/*!
  \property DeviceInfo::driverId

  \brief Unique driver identifier.
 */
QString DeviceInfo::driverId()
{
    return this->m_driverId;
}

/*!
  \property DeviceInfo::isEnabled

  \brief This indicates if the device is enabled.
 */
bool DeviceInfo::isEnabled()
{
    return this->m_isEnabled;
}

/*!
  \property DeviceInfo::summary

  \brief Human readable device description.

  If for example the device is a webcam, this will return the name of that
  webcam, if the device is a image this will return the image file name, etc..
 */
QString DeviceInfo::summary()
{
    return this->m_summary;
}

/*!
  \property DeviceInfo::icon

  \brief This will return the path of an descriptive icon file for the device.
 */
QString DeviceInfo::icon()
{
    return this->m_icon;
}

/*!
  \property DeviceInfo::isConfigurable

  \brief This indicates if the device is configurable.
 */
bool DeviceInfo::isConfigurable()
{
    return this->m_isConfigurable;
}

/*!
  \fn void DeviceInfo::setId(QString value)

  \param value The unique string of the device.

  \brief Set the unique device identifier.
 */
void DeviceInfo::setId(QString value)
{
    this->m_id = value;
}

/*!
  \fn void DeviceInfo::setDriverId(QString value)

  \param value The unique string of the driver.

  \brief Set the unique driver identifier.
 */
void DeviceInfo::setDriverId(QString value)
{
    this->m_driverId = value;
}

/*!
  \fn void DeviceInfo::setIsEnabled(bool value)

  \param value \b true if the device is enabled, else \b false.

  \brief Set if the device is enabled or disabled.
 */
void DeviceInfo::setIsEnabled(bool value)
{
    this->m_isEnabled = value;
}

/*!
  \fn void DeviceInfo::setSummary(QString value)

  \param value The human readable device description.

  \brief Set the human readable device description.
 */
void DeviceInfo::setSummary(QString value)
{
    this->m_summary = value;
}

/*!
  \fn void DeviceInfo::setIcon(QString value)

  \param value The device icon.

  \brief Set the path of an descriptive icon file for the device.
 */
void DeviceInfo::setIcon(QString value)
{
    this->m_icon = value;
}

/*!
  \fn void DeviceInfo::setIsConfigurable(bool value)

  \param value \b true if the device is configurable, else \b false.

  \brief Set if the device is configurable.
 */
void DeviceInfo::setIsConfigurable(bool value)
{
    this->m_isConfigurable = value;
}

/*!
  \fn void DeviceInfo::resetId()

  \brief Reset DeviceInfo::id to "".
 */
void DeviceInfo::resetId()
{
    this->m_id = "";
}

/*!
  \fn void DeviceInfo::resetDriverId()

  \brief Reset DeviceInfo::driverId to "".
 */
void DeviceInfo::resetDriverId()
{
    this->m_driverId = "";
}

/*!
  \fn void DeviceInfo::resetIsEnabled()

  \brief Reset DeviceInfo::isEnabled to \b false.
 */
void DeviceInfo::resetIsEnabled()
{
    this->m_isEnabled = false;
}

/*!
  \fn void DeviceInfo::resetSummary()

  \brief Reset DeviceInfo::summary to "".
 */
void DeviceInfo::resetSummary()
{
    this->m_summary = "";
}

/*!
  \fn void DeviceInfo::resetIcon()

  \brief Reset DeviceInfo::icon to "".
 */
void DeviceInfo::resetIcon()
{
    this->m_icon = "";
}

/*!
  \fn void DeviceInfo::resetIsConfigurable()

  \brief Reset DeviceInfo::isConfigurable to \b false.
 */
void DeviceInfo::resetIsConfigurable()
{
    this->m_isConfigurable = false;
}
