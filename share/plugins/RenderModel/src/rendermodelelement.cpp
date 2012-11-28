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

void RenderModelElement::iStream(const void *data, int datalen, QString dataType)
{
    Q_UNUSED(datalen)

    if (dataType != "QImage")
        return;

    QImage *iFrame = (QImage *) data;

    this->m_ogl.resize(iFrame->size());
    this->m_ogl.setImage(*iFrame);

    this->m_oFrame = this->m_ogl.renderPixmap(this->m_ogl.width(),this->m_ogl.height()).toImage();

    emit(this->oStream((const void *) &this->m_oFrame, 0, dataType));
}

bool RenderModelElement::event(QEvent *event)
{
    foreach (Element *src, this->m_srcs)
        QCoreApplication::sendEvent(src, event);

    return false;
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
