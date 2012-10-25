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

#ifndef IMAGESOURCEELEMENT_H
#define IMAGESOURCEELEMENT_H

#include "element.h"

class ImageSourceElement: public Element
{
    Q_OBJECT

    Q_PROPERTY(QString fileName READ fileName WRITE setFileName RESET resetFileName)

    public:
        ImageSourceElement();
        QString fileName();

        Q_INVOKABLE bool start();
        Q_INVOKABLE bool stop();

    private:
        QString m_fileName;
        QByteArray m_bImage;

        void imageToByteArray(QImage *image, QByteArray *ba);

    public slots:
        // Input Channels
        void iStream(QByteArray *data);

        void setPipeline(Pipeline *pipeline);

        void setFileName(QString fileName);
        void resetFileName();
};

#endif // IMAGESOURCEELEMENT_H
