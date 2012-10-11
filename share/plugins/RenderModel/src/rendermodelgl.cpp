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

#include "rendermodelgl.h"

RenderModelGL::RenderModelGL(): QGLWidget()
{
    this->m_viewer = new osgViewer::Viewer;

    this->m_viewer->getCamera()->setClearMask(GL_DEPTH_BUFFER_BIT);
    this->m_viewer->setCameraManipulator(new osgGA::TrackballManipulator);

    this->m_rot = 0;

    this->resetModelFileName();
    this->resetImage();
}

QString RenderModelGL::modelFileName()
{
    return this->m_modelFileName;
}

QImage RenderModelGL::image()
{
    return this->m_image;
}

void RenderModelGL::initializeGL()
{
    if (this->m_window.valid())
        this->m_window->releaseContext();

    this->m_window = this->m_viewer->setUpViewerAsEmbeddedInWindow(0, 0, width(), height());
}

void RenderModelGL::resizeGL(qint32 width, qint32 height)
{
    if (this->m_window.valid())
    {
        this->m_window->resized(this->m_window->getTraits()->x, this->m_window->getTraits()->y, width, height);

        this->m_window->getEventQueue()->windowResize(this->m_window->getTraits()->x,
                                                      this->m_window->getTraits()->y,
                                                      width,
                                                      height);
    }
}

void RenderModelGL::paintGL()
{
    this->m_group  = new osg::Group;

    this->m_transformation = new osg::MatrixTransform;
    this->m_transformation->setMatrix(osg::Matrix::rotate(this->m_rot, 0, 0, 1));
    this->m_transformation->addChild(this->m_loadedModel.get());
    this->m_group->addChild(this->m_transformation.get());

    osg::ref_ptr<osg::Geode> frameGeode = createFrameGeode(this->m_image);
    osg::ref_ptr<osg::Camera> orthoCamera = createOrthoCamera();
    orthoCamera->addChild(frameGeode.get());
    this->m_group->addChild(orthoCamera.get());

    this->m_viewer->setSceneData(this->m_group.get());

    this->m_rot += 0.1;

    if (this->m_viewer.valid())
        this->m_viewer->frame();
}

osg::ref_ptr<osg::TextureRectangle> RenderModelGL::convertQImageToOsgTexture(const QImage &qimage)
{
    osg::ref_ptr<osg::Image> image = new osg::Image;

    image->setImage(qimage.width(),
                    qimage.height(),
                    1,
                    GL_RGB,
                    GL_RGB,
                    GL_UNSIGNED_BYTE,
                    (unsigned char *)qimage.bits(),
                    osg::Image::NO_DELETE,
                    1);

    osg::ref_ptr<osg::TextureRectangle> texture = new osg::TextureRectangle(image.get());
    texture->setResizeNonPowerOfTwoHint(false);
    texture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR);
    texture->setWrap(osg::Texture::WRAP_S, osg::Texture::CLAMP_TO_EDGE);
    texture->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP_TO_EDGE);

    return texture;
}

osg::ref_ptr<osg::Geode> RenderModelGL::createFrameGeode(const QImage &image)
{
    osg::ref_ptr<osg::TextureRectangle> frameTexture = convertQImageToOsgTexture(image);
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    osg::ref_ptr<osg::StateSet> stateset = geode->getOrCreateStateSet();
    stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

    osg::ref_ptr<osg::Geometry> geom = osg::createTexturedQuadGeometry(osg::Vec3(),
                                                                       osg::Vec3(width(), 0.0f, 0.0f),
                                                                       osg::Vec3(0.0f, height(), 0.0f),
                                                                       0.0f, height(), width(), 0.0f);

    geom->getOrCreateStateSet()->setTextureAttributeAndModes(0, frameTexture, osg::StateAttribute::ON);
    geode->addDrawable(geom.get());

    return geode;
}

osg::ref_ptr<osg::Camera> RenderModelGL::createOrthoCamera()
{
    osg::ref_ptr<osg::Camera> orthoCamera = new osg::Camera;

    orthoCamera->setProjectionMatrix(osg::Matrix::ortho2D(0, width(), 0, height()));
    orthoCamera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
    orthoCamera->setViewMatrix(osg::Matrix::identity());
    orthoCamera->setClearMask(GL_DEPTH_BUFFER_BIT);
    orthoCamera->setRenderOrder(osg::Camera::PRE_RENDER);
    orthoCamera->setAllowEventFocus(false);

    return orthoCamera;
}

void RenderModelGL::setModelFileName(QString modelFileName)
{
    this->m_modelFileName = modelFileName;
    this->m_loadedModel = osgDB::readNodeFile(modelFileName.toUtf8().constData());
}

void RenderModelGL::setImage(const QImage &image)
{
    this->m_image = image;
}

void RenderModelGL::resetModelFileName()
{
    this->setModelFileName("");
}

void RenderModelGL::resetImage()
{
    this->setImage(QImage());
}
