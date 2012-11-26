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

#ifndef VIDEOSOURCEELEMENT_H
#define VIDEOSOURCEELEMENT_H

#include <opencv2/opencv.hpp>

#include "element.h"

class VideoSourceElement: public Element
{
    Q_OBJECT
        Q_PROPERTY(QString fileName READ fileName WRITE setFileName RESET resetFileName)
        Q_PROPERTY(int fps READ fps WRITE setFps RESET resetFps)

    public:
        VideoSourceElement();
        QString fileName();
        int fps();

        Q_INVOKABLE bool start();
        Q_INVOKABLE bool stop();

    private:
        QString m_fileName;
        int m_fps;
        cv::VideoCapture m_video;
        QTimer m_timer;
        QByteArray m_curFrame;

        void imageToByteArray(QImage *image, QByteArray *ba);

    signals:
        void fail();

    public slots:
        // Input Channels
        void iStream(QByteArray *data);
        void iEvent(QEvent *event);
        void setPipeline(Pipeline *pipeline);
        void setPeers(QList<Element *> srcs, QList<Element *> sinks);

        void setFileName(QString fileName);
        void setFps(int fps);
        void resetFileName();
        void resetFps();

    private slots:
        void timeout();
};

#endif // VIDEOSOURCEELEMENT_H
