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

#include "../include/defaultplugin.h"

QString DefaultPlugin::author()
{
    return "hipersayan_x";
}

QString DefaultPlugin::mail()
{
    return "hipersayan.x@gmail.com";
}

QString DefaultPlugin::website()
{
    return "hipersayanx.blogspot.com";
}

QString DefaultPlugin::category()
{
    return "OpenGL";
}

QString DefaultPlugin::id()
{
    return "videoplugin.DefaultPlugin";
}

QString DefaultPlugin::license()
{
    return "GPLv3";
}

QString DefaultPlugin::name()
{
    return "DefaultPlugin";
}

QString DefaultPlugin::summary()
{
    return "Default video plugin";
}

QString DefaultPlugin::thumbnail()
{
    return "../../../../../share/plugins/DefaultPlugin/share/thumbnail-128x96.png";
}

bool DefaultPlugin::is3D()
{
    return true;
}

QString DefaultPlugin::version()
{
    return "1.0.0";
}

bool DefaultPlugin::isConfigurable()
{
    return false;
}

void DefaultPlugin::begin()
{
}

void DefaultPlugin::addSpace(QString spaceId, QSize frameSize)
{
    this->glWidget[spaceId] = new QOSGWidget();
    this->glWidget[spaceId]->resize(frameSize);
}

void DefaultPlugin::removeSpace(QString spaceId)
{
    delete this->glWidget[spaceId];
    this->glWidget.remove(spaceId);
}

QImage DefaultPlugin::render(QString spaceId, const QImage &image)
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

void DefaultPlugin::end()
{
    QStringList spaces = this->glWidget.keys();

    foreach (QString spaceId, spaces)
        this->removeSpace(spaceId);
}

void DefaultPlugin::configure()
{
}

QVariant DefaultPlugin::configs()
{
    return QVariant();
}

void DefaultPlugin::setConfigs(QVariant configs)
{
    Q_UNUSED(configs)
}

void DefaultPlugin::mouseDoubleClickEvent(QString spaceId, QMouseEvent *event)
{
    Q_UNUSED(spaceId)
    Q_UNUSED(event)
}

void DefaultPlugin::mouseMoveEvent(QString spaceId, QMouseEvent *event)
{
    Q_UNUSED(spaceId)
    Q_UNUSED(event)
}

void DefaultPlugin::mousePressEvent(QString spaceId, QMouseEvent *event)
{
    Q_UNUSED(spaceId)
    Q_UNUSED(event)
}

void DefaultPlugin::mouseReleaseEvent(QString spaceId, QMouseEvent *event)
{
    Q_UNUSED(spaceId)
    Q_UNUSED(event)
}

Q_EXPORT_PLUGIN2(DefaultPlugin, DefaultPlugin)
