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

#include "sleep.h"
#include "webcamdetectelement.h"

WebcamDetectElement::WebcamDetectElement(): Element()
{
    this->m_fsWatcher = NULL;
    this->resetDevicesPath();
}

QList<QStringList> WebcamDetectElement::webcams(QString dir)
{
    Sleep::msleep(250);
    QDir devicesDir(dir);

    QStringList devices = devicesDir.entryList(QStringList("video*"),
                                               QDir::System |
                                               QDir::Readable |
                                               QDir::Writable |
                                               QDir::NoSymLinks |
                                               QDir::NoDotAndDotDot |
                                               QDir::CaseSensitive,
                                               QDir::Name);

    QList<QStringList> webcams;
    struct v4l2_capability capability;

    foreach (QString device, devices)
    {
        QFile devicePath(devicesDir.absoluteFilePath(device));

        if (!devicePath.open(QIODevice::ReadWrite))
            continue;

        ioctl(devicePath.handle(), VIDIOC_QUERYCAP, &capability);

        if (capability.capabilities & V4L2_CAP_VIDEO_CAPTURE)
            webcams << (QStringList() << devicePath.fileName() << QString((const char *)capability.card));

        devicePath.close();
    }

    return webcams;
}

void WebcamDetectElement::iVideo(QImage *frame)
{
    Q_UNUSED(frame)
}

void WebcamDetectElement::iAudio(QByteArray *frame)
{
    Q_UNUSED(frame)
}

bool WebcamDetectElement::start()
{
    this->m_fsWatcher = new QFileSystemWatcher(QStringList(this->m_devicesPath), this);

    if (!this->m_fsWatcher)
        return false;

    QObject::connect(this->m_fsWatcher, SIGNAL(directoryChanged(QString)), this, SLOT(devicesChanged(QString)));

    return true;
}

bool WebcamDetectElement::stop()
{
    if (!this->m_fsWatcher)
        return true;

    QObject::disconnect(this->m_fsWatcher, SIGNAL(directoryChanged(QString)), this, SLOT(devicesChanged(QString)));
    delete this->m_fsWatcher;
    this->m_fsWatcher = NULL;

    return true;
}

void WebcamDetectElement::configure()
{
}

void WebcamDetectElement::setManager(QObject *manager)
{
    Q_UNUSED(manager)
}

template <typename T>  QList<T> WebcamDetectElement::substractList(QList<T> a, QList<T> b)
{
    QList<T> s;

    foreach (T item, a)
        if (!b.contains(item))
            s << item;

    return s;
}

void WebcamDetectElement::devicesChanged(QString path)
{
    QList<QStringList> webcams = this->webcams(path);

    if (!this->m_fsWatcher->directories().isEmpty() && webcams == this->m_webcams)
        return;

    emit(webcamsUpdated(webcams));

    QList<QStringList> removed = this->substractList(this->m_webcams, webcams);
    QList<QStringList> added = this->substractList(webcams, this->m_webcams);

    if (!added.isEmpty())
        emit(webcamsAdded(added));

    if (!removed.isEmpty())
        emit(webcamsRemoved(removed));

    this->m_webcams = webcams;
}

void WebcamDetectElement::updateWebcams()
{
    this->m_fsWatcher->removePath(this->m_devicesPath);
    this->devicesChanged(this->m_devicesPath);
    this->m_fsWatcher->addPath(this->m_devicesPath);
}

QString WebcamDetectElement::devicesPath()
{
    return this->m_devicesPath;
}

void WebcamDetectElement::setDevicesPath(QString devicesPath)
{
    if (this->m_fsWatcher)
    {
        if (this->m_devicesPath != "")
            this->m_fsWatcher->removePath(this->m_devicesPath);

        this->m_fsWatcher->addPath(devicesPath);
    }

    this->m_devicesPath = devicesPath;
}

void WebcamDetectElement::resetDevicesPath()
{
    this->setDevicesPath("/dev");
}
