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

#include "include/themask.h"

QString TheMask::pluginId()
{
    return "TheMask";
}

QString TheMask::name()
{
    return "The Mask";
}

QString TheMask::version()
{
    return "1.0.0";
}

QString TheMask::summary()
{
    return "Cover your face with a mask";
}

QString TheMask::type()
{
    return "video";
}

QString TheMask::category()
{
    return "OpenCV";
}

QString TheMask::thumbnail()
{
    return "../../../../../share/plugins/TheMask/share/thumbnail-128x96.png";
}

QString TheMask::license()
{
    return "GPLv3";
}

QString TheMask::author()
{
    return "Gonzalo Exequiel Pedone";
}

QString TheMask::website()
{
    return "https://github.com/hipersayanX/Carnival-LiveCam";
}

QString TheMask::mail()
{
    return "hipersayan DOT x AT gmail DOT com";
}

bool TheMask::isConfigurable()
{
    return false;
}

Element *TheMask::newElement()
{
    return new TheMaskElement();
}

TheMask::~TheMask()
{
}

Q_EXPORT_PLUGIN2(TheMask, TheMask)
