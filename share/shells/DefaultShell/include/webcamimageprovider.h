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

#ifndef WEBCAMIMAGEPROVIDER_H
#define WEBCAMIMAGEPROVIDER_H

#include <QDeclarativeImageProvider>

class WebcamImageProvider: public QDeclarativeImageProvider
{
    public:
        WebcamImageProvider(QDeclarativeImageProvider::ImageType type=QDeclarativeImageProvider::Image);
        ~WebcamImageProvider();
        QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);
        void setFrame(const QImage &image);

    private:
        QImage frame;
};

#endif // WEBCAMIMAGEPROVIDER_H
