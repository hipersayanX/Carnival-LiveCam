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

#ifndef PLUGININFO_H
#define PLUGININFO_H

#include <QObject>
#include <QStringList>

class PluginInfo: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString fileName READ fileName WRITE setFileName RESET resetFileName)
    Q_PROPERTY(QString pluginId READ pluginId WRITE setPluginId RESET resetPluginId)
    Q_PROPERTY(bool isEnabled READ isEnabled WRITE setIsEnabled RESET resetIsEnabled)
    Q_PROPERTY(QString name READ name WRITE setName RESET resetName)
    Q_PROPERTY(QString version READ version WRITE setVersion RESET resetVersion)
    Q_PROPERTY(QString summary READ summary WRITE setSummary RESET resetSummary)
    Q_PROPERTY(QString category READ category WRITE setCategory RESET resetCategory)
    Q_PROPERTY(QString thumbnail READ thumbnail WRITE setThumbnail RESET resetThumbnail)
    Q_PROPERTY(QString license READ license WRITE setLicense RESET resetLicense)
    Q_PROPERTY(QString author READ author WRITE setAuthor RESET resetAuthor)
    Q_PROPERTY(QString website READ website WRITE setWebsite RESET resetWebsite)
    Q_PROPERTY(QString mail READ mail WRITE setMail RESET resetMail)
    Q_PROPERTY(bool is3D READ is3D WRITE setIs3D RESET resetIs3D)
    Q_PROPERTY(bool isConfigurable READ isConfigurable WRITE setIsConfigurable RESET resetIsConfigurable)
    Q_PROPERTY(QStringList applyTo READ applyTo WRITE setApplyTo RESET resetApplyTo)

    public:
        explicit PluginInfo(QObject *parent = 0);
        PluginInfo(const PluginInfo &object);

        PluginInfo(QString fileName,
                   QString pluginId,
                   bool isEnabled,
                   QString name,
                   QString version,
                   QString summary,
                   QString category,
                   QString thumbnail,
                   QString license,
                   QString author,
                   QString website,
                   QString mail,
                   bool is3D,
                   bool isConfigurable,
                   QStringList applyTo);

        PluginInfo& operator =(const PluginInfo &other);

        QString fileName();
        QString pluginId();
        bool isEnabled();
        QString name();
        QString version();
        QString summary();
        QString category();
        QString thumbnail();
        QString license();
        QString author();
        QString website();
        QString mail();
        bool is3D();
        bool isConfigurable();
        QStringList applyTo();

    private:
        QString m_fileName;
        QString m_pluginId;
        bool m_isEnabled;
        QString m_name;
        QString m_version;
        QString m_summary;
        QString m_category;
        QString m_thumbnail;
        QString m_license;
        QString m_author;
        QString m_website;
        QString m_mail;
        bool m_is3D;
        bool m_isConfigurable;
        QStringList m_applyTo;

    public slots:
        void setFileName(QString value);
        void setPluginId(QString value);
        void setIsEnabled(bool value);
        void setName(QString value);
        void setVersion(QString value);
        void setSummary(QString value);
        void setCategory(QString value);
        void setThumbnail(QString value);
        void setLicense(QString value);
        void setAuthor(QString value);
        void setWebsite(QString value);
        void setMail(QString value);
        void setIs3D(bool value);
        void setIsConfigurable(bool value);
        void setApplyTo(QStringList value);
        void resetFileName();
        void resetPluginId();
        void resetIsEnabled();
        void resetName();
        void resetVersion();
        void resetSummary();
        void resetCategory();
        void resetThumbnail();
        void resetLicense();
        void resetAuthor();
        void resetWebsite();
        void resetMail();
        void resetIs3D();
        void resetIsConfigurable();
        void resetApplyTo();
};

#endif // PLUGININFO_H
