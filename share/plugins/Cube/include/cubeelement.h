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

#ifndef CUBEELEMENT_H
#define CUBEELEMENT_H

#include "element.h"
#include "cubegl.h"

class CubeElement: public Element
{
    Q_OBJECT
    Q_PROPERTY(float xrot READ xrot WRITE setXrot RESET resetXrot)
    Q_PROPERTY(float yrot READ yrot WRITE setYrot RESET resetYrot)

    public:
        explicit CubeElement();
        float xrot();
        float yrot();

        Q_INVOKABLE bool start();
        Q_INVOKABLE bool stop();

    private:
        CubeGL m_ogl;
        QByteArray m_bImage;
        GLfloat m_xrot;
        GLfloat m_yrot;

        QImage byteArrayToImage(QByteArray *ba);
        void imageToByteArray(QImage *image, QByteArray *ba);

    public slots:
        // Input Channels
        void iStream(QByteArray *data);
        void iEvent(QEvent *event);
        void setPipeline(Pipeline *pipeline);
        void setPeers(QList<Element *> srcs, QList<Element *> sinks);

        void setXrot(float xrot);
        void setYrot(float yrot);
        void resetXrot();
        void resetYrot();
};

#endif // CUBEELEMENT_H
