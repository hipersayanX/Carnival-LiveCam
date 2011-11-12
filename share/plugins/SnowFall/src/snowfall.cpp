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

#include "../include/snowfall.h"

QString SnowFall::author()
{
    return "Gonzalo Exequiel Pedone";
}

QString SnowFall::mail()
{
    return "hipersayan.x@gmail.com";
}

QString SnowFall::website()
{
    return "hipersayanx.blogspot.com";
}

QString SnowFall::category()
{
    return "Snow";
}

QString SnowFall::id()
{
    return "plugin.SnowFall";
}

QString SnowFall::license()
{
    return "GPLv3";
}

QString SnowFall::name()
{
    return "Snow Fall";
}

QString SnowFall::summary()
{
    return "Falling snow flakes";
}

QString SnowFall::thumbnail()
{
    return "../../../../../share/plugins/SnowFall/share/thumbnail-128x96.png";
}

bool SnowFall::is3D()
{
    return false;
}

QString SnowFall::version()
{
    return "1.0.0";
}

bool SnowFall::isConfigurable()
{
    return false;
}

void SnowFall::begin()
{
    this->snow = new Snow(640, // width
                          480, // height
                          75,  // nFlakes
                          0.12,   // acceleration
                          10,  // direction
                          0.1, // randFactor
                          100,  // border
                          0.25, // minZ
                          1,   // maxZ
                          0.1, // minScale
                          0.2);
}

void SnowFall::resize(int width, int height)
{
    this->snow->resize(width, height);
}

QImage SnowFall::render(const QImage &image)
{
    QImage frame = this->snow->render(image);

    this->snow->next();

    return frame;
}

void SnowFall::end()
{
    delete this->snow;
}

void SnowFall::configure()
{
}

Q_EXPORT_PLUGIN2(SnowFall, SnowFall)
