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

#include <sys/types.h>
#include <sys/stat.h>

#include "mediarecorderelement.h"

MediaRecorderElement::MediaRecorderElement(): Element()
{
    this->resetVideoFormats();
    this->resetFps();
    this->resetSize();
    this->resetRecordAudio();
    this->resetFfmpegPath();
    this->resetShowOutput();
}

QMap<QString, QVariant> MediaRecorderElement::videoFormats()
{
    return this->m_videoFormats;
}

int MediaRecorderElement::fps()
{
    return this->m_fps;
}

QSize MediaRecorderElement::size()
{
    return this->m_size;
}

bool MediaRecorderElement::recordAudio()
{
    return this->m_recordAudio;
}

QString MediaRecorderElement::ffmpegPath()
{
    return this->m_ffmpegPath;
}

bool MediaRecorderElement::showOutput()
{
    return this->m_showOutput;
}

bool MediaRecorderElement::recording()
{
    return this->m_recording;
}

bool MediaRecorderElement::start()
{
    this->m_recording = false;
    this->m_videoPipeFilename = QString("%1%2%3").arg(QDir::tempPath()).arg(QDir::separator()).arg("video_pipe.tmp");

    connect(&this->m_ffmpeg, SIGNAL(readyReadStandardError()), this, SLOT(ffmpegOutput()));

    return true;
}

bool MediaRecorderElement::stop()
{
    disconnect(&this->m_ffmpeg, SIGNAL(readyReadStandardError()), this, SLOT(ffmpegOutput()));

    return true;
}

QImage MediaRecorderElement::byteArrayToImage(QByteArray *ba)
{
    if (!ba)
        return QImage();

    QDataStream iDataStream(ba, QIODevice::ReadOnly);
    int type;

    iDataStream >> type;

    if (type != ARGB32)
        return QImage();

    int width;
    int height;

    iDataStream >> width >> height;

    QByteArray pixels(4 * width * height, 0);
    iDataStream.readRawData(pixels.data(), pixels.size());

    return QImage((const uchar *) pixels.constData(), width, height, QImage::Format_ARGB32);
}

void MediaRecorderElement::iStream(QByteArray *data)
{
    QImage iFrame = this->byteArrayToImage(data);

    if (iFrame.isNull())
        return;

    this->m_currentFrame = QImage(this->m_size, QImage::Format_RGB888);
    this->m_currentFrame.fill(QColor(0, 0, 0));

    QImage scaledFrame(iFrame.scaled(this->m_size, Qt::KeepAspectRatio));
    QPoint point((this->m_size.width() - scaledFrame.width()) >> 1,
                 (this->m_size.height() - scaledFrame.height()) >> 1);

    QPainter painter;

    painter.begin(&this->m_currentFrame);
    painter.drawImage(point, scaledFrame);
    painter.end();

    this->m_outvideoStream.writeRawData((const char *)this->m_currentFrame.constBits(), this->m_currentFrame.byteCount());
}

void MediaRecorderElement::iEvent(QEvent *event)
{
    Q_UNUSED(event)
}

void MediaRecorderElement::setPipeline(Pipeline *pipeline)
{
    Q_UNUSED(pipeline)
}

void MediaRecorderElement::setPeers(QList<Element *> srcs, QList<Element *> sinks)
{
    Q_UNUSED(srcs)
    Q_UNUSED(sinks)
}

void MediaRecorderElement::setVideoFormats(QMap<QString, QVariant> videoFormats)
{
    this->m_videoFormats.clear();

    foreach (QString key, videoFormats.keys())
        this->m_videoFormats[key.toLower()] = videoFormats[key];
}

void MediaRecorderElement::setFps(int fps)
{
    this->m_fps = fps;
}

void MediaRecorderElement::setSize(QSize size)
{
    this->m_size = size;
}

void MediaRecorderElement::setRecordAudio(bool recordAudio)
{
    this->m_recordAudio = recordAudio;
}

void MediaRecorderElement::setFfmpegPath(QString ffmpegPath)
{
    this->m_ffmpegPath = ffmpegPath;
}

