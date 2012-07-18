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

#ifndef QOSGWIDGET_H
#define QOSGWIDGET_H

#include <QGLWidget>
#include <osgViewer/Viewer>
#include <osg/MatrixTransform>
#include <osg/TextureRectangle>
#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>

class QOSGWidget: public QGLWidget
{
    Q_OBJECT

    Q_PROPERTY(QImage webcamImage READ webcamImage WRITE setWebcamImage RESET resetWebcamImage)

    public:
        explicit QOSGWidget(QWidget *parent = 0);
        QImage webcamImage();

    public slots:
        void setWebcamImage(const QImage &image);
        void resetWebcamImage();

    private:
        qreal cow_rot;
        QImage m_webcamImage;

        osg::ref_ptr<osgViewer::Viewer> viewer;
        osg::observer_ptr<osgViewer::GraphicsWindowEmbedded> window;
        osg::ref_ptr<osg::Node> loadedModel;
        osg::ref_ptr<osg::MatrixTransform> transformation;
        osg::ref_ptr<osg::Group> group;

        void initializeGL();
        void resizeGL(qint32 width, qint32 height);
        void paintGL();

        osg::ref_ptr<osg::TextureRectangle> convertQImageToOsgTexture(const QImage &qimage);
        osg::ref_ptr<osg::Geode> createWebcamFrameGeode(const QImage &image);
        osg::ref_ptr<osg::Camera> createOrthoCamera();
};

#endif // QOSGWIDGET_H
