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

#include "../include/videodriver.h"

/*!
  \class VideoDriver

  \brief This drive captures from video files.

  This driver convert the videos selected by the user in capture devices.
 */

QString VideoDriver::id()
{
    return "driver.VideoDriver";
}

QString VideoDriver::name()
{
    return "Video Driver";
}

QString VideoDriver::version()
{
    return "1.0.0";
}

QString VideoDriver::summary()
{
    return "Capture from video file";
}

QString VideoDriver::type()
{
    return "image";
}

QString VideoDriver::icon()
{
    return "../../../../../share/drivers/VideoDriver/share/icons/video.png";
}

QString VideoDriver::license()
{
    return "GPLv3";
}

QString VideoDriver::author()
{
    return "Gonzalo Exequiel Pedone";
}

QString VideoDriver::website()
{
    return "http://hipersayanx.blogspot.com/";
}

QString VideoDriver::mail()
{
    return "mailto://hipersayan.x@gmail.com";
}

bool VideoDriver::isConfigurable()
{
    return true;
}

QStringList VideoDriver::captureDevices()
{
    if (this->videoDevices.count() < 1)
    {
        QStringList devices;

        devices << "/video/null";

        return devices;
    }
    else
        return this->videoDevices;
}

QString VideoDriver::deviceSummary(QString id)
{
    if (this->videoDevices.contains(id))
    {
        QFileInfo fileInfo(id);

        return fileInfo.fileName();
    }
    else
        return "No Video";
}

QImage VideoDriver::captureFrame(QString id)
{
    if (this->video.contains(id))
    {
        cv::Mat matFrame;

        this->video[id] >> matFrame;

        QImage qtFrame((const uchar *)matFrame.data, matFrame.cols, matFrame.rows, QImage::Format_RGB888);

        return qtFrame.rgbSwapped();
    }
    else
    {
        QImage frame(1, 1, QImage::Format_RGB888);

        frame.fill(0);

        return frame;
    }
}

QSize VideoDriver::frameSize(QString id)
{
    if (this->video.contains(id))
        return QSize(this->video[id].get(CV_CAP_PROP_FRAME_WIDTH), this->video[id].get(CV_CAP_PROP_FRAME_HEIGHT));
    else
        return QSize(1, 1);
}

void VideoDriver::begin()
{
    this->config.setVideoDevices(&this->videoDevices);
}

void VideoDriver::end()
{
}

bool VideoDriver::disableDevice(QString id)
{
    if (!this->video.contains(id))
        return false;

    this->video.remove(id);

    return true;
}

bool VideoDriver::enableDevice(QString id)
{
    cv::VideoCapture video;

    if (!video.open(id.toUtf8().constData()))
        return false;

    this->video[id] = video;

    return true;
}

bool VideoDriver::isActive(QString id)
{
    return this->video.contains(id);
}

void VideoDriver::configureDevice(QString id)
{
    Q_UNUSED(id)

    config.exec();
    emit devicesModified();
}

QVariant VideoDriver::configs()
{
    return QVariant(this->videoDevices);
}

void VideoDriver::setConfigs(QVariant configs)
{
    this->videoDevices = configs.toStringList();
}
