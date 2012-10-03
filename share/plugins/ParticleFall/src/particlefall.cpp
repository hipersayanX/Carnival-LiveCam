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

#include "include/particlefall.h"

QString ParticleFall::pluginId()
{
    return "ParticleFall";
}

QString ParticleFall::name()
{
    return "Particle Fall";
}

QString ParticleFall::version()
{
    return "1.0.0";
}

QString ParticleFall::summary()
{
    return "Falling particles";
}

QString ParticleFall::type()
{
    return "video";
}

QString ParticleFall::category()
{
    return "plugin";
}

QString ParticleFall::thumbnail()
{
    return "../../../../../share/plugins/ParticleFall/share/thumbnail-128x96.png";
}

QString ParticleFall::license()
{
    return "GPLv3";
}

QString ParticleFall::author()
{
    return "Gonzalo Exequiel Pedone";
}

QString ParticleFall::website()
{
    return "https://github.com/hipersayanX/Carnival-LiveCam";
}

QString ParticleFall::mail()
{
    return "hipersayan DOT x AT gmail DOT com";
}

bool ParticleFall::isConfigurable()
{
    return false;
}

Element *ParticleFall::newElement()
{
    return new ParticleFallElement();
}

Q_EXPORT_PLUGIN2(ParticleFall, ParticleFall)
