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

#include "../include/thecow.h"

QString TheCow::author()
{
    return "hipersayan_x";
}

QString TheCow::mail()
{
    return "hipersayan.x@gmail.com";
}

QString TheCow::website()
{
    return "hipersayanx.blogspot.com";
}

QString TheCow::category()
{
    return "OpenGL";
}

QString TheCow::id()
{
    return "videoplugin.TheCow";
}

QString TheCow::license()
{
    return "GPLv3";
}

QString TheCow::name()
{
    return "The Cow";
}

QString TheCow::summary()
{
    return "This plugin shows a cow 3D model";
}

QString TheCow::thumbnail()
{
    return "../../../../../share/plugins/DefaultPlugin/share/thumbnail-128x96.png";
}

bool TheCow::is3D()
{
    return true;
}

QString TheCow::version()
{
    return "1.0.0";
}

bool TheCow::isConfigurable()
{
    return false;
}

void TheCow::begin()
{
}

void TheCow::addSpace(QString spaceId, QSize frameSize)
{
    this->glWidget[spaceId] = new QOSGWidget();
    this->glWidget[spaceId]->resize(frameSize);
}

void TheCow::removeSpace(QString spaceId)
{
    delete this->glWidget[spaceId];
    this->glWidget.remove(spaceId);
}

QImage TheCow::render(QString spaceId, const QImage &image)
{
    if (this->glWidget.contains(spaceId))
    {
        this->glWidget[spaceId]->setWebcamImage(image);

        return this->glWidget[spaceId]->renderPixmap(this->glWidget[spaceId]->width(),
                                                     this->glWidget[spaceId]->height(),
                                                     true).toImage();
    }

    return image;
}

void TheCow::end()
{
    QStringList spaces = this->glWidget.keys();

    foreach (QString spaceId, spaces)
        this->removeSpace(spaceId);
}

void TheCow::configure()
{
}

QVariant TheCow::configs()
{
    return QVariant();
}

void TheCow::setConfigs(QVariant configs)
{
    Q_UNUSED(configs)
}

void TheCow::mouseDoubleClickEvent(QString spaceId, QMouseEvent *event)
{
    Q_UNUSED(spaceId)
    Q_UNUSED(event)
}

void TheCow::mouseMoveEvent(QString spaceId, QMouseEvent *event)
{
    Q_UNUSED(spaceId)
    Q_UNUSED(event)
}

void TheCow::mousePressEvent(QString spaceId, QMouseEvent *event)
{
    Q_UNUSED(spaceId)
    Q_UNUSED(event)
}

void TheCow::mouseReleaseEvent(QString spaceId, QMouseEvent *event)
{
    Q_UNUSED(spaceId)
    Q_UNUSED(event)
}

Q_EXPORT_PLUGIN2(TheCow, TheCow)
