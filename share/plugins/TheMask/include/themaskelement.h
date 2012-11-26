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

#ifndef THEMASKELEMENT_H
#define THEMASKELEMENT_H

#include <opencv2/opencv.hpp>

#include "element.h"

class TheMaskElement: public Element
{
    Q_OBJECT

    Q_PROPERTY(QString haarCascadeFile READ haarCascadeFile WRITE setHaarCascadeFile RESET resetHaarCascadeFile)
    Q_PROPERTY(QString sprite READ sprite WRITE setSprite RESET resetSprite)

    public:
        explicit TheMaskElement();

        QString haarCascadeFile();
        QString sprite();

        Q_INVOKABLE bool start();
        Q_INVOKABLE bool stop();

    private:
        QString m_haarCascadeFile;
        QString m_sprite;
        QByteArray m_curFrame;
        QImage m_maskImage;
        cv::CascadeClassifier m_cascadeClassifier;
        QList<Element *> m_srcs;
        QList<Element *> m_sinks;

        QImage byteArrayToImage(QByteArray *ba);
        void imageToByteArray(QImage *image, QByteArray *ba);

    public slots:
        void setHaarCascadeFile(QString haarCascadeFile);
        void setSprite(QString sprite);
        void resetHaarCascadeFile();
        void resetSprite();

        void iStream(QByteArray *data);
        void iEvent(QEvent *event);
        void setPipeline(Pipeline *pipeline);
        void setPeers(QList<Element *> srcs, QList<Element *> sinks);
};

#endif // THEMASKELEMENT_H
