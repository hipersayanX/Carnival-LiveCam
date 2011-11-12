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
 */

#ifndef MEDIASTREAMING_H
#define MEDIASTREAMING_H

#include <QObject>
#include <QImage>
#include <QTimer>
#include <QFile>
#include <QProcess>
#include <QHash>

#include "outputformat.h"

class MediaStreaming: public QObject
{
    Q_OBJECT

    public:
        explicit MediaStreaming(QObject *parent = 0);

        void setFPS(int fps);
        void addOutputFormat(const OutputFormat &outputformat);
        QStringList supportedSuffix();
        bool isRecording();

    signals:
        void captureFrame();

    public slots:
        void startRecord();
        void stopRecord();
        void startStopRecord();
        void takePicture();
        void setFrame(QImage frame);

    private:
        int fps;
        bool recording;
        QTimer timerCapture;
        QTimer timerRecord;
        QImage currentFrame;
        QFile videoPipe;
        QDataStream outvideoStream;
        QString videoPipeFilename;
        QProcess ffmpeg;
        QHash<QString, OutputFormat> outputFormats;
        QHash<int, QString> qtToFFmpegPixFMT;

        QString saveFile(QString filters);
        QStringList outputParameters(QString filename);
        QString videoFilters();

    private slots:
        void saveVideoFrame();
        void slotCaptureFrame();
        void showOutput();
};

#endif // MEDIASTREAMING_H
