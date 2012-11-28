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

void ImageSourceElement::iStream(const void *data, int datalen, QString dataType)
{
    Q_UNUSED(data)
    Q_UNUSED(datalen)
    Q_UNUSED(dataType)
}

bool ImageSourceElement::start()
{
    emit(this->oStream((const void *) &this->m_oFrame, 0, "QImage"));

    return true;
}

bool ImageSourceElement::stop()
{
    return true;
}

void ImageSourceElement::setPipeline(Pipeline *pipeline)
{
    Q_UNUSED(pipeline)
}

void ImageSourceElement::setPeers(QList<Element *> srcs, QList<Element *> sinks)
{
    Q_UNUSED(srcs)
    Q_UNUSED(sinks)
}

QString ImageSourceElement::fileName()
{
    return this->m_fileName;
}

void ImageSourceElement::setFileName(QString fileSource)
{
    this->m_fileName = fileSource;
    this->m_oFrame = QImage(this->m_fileName);
}

void ImageSourceElement::resetFileName()
{
    this->setFileName("");
}
