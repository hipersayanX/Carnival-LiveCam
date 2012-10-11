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

#ifndef RENDERMODELELEMENT_H
#define RENDERMODELELEMENT_H

#include "element.h"
#include "rendermodelgl.h"

class RenderModelElement: public Element
{
    Q_OBJECT

    Q_PROPERTY(QString modelFileName READ modelFileName WRITE setModelFileName RESET resetModelFileName)

    public:
        explicit RenderModelElement();

        QString modelFileName();

        Q_INVOKABLE bool start();
        Q_INVOKABLE bool stop();

    private:
        QString m_modelFileName;
        RenderModelGL m_ogl;
        QImage m_image;

    public slots:
        // Input Channels
        void iVideo(QImage *frame);
        void iAudio(QByteArray *frame);

        void configure();
        void setManager(QObject *manager);

        void setModelFileName(QString modelFileName);
        void resetModelFileName();
};

#endif // RENDERMODELELEMENT_H
