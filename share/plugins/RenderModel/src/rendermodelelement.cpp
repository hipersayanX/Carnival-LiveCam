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

#include "rendermodelelement.h"

RenderModelElement::RenderModelElement(): Element()
{
    this->resetModelFileName();
}

QString RenderModelElement::modelFileName()
{
    return this->m_modelFileName;
}

bool RenderModelElement::start()
{
    return true;
}

bool RenderModelElement::stop()
{
    return true;
}

QImage RenderModelElement::byteArrayToImage(QByteArray *ba)
{
    if (!ba)
        return QImage();

    QDataStream iDataStream(ba, QIODevice::ReadOnly);
    int type;

    iDataStream >> type;

    if (type != ARGB32)
        return QImage();

    int width;
    int height;

    iDataStream >> width >> height;

    QByteArray pixels(4 * width * height, 0);
    iDataStream.readRawData(pixels.data(), pixels.size());

    return QImage((const uchar *) pixels.constData(), width, height, QImage::Format_ARGB32);
}

void RenderModelElement::imageToByteArray(QImage *image, QByteArray *ba)
{
    if (!image || !ba)
        return;

    QDataStream oDataStream(ba, QIODevice::WriteOnly);

    oDataStream << ARGB32 << image->width() << image->height();
    oDataStream.writeRawData((const char *) image->constBits(), image->byteCount());
}

void RenderModelElement::iStream(QByteArray *data)
{
    QImage iFrame = this->byteArrayToImage(data);

    if (iFrame.isNull())
        return;

    this->m_ogl.resize(iFrame.size());
    this->m_ogl.setImage(iFrame);

    QImage image = this->m_ogl.renderPixmap(this->m_ogl.width(),this->m_ogl.height()).toImage();

    this->imageToByteArray(&image, &this->m_bImage);

    emit(oStream(&this->m_bImage));
}

void RenderModelElement::iEvent(QEvent *event)
{
    foreach (Element *element, this->m_srcs)
        element->iEvent(event);
}

void RenderModelElement::setPipeline(Pipeline *pipeline)
{
    Q_UNUSED(pipeline)
}

void RenderModelElement::setPeers(QList<Element *> srcs, QList<Element *> sinks)
{
    this->m_srcs = srcs;
    this->m_sinks = sinks;
}

void RenderModelElement::setModelFileName(QString modelFileName)
{
    this->m_modelFileName = modelFileName;
    this->m_ogl.setModelFileName(modelFileName);
}

void RenderModelElement::resetModelFileName()
{
    this->setModelFileName("share/plugins/RenderModel/share/data/cow.osg");
}
