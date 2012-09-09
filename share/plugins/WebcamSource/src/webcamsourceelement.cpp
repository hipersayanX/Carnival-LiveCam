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
/*
#include <sys/ioctl.h>
#include <linux/videodev2.h>
#include <QDir>
*/
#include "../include/webcamsourceelement.h"

WebcamSourceElement::WebcamSourceElement(): Element()
{
    this->m_device = "/dev/video0";
    this->m_size = QSize(640, 480);
    this->m_fps = 30;

    this->m_webcam.set(CV_CAP_PROP_FRAME_WIDTH, this->m_size.width());
    this->m_webcam.set(CV_CAP_PROP_FRAME_HEIGHT, this->m_size.height());
    this->m_timer.setInterval((int)(1000.0 / (float) this->m_fps));
    QObject::connect(&this->m_timer, SIGNAL(timeout()), this, SLOT(timeout()));
}

QString WebcamSourceElement::device()
{
    return this->m_device;
}

QSize WebcamSourceElement::size()
{
    return this->m_size;
}

int WebcamSourceElement::fps()
{
    return this->m_fps;
}

void WebcamSourceElement::iVideo(QImage *frame)
{
    Q_UNUSED(frame)
}

void WebcamSourceElement::iAudio(QByteArray *frame)
{
    Q_UNUSED(frame)
}

void WebcamSourceElement::start()
{
    // Try to open webcam device,
    if (!this->m_webcam.open(QString(this->m_device).remove("/dev/video").toInt()))
    {
        emit(fail());

        return;
    }

    this->m_timer.start();
}

void WebcamSourceElement::stop()
{
    if (this->m_timer.isActive())
    {
        this->m_timer.stop();
        this->m_webcam.release();
    }
}

void WebcamSourceElement::configure()
{
}

void WebcamSourceElement::setPluginList(QList<QVariant> list)
{
    Q_UNUSED(list)
}

void WebcamSourceElement::setDevice(QString device)
{
    bool active = this->m_timer.isActive();

    if (active)
        this->stop();

    this->m_device = device;

    if (active)
        this->start();
}

void WebcamSourceElement::setSize(QSize size)
{
    bool active = this->m_timer.isActive();

    if (active)
        this->stop();

    this->m_size = size;
    this->m_webcam.set(CV_CAP_PROP_FRAME_WIDTH, this->m_size.width());
    this->m_webcam.set(CV_CAP_PROP_FRAME_HEIGHT, this->m_size.height());

    if (active)
        this->start();
}

void WebcamSourceElement::setFps(int fps)
{
    this->m_fps = fps;

    this->m_timer.setInterval((int)(1000.0 / (float) this->m_fps));
}

void WebcamSourceElement::resetDevice()
{
    this->m_device = "/dev/video0";
    this->setDevice(this->m_device);
}

void WebcamSourceElement::resetSize()
{
    this->setSize(QSize(640, 480));
}

void WebcamSourceElement::resetFps()
{
    this->m_fps = 30;

    this->m_timer.setInterval((int)(1000.0 / (float) this->m_fps));
}

void WebcamSourceElement::timeout()
{
    if (!this->m_webcam.isOpened())
        return;

    cv::Mat matFrame;

    // Capture a frame in cvMat format...
    this->m_webcam >> matFrame;

    // and convert it to QImage.
    QImage qtFrame((const uchar *)matFrame.data, matFrame.cols, matFrame.rows, QImage::Format_RGB888);

    this->m_curFrame = qtFrame.rgbSwapped();

    emit(oVideo(&this->m_curFrame));
}
