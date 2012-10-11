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

#include "videosourceelement.h"

VideoSourceElement::VideoSourceElement()
{
    QObject::connect(&this->m_timer, SIGNAL(timeout()), this, SLOT(timeout()));

    this->resetFileName();
    this->resetFps();
}

QString VideoSourceElement::fileName()
{
    return this->m_fileName;
}

int VideoSourceElement::fps()
{
    return this->m_fps;
}

void VideoSourceElement::iVideo(QImage *frame)
{
    Q_UNUSED(frame)
}

void VideoSourceElement::iAudio(QByteArray *frame)
{
    Q_UNUSED(frame)
}

bool VideoSourceElement::start()
{
    if (!this->m_video.open(this->m_fileName.toUtf8().constData()))
    {
        emit(fail());

        return false;
    }

    this->m_timer.start();

    return true;
}

bool VideoSourceElement::stop()
{
    if (this->m_timer.isActive())
    {
        this->m_timer.stop();
        this->m_video.release();
    }

    return true;
}

void VideoSourceElement::configure()
{
}

void VideoSourceElement::setManager(QObject *manager)
{
    Q_UNUSED(manager)
}

void VideoSourceElement::setFileName(QString fileName)
{
    bool active = this->m_timer.isActive();

    if (active)
        this->stop();

    this->m_fileName = fileName;

    if (active && fileName != "")
        this->start();
}

void VideoSourceElement::setFps(int fps)
{
    this->m_fps = fps;

    this->m_timer.setInterval((int)(1000.0 / (float) this->m_fps));
}

void VideoSourceElement::resetFileName()
{
    this->setFileName("");
}

void VideoSourceElement::resetFps()
{
    this->setFps(30);
}

void VideoSourceElement::timeout()
{
    if (!this->m_video.isOpened())
        return;

    cv::Mat matFrame;

    // Capture a frame in cvMat format...
    this->m_video >> matFrame;

    // and convert it to QImage.
    QImage qtFrame((const uchar *)matFrame.data, matFrame.cols, matFrame.rows, QImage::Format_RGB888);

    this->m_curFrame = qtFrame.rgbSwapped();

    emit(oVideo(&this->m_curFrame));
}
