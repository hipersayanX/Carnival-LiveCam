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

#ifndef SHELL_H
#define SHELL_H

#include <QImage>

class Shell: public QObject
{
    Q_OBJECT

    public:
        virtual QString id() = 0;
        virtual QString name() = 0;
        virtual QString version() = 0;
        virtual QString summary() = 0;
        virtual QString type() = 0;
        virtual QString thumbnail() = 0;
        virtual QString license() = 0;
        virtual QString author() = 0;
        virtual QString website() = 0;
        virtual QString mail() = 0;
        virtual bool isConfigurable() = 0;

        virtual void begin() = 0;
        virtual void end() = 0;
        virtual void configure() = 0;
        virtual QWidget *widget() = 0;

    public slots:
        virtual void setFrame(const QImage &frame) = 0;
        virtual void updateDevices(const QList<QVariant> &devices) = 0;
        virtual void updatePlugins(const QList<QVariant> &plugins) = 0;

    signals:
        void takePicture();
        void startStopRecord();
        void deviceSelected(QString deviceId);
        void pluginActivated(QString pluginId);
        void pluginDeactivated(QString pluginId);
        void pluginMoved(int from, int to);
        void pluginConfigureClicked(QString pluginId);
        void deviceConfigureClicked(QString deviceId);
        void closed();
};

#endif // SHELL_H
