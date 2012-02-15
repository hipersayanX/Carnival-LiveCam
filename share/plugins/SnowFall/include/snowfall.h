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
 * Snow fall plugin
 */

#ifndef SNOWFALL_H
#define SNOWFALL_H

#include <QVariant>

#include "config.h"
#include "plugin.h"
#include "snow.h"

class SnowFall: public QObject, public Plugin
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
        void resize(qint32 width, qint32 height);
        QImage render(const QImage &image);
        void end();

        void configure();
        QVariant configs();
        void setConfigs(QVariant configs);

    private:
        Snow *snow;
        Config config;
};

#endif // SNOWFALL_H
