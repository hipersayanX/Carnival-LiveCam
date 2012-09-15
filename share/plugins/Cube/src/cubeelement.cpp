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

#include "include/cubeelement.h"

CubeElement::CubeElement(): Element()
{
    this->m_ogl = NULL;
    this->m_xrot = 30.0f;
    this->m_yrot = 60.0f;
}

void CubeElement::mouseMove(QMouseEvent *event)
{
    if (this->m_ogl)
        this->m_ogl->mouseMove(event);
}

void CubeElement::mousePress(QMouseEvent *event)
{
    if (this->m_ogl)
        this->m_ogl->mousePress(event);
}

void CubeElement::mouseRelease(QMouseEvent *event)
{
    if (this->m_ogl)
        this->m_ogl->mouseRelease(event);
}

void CubeElement::iVideo(QImage *frame)
{
    if (!this->m_ogl)
        return;

    this->m_ogl->resize(frame->size());
    this->m_ogl->setImage(*frame);
    this->m_image = this->m_ogl->renderPixmap(this->m_ogl->width(),this->m_ogl->height()).toImage();

    emit(oVideo(&this->m_image));
}

void CubeElement::iAudio(QByteArray *frame)
{
    Q_UNUSED(frame)
}

bool CubeElement::start()
{
    this->m_ogl = new OGL();

    if (!this->m_ogl)
        return false;

    QObject::connect(this->m_ogl, SIGNAL(xrotChanged(float)), this, SLOT(setXrot(float)));
    QObject::connect(this->m_ogl, SIGNAL(yrotChanged(float)), this, SLOT(setYrot(float)));

    return true;
}

bool CubeElement::stop()
{
    if (!this->m_ogl)
        return true;

    QObject::disconnect(this->m_ogl, SIGNAL(xrotChanged(float)), this, SLOT(setXrot(float)));
    QObject::disconnect(this->m_ogl, SIGNAL(yrotChanged(float)), this, SLOT(setYrot(float)));
    delete this->m_ogl;

    return true;
}

void CubeElement::configure()
{
}

void CubeElement::setManager(QObject *manager)
{
    Q_UNUSED(manager)
}

float CubeElement::xrot()
{
    return this->m_xrot;
}

float CubeElement::yrot()
{
    return this->m_yrot;
}

void CubeElement::setXrot(float xrot)
{
    this->m_xrot = xrot;

    if (this->m_ogl)
        this->m_ogl->setXrot(xrot);
}

void CubeElement::setYrot(float yrot)
{
    this->m_yrot = yrot;

    if (this->m_ogl)
        this->m_ogl->setYrot(yrot);
}

void CubeElement::resetXrot()
{
    this->setXrot(30.0f);
}

void CubeElement::resetYrot()
{
    this->setYrot(60.0f);
}
