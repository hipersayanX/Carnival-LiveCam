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

#include "../include/cube.h"

QString Cube::author()
{
    return "hipersayan_x";
}

QString Cube::mail()
{
    return "hipersayan.x@gmail.com";
}

QString Cube::website()
{
    return "hipersayanx.blogspot.com";
}

QString Cube::category()
{
    return "OpenGL";
}

QString Cube::id()
{
    return "videoplugin.Cube";
}

QString Cube::license()
{
    return "GPLv3";
}

QString Cube::name()
{
    return "Cube";
}

QString Cube::summary()
{
    return "Render the webcam image in a cube.";
}

QString Cube::thumbnail()
{
    return "../../../../../share/plugins/Cube/share/thumbnail-128x96.png";
}

bool Cube::is3D()
{
    return true;
}

QString Cube::version()
{
    return "1.0.0";
}

bool Cube::isConfigurable()
{
    return false;
}

void Cube::begin()
{
}

void Cube::addSpace(QString spaceId, QSize frameSize)
{
    this->glWidget[spaceId] = new OGL();
    this->glWidget[spaceId]->resize(frameSize);
}

void Cube::removeSpace(QString spaceId)
{
    delete this->glWidget[spaceId];
    this->glWidget.remove(spaceId);
}

QImage Cube::render(QString spaceId, const QImage &image)
{
    if (this->glWidget.contains(spaceId))
    {
        this->glWidget[spaceId]->setWebcamImage(image);

        return this->glWidget[spaceId]->renderPixmap(this->glWidget[spaceId]->width(),
                                                     this->glWidget[spaceId]->height()).toImage();
    }

    return image;
}

void Cube::end()
{
    QStringList spaces = this->glWidget.keys();

    foreach (QString spaceId, spaces)
        this->removeSpace(spaceId);
}

void Cube::configure()
{
}

QVariant Cube::configs()
{
    return QVariant();
}

void Cube::setConfigs(QVariant configs)
{
    Q_UNUSED(configs)
}

void Cube::mouseDoubleClickEvent(QString spaceId, QMouseEvent *event)
{
    if (this->glWidget.contains(spaceId))
        this->glWidget[spaceId]->mouseDoubleClick(event);
}

void Cube::mouseMoveEvent(QString spaceId, QMouseEvent *event)
{
    if (this->glWidget.contains(spaceId))
        this->glWidget[spaceId]->mouseMove(event);
}

void Cube::mousePressEvent(QString spaceId, QMouseEvent *event)
{
    if (this->glWidget.contains(spaceId))
        this->glWidget[spaceId]->mousePress(event);
}

void Cube::mouseReleaseEvent(QString spaceId, QMouseEvent *event)
{
    if (this->glWidget.contains(spaceId))
        this->glWidget[spaceId]->mouseRelease(event);
}

Q_EXPORT_PLUGIN2(Cube, Cube)
