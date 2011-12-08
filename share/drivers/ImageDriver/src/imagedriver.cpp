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
 * Webcam driver for linux
 */

#include <QDebug>
#include <QFileInfo>

#include "../include/imagedriver.h"

/*!
  \class ImageDriver

  \brief This drive captures from image files.

  This driver convert the images selected by the user in capture devices.
 */

QString ImageDriver::id()
{
    return "driver.ImageDriver";
}

QString ImageDriver::name()
{
    return "Image Driver";
}

QString ImageDriver::version()
{
    return "1.0.0";
}

QString ImageDriver::summary()
{
    return "Capture from image file";
}

QString ImageDriver::type()
{
    return "image";
}

QString ImageDriver::icon()
{
    return "../../../../../share/drivers/ImageDriver/share/icons/image.png";
}

QString ImageDriver::license()
{
    return "GPLv3";
}

QString ImageDriver::author()
{
    return "Gonzalo Exequiel Pedone";
}

QString ImageDriver::website()
{
    return "http://hipersayanx.blogspot.com/";
}

QString ImageDriver::mail()
{
    return "mailto://hipersayan.x@gmail.com";
}

bool ImageDriver::isConfigurable()
{
    return true;
}

QStringList ImageDriver::captureDevices()
{
    if (this->imageDevices.count() < 1)
    {
        QStringList devices;

        devices << "/image/null";

        return devices;
    }
    else
        return this->imageDevices;
}

QString ImageDriver::deviceSummary(QString id)
{
    if (this->imageDevices.contains(id))
    {
        QFileInfo fileInfo(id);

        return fileInfo.fileName();
    }
    else
        return "No Image";
}

QImage ImageDriver::captureFrame(QString id)
{
    if (this->images.contains(id))
        return this->images[id];
    else
    {
        QImage frame(1, 1, QImage::Format_RGB888);

        frame.fill(0);

        return frame;
    }
}

QSize ImageDriver::frameSize(QString id)
{
    if (this->images.contains(id))
        return this->images[id].size();
    else
        return QSize(1, 1);
}

void ImageDriver::begin()
{
    this->config.setImageDevices(&this->imageDevices);
}

void ImageDriver::end()
{
}

bool ImageDriver::disableDevice(QString id)
{
    if (!this->images.contains(id))
        return false;

    this->images.remove(id);

    return true;
}

bool ImageDriver::enableDevice(QString id)
{
    QImage image;

    if (!image.load(id))
        return false;

    this->images[id] = image.convertToFormat(QImage::Format_RGB888);

    return true;
}

bool ImageDriver::isActive(QString id)
{
    return this->images.contains(id);
}

void ImageDriver::configureDevice(QString id)
{
    Q_UNUSED(id)

    this->config.exec();
    emit devicesModified();
}

QVariant ImageDriver::configs()
{
    return QVariant(this->imageDevices);
}

void ImageDriver::setConfigs(QVariant configs)
{
    this->imageDevices = configs.toStringList();
}
