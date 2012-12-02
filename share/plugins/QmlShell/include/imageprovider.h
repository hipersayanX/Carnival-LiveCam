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

#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include <QtQuick>

class ImageProvider: public QObject, public QQuickImageProvider
{
    Q_OBJECT

    public:
        ImageProvider(QQuickImageProvider::ImageType type=QQuickImageProvider::Image,
                      QQuickImageProvider::Flags flags=QQmlImageProviderBase::ForceAsynchronousImageLoading);

        ~ImageProvider();

        QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);

    private:
        QImage m_frame;

    public slots:
        void setFrame(const QImage &frame);
};

#endif // IMAGEPROVIDER_H
