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

#ifndef OGL_H
#define OGL_H

#include <QtOpenGL>
#include <QTime>

class OGL: public QGLWidget
{
    Q_OBJECT

    Q_PROPERTY(QImage webcamImage READ webcamImage WRITE setWebcamImage RESET resetWebcamImage)

    public:
        explicit OGL(QWidget *parent = 0);
        QImage webcamImage();

    public slots:
        void mouseDoubleClick(QMouseEvent *event);
        void mouseMove(QMouseEvent *event);
        void mousePress(QMouseEvent *event);
        void mouseRelease(QMouseEvent *event);

    public slots:
        void setWebcamImage(const QImage &image);
        void resetWebcamImage();

    private:
        QImage m_webcamImage;
        bool m_mousePressed;
        QPoint m_mousePos0;
        GLfloat m_xrot;
        GLfloat m_yrot;

        void initializeGL();
        void resizeGL(qint32 width, qint32 height);
        void paintGL();
};

#endif // OGL_H
