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

class MediaRecorderElement: public Element
{
    Q_OBJECT
        Q_PROPERTY(QMap videoFormats READ videoFormats WRITE setVideoFormats RESET resetVideoFormats)
        Q_PROPERTY(int fps READ fps WRITE setFps RESET resetFps)
        Q_PROPERTY(QSize size READ size WRITE setSize RESET resetSize)
        Q_PROPERTY(bool recordAudio READ recordAudio WRITE setRecordAudio RESET resetRecordAudio)
        Q_PROPERTY(QString ffmpegPath READ ffmpegPath WRITE setFfmpegPath RESET resetFfmpegPath)
        Q_PROPERTY(bool showOutput READ showOutput WRITE setShowOutput RESET resetShowOutput)
        Q_PROPERTY(bool recording READ recording)

    public:
        explicit MediaRecorderElement();

        QMap<QString, QVariant> videoFormats();
        int fps();
        QSize size();
        bool recordAudio();
        QString ffmpegPath();
        bool showOutput();
        bool recording();

        Q_INVOKABLE bool start();
        Q_INVOKABLE bool stop();

    private:
        QMap<QString, QVariant> m_videoFormats;
        int m_fps;
        QSize m_size;
        bool m_recordAudio;
        QString m_ffmpegPath;
        bool m_showOutput;
        bool m_recording;

        QImage m_currentFrame;
        QFile m_videoPipe;
        QDataStream m_outvideoStream;
        QString m_videoPipeFilename;
        QProcess m_ffmpeg;

    signals:
        void fail();

    public slots:
        // Input Channels
        void iVideo(QImage *frame);
        void iAudio(QByteArray *frame);
        void configure();
        void setManager(QObject *manager);

        void setVideoFormats(QMap<QString, QVariant> videoFormats);
        void setFps(int fps);
        void setSize(QSize size);
        void setRecordAudio(bool recordAudio);
        void setFfmpegPath(QString ffmpegPath);
        void setShowOutput(bool showOutput);
        void resetVideoFormats();
        void resetFps();
        void resetSize();
        void resetRecordAudio();
        void resetFfmpegPath();
        void resetShowOutput();

        void startRecord(QString fileName);
        void stopRecord();
        void savePicture(QString fileName);

    private slots:
        void ffmpegOutput();
};

#endif // MEDIARECORDERELEMENT_H
