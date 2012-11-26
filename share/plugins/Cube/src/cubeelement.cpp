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

#include "cubeelement.h"

CubeElement::CubeElement(): Element()
{
    this->m_xrot = 30.0f;
    this->m_yrot = 60.0f;
}

float CubeElement::xrot()
{
    return this->m_xrot;
}

float CubeElement::yrot()
{
    return this->m_yrot;
}

bool CubeElement::start()
{
    QObject::connect(&this->m_ogl, SIGNAL(xrotChanged(float)), this, SLOT(setXrot(float)));
    QObject::connect(&this->m_ogl, SIGNAL(yrotChanged(float)), this, SLOT(setYrot(float)));

    return true;
}

bool CubeElement::stop()
{
    QObject::disconnect(&this->m_ogl, SIGNAL(xrotChanged(float)), this, SLOT(setXrot(float)));
    QObject::disconnect(&this->m_ogl, SIGNAL(yrotChanged(float)), this, SLOT(setYrot(float)));

    return true;
}

QImage CubeElement::byteArrayToImage(QByteArray *ba)
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

void CubeElement::imageToByteArray(QImage *image, QByteArray *ba)
{
    if (!image || !ba)
        return;

    QDataStream oDataStream(ba, QIODevice::WriteOnly);

    oDataStream << ARGB32 << image->width() << image->height();
    oDataStream.writeRawData((const char *) image->constBits(), image->byteCount());
}

void CubeElement::iStream(QByteArray *data)
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

void CubeElement::iEvent(QEvent *event)
{
    switch (event->type())
    {
        case QEvent::MouseMove:
            this->m_ogl.mouseMove(static_cast<QMouseEvent *>(event));
        break;

        case QEvent::MouseButtonPress:
            this->m_ogl.mousePress(static_cast<QMouseEvent *>(event));
        break;

        case QEvent::MouseButtonRelease:
            this->m_ogl.mouseRelease(static_cast<QMouseEvent *>(event));
        break;

        default:
        break;
    }
}

void CubeElement::setPipeline(Pipeline *pipeline)
{
    Q_UNUSED(pipeline)
}

void CubeElement::setPeers(QList<Element *> srcs, QList<Element *> sinks)
{
    Q_UNUSED(srcs)
    Q_UNUSED(sinks)
}

void CubeElement::setXrot(float xrot)
{
    this->m_xrot = xrot;
    this->m_ogl.setXrot(xrot);
}

void CubeElement::setYrot(float yrot)
{
    this->m_yrot = yrot;
    this->m_ogl.setYrot(yrot);
}

void CubeElement::resetXrot()
{
    this->setXrot(30.0f);
}

void CubeElement::resetYrot()
{
    this->setYrot(60.0f);
}
