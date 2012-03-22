/*
 * Carnival LiveCam, Augmented reality made easy.
 * Copyright (C) 2011  Gonzalo Exequiel Pedone
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with This program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Email   : hipersayan DOT x AT gmail DOT com
 * Web-Site: http://hipersayanx.blogspot.com/
 *
 * OpenSceneGraph test plugin
 */

#ifndef OGL_H
#define OGL_H

#include <QtOpenGL>

class OGL: public QGLWidget
{
    Q_OBJECT

    Q_PROPERTY(QImage webcamImage READ webcamImage WRITE setWebcamImage RESET resetWebcamImage)

    public:
        explicit OGL(QWidget *parent = 0);
        QImage webcamImage();

    public slots:
        void setWebcamImage(const QImage &image);
        void resetWebcamImage();

    private:
        QImage m_webcamImage;
        GLfloat xrot; /* X Rotation ( NEW ) */
        GLfloat yrot; /* Y Rotation ( NEW ) */
        GLfloat zrot; /* Z Rotation ( NEW ) */

        void initializeGL();
        void resizeGL(qint32 width, qint32 height);
        void paintGL();
};

#endif // OGL_H
