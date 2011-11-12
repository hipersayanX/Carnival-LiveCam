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

#include <QFileDialog>
#include <QDebug>

#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "../../include/streaming/mediastreaming.h"

MediaStreaming::MediaStreaming(QObject *parent): QObject(parent)
{
    recording = false;
    videoPipeFilename = QDir::tempPath() + QDir::separator() + "video_pipe.tmp";

    setFPS(19);
    currentFrame = QImage(640, 480, QImage::Format_RGB888);

    qtToFFmpegPixFMT[QImage::Format_Mono] = "monow";
    qtToFFmpegPixFMT[QImage::Format_RGB32] = "bgra";
    qtToFFmpegPixFMT[QImage::Format_ARGB32] = "bgra";
    qtToFFmpegPixFMT[QImage::Format_RGB16] = "rgb565le";
    qtToFFmpegPixFMT[QImage::Format_RGB888] = "rgb24";

    timerCapture.setInterval(1);
    connect(&timerCapture, SIGNAL(timeout()), this, SLOT(slotCaptureFrame()));
    timerCapture.start();

    connect(&timerRecord, SIGNAL(timeout()), this, SLOT(saveVideoFrame()));

    connect(&ffmpeg, SIGNAL(readyReadStandardError()), this, SLOT(showOutput()));
}

void MediaStreaming::startRecord()
{
    QString filename = saveFile(videoFilters());

    if (filename == "")
        return;

    QFile::remove(videoPipeFilename);
    mkfifo(videoPipeFilename.toUtf8().constData(), 0644);

    ffmpeg.start("ffmpeg", outputParameters(filename));
    videoPipe.setFileName(videoPipeFilename);
    videoPipe.open(QIODevice::WriteOnly);
    outvideoStream.setDevice(&videoPipe);
    timerRecord.start();
    recording = true;
}

void MediaStreaming::stopRecord()
{
    recording = false;
    ffmpeg.terminate();
    timerRecord.stop();
    videoPipe.close();
    QFile::remove(videoPipeFilename);
}

void MediaStreaming::startStopRecord()
{
    if (recording)
        stopRecord();
    else
        startRecord();
}

void MediaStreaming::takePicture()
{
    QImage image(currentFrame);
    QString filename = saveFile("PNG file (*.png)");

    if (filename != "")
        image.save(filename);
}

void MediaStreaming::setFrame(QImage frame)
{
    currentFrame = frame;
}

void MediaStreaming::saveVideoFrame()
{
    outvideoStream.writeRawData((const char *)currentFrame.constBits(), currentFrame.byteCount());
}

QString MediaStreaming::saveFile(QString filters)
{
    QStringList selected_files;
    QFileDialog save_file_dialog(dynamic_cast<QWidget *>(parent()), "", ".", filters);

    save_file_dialog.setModal(true);
    save_file_dialog.setFileMode(QFileDialog::AnyFile);
    save_file_dialog.setAcceptMode(QFileDialog::AcceptSave);
    save_file_dialog.exec();

    selected_files = save_file_dialog.selectedFiles();

    if (!selected_files.isEmpty())
        return selected_files.first();
    else
        return QString();
}

void MediaStreaming::slotCaptureFrame()
{
    emit captureFrame();
}

void MediaStreaming::showOutput()
{
    qDebug() << ffmpeg.readAllStandardError();
}

void MediaStreaming::addOutputFormat(const OutputFormat &outputformat)
{
    outputFormats[outputformat.suffix] = outputformat;
}

QStringList MediaStreaming::outputParameters(QString filename)
{
    QStringList arguments;

    arguments << "-y" << "-f" << "rawvideo" << "-pix_fmt" << qtToFFmpegPixFMT[currentFrame.format()] << "-r" << QString::number(fps) << "-s" << QString("%1x%2").arg(currentFrame.width()).arg(currentFrame.height()) << "-i" << videoPipeFilename
                      << "-f" << "alsa" << "-ac" << "2" << "-i" << "hw:0"
                      << outputFormats[QFileInfo(filename).completeSuffix()].toStringList(fps, currentFrame.width(), currentFrame.height()) << filename;

    return arguments;
}

void MediaStreaming::setFPS(int fps)
{
    this->fps = fps;

    timerRecord.setInterval((int)round(1000.0f / (float)fps));
}

QStringList MediaStreaming::supportedSuffix()
{
    return outputFormats.keys();
}

bool MediaStreaming::isRecording()
{
    return recording;
}

QString MediaStreaming::videoFilters()
{
    QString filters;
    bool fst = true;

    foreach (QString suffix, supportedSuffix())
    {
        if (fst)
            fst = false;
        else
            filters += ";;";

        filters += suffix.toUpper() + " file (*." + suffix + ")";
    }

    return filters;
}
