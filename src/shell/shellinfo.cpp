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

#include "../../include/shell/shellinfo.h"

/*!
  \class ShellInfo

  \brief Store shell information.

  This class stores information provided by the shells.
 */

/*!
  \fn ShellInfo::ShellInfo(QObject *parent): QObject(parent)

  \param parent Parent widget.
 */
ShellInfo::ShellInfo(QObject *parent): QObject(parent)
{
    this->m_fileName = "";
    this->m_isEnabled = false;
    this->m_shellId = "";
    this->m_name = "";
    this->m_version = "";
    this->m_summary = "";
    this->m_type = "";
    this->m_thumbnail = "";
    this->m_license = "";
    this->m_author = "";
    this->m_website = "";
    this->m_mail = "";
    this->m_isConfigurable = false;
}

/*!
  \fn ShellInfo::ShellInfo(const ShellInfo &object)

  \param object Another ShellInfo object.
 */
ShellInfo::ShellInfo(const ShellInfo &object):
    QObject(object.parent()),
    m_fileName(object.m_fileName),
    m_isEnabled(object.m_isEnabled),
    m_shellId(object.m_shellId),
    m_name(object.m_name),
    m_version(object.m_version),
    m_summary(object.m_summary),
    m_type(object.m_type),
    m_thumbnail(object.m_thumbnail),
    m_license(object.m_license),
    m_author(object.m_author),
    m_website(object.m_website),
    m_mail(object.m_mail),
    m_isConfigurable(object.m_isConfigurable)
{
}

/*!
  \fn ShellInfo::ShellInfo(QString fileName,
                             bool isEnabled,
                             QString id,
                             QString name,
                             QString version,
                             QString summary,
                             QString type,
                             QString thumbnail,
                             QString license,
                             QString author,
                             QString website,
                             QString mail,
                             bool isConfigurable)

  \param fileName The path from were the shell is loaded.
  \param isEnabled \b true if the shell is loaded, else \b false.
  \param id Unique shell identifier.
  \param name Human readable shell name.
  \param version Version of the shell.
  \param summary Brief human readable description of the shell.
  \param type The type of the shell, i.e.: Qml, Qt Widget, web gui, etc..
  \param thumbnail Shell preview image.
  \param license Lisence of the shell, i.e.: GPLv3, LGPL, BSD, etc..
  \param author The author of the shell.
  \param website The website where the shell is hosted.
  \param mail The mail of the shell author.
  \param isConfigurable \b true if the shell has a configuration dialog, \b else false.
 */
ShellInfo::ShellInfo(QString fileName,
                     bool isEnabled,
                     QString id,
                     QString name,
                     QString version,
                     QString summary,
                     QString type,
                     QString thumbnail,
                     QString license,
                     QString author,
                     QString website,
                     QString mail,
                     bool isConfigurable):
    m_fileName(fileName),
    m_isEnabled(isEnabled),
    m_shellId(id),
    m_name(name),
    m_version(version),
    m_summary(summary),
    m_type(type),
    m_thumbnail(thumbnail),
    m_license(license),
    m_author(author),
    m_website(website),
    m_mail(mail),
    m_isConfigurable(isConfigurable)
{
}

/*!
  \fn ShellInfo& ShellInfo::operator =(const ShellInfo &other)

  \param other Another ShellInfo object.
 */
ShellInfo& ShellInfo::operator =(const ShellInfo &other)
{
    if (this != &other)
    {
        this->m_fileName = other.m_fileName;
        this->m_isEnabled = other.m_isEnabled;
        this->m_shellId = other.m_shellId;
        this->m_name = other.m_name;
        this->m_version = other.m_version;
        this->m_summary = other.m_summary;
        this->m_type = other.m_type;
        this->m_thumbnail = other.m_thumbnail;
        this->m_license = other.m_license;
        this->m_author = other.m_author;
        this->m_website = other.m_website;
        this->m_mail = other.m_mail;
        this->m_isConfigurable = other.m_isConfigurable;
    }

    return *this;
}

