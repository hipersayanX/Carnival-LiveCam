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

#include "../include/imagesource.h"

QString ImageSource::pluginId()
{
    return "ImageSource";
}

QString ImageSource::name()
{
    return "Image Source";
}

QString ImageSource::version()
{
    return "1.0.0";
}

QString ImageSource::summary()
{
    return "Create a source from a static image file.";
}

QString ImageSource::type()
{
    return "video";
}

QString ImageSource::category()
{
    return "image";
}

QString ImageSource::thumbnail()
{
    return "";
}

QString ImageSource::license()
{
    return "GPLv3";
}

QString ImageSource::author()
{
    return "Gonzalo Exequiel Pedone";
}

QString ImageSource::website()
{
    return "https://github.com/hipersayanX/Carnival-LiveCam";
}

QString ImageSource::mail()
{
    return "hipersayan DOT x AT gmail DOT com";
}

bool ImageSource::isConfigurable()
{
    return false;
}

Element *ImageSource::newElement()
{
    ImageSourceElement *element = new ImageSourceElement();

    return qobject_cast<Element *>(element);
}

ImageSource::~ImageSource()
{
}

Q_EXPORT_PLUGIN2(ImageSource, ImageSource)
