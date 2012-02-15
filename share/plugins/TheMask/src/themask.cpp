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

#include "../include/themask.h"

QString TheMask::author()
{
    return "Gonzalo Exequiel Pedone";
}

QString TheMask::mail()
{
    return "hipersayan.x@gmail.com";
}

QString TheMask::website()
{
    return "hipersayanx.blogspot.com";
}

QString TheMask::category()
{
    return "OpenCV";
}

QString TheMask::id()
{
    return "plugin.TheMask";
}

QString TheMask::license()
{
    return "GPLv3";
}

QString TheMask::name()
{
    return "The Mask";
}

QString TheMask::summary()
{
    return "Cover your face with a mask";
}

QString TheMask::thumbnail()
{
    return "../../../../../share/plugins/TheMask/share/thumbnail-128x96.png";
}

bool TheMask::is3D()
{
    return false;
}

QString TheMask::version()
{
    return "1.0.0";
}

bool TheMask::isConfigurable()
{
    return false;
}

void TheMask::begin()
{
    this->mask = new Mask("share/plugins/TheMask/share/masks/cow.png");
//    this->mask = new Mask("share/plugins/TheMask/share/masks/guyfawkes.png");
}

void TheMask::resize(qint32 width, qint32 height)
{
    Q_UNUSED(width)
    Q_UNUSED(height)
}

QImage TheMask::render(const QImage &image)
{
    return this->mask->render(image);
}

void TheMask::end()
{
    delete this->mask;
}

void TheMask::configure()
{
}

QVariant TheMask::configs()
{
    return QVariant();
}

void TheMask::setConfigs(QVariant configs)
{
    Q_UNUSED(configs)
}

Q_EXPORT_PLUGIN2(TheMask, TheMask)
