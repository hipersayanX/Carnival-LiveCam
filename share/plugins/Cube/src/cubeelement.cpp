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

void CubeElement::iStream(const void *data, int datalen, QString dataType)
{
    Q_UNUSED(datalen)

    if (dataType != "QImage")
        return;

    QImage *iFrame = (QImage *) data;

    this->m_ogl.resize(iFrame->size());
    this->m_ogl.setImage(*iFrame);

    this->m_oFrame = this->m_ogl.renderPixmap(this->m_ogl.width(),this->m_ogl.height()).toImage();

    emit this->oStream((const void *) &this->m_oFrame, 0, dataType);
}

bool CubeElement::event(QEvent *event)
{
    switch (event->type())
    {
        case QEvent::MouseMove:
            this->m_ogl.mouseMove(static_cast<QMouseEvent *>(event));

            return true;
        break;

        case QEvent::MouseButtonPress:
            this->m_ogl.mousePress(static_cast<QMouseEvent *>(event));

            return true;
        break;

        case QEvent::MouseButtonRelease:
            this->m_ogl.mouseRelease(static_cast<QMouseEvent *>(event));

            return true;
        break;

        default:
            foreach (Element *src, this->m_srcs)
                QCoreApplication::sendEvent(src, event);

            return false;
    }
}

void CubeElement::setPipeline(Pipeline *pipeline)
{
    Q_UNUSED(pipeline)
}

void CubeElement::setPeers(QList<Element *> srcs, QList<Element *> sinks)
{
    this->m_srcs = srcs;
    this->m_sinks = sinks;
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
