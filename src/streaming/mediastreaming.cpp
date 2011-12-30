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

/*!
  \class MediaStreaming

  \brief This class is used for record video and images.

  This class can record video with audio from post processed frames using
  FFmpeg.
  It can also record individual frames to a file, and controls the time between
  each frame capture.
 */

/*!
  \fn MediaStreaming::MediaStreaming(QObject *parent)

  \param parent Parent widget.
 */
MediaStreaming::MediaStreaming(QObject *parent): QObject(parent)
{
    this->recording = false;
    this->videoPipeFilename = QDir::tempPath() + QDir::separator() + "video_pipe.tmp";

    setFPS(19);
    this->currentFrame = QImage(640, 480, QImage::Format_RGB888);

    this->qtToFFmpegPixFMT[QImage::Format_Mono] = "monow";
    this->qtToFFmpegPixFMT[QImage::Format_RGB32] = "bgra";
    this->qtToFFmpegPixFMT[QImage::Format_ARGB32] = "bgra";
    this->qtToFFmpegPixFMT[QImage::Format_RGB16] = "rgb565le";
    this->qtToFFmpegPixFMT[QImage::Format_RGB888] = "rgb24";

    this->timerCapture.setInterval(1);
    connect(&this->timerCapture, SIGNAL(timeout()), this, SLOT(slotCaptureFrame()));
    timerCapture.start();

    connect(&this->timerRecord, SIGNAL(timeout()), this, SLOT(saveVideoFrame()));

    connect(&this->ffmpeg, SIGNAL(readyReadStandardError()), this, SLOT(showOutput()));
}

/*!
  \fn void MediaStreaming::startRecord()

  \brief Starts video recording.
 */
void MediaStreaming::startRecord()
{
    if (this->recording)
        return;

    QString filename = this->saveFile(videoFilters());

    if (filename == "")
        return;

    QFile::remove(this->videoPipeFilename);
    mkfifo(this->videoPipeFilename.toUtf8().constData(), 0644);

    this->ffmpeg.start("ffmpeg", this->outputParameters(filename));
    this->videoPipe.setFileName(this->videoPipeFilename);
    this->videoPipe.open(QIODevice::WriteOnly);
    this->outvideoStream.setDevice(&this->videoPipe);
    this->timerRecord.start();
    this->recording = true;
}

/*!
  \fn void MediaStreaming::stopRecord()

  \brief Stop video recording.
 */
void MediaStreaming::stopRecord()
{
    if (!this->recording)
        return;

    this->recording = false;
    this->ffmpeg.terminate();
    this->timerRecord.stop();
    this->videoPipe.close();
    QFile::remove(this->videoPipeFilename);
}

/*!
  \fn void MediaStreaming::startStopRecord()

  \brief Starts video recording, if already recording stop it.
 */
void MediaStreaming::startStopRecord()
{
    if (this->recording)
        stopRecord();
    else
        startRecord();
}

/*!
  \fn void MediaStreaming::takePicture()

  \brief Save the current frame to a image file.
 */
void MediaStreaming::takePicture()
{
    QImage image(this->currentFrame);
    QString filename = saveFile("PNG file (*.png)");

    if (filename != "")
        image.save(filename);
}

/*!
  \fn void MediaStreaming::setFrame(QImage frame)

  \param frame The video frame to be recorded.

  \brief Set the video frame to be recorded.
 */
void MediaStreaming::setFrame(QImage frame)
{
    this->currentFrame = frame;
}

/*!
  \internal

  \fn void MediaStreaming::saveVideoFrame()

  \brief Save the current frame to a video file.
 */
void MediaStreaming::saveVideoFrame()
{
    this->outvideoStream.writeRawData((const char *)this->currentFrame.constBits(), this->currentFrame.byteCount());
}

/*!
  \internal

  \fn QString MediaStreaming::saveFile(QString filters)

  \return Selected output file name.

  \param filters Output format filter

  \brief Show a save file dialog for the output file.
 */
QString MediaStreaming::saveFile(QString filters)
{
    QStringList selected_files;
    QFileDialog save_file_dialog(dynamic_cast<QWidget *>(parent()), "", ".", filters);

    save_file_dialog.setModal(true);
    save_file_dialog.setFileMode(QFileDialog::AnyFile);
    save_file_dialog.setAcceptMode(QFileDialog::AcceptSave);
    save_file_dialog.exec();

    selected_files = save_file_dialog.selectedFiles();

    return (selected_files.isEmpty())? QString(): selected_files.first();
}

/*!
  \internal

  \fn void MediaStreaming::slotCaptureFrame()

  \brief This slot is called when the internal timer reach the timeout state.

  This slot emits the captureFrame() signal indicating that a new frame must be captured.
 */
void MediaStreaming::slotCaptureFrame()
{
    emit captureFrame();
}

/*!
  \internal

  \fn void MediaStreaming::showOutput()

  \brief Show the output of FFmpeg.
 */
void MediaStreaming::showOutput()
{
    qDebug() << this->ffmpeg.readAllStandardError();
}

/*!
  \fn void MediaStreaming::addOutputFormat(const OutputFormat &outputformat)

  \param outputformat The new output format.

  \brief Add a new output format for video record.
 */
void MediaStreaming::addOutputFormat(const OutputFormat &outputformat)
{
    OutputFormat ncOutputformat(outputformat);

    this->outputFormats[ncOutputformat.suffix()] = outputformat;
}

/*!
  \internal

  \fn QStringList MediaStreaming::outputParameters(QString filename)

  \return Output parameters for FFmpeg.

  \param filename Output file name.

  \brief Get the best output parameters for FFmpeg from file name.
 */
QStringList MediaStreaming::outputParameters(QString filename)
{
    QStringList arguments;

    arguments << "-y" << "-f" << "rawvideo" << "-pix_fmt" << this->qtToFFmpegPixFMT[currentFrame.format()] << "-r" << QString::number(this->fps) << "-s" << QString("%1x%2").arg(this->currentFrame.width()).arg(this->currentFrame.height()) << "-i" << this->videoPipeFilename
                      << "-f" << "alsa" << "-ac" << "2" << "-i" << "hw:0"
                      << this->outputFormats[QFileInfo(filename).completeSuffix()].toStringList(this->fps, this->currentFrame.width(), this->currentFrame.height()) << filename;

    return arguments;
}

/*!
  \fn void MediaStreaming::setFPS(int fps)

  \param fps Frames Per Second.

  \brief Set the recording FPS.
 */
void MediaStreaming::setFPS(int fps)
{
    this->fps = fps;

    this->timerRecord.setInterval((int)round(1000.0f / (qreal)fps));
}

/*!
  \fn QStringList MediaStreaming::supportedSuffix()

  \return Supported suffixes.

  \brief Return the supported suffixes.
 */
QStringList MediaStreaming::supportedSuffix()
{
    return this->outputFormats.keys();
}

/*!
  \fn bool MediaStreaming::isRecording()

  \retval true if recording video.
  \retval false if not recording video.

  \brief Indicates if currently is recording video.
 */
bool MediaStreaming::isRecording()
{
    return this->recording;
}

/*!
  \internal

  \fn QString MediaStreaming::videoFilters()

  \return File filters.

  \brief Return the file filters for current output formats.
 */
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
