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

#ifndef SPACE_H
#define SPACE_H

#include <QObject>
#include <QImage>

class Space: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QImage maskImage READ maskImage WRITE setMaskImage RESET resetMaskImage)
    Q_PROPERTY(QSize frameSize READ frameSize WRITE setFrameSize RESET resetFrameSize)

    public:
        explicit Space(QObject *parent = 0);
        Space(const Space &object);

        Space(QImage maskImage,
              QSize frameSize);

        Space& operator =(const Space &other);

        QImage maskImage();
        QSize frameSize();

    private:
        QImage m_maskImage;
        QSize m_frameSize;

    public slots:
        void setMaskImage(QImage value);
        void setFrameSize(QSize value);
        void resetMaskImage();
        void resetFrameSize();
};

#endif // SPACE_H
