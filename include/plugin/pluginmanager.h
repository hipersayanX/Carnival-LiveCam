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

#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include "pluginfactory.h"
#include "plugininfo.h"

class PluginManager: public QObject
{
    Q_OBJECT

    public:
        explicit PluginManager(QObject *parent = 0);
        Q_INVOKABLE Plugin *plugin(QString pluginId);
        Q_INVOKABLE QList<QVariant> toList();
        Q_INVOKABLE QImage render(QString deviceId, const QImage &image);

    private:
        QPluginLoader m_pluginLoader;
        QList<Plugin *> m_activePlugins;
        QHash<QString, QStringList> m_plugins;
        QHash<QString, PluginInfo> m_pluginsInfo;
        QHash<QString, QVariant> m_pluginConfigs;

    signals:
        // Drivers

        void devicesModified(QString driverId);

        // Shells

        void viewPortSizeChanged(QString shellId, QSize size);
        void mouseDoubleClicked(QString shellId, QMouseEvent *event);
        void mousePositionChanged(QString shellId, QMouseEvent *event);
        void mousePressed(QString shellId, QMouseEvent *event);
        void mouseReleased(QString shellId, QMouseEvent *event);
        void toggleEditMode(QString shellId);
        void takePicture(QString shellId);
        void startStopRecord(QString shellId);
        void closed(QString shellId);

        void setEffect(QString pluginId, QString spaceId);
        void unsetEffect(QString pluginId, QString spaceId);
        void effectMoved(QString spaceId, qint32 from, qint32 to);
        void effectConfigureClicked(QString pluginId);
        void deviceMoved(qint32 from, qint32 to);
        void deviceEnabled(QString deviceId);
        void deviceDisabled(QString deviceId);
        void deviceConfigureClicked(QString deviceId);

        // Streamming

        /*void rosterChanged(QString streamId, QList<QVariant> roster);
        void stateChanged(QString streamId, int state);*/

    public slots:
        // Common methods.

        /// This method is called before Plugin::begin().
        /// Set all configurations presaved with Plugin::configs().
        ///
        /// \param configs Plugin configurations.
        void setConfigs(QString pluginId, const QVariant &configs);

        void resetConfigs(QString pluginId);

        void setFrame(QString pluginId, QString deviceId, const QImage &frame);
        void setFrameSize(QString pluginId, QString deviceId, const QSize &size);

        void addSpace(QString spaceId, QSize frameSize);
        void removeSpace(QString spaceId);

        // Effects

        bool setEffect(QString pluginId, QString spaceId, QSize frameSize);
        bool unsetEffect(QString pluginId, QString spaceId);
        void unsetEffects(QString spaceId);
        void configureEffect(QString pluginId);
        void moveEffect(QString spaceId, qint32 from, qint32 to);

        void mouseDoubleClickEvent(QString spaceId, QMouseEvent *event);
        void mouseMoveEvent(QString spaceId, QMouseEvent *event);
        void mousePressEvent(QString spaceId, QMouseEvent *event);
        void mouseReleaseEvent(QString spaceId, QMouseEvent *event);

        // Shells

        void setPreview(QString shellId, const QImage &frame);

        /// \brief Set the devices to be selected by the user in the GUI.
        ///
        /// \param devices Devices info list.
        void updateDevices(QString shellId, const QList<QVariant> &devices, const QStringList &activeSpaces);

        /// \brief Set the plugins to be selected by the user in the GUI.
        ///
        /// \param plugins Plugins info list.
        void updateEffects(QString shellId, const QList<QVariant> &plugins);

        void setControlButtons(QString shellId, QPushButton *toggleMaximizedButton, QPushButton *scaleAndRotateButton);

        void moveDevice(QString shellId, qint32 from, qint32 to);

        // Streamming

        /*void login(QString streamId, QString userId, QString password);
        void startCall(QString streamId, QString userId);
        void endCall(QString streamId, QString userId);
        void startIM(QString streamId, QString userId);
        void endIM(QString streamId, QString userId);
        void sendMail(QString streamId, QString userId, QString mail);*/
};

#endif // PLUGINMANAGER_H
