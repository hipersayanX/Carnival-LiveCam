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

#include "include/rendermodel.h"

QString RenderModel::pluginId()
{
    return "RenderModel";
}

QString RenderModel::name()
{
    return "Render Model";
}

QString RenderModel::version()
{
    return "1.0.0";
}

QString RenderModel::summary()
{
    return "This plugin shows a 3D model";
}

QString RenderModel::type()
{
    return "video";
}

QString RenderModel::category()
{
    return "plugin";
}

QString RenderModel::thumbnail()
{
    return "../../../../../share/plugins/RenderModel/share/thumbnail-128x96.png";
}

QString RenderModel::license()
{
    return "GPLv3";
}

QString RenderModel::author()
{
    return "Gonzalo Exequiel Pedone";
}

QString RenderModel::website()
{
    return "https://github.com/hipersayanX/Carnival-LiveCam";
}

QString RenderModel::mail()
{
    return "hipersayan DOT x AT gmail DOT com";
}

bool RenderModel::isConfigurable()
{
    return false;
}

Element *RenderModel::newElement()
{
    return new RenderModelElement();
}

RenderModel::~RenderModel()
{
}

Q_EXPORT_PLUGIN2(RenderModel, RenderModel)
