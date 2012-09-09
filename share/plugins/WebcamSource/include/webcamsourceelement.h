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

#ifndef WEBCAMSOURCEELEMENT_H
#define WEBCAMSOURCEELEMENT_H

#include <opencv2/opencv.hpp>

#include "element.h"

class WebcamSourceElement: public Element
{
    Q_OBJECT

    Q_PROPERTY(QString device READ device WRITE setDevice RESET resetDevice)
    Q_PROPERTY(QSize size READ size WRITE setSize RESET resetSize)
    Q_PROPERTY(int fps READ fps WRITE setFps RESET resetFps)

    public:
        WebcamSourceElement();
        QString device();
        QSize size();
        int fps();

    private:
        QString m_device;
        QSize m_size;
        int m_fps;
        cv::VideoCapture m_webcam;
        QTimer m_timer;
        QImage m_curFrame;

    signals:
        void fail();

    public slots:
        // Input Channels
        void iVideo(QImage *frame);
        void iAudio(QByteArray *frame);

        void start();
        void stop();

        void configure();

        void setPluginList(QList<QVariant> list);

        void setDevice(QString device);
        void setSize(QSize size);
        void setFps(int fps);
        void resetDevice();
        void resetSize();
        void resetFps();

    private slots:
        void timeout();
};

#endif // WEBCAMSOURCEELEMENT_H
