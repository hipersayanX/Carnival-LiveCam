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

#ifndef DEVICEINFO_H
#define DEVICEINFO_H

#include <QObject>
#include <QStringList>

class DeviceInfo: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString deviceId READ deviceId WRITE setDeviceId RESET resetDeviceId)
    Q_PROPERTY(QString driverId READ driverId WRITE setDriverId RESET resetDriverId)
    Q_PROPERTY(bool isEnabled READ isEnabled WRITE setIsEnabled RESET resetIsEnabled)
    Q_PROPERTY(QString summary READ summary WRITE setSummary RESET resetSummary)
    Q_PROPERTY(QString icon READ icon WRITE setIcon RESET resetIcon)
    Q_PROPERTY(bool isConfigurable READ isConfigurable WRITE setIsConfigurable RESET resetIsConfigurable)
    Q_PROPERTY(QStringList effects READ effects WRITE setEffects RESET resetEffects)

    public:
        explicit DeviceInfo(QObject *parent = 0);
        DeviceInfo(const DeviceInfo &object);

        DeviceInfo(QString deviceId,
                   QString driverId,
                   bool isEnabled,
                   QString summary,
                   QString icon,
                   bool isConfigurable,
                   QStringList effects);

        DeviceInfo& operator =(const DeviceInfo &other);

        QString deviceId();
        QString driverId();
        bool isEnabled();
        QString summary();
        QString icon();
        bool isConfigurable();
        QStringList effects();

    private:
        QString m_deviceId;
        QString m_driverId;
        bool m_isEnabled;
        QString m_summary;
        QString m_icon;
        bool m_isConfigurable;
        QStringList m_effects;

    public slots:
        void setDeviceId(QString value);
        void setDriverId(QString value);
        void setIsEnabled(bool value);
        void setSummary(QString value);
        void setIcon(QString value);
        void setIsConfigurable(bool value);
        void setEffects(QStringList value);
        void resetDeviceId();
        void resetDriverId();
        void resetIsEnabled();
        void resetSummary();
        void resetIcon();
        void resetIsConfigurable();
        void resetEffects();
};

#endif // DEVICEINFO_H
