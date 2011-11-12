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

    public:
        explicit QOSGWidget(QWidget *parent = 0);
        QImage webcam_image;

    private:
        float cow_rot;

        osg::ref_ptr<osgViewer::Viewer> viewer;
        osg::observer_ptr<osgViewer::GraphicsWindowEmbedded> window;
        osg::ref_ptr<osg::Node> loadedModel;
        osg::ref_ptr<osg::MatrixTransform> transformation;
        osg::ref_ptr<osg::Group> group;

        void initializeGL();
        void resizeGL(int width, int height);
        void paintGL();

        osg::ref_ptr<osg::TextureRectangle> convertQImageToOsgTexture(const QImage &qimage);
        osg::ref_ptr<osg::Geode> createWebcamFrameGeode(const QImage &image);
        osg::ref_ptr<osg::Camera> createOrthoCamera();
};

#endif // QOSGWIDGET_H
