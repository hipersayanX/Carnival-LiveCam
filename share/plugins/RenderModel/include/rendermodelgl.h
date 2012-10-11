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

#ifndef RENDERMODELGL_H
#define RENDERMODELGL_H

#include <QtOpenGL>

#include <osgViewer/Viewer>
#include <osg/MatrixTransform>
#include <osg/TextureRectangle>
#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>

class RenderModelGL: public QGLWidget
{
    Q_OBJECT

    Q_PROPERTY(QString modelFileName READ modelFileName WRITE setModelFileName RESET resetModelFileName)
    Q_PROPERTY(QImage image READ image WRITE setImage RESET resetImage)

    public:
        explicit RenderModelGL();
        QString modelFileName();
        QImage image();

    private:
        QString m_modelFileName;
        float m_rot;
        QImage m_image;

        osg::ref_ptr<osgViewer::Viewer> m_viewer;
        osg::observer_ptr<osgViewer::GraphicsWindowEmbedded> m_window;
        osg::ref_ptr<osg::Node> m_loadedModel;
        osg::ref_ptr<osg::MatrixTransform> m_transformation;
        osg::ref_ptr<osg::Group> m_group;

        void initializeGL();
        void resizeGL(qint32 width, qint32 height);
        void paintGL();

        osg::ref_ptr<osg::TextureRectangle> convertQImageToOsgTexture(const QImage &qimage);
        osg::ref_ptr<osg::Geode> createFrameGeode(const QImage &image);
        osg::ref_ptr<osg::Camera> createOrthoCamera();

    public slots:
        void setModelFileName(QString modelFileName);
        void setImage(const QImage &image);
        void resetModelFileName();
        void resetImage();
};

#endif // RENDERMODELGL_H
