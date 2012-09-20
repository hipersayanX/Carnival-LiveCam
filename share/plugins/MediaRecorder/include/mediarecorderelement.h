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

#ifndef MEDIARECORDERELEMENT_H
#define MEDIARECORDERELEMENT_H

#include "element.h"

#include "outputformat.h"

class MediaRecorderElement: public Element
{
    Q_OBJECT

    public:
        explicit MediaRecorderElement();

        Q_INVOKABLE bool start();
        Q_INVOKABLE bool stop();

        Q_INVOKABLE void setFPS(qint32 fps);
        Q_INVOKABLE void addOutputFormat(const OutputFormat &outputformat);
        Q_INVOKABLE QStringList supportedSuffix();
        Q_INVOKABLE bool isRecording();

    private:
        qint32 fps;
        bool recording;
        QTimer timerCapture;
        QTimer timerRecord;
        QImage currentFrame;
        QFile videoPipe;
        QDataStream outvideoStream;
        QString videoPipeFilename;
        QProcess ffmpeg;
        QHash<QString, OutputFormat> outputFormats;
        QHash<qint32, QString> qtToFFmpegPixFMT;

        QString saveFile(QString filters);
        QStringList outputParameters(QString filename);
        QString videoFilters();

    signals:
        void captureFrame();

    public slots:
        // Input Channels
        void iVideo(QImage *frame);
        void iAudio(QByteArray *frame);

        void configure();
        void setManager(QObject *manager);

        void startRecord();
        void stopRecord();
        void startStopRecord();
        void takePicture();
        void setFrame(QImage frame);

    private slots:
        void saveVideoFrame();
        void slotCaptureFrame();
        void showOutput();
};

#endif // MEDIARECORDERELEMENT_H
