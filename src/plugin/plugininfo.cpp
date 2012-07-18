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

#include "../../include/plugin/plugininfo.h"

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
    this->m_fileName = "";
    this->m_pluginId = "";
    this->m_name = "";
    this->m_version = "";
    this->m_summary = "";
    this->m_type = Plugin::PluginUnknown;
    this->m_category = "";
    this->m_thumbnail = "";
    this->m_license = "";
    this->m_author = "";
    this->m_website = "";
    this->m_mail = "";
    this->m_isConfigurable = false;
    this->m_configs = QVariant();
    this->m_applyTo = QStringList();
}

/*!
  \fn PluginInfo::PluginInfo(const PluginInfo &object)

  \param object Another PluginInfo object.
 */
PluginInfo::PluginInfo(const PluginInfo &object):
    QObject(object.parent()),
    m_fileName(object.m_fileName),
    m_pluginId(object.m_pluginId),
    m_name(object.m_name),
    m_version(object.m_version),
    m_summary(object.m_summary),
    m_type(object.m_type),
    m_category(object.m_category),
    m_thumbnail(object.m_thumbnail),
    m_license(object.m_license),
    m_author(object.m_author),
    m_website(object.m_website),
    m_mail(object.m_mail),
    m_isConfigurable(object.m_isConfigurable),
    m_configs(object.m_configs),
    m_applyTo(object.m_applyTo)
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
                       QString id,
                       QString name,
                       QString version,
                       QString summary,
                       Plugin::PluginType type,
                       QString category,
                       QString thumbnail,
                       QString license,
                       QString author,
                       QString website,
                       QString mail,
                       bool isConfigurable,
                       QVariant configs,
                       QStringList applyTo):
    m_fileName(fileName),
    m_pluginId(id),
    m_name(name),
    m_version(version),
    m_summary(summary),
    m_type(type),
    m_category(category),
    m_thumbnail(thumbnail),
    m_license(license),
    m_author(author),
    m_website(website),
    m_mail(mail),
    m_isConfigurable(isConfigurable),
    m_configs(configs),
    m_applyTo(applyTo)
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
        this->m_pluginId = other.m_pluginId;
        this->m_name = other.m_name;
        this->m_version = other.m_version;
        this->m_summary = other.m_summary;
        this->m_type = other.m_type;
        this->m_category = other.m_category;
        this->m_thumbnail = other.m_thumbnail;
        this->m_license = other.m_license;
        this->m_author = other.m_author;
        this->m_website = other.m_website;
        this->m_mail = other.m_mail;
        this->m_isConfigurable = other.m_isConfigurable;
        this->m_configs = other.m_configs;
        this->m_applyTo = other.m_applyTo;
    }

    return *this;
}