/*!
  \property ShellInfo::fileName

  \brief The path from were the shell is loaded.
 */
QString ShellInfo::fileName()
{
    return this->m_fileName;
}

/*!
  \property ShellInfo::isEnabled

  \brief \b true if the shell is loaded, else \b false.
 */
bool ShellInfo::isEnabled()
{
    return this->m_isEnabled;
}

/*!
  \property ShellInfo::id

  \brief The unique shell identifier.
 */
QString ShellInfo::shellId()
{
    return this->m_shellId;
}

/*!
  \property ShellInfo::name

  \brief Human readable shell name.
 */
QString ShellInfo::name()
{
    return this->m_name;
}

/*!
  \property ShellInfo::version

  \brief Version of the shell.
 */
QString ShellInfo::version()
{
    return this->m_version;
}

/*!
  \property ShellInfo::summary

  \brief Brief human readable description of the shell.
 */
QString ShellInfo::summary()
{
    return this->m_summary;
}

/*!
  \property ShellInfo::type

  \brief The category of the shell.
 */
QString ShellInfo::type()
{
    return this->m_type;
}

/*!
  \property ShellInfo::thumbnail

  \brief The shell preview image.
 */
QString ShellInfo::thumbnail()
{
    return this->m_thumbnail;
}

/*!
  \property ShellInfo::license

  \brief Lisence of the shell.
 */
QString ShellInfo::license()
{
    return this->m_license;
}

/*!
  \property ShellInfo::author

  \brief The author of the shell.
 */
QString ShellInfo::author()
{
    return this->m_author;
}

/*!
  \property ShellInfo::website

  \brief The website where the shell is hosted.
 */
QString ShellInfo::website()
{
    return this->m_website;
}

/*!
  \property ShellInfo::mail

  \brief The mail of the shell author.
 */
QString ShellInfo::mail()
{
    return this->m_mail;
}

/*!
  \property ShellInfo::isConfigurable

  \brief \b true if the shell has a configuration dialog, \b else false.
 */
bool ShellInfo::isConfigurable()
{
    return this->m_isConfigurable;
}

/*!
  \fn void ShellInfo::setFileName(QString value)

  \param value The shell file name.

  \brief Set the shell file name.
 */
void ShellInfo::setFileName(QString value)
{
    this->m_fileName = value;
}

/*!
  \fn void ShellInfo::setIsEnabled(bool value)

  \param value \b true if the shell is activated, else \b false.

  \brief Set if the shell is activated.
 */
void ShellInfo::setIsEnabled(bool value)
{
    this->m_isEnabled = value;
}

/*!
  \fn void ShellInfo::setId(QString value)

  \param value Unique shell identifier.

  \brief Set the unique shell identifier.
 */
void ShellInfo::setShellId(QString value)
{
    this->m_shellId = value;
}

/*!
  \fn void ShellInfo::setName(QString value)

  \param value Human readable shell name.

  \brief Set the human readable shell name.
 */
void ShellInfo::setName(QString value)
{
    this->m_name = value;
}

/*!
  \fn void ShellInfo::setVersion(QString value)

  \param value Version of the shell.

  \brief Set the version of the shell.
 */
void ShellInfo::setVersion(QString value)
{
    this->m_version = value;
}

/*!
  \fn void ShellInfo::setSummary(QString value)

  \param value Shell description.

  \brief Set the description of the shell.
 */
void ShellInfo::setSummary(QString value)
{
    this->m_summary = value;
}

/*!
  \fn void ShellInfo::setType(QString value)

  \param value Shell type.

  \brief The type of the shell.
 */
void ShellInfo::setType(QString value)
{
    this->m_type = value;
}

/*!
  \fn void ShellInfo::setThumbnail(QString value)

  \param value Shell thumbnail.

  \brief Set the thumbnail of the shell.
 */
