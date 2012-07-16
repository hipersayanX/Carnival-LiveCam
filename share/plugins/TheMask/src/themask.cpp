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
}

void TheMask::addSpace(QString spaceId, QSize frameSize)
{
    this->spaces[spaceId] = Space(QImage("share/plugins/TheMask/share/masks/cow.png"), frameSize);
}

void TheMask::removeSpace(QString spaceId)
{
    this->spaces.remove(spaceId);
}

QImage TheMask::render(QString spaceId, const QImage &image)
{
    if (this->spaces.contains(spaceId))
    {
        this->mask.setMaskImage(this->spaces[spaceId].maskImage());

        return this->mask.render(image);
    }
    else
        return image;
}

void TheMask::end()
{
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

void TheMask::mouseDoubleClickEvent(QString spaceId, QMouseEvent *event)
{
    Q_UNUSED(spaceId)
    Q_UNUSED(event)
}

void TheMask::mouseMoveEvent(QString spaceId, QMouseEvent *event)
{
    Q_UNUSED(spaceId)
    Q_UNUSED(event)
}

void TheMask::mousePressEvent(QString spaceId, QMouseEvent *event)
{
    Q_UNUSED(spaceId)
    Q_UNUSED(event)
}

void TheMask::mouseReleaseEvent(QString spaceId, QMouseEvent *event)
{
    Q_UNUSED(spaceId)
    Q_UNUSED(event)
}

Q_EXPORT_PLUGIN2(TheMask, TheMask)