void MediaRecorderElement::setShowOutput(bool showOutput)
{
    this->m_showOutput = showOutput;
}

void MediaRecorderElement::resetVideoFormats()
{
    QMap<QString, QVariant> videoFormats;

    videoFormats["webm"] = "-vcodec libvpx " \
                           "-b:v 500000 " \
                           "-r %fps " \
                           "-s %size " \
                           "-acodec libvorbis " \
                           "-b:a 128000 " \
                           "-f webm";

    videoFormats["ogv"] = "-vcodec libtheora " \
                          "-b:v 500000 " \
                          "-r %fps " \
                          "-s %size " \
                          "-acodec libvorbis " \
                          "-b:a 128000 " \
                          "-f ogg";

    videoFormats["ogg"] = videoFormats["ogv"];

    this->setVideoFormats(videoFormats);
}

void MediaRecorderElement::resetFps()
{
    this->setFps(30);
}

void MediaRecorderElement::resetSize()
{
    this->setSize(QSize(640, 480));
}

void MediaRecorderElement::resetRecordAudio()
{
    this->setRecordAudio(true);
}

void MediaRecorderElement::resetFfmpegPath()
{
    this->setFfmpegPath("/usr/bin/ffmpeg");
}

void MediaRecorderElement::resetShowOutput()
{
    this->setShowOutput(false);
}

void MediaRecorderElement::startRecord(QString fileName)
{
    this->stopRecord();

    if (fileName == "")
        return;

    QString ext = fileName.mid(fileName.lastIndexOf(".")).toLower();

    if (!this->m_videoFormats.contains(ext))
        return;

    QStringList args;

    args << "-y"
         << "-f" << "rawvideo"
         << "-pix_fmt" << "rgb24"
         << "-r" << QString("%1").arg(this->m_fps)
         << "-s" << QString("%1x%2").arg(this->m_size.width()).arg(this->m_size.height())
         << "-i" << this->m_videoPipeFilename;

    if (this->m_recordAudio)
    {
        // PulseAudio
        if (QFile::exists("/usr/bin/pulseaudio"))
            args << "-f" << "alsa"
                 << "-ac" << "2"
                 << "-i" << "pulse";
        // Alsa
        else if (QFile::exists("/proc/asound/version"))
            args << "-f" << "alsa"
                 << "-ac" << "2"
                 << "-i" << "hw:0";
        // OSS
        else if (QFile::exists("/dev/dsp"))
            args << "-f" << "oss"
                 << "-ac" << "2"
                 << "-i" << "/dev/dsp";
    }

    QString outArgs = this->m_videoFormats[ext].toString() \
                                               .replace("%fps", QString("%1").arg(this->m_fps)) \
                                               .replace("%size", QString("%1x%2").arg(this->m_size.width()) \
                                                                                 .arg(this->m_size.height()));

    args << outArgs.split(" ", QString::SkipEmptyParts)
         << fileName;

    QFile::remove(this->m_videoPipeFilename);
    mkfifo(this->m_videoPipeFilename.toUtf8().constData(), 0644);
    this->m_ffmpeg.start(this->m_ffmpegPath, args);
    this->m_videoPipe.setFileName(this->m_videoPipeFilename);
    this->m_videoPipe.open(QIODevice::WriteOnly);
    this->m_outvideoStream.setDevice(&this->m_videoPipe);
    this->m_recording = true;
}

void MediaRecorderElement::stopRecord()
{
    if (!this->m_recording)
        return;

    this->m_recording = false;
    this->m_ffmpeg.terminate();
    this->m_videoPipe.close();
    QFile::remove(this->m_videoPipeFilename);
}

void MediaRecorderElement::savePicture(QString fileName)
{
    if (fileName != "")
        this->m_currentFrame.save(fileName);
}

/*!
  \internal

  \fn void MediaStreaming::showOutput()

  \brief Show the output of FFmpeg.
 */
void MediaRecorderElement::ffmpegOutput()
{
    if (this->m_showOutput)
        qDebug() << this->m_ffmpeg.readAllStandardError();
}
