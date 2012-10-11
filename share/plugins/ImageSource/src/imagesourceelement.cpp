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

#include "imagesourceelement.h"

ImageSourceElement::ImageSourceElement()
{
    this->resetFileName();
}

void ImageSourceElement::iVideo(QImage *frame)
{
    Q_UNUSED(frame)
}

void ImageSourceElement::iAudio(QByteArray *frame)
{
    Q_UNUSED(frame)
}

bool ImageSourceElement::start()
{
    emit(oVideo(&this->m_image));

    return true;
}

bool ImageSourceElement::stop()
{
    return true;
}

void ImageSourceElement::configure()
{
}

void ImageSourceElement::setManager(QObject *manager)
{
    Q_UNUSED(manager)
}

QString ImageSourceElement::fileName()
{
    return this->m_fileName;
}

void ImageSourceElement::setFileName(QString fileSource)
{
    this->m_fileName = fileSource;
    this->m_image = QImage(this->m_fileName);
}

void ImageSourceElement::resetFileName()
{
    this->setFileName("");
}
