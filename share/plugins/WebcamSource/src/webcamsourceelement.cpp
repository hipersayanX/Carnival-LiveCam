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

#include "webcamsourceelement.h"

WebcamSourceElement::WebcamSourceElement(): Element()
{
    QObject::connect(&this->m_timer, SIGNAL(timeout()), this, SLOT(timeout()));

    this->resetDevice();
    this->resetSize();
    this->resetFps();
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

void WebcamSourceElement::iStream(const void *data, int datalen, QString dataType)
{
    Q_UNUSED(data)
    Q_UNUSED(datalen)
    Q_UNUSED(dataType)
}

bool WebcamSourceElement::start()
{
    // Try to open webcam device,
    if (!this->m_webcam.open(QString(this->m_device).remove("/dev/video").toInt()))
    {
        emit(this->fail());

        return false;
    }

    this->m_timer.start();

    return true;
}

bool WebcamSourceElement::stop()
{
    if (this->m_timer.isActive())
    {
        this->m_timer.stop();
        this->m_webcam.release();
    }

    return true;
}

void WebcamSourceElement::setPipeline(Pipeline *pipeline)
{
    Q_UNUSED(pipeline)
}

void WebcamSourceElement::setPeers(QList<Element *> srcs, QList<Element *> sinks)
{
    Q_UNUSED(srcs)
    Q_UNUSED(sinks)
}

void WebcamSourceElement::setDevice(QString device)
{
    bool active = this->m_timer.isActive();

    if (active)
        this->stop();

    this->m_device = device;

    if (active && device != "")
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
    this->setDevice("/dev/video0");
}

void WebcamSourceElement::resetSize()
{
    this->setSize(QSize(640, 480));
}

void WebcamSourceElement::resetFps()
{
    this->setFps(30);
}

void WebcamSourceElement::timeout()
{
    if (!this->m_webcam.isOpened())
        return;

    cv::Mat matFrame;

    // Capture a frame in cvMat format...
    this->m_webcam >> matFrame;

    // and convert it to QImage.
    this->m_oFrame = QImage((const uchar *) matFrame.data,
                            matFrame.cols,
                            matFrame.rows,
                            QImage::Format_RGB888).rgbSwapped();

    emit(this->oStream((const void *) &this->m_oFrame, 0, "QImage"));
}