QMap<QString, QVariant> PluginInfo::toMap()
{
    QMap<QString, QVariant> map;

    map["fileName"] = QVariant(this->m_fileName);
    map["pluginId"] = QVariant(this->m_pluginId);
    map["name"] = QVariant(this->m_name);
    map["version"] = QVariant(this->m_version);
    map["summary"] = QVariant(this->m_summary);
    map["type"] = QVariant(this->m_type);
    map["category"] = QVariant(this->m_category);
    map["thumbnail"] = QVariant(this->m_thumbnail);
    map["license"] = QVariant(this->m_license);
    map["author"] = QVariant(this->m_author);
    map["website"] = QVariant(this->m_website);
    map["mail"] = QVariant(this->m_mail);
    map["isConfigurable"] = QVariant(this->m_isConfigurable);
    map["configs"] = QVariant(this->m_configs);
    map["applyTo"] = QVariant(this->m_applyTo);

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
QString PluginInfo::pluginId()
{
    return this->m_pluginId;
}

/*!
  \property PluginInfo::name

  \brief Human readable plugin name.
 */
QString PluginInfo::name()
{
    return this->m_name;
}

/*!
  \property PluginInfo::version

  \brief Version of the plugin.
 */
QString PluginInfo::version()
{
    return this->m_version;
}

/*!
  \property PluginInfo::summary

  \brief Brief human readable description of the plugin.
 */
QString PluginInfo::summary()
{
    return this->m_summary;
}

Plugin::PluginType PluginInfo::type()
{
    return this->m_type;
}

/*!
  \property PluginInfo::category

  \brief The category of the plugin.
 */
QString PluginInfo::category()
{
    return this->m_category;
}

/*!
  \property PluginInfo::thumbnail

  \brief The plugin preview image.
 */
QString PluginInfo::thumbnail()
{
    return this->m_thumbnail;
}

/*!
  \property PluginInfo::license

  \brief Lisence of the plugin.
 */
QString PluginInfo::license()
{
    return this->m_license;
}

/*!
  \property PluginInfo::author

  \brief The author of the plugin.
 */
QString PluginInfo::author()
{
    return this->m_author;
}

/*!
  \property PluginInfo::website

  \brief The website where the plugin is hosted.
 */
QString PluginInfo::website()
{
    return this->m_website;
}

/*!
  \property PluginInfo::mail

  \brief The mail of the plugin author.
 */
QString PluginInfo::mail()
{
    return this->m_mail;
}

/*!
  \property PluginInfo::isConfigurable

  \brief \b true if the plugin has a configuration dialog, \b else false.
 */
bool PluginInfo::isConfigurable()
{
    return this->m_isConfigurable;
}

QVariant PluginInfo::configs()
{
    return this->m_configs;
}

QStringList PluginInfo::applyTo()
{
    return this->m_applyTo;
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
void PluginInfo::setPluginId(QString pluginId)
{
    this->m_pluginId = pluginId;
}

/*!
  \fn void PluginInfo::setName(QString value)

  \param value Human readable plugin name.

  \brief Set the human readable plugin name.
 */
void PluginInfo::setName(QString name)
{
    this->m_name = name;
}

/*!
  \fn void PluginInfo::setVersion(QString value)

  \param value Version of the plugin.

  \brief Set the version of the plugin.
 */
void PluginInfo::setVersion(QString version)
{
    this->m_version = version;
}

/*!
  \fn void PluginInfo::setSummary(QString value)

  \param value Plugin description.

  \brief Set the description of the plugin.
 */
void PluginInfo::setSummary(QString summary)
{
    this->m_summary = summary;
}

void PluginInfo::setType(Plugin::PluginType type)
{
    this->m_type = type;
}

/*!
  \fn void PluginInfo::setCategory(QString value)

  \param value Plugin category.

  \brief The category of the plugin.
 */
void PluginInfo::setCategory(QString category)
{
    this->m_category = category;
}

/*!
  \fn void PluginInfo::setThumbnail(QString value)

  \param value Plugin thumbnail.

  \brief Set the thumbnail of the plugin.
 */
void PluginInfo::setThumbnail(QString thumbnail)
{
    this->m_thumbnail = thumbnail;
}

/*!
  \fn void PluginInfo::setLicense(QString value)

  \param value Plugin license.

  \brief Set the lisence of the plugin.
 */
void PluginInfo::setLicense(QString license)
{
    this->m_license = license;
}

/*!
  \fn void PluginInfo::setAuthor(QString value)

  \param value Plugin author.

  \brief Set the author of the plugin.
 */
void PluginInfo::setAuthor(QString author)
{
    this->m_author = author;
}

/*!
  \fn void PluginInfo::setWebsite(QString value)

  \param value The website where the plugin is hosted.

  \brief Set the website of the plugin.
 */
void PluginInfo::setWebsite(QString website)
{
    this->m_website = website;
}

/*!
  \fn void PluginInfo::setMail(QString value)

  \param value The mail of the plugin author.

  \brief Set the mail of the plugin author.
 */
void PluginInfo::setMail(QString mail)
{
    this->m_mail = mail;
}

/*!
  \fn void PluginInfo::setIsConfigurable(bool value)

  \param value \b true if the plugin has a configuration dialog, else \b false.

  \brief Set if plugin is configurable.
 */
void PluginInfo::setIsConfigurable(bool isConfigurable)
{
    this->m_isConfigurable = isConfigurable;
}

void PluginInfo::setConfigs(const QVariant &configs)
{
    this->m_configs = configs;
}

void PluginInfo::setApplyTo(QStringList applyTo)
{
    this->m_applyTo = applyTo;
}

/*!
  \fn void PluginInfo::resetFileName()

  \brief Reset PluginInfo::fileName to "".
 */
void PluginInfo::resetFileName()
{
    this->m_fileName = "";
}

/*!
  \fn void PluginInfo::resetId()

  \brief Reset PluginInfo::id to "".
 */
void PluginInfo::resetPluginId()
{
    this->m_pluginId = "";
}

/*!
  \fn void PluginInfo::resetName()

  \brief Reset PluginInfo::name to "".
 */
void PluginInfo::resetName()
{
    this->m_name = "";
}

/*!
  \fn void PluginInfo::resetVersion()

  \brief Reset PluginInfo::version to "".
 */
void PluginInfo::resetVersion()
{
    this->m_version = "";
}

/*!
  \fn void PluginInfo::resetSummary()

  \brief Reset PluginInfo::summary to "".
 */
void PluginInfo::resetSummary()
{
    this->m_summary = "";
}

void PluginInfo::resetType()
{
    this->m_type = Plugin::PluginUnknown;
}

/*!
  \fn void PluginInfo::resetCategory()

  \brief Reset PluginInfo::category to "".
 */
void PluginInfo::resetCategory()
{
    this->m_category = "";
}

/*!
  \fn void PluginInfo::resetThumbnail()

  \brief Reset PluginInfo::thumbnail to "".
 */
void PluginInfo::resetThumbnail()
{
    this->m_thumbnail = "";
}

/*!
  \fn void PluginInfo::resetLicense()

  \brief Reset PluginInfo::license to "".
 */
void PluginInfo::resetLicense()
{
    this->m_license = "";
}

/*!
  \fn void PluginInfo::resetAuthor()

  \brief Reset PluginInfo::author to "".
 */
void PluginInfo::resetAuthor()
{
    this->m_author = "";
}

/*!
  \fn void PluginInfo::resetWebsite()

  \brief Reset PluginInfo::website to "".
 */
void PluginInfo::resetWebsite()
{
    this->m_website = "";
}

/*!
  \fn void PluginInfo::resetMail()

  \brief Reset PluginInfo::mail to "".
 */
void PluginInfo::resetMail()
{
    this->m_mail = "";
}

/*!
  \fn void PluginInfo::resetIsConfigurable()

  \brief Reset PluginInfo::isConfigurable to \b false.
 */
void PluginInfo::resetIsConfigurable()
{
    this->m_isConfigurable = false;
}

void PluginInfo::resetConfigs()
{
    this->m_configs = QVariant();
}

void PluginInfo::resetApplyTo()
{
    this->m_applyTo = QStringList();
}