void ShellInfo::setThumbnail(QString value)
{
    this->m_thumbnail = value;
}

/*!
  \fn void ShellInfo::setLicense(QString value)

  \param value Shell license.

  \brief Set the lisence of the shell.
 */
void ShellInfo::setLicense(QString value)
{
    this->m_license = value;
}

/*!
  \fn void ShellInfo::setAuthor(QString value)

  \param value Shell author.

  \brief Set the author of the shell.
 */
void ShellInfo::setAuthor(QString value)
{
    this->m_author = value;
}

/*!
  \fn void ShellInfo::setWebsite(QString value)

  \param value The website where the shell is hosted.

  \brief Set the website of the shell.
 */
void ShellInfo::setWebsite(QString value)
{
    this->m_website = value;
}

/*!
  \fn void ShellInfo::setMail(QString value)

  \param value The mail of the shell author.

  \brief Set the mail of the shell author.
 */
void ShellInfo::setMail(QString value)
{
    this->m_mail = value;
}

/*!
  \fn void ShellInfo::setIsConfigurable(bool value)

  \param value \b true if the shell has a configuration dialog, else \b false.

  \brief Set if shell is configurable.
 */
void ShellInfo::setIsConfigurable(bool value)
{
    this->m_isConfigurable = value;
}

/*!
  \fn void ShellInfo::resetFileName()

  \brief Reset ShellInfo::fileName to "".
 */
void ShellInfo::resetFileName()
{
    this->m_fileName = "";
}

/*!
  \fn void ShellInfo::resetIsEnabled()

  \brief Reset ShellInfo::isEnabled to \b false.
 */
void ShellInfo::resetIsEnabled()
{
    this->m_isEnabled = false;
}

/*!
  \fn void ShellInfo::resetId()

  \brief Reset ShellInfo::id to "".
 */
void ShellInfo::resetShellId()
{
    this->m_shellId = "";
}

/*!
  \fn void ShellInfo::resetName()

  \brief Reset ShellInfo::name to "".
 */
void ShellInfo::resetName()
{
    this->m_name = "";
}

/*!
  \fn void ShellInfo::resetVersion()

  \brief Reset ShellInfo::version to "".
 */
void ShellInfo::resetVersion()
{
    this->m_version = "";
}

/*!
  \fn void ShellInfo::resetSummary()

  \brief Reset ShellInfo::summary to "".
 */
void ShellInfo::resetSummary()
{
    this->m_summary = "";
}

/*!
  \fn void ShellInfo::resetType()

  \brief Reset ShellInfo::type to "".
 */
void ShellInfo::resetType()
{
    this->m_type = "";
}

/*!
  \fn void ShellInfo::resetThumbnail()

  \brief Reset ShellInfo::thumbnail to "".
 */
void ShellInfo::resetThumbnail()
{
    this->m_thumbnail = "";
}

/*!
  \fn void ShellInfo::resetLicense()

  \brief Reset ShellInfo::license to "".
 */
void ShellInfo::resetLicense()
{
    this->m_license = "";
}

/*!
  \fn void ShellInfo::resetAuthor()

  \brief Reset ShellInfo::author to "".
 */
void ShellInfo::resetAuthor()
{
    this->m_author = "";
}

/*!
  \fn void ShellInfo::resetWebsite()

  \brief Reset ShellInfo::website to "".
 */
void ShellInfo::resetWebsite()
{
    this->m_website = "";
}

/*!
  \fn void ShellInfo::resetMail()

  \brief Reset ShellInfo::mail to "".
 */
void ShellInfo::resetMail()
{
    this->m_mail = "";
}

/*!
  \fn void ShellInfo::resetIsConfigurable()

  \brief Reset ShellInfo::isConfigurable to \b false.
 */
void ShellInfo::resetIsConfigurable()
{
    this->m_isConfigurable = false;
}
