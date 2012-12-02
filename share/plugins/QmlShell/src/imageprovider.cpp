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

#include "imageprovider.h"

ImageProvider::ImageProvider(QQuickImageProvider::ImageType type,
                             QQuickImageProvider::Flags flags):
    QQuickImageProvider(type, flags)
{
    this->m_frame = QImage(1, 1, QImage::Format_RGB888);
    this->m_frame.fill(0);
}

ImageProvider::~ImageProvider()
{
}

QImage ImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(id)

    *size = this->m_frame.size();

    if (requestedSize.isValid())
        return this->m_frame.scaled(requestedSize, Qt::IgnoreAspectRatio, Qt::FastTransformation);
    else
        return this->m_frame;
}

void ImageProvider::setFrame(const QImage &frame)
{
    this->m_frame = frame;
}
