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

#include <sys/ioctl.h>
#include <linux/videodev2.h>
#include <QDir>
#include <QDebug>

#include "../include/webcamlinux.h"
#include "../include/sleep.h"

/*!
  \class WebcamLinux

  \brief This drive captures from webcam devices using OpenCV.
 */

QString WebcamLinux::id()
{
    return "driver.WebcamLinux";
}

QString WebcamLinux::name()
{
    return "Webcam Linux";
}

QString WebcamLinux::version()
{
    return "1.0.0";
}

QString WebcamLinux::summary()
{
    return "Webcam driver for Linux";
}

QString WebcamLinux::type()
{
    return "webcam";
}

QString WebcamLinux::icon()
{
    return "../../../../../share/drivers/WebcamLinux/share/icons/camera-web.png";
}

QString WebcamLinux::license()
{
    return "GPLv3";
}

QString WebcamLinux::author()
{
    return "hipersayan_x";
}

QString WebcamLinux::website()
{
    return "http://hipersayanx.blogspot.com/";
}

QString WebcamLinux::mail()
{
    return "mailto://hipersayan.x@gmail.com";
}

bool WebcamLinux::isConfigurable()
{
    return false;
}

QStringList WebcamLinux::captureDevices()
{
    Sleep::msleep(250);
    QStringList webcamsDevices;
    QDir devicesDir("/dev");
    QStringList devices = devicesDir.entryList(QStringList("video*"), QDir::System | QDir::Readable | QDir::Writable | QDir::NoSymLinks | QDir::NoDotAndDotDot | QDir::CaseSensitive, QDir::Name);
    QList<QString>::iterator device;
    QFile fd;
    struct v4l2_capability capability;

    for(device = devices.begin(); device != devices.end(); device++)
    {
        fd.setFileName(devicesDir.absoluteFilePath(*device));

        if(fd.open(QIODevice::ReadWrite))
        {
            ioctl(fd.handle(), VIDIOC_QUERYCAP, &capability);

            if(capability.capabilities & V4L2_CAP_VIDEO_CAPTURE)
                webcamsDevices << fd.fileName();

            fd.close();
        }
    }

    return webcamsDevices;
}

QString WebcamLinux::deviceSummary(QString id)
{
    QFile fd;
    struct v4l2_capability capability;

    fd.setFileName(id);

    if(fd.open(QIODevice::ReadWrite))
    {
        ioctl(fd.handle(), VIDIOC_QUERYCAP, &capability);

        if(capability.capabilities & V4L2_CAP_VIDEO_CAPTURE)
            return QString((const char *)capability.card);

        fd.close();
    }

    return "";
}

QImage WebcamLinux::captureFrame(QString id)
{
    if (this->activeWebcams.contains(id))
    {
        cv::Mat matFrame;

        // Capture a frame in cvMat format...
        this->activeWebcams[id] >> matFrame;

        // and convert it to QImage.
        QImage qtFrame((const uchar *)matFrame.data, matFrame.cols, matFrame.rows, QImage::Format_RGB888);

        return qtFrame.rgbSwapped();
    }
    else
    {
        // Else return a 1x1 black image.
        QImage frame(1, 1, QImage::Format_RGB888);

        frame.fill(0);

        return frame;
    }
}

QSize WebcamLinux::frameSize(QString id)
{
    if (this->activeWebcams.contains(id))
        return QSize(this->activeWebcams[id].get(CV_CAP_PROP_FRAME_WIDTH), this->activeWebcams[id].get(CV_CAP_PROP_FRAME_HEIGHT));
    else
        return QSize(0, 0);
}

void WebcamLinux::begin()
{
    this->fs_watcher = new QFileSystemWatcher(QStringList("/dev"), this);
    connect(this->fs_watcher, SIGNAL(directoryChanged(QString)), this, SLOT(modified(QString)));
}

void WebcamLinux::end()
{
    if (!this->fs_watcher)
        return;

    disconnect(this->fs_watcher, SIGNAL(directoryChanged(QString)), this, SLOT(modified(QString)));
    delete this->fs_watcher;
    this->fs_watcher = NULL;
}

bool WebcamLinux::disableDevice(QString id)
{
    if (!this->activeWebcams.contains(id))
        return false;

    this->activeWebcams.remove(id);

    return true;
}

bool WebcamLinux::enableDevice(QString id)
{
    cv::VideoCapture webcam;

    // Try to open webcam device,
    if (!webcam.open(QString(id).remove("/dev/video").toInt()))
        return false;

    // and append it to activeWebcams.
    this->activeWebcams[id] = webcam;

    return true;
}

bool WebcamLinux::isActive(QString id)
{
    return this->activeWebcams.contains(id);
}

void WebcamLinux::configureDevice(QString id)
{
    Q_UNUSED(id)
}

QVariant WebcamLinux::configs()
{
    QVariant configs;

    return configs;
}

void WebcamLinux::setConfigs(QVariant configs)
{
    Q_UNUSED(configs)
}

/*!
  \internal

  fn void WebcamLinux::modified(QString id)

  \param Unique device identifier.

  \brief This slot is called when a webcam is added or removed.
 */
void WebcamLinux::modified(QString id)
{
    Q_UNUSED(id)

    emit devicesModified();
}
