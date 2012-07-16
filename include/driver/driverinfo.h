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

#ifndef DRIVERINFO_H
#define DRIVERINFO_H

#include <QObject>

class DriverInfo: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString fileName READ fileName WRITE setFileName RESET resetFileName)
    Q_PROPERTY(QString driverId READ driverId WRITE setDriverId RESET resetDriverId)
    Q_PROPERTY(bool isEnabled READ isEnabled WRITE setIsEnabled RESET resetIsEnabled)
    Q_PROPERTY(QString name READ name WRITE setName RESET resetName)
    Q_PROPERTY(QString version READ version WRITE setVersion RESET resetVersion)
    Q_PROPERTY(QString summary READ summary WRITE setSummary RESET resetSummary)
    Q_PROPERTY(QString type READ type WRITE setType RESET resetType)
    Q_PROPERTY(QString icon READ icon WRITE setIcon RESET resetIcon)
    Q_PROPERTY(QString license READ license WRITE setLicense RESET resetLicense)
    Q_PROPERTY(QString author READ author WRITE setAuthor RESET resetAuthor)
    Q_PROPERTY(QString website READ website WRITE setWebsite RESET resetWebsite)
    Q_PROPERTY(QString mail READ mail WRITE setMail RESET resetMail)
    Q_PROPERTY(bool isConfigurable READ isConfigurable WRITE setIsConfigurable RESET resetIsConfigurable)

    public:
        explicit DriverInfo(QObject *parent = 0);
        DriverInfo(const DriverInfo &object);

        DriverInfo(QString fileName,
                   QString driverId,
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
                   bool isConfigurable);

        DriverInfo& operator =(const DriverInfo &other);

        QString fileName();
        QString driverId();
        bool isEnabled();
        QString name();
        QString version();
        QString summary();
        QString type();
        QString icon();
        QString license();
        QString author();
        QString website();
        QString mail();
        bool isConfigurable();

    private:
        QString m_fileName;
        QString m_driverId;
        bool m_isEnabled;
        QString m_name;
        QString m_version;
        QString m_summary;
        QString m_type;
        QString m_icon;
        QString m_license;
        QString m_author;
        QString m_website;
        QString m_mail;
        bool m_isConfigurable;

    public slots:
        void setFileName(QString value);
        void setDriverId(QString value);
        void setIsEnabled(bool value);
        void setName(QString value);
        void setVersion(QString value);
        void setSummary(QString value);
        void setType(QString value);
        void setIcon(QString value);
        void setLicense(QString value);
        void setAuthor(QString value);
        void setWebsite(QString value);
        void setMail(QString value);
        void setIsConfigurable(bool value);
        void resetFileName();
        void resetDriverId();
        void resetIsEnabled();
        void resetName();
        void resetVersion();
        void resetSummary();
        void resetType();
        void resetIcon();
        void resetLicense();
        void resetAuthor();
        void resetWebsite();
        void resetMail();
        void resetIsConfigurable();
};

#endif // DRIVERINFO_H
