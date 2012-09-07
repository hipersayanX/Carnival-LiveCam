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

#include "../include/webcamdetect.h"

QString WebcamDetect::pluginId()
{
    return "WebcamDetect";
}

QString WebcamDetect::name()
{
    return "Webcam detect";
}

QString WebcamDetect::version()
{
    return "1.0.0";
}

QString WebcamDetect::summary()
{
    return "Detect all available webcam devices";
}

QString WebcamDetect::type()
{
    return "utils";
}

QString WebcamDetect::category()
{
    return "webcam";
}

QString WebcamDetect::thumbnail()
{
    return "../../../../../share/drivers/WebcamLinux/share/icons/camera-web.png";
}

QString WebcamDetect::license()
{
    return "GPLv3";
}

QString WebcamDetect::author()
{
    return "Gonzalo Exequiel Pedone";
}

QString WebcamDetect::website()
{
    return "https://github.com/hipersayanX/Carnival-LiveCam";
}

QString WebcamDetect::mail()
{
    return "hipersayan DOT x AT gmail DOT com";
}

bool WebcamDetect::isConfigurable()
{
    return false;
}

WebcamDetectElement *WebcamDetect::newElement()
{
    return new WebcamDetectElement();
}

WebcamDetect::~WebcamDetect()
{
}

Q_EXPORT_PLUGIN2(WebcamDetect, WebcamDetect)
