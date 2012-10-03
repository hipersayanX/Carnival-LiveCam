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

#include "include/cube.h"

QString Cube::pluginId()
{
    return "Cube";
}

QString Cube::name()
{
    return "Cube";
}

QString Cube::version()
{
    return "1.0.0";
}

QString Cube::summary()
{
    return "Render the webcam image in a cube.";
}

QString Cube::type()
{
    return "video";
}

QString Cube::category()
{
    return "plugin";
}

QString Cube::thumbnail()
{
    return "../../../../../share/plugins/Cube/share/thumbnail-128x96.png";
}

QString Cube::license()
{
    return "GPLv3";
}

QString Cube::author()
{
    return "Gonzalo Exequiel Pedone";
}

QString Cube::website()
{
    return "https://github.com/hipersayanX/Carnival-LiveCam";
}

QString Cube::mail()
{
    return "hipersayan DOT x AT gmail DOT com";
}

bool Cube::isConfigurable()
{
    return false;
}

Element *Cube::newElement()
{
    return new CubeElement();
}

Q_EXPORT_PLUGIN2(Cube, Cube)
