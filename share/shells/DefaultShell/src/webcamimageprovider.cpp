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
 * QML shell plugin
 */

#include <QtDebug>

#include "../include/webcamimageprovider.h"

WebcamImageProvider::WebcamImageProvider(QDeclarativeImageProvider::ImageType type): QDeclarativeImageProvider(type)
{
    this->frame = QImage(1, 1, QImage::Format_RGB888);
    this->frame.fill(0);
}

WebcamImageProvider::~WebcamImageProvider()
{
}

QImage WebcamImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(id)

    *size = this->frame.size();

    if (requestedSize.isValid())
        return this->frame.scaled(requestedSize, Qt::IgnoreAspectRatio, Qt::FastTransformation);
    else
        return this->frame;
}

void WebcamImageProvider::setFrame(const QImage &image)
{
    this->frame = image;
}
