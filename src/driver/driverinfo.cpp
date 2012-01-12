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

/*!
  \class DriverInfo

  \brief Store driver information.

  This class stores information provided by the drivers.
 */

/*!
  \fn DriverInfo::DriverInfo(QObject *parent)

  \param parent Parent widget.
 */
DriverInfo::DriverInfo(QObject *parent): QObject(parent)
{
    this->m_fileName = "";
    this->m_driverId = "";
    this->m_isEnabled = false;
    this->m_name = "";
    this->m_version = "";
    this->m_summary = "";
    this->m_type = "";
    this->m_icon = "";
    this->m_license = "";
    this->m_author = "";
    this->m_website = "";
    this->m_mail = "";
    this->m_isConfigurable = false;
}

/*!
  \fn DriverInfo::DriverInfo(const DriverInfo &object)

  \param object Another DriverInfo object.
 */
DriverInfo::DriverInfo(const DriverInfo &object):
    QObject(object.parent()),
    m_fileName(object.m_fileName),
    m_driverId(object.m_driverId),
    m_isEnabled(object.m_isEnabled),
    m_name(object.m_name),
    m_version(object.m_version),
    m_summary(object.m_summary),
    m_type(object.m_type),
    m_icon(object.m_icon),
    m_license(object.m_license),
    m_author(object.m_author),
    m_website(object.m_website),
    m_mail(object.m_mail),
    m_isConfigurable(object.m_isConfigurable)
{
}

/*!
  \fn DriverInfo::DriverInfo(QString fileName,
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
                             bool isConfigurable)

  \param fileName The path from were the driver is loaded.
  \param id Unique driver identifier.
  \param isEnabled \b true if the driver is loaded, else \b false.
  \param name Human readable driver name.
  \param version Version of the driver.
  \param summary Brief human readable description of the driver.
  \param type The type/category of the driver, i.e.: video, image, webcam, etc..
  \param icon Driver icon.
  \param license Lisence of the driver, i.e.: GPLv3, LGPL, BSD, etc..
  \param author The author of the driver.
  \param website The website where the driver is hosted.
  \param mail The mail of the driver author.
  \param isConfigurable \b true if the driver has a configuration dialog, \b else false.
 */
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
    m_fileName(fileName),
    m_driverId(id),
    m_isEnabled(isEnabled),
    m_name(name),
    m_version(version),
    m_summary(summary),
    m_type(type),
    m_icon(icon),
    m_license(license),
    m_author(author),
    m_website(website),
    m_mail(mail),
    m_isConfigurable(isConfigurable)
{
}

/*!
  \fn DriverInfo& DriverInfo::operator =(const DriverInfo &other)

  \param other Another DriverInfo object.
 */
DriverInfo& DriverInfo::operator =(const DriverInfo &other)
{
    if (this != &other)
    {
        this->m_fileName = other.m_fileName;
        this->m_driverId = other.m_driverId;
        this->m_isEnabled = other.m_isEnabled;
        this->m_name = other.m_name;
        this->m_version = other.m_version;
        this->m_summary = other.m_summary;
        this->m_type = other.m_type;
        this->m_icon = other.m_icon;
        this->m_license = other.m_license;
        this->m_author = other.m_author;
        this->m_website = other.m_website;
        this->m_mail = other.m_mail;
        this->m_isConfigurable = other.m_isConfigurable;
    }

    return *this;
}

/*!
  \property DriverInfo::fileName

  \brief The path from were the driver is loaded.
 */
QString DriverInfo::fileName()
{
    return this->m_fileName;
}

/*!
  \property DriverInfo::id

  \brief The unique driver identifier.
 */
QString DriverInfo::driverId()
{
    return this->m_driverId;
}

/*!
  \property DriverInfo::isEnabled

  \brief \b true if the driver is loaded, else \b false.
 */
bool DriverInfo::isEnabled()
{
    return this->m_isEnabled;
}

/*!
  \property DriverInfo::name

  \brief Human readable driver name.
 */
QString DriverInfo::name()
{
    return this->m_name;
}

/*!
  \property DriverInfo::version

  \brief Version of the driver.
 */
QString DriverInfo::version()
{
    return this->m_version;
}

/*!
  \property DriverInfo::summary

  \brief Brief human readable description of the driver.
 */
QString DriverInfo::summary()
{
    return this->m_summary;
}

/*!
  \property DriverInfo::type

  \brief The type/category of the driver.
 */
QString DriverInfo::type()
{
    return this->m_type;
}

/*!
  \property DriverInfo::icon

  \brief Driver icon.
 */
QString DriverInfo::icon()
{
    return this->m_icon;
}

/*!
  \property DriverInfo::license

  \brief Lisence of the driver.
 */
QString DriverInfo::license()
{
    return this->m_license;
}

/*!
  \property DriverInfo::author

  \brief The author of the driver.
 */
QString DriverInfo::author()
{
    return this->m_author;
}

/*!
  \property DriverInfo::website

  \brief The website where the driver is hosted.
 */
QString DriverInfo::website()
{
    return this->m_website;
}

/*!
  \property DriverInfo::mail

  \brief The mail of the driver author.
 */
QString DriverInfo::mail()
{
    return this->m_mail;
}

/*!
  \property DriverInfo::isConfigurable

  \brief \b true if the driver has a configuration dialog, \b else false.
 */
bool DriverInfo::isConfigurable()
{
    return this->m_isConfigurable;
}

