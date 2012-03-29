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
 *
 * OpenCV face recognition plugin
 */

#ifndef DEFAULTPLUGIN_H
#define DEFAULTPLUGIN_H

#include <QVariant>
#include <QHash>

#include "plugin.h"
#include "mask.h"
#include "space.h"

class TheMask: public QObject, public Plugin
{
    Q_OBJECT
    Q_INTERFACES(Plugin)

    public:
        QString author();
        QString mail();
        QString website();
        QString category();
        QString id();
        QString license();
        QString name();
        QString summary();
        QString  thumbnail();
        bool is3D();
        QString version();
        bool isConfigurable();

        void begin();
        void addSpace(QString spaceId, QSize frameSize);
        void removeSpace(QString spaceId);
        QImage render(QString spaceId, const QImage &image);
        void end();

        void configure();
        QVariant configs();
        void setConfigs(QVariant configs);

        void mouseDoubleClickEvent(QString spaceId, QMouseEvent *event);
        void mouseMoveEvent(QString spaceId, QMouseEvent *event);
        void mousePressEvent(QString spaceId, QMouseEvent *event);
        void mouseReleaseEvent(QString spaceId, QMouseEvent *event);

    private:
        Mask mask;
        QHash<QString, Space> spaces;
};

#endif // DEFAULTPLUGIN_H
