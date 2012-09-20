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

#include "include/webcamsource.h"

QString WebcamSource::pluginId()
{
    return "WebcamSource";
}

QString WebcamSource::name()
{
    return "Webcam Source";
}

QString WebcamSource::version()
{
    return "1.0.0";
}

QString WebcamSource::summary()
{
    return "Capture video from a webcam";
}

QString WebcamSource::type()
{
    return "video";
}

QString WebcamSource::category()
{
    return "webcam";
}

QString WebcamSource::thumbnail()
{
    return "../../../../../share/drivers/WebcamLinux/share/icons/camera-web.png";
}

QString WebcamSource::license()
{
    return "GPLv3";
}

QString WebcamSource::author()
{
    return "Gonzalo Exequiel Pedone";
}

QString WebcamSource::website()
{
    return "https://github.com/hipersayanX/Carnival-LiveCam";
}

QString WebcamSource::mail()
{
    return "hipersayan DOT x AT gmail DOT com";
}

bool WebcamSource::isConfigurable()
{
    return false;
}

Element *WebcamSource::newElement()
{
    return new WebcamSourceElement();
}

WebcamSource::~WebcamSource()
{
}

Q_EXPORT_PLUGIN2(WebcamSource, WebcamSource)