/*!
  \fn void DriverInfo::setFileName(QString value)

  \param value The driver file name.

  \brief Set the driver file name.
 */
void DriverInfo::setFileName(QString value)
{
    this->m_fileName = value;
}

/*!
  \fn void DriverInfo::setId(QString value)

  \param value Unique driver identifier.

  \brief Set the unique driver identifier.
 */
void DriverInfo::setDriverId(QString value)
{
    this->m_driverId = value;
}

/*!
  \fn void DriverInfo::setIsEnabled(bool value)

  \param value \b true if the driver is activated, else \b false.

  \brief Set if the driver is activated.
 */
void DriverInfo::setIsEnabled(bool value)
{
    this->m_isEnabled = value;
}

/*!
  \fn void DriverInfo::setName(QString value)

  \param value Human readable driver name.

  \brief Set the human readable driver name.
 */
void DriverInfo::setName(QString value)
{
    this->m_name = value;
}

/*!
  \fn void DriverInfo::setVersion(QString value)

  \param value Version of the driver.

  \brief Set the version of the driver.
 */
void DriverInfo::setVersion(QString value)
{
    this->m_version = value;
}

/*!
  \fn void DriverInfo::setSummary(QString value)

  \param value Driver description.

  \brief Set the description of the driver.
 */
void DriverInfo::setSummary(QString value)
{
    this->m_summary = value;
}

/*!
  \fn void DriverInfo::setType(QString value)

  \param value Driver type.

  \brief The type/category of the driver.
 */
void DriverInfo::setType(QString value)
{
    this->m_type = value;
}

/*!
  \fn void DriverInfo::setIcon(QString value)

  \param value Driver icon.

  \brief Set the icon of the driver.
 */
void DriverInfo::setIcon(QString value)
{
    this->m_icon = value;
}

/*!
  \fn void DriverInfo::setLicense(QString value)

  \param value Driver lisence.

  \brief Set the lisence of the driver.
 */
void DriverInfo::setLicense(QString value)
{
    this->m_license = value;
}

/*!
  \fn void DriverInfo::setAuthor(QString value)

  \param value Driver author.

  \brief Set the author of the driver.
 */
void DriverInfo::setAuthor(QString value)
{
    this->m_author = value;
}

/*!
  \fn void DriverInfo::setWebsite(QString value)

  \param value The website where the driver is hosted.

  \brief Set the website of the driver.
 */
void DriverInfo::setWebsite(QString value)
{
    this->m_website = value;
}

/*!
  \fn void DriverInfo::setMail(QString value)

  \param value The mail of the driver author.

  \brief Set the mail of the driver author.
 */
void DriverInfo::setMail(QString value)
{
    this->m_mail = value;
}

/*!
  \fn void DriverInfo::setIsConfigurable(bool value)

  \param value \b true if the driver has a configuration dialog, else \b false.

  \brief Set if driver is configurable.
 */
void DriverInfo::setIsConfigurable(bool value)
{
    this->m_isConfigurable = value;
}

/*!
  \fn void DriverInfo::resetFileName()

  \brief Reset DriverInfo::fileName to "".
 */
void DriverInfo::resetFileName()
{
    this->m_fileName = "";
}

/*!
  \fn void DriverInfo::resetId()

  \brief Reset DriverInfo::resetId to "".
 */
void DriverInfo::resetDriverId()
{
    this->m_driverId = "";
}

/*!
  \fn void DriverInfo::resetIsEnabled()

  \brief Reset DriverInfo::isEnabled to \b false.
 */
void DriverInfo::resetIsEnabled()
{
    this->m_isEnabled = false;
}

/*!
  \fn void DriverInfo::resetName()

  \brief Reset DriverInfo::name to "".
 */
void DriverInfo::resetName()
{
    this->m_name = "";
}

/*!
  \fn void DriverInfo::resetVersion()

  \brief Reset DriverInfo::version to "".
 */
void DriverInfo::resetVersion()
{
    this->m_version = "";
}

/*!
  \fn void DriverInfo::resetSummary()

  \brief Reset DriverInfo::summary to "".
 */
void DriverInfo::resetSummary()
{
    this->m_summary = "";
}

/*!
  \fn void DriverInfo::resetType()

  \brief Reset DriverInfo::type to "".
 */
void DriverInfo::resetType()
{
    this->m_type = "";
}

/*!
  \fn void DriverInfo::resetIcon()

  \brief Reset DriverInfo::icon to "".
 */
void DriverInfo::resetIcon()
{
    this->m_icon = "";
}

/*!
  \fn void DriverInfo::resetLicense()

  \brief Reset DriverInfo::license to "".
 */
void DriverInfo::resetLicense()
{
    this->m_license = "";
}

/*!
  \fn void DriverInfo::resetAuthor()

  \brief Reset DriverInfo::author to "".
 */
void DriverInfo::resetAuthor()
{
    this->m_author = "";
}

/*!
  \fn void DriverInfo::resetWebsite()

  \brief Reset DriverInfo::website to "".
 */
void DriverInfo::resetWebsite()
{
    this->m_website = "";
}

/*!
  \fn void DriverInfo::resetMail()

  \brief Reset DriverInfo::mail to "".
 */
void DriverInfo::resetMail()
{
    this->m_mail = "";
}

/*!
  \fn void DriverInfo::resetIsConfigurable()

  \brief Reset DriverInfo::isConfigurable to \b false.
 */
void DriverInfo::resetIsConfigurable()
{
    this->m_isConfigurable = false;
}
