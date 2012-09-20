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

#include "include/mediarecorder.h"

QString MediaRecorder::pluginId()
{
    return "MediaRecorder";
}

QString MediaRecorder::name()
{
    return "Media Recorder";
}

QString MediaRecorder::version()
{
    return "1.0.0";
}

QString MediaRecorder::summary()
{
    return "Record video using FFmpeg";
}

QString MediaRecorder::type()
{
    return "video";
}

QString MediaRecorder::category()
{
    return "utils";
}

QString MediaRecorder::thumbnail()
{
    return "";
}

QString MediaRecorder::license()
{
    return "GPLv3";
}

QString MediaRecorder::author()
{
    return "Gonzalo Exequiel Pedone";
}

QString MediaRecorder::website()
{
    return "https://github.com/hipersayanX/Carnival-LiveCam";
}

QString MediaRecorder::mail()
{
    return "hipersayan DOT x AT gmail DOT com";
}

bool MediaRecorder::isConfigurable()
{
    return false;
}

Element *MediaRecorder::newElement()
{
    return new MediaRecorderElement();
}

MediaRecorder::~MediaRecorder()
{
}
