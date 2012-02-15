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

#include "../include/qosgwidget.h"

QOSGWidget::QOSGWidget(QWidget *parent): QGLWidget(parent)
{
    viewer = new osgViewer::Viewer;

    loadedModel = osgDB::readNodeFile("share/plugins/DefaultPlugin/share/data/cow.osg");

    viewer->getCamera()->setClearMask(GL_DEPTH_BUFFER_BIT);
    viewer->setCameraManipulator(new osgGA::TrackballManipulator);

    cow_rot = 0;
}

void QOSGWidget::initializeGL()
{
    if (window.valid())
        window->releaseContext();

    window = viewer->setUpViewerAsEmbeddedInWindow(0, 0, width(), height());
}

void QOSGWidget::resizeGL(qint32 width, qint32 height)
{
    if (window.valid())
    {
        window->resized(window->getTraits()->x, window->getTraits()->y, width, height);
        window->getEventQueue()->windowResize(window->getTraits()->x, window->getTraits()->y, width, height);
    }
}

void QOSGWidget::paintGL()
{
    group  = new osg::Group;

    transformation = new osg::MatrixTransform;
    transformation->setMatrix(osg::Matrix::rotate(cow_rot, 0, 0, 1));
    transformation->addChild(loadedModel.get());
    group->addChild(transformation.get());

    osg::ref_ptr<osg::Geode> webcam_geode = createWebcamFrameGeode(webcam_image);
    osg::ref_ptr<osg::Camera> ortho_camera = createOrthoCamera();
    ortho_camera->addChild(webcam_geode.get());
    group->addChild(ortho_camera.get());

    viewer->setSceneData(group.get());

    cow_rot += 0.1;

    if (viewer.valid())
        viewer->frame();
}

osg::ref_ptr<osg::TextureRectangle> QOSGWidget::convertQImageToOsgTexture(const QImage &qimage)
{
    osg::ref_ptr<osg::Image> image = new osg::Image;
    image->setImage(qimage.width(), qimage.height(), 1, GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, (unsigned char *)qimage.bits(), osg::Image::NO_DELETE, 1);

    osg::ref_ptr<osg::TextureRectangle> texture = new osg::TextureRectangle(image.get());
    texture->setResizeNonPowerOfTwoHint(false);
    texture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR);
    texture->setWrap(osg::Texture::WRAP_S, osg::Texture::CLAMP_TO_EDGE);
    texture->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP_TO_EDGE);

    return texture;
}

osg::ref_ptr<osg::Geode> QOSGWidget::createWebcamFrameGeode(const QImage &image)
{
    osg::ref_ptr<osg::TextureRectangle> webcam_frame_texture = convertQImageToOsgTexture(image);
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    osg::ref_ptr<osg::StateSet> stateset = geode->getOrCreateStateSet();
    stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

    osg::ref_ptr<osg::Geometry> geom = osg::createTexturedQuadGeometry(
                osg::Vec3(),
                osg::Vec3(width(), 0.0f, 0.0f),
                osg::Vec3(0.0f, height(), 0.0f),
                0.0f, height(), width(), 0.0f
            );

    geom->getOrCreateStateSet()->setTextureAttributeAndModes(0, webcam_frame_texture, osg::StateAttribute::ON);
    geode->addDrawable(geom.get());

    return geode;
}

osg::ref_ptr<osg::Camera> QOSGWidget::createOrthoCamera()
{
    osg::ref_ptr<osg::Camera> ortho_camera = new osg::Camera;

    ortho_camera->setProjectionMatrix(osg::Matrix::ortho2D(0, width(), 0, height()));
    ortho_camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
    ortho_camera->setViewMatrix(osg::Matrix::identity());
    ortho_camera->setClearMask(GL_DEPTH_BUFFER_BIT);
    ortho_camera->setRenderOrder(osg::Camera::PRE_RENDER);
    ortho_camera->setAllowEventFocus(false);

    return ortho_camera;
}

