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

#include "../include/qosgwidget.h"

QOSGWidget::QOSGWidget(QWidget *parent): QGLWidget(parent)
{
    this->viewer = new osgViewer::Viewer;

    this->loadedModel = osgDB::readNodeFile("share/plugins/DefaultPlugin/share/data/cow.osg");

    this->viewer->getCamera()->setClearMask(GL_DEPTH_BUFFER_BIT);
    this->viewer->setCameraManipulator(new osgGA::TrackballManipulator);

    this->cow_rot = 0;
}

QImage QOSGWidget::webcamImage()
{
    return this->m_webcamImage;
}

void QOSGWidget::setWebcamImage(const QImage &image)
{
    this->m_webcamImage = image;
}

void QOSGWidget::resetWebcamImage()
{
    this->m_webcamImage = QImage();
}

void QOSGWidget::initializeGL()
{
    if (this->window.valid())
        this->window->releaseContext();

    this->window = this->viewer->setUpViewerAsEmbeddedInWindow(0, 0, width(), height());
}

void QOSGWidget::resizeGL(qint32 width, qint32 height)
{
    if (this->window.valid())
    {
        this->window->resized(this->window->getTraits()->x, this->window->getTraits()->y, width, height);
        this->window->getEventQueue()->windowResize(this->window->getTraits()->x, this->window->getTraits()->y, width, height);
    }
}

void QOSGWidget::paintGL()
{
    this->group  = new osg::Group;

    this->transformation = new osg::MatrixTransform;
    this->transformation->setMatrix(osg::Matrix::rotate(this->cow_rot, 0, 0, 1));
    this->transformation->addChild(this->loadedModel.get());
    this->group->addChild(this->transformation.get());

    osg::ref_ptr<osg::Geode> webcam_geode = createWebcamFrameGeode(this->m_webcamImage);
    osg::ref_ptr<osg::Camera> ortho_camera = createOrthoCamera();
    ortho_camera->addChild(webcam_geode.get());
    this->group->addChild(ortho_camera.get());

    this->viewer->setSceneData(this->group.get());

    this->cow_rot += 0.1;

    if (this->viewer.valid())
        this->viewer->frame();
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
