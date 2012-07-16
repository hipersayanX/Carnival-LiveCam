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

#include "../../include/streaming/outputformat.h"

/*!
  \class OutputFormat

  \brief Video output format descriptor.

  This class is used for store video output format parameters.
 */

/*!
  \fn OutputFormat::OutputFormat(QObject *parent): QObject(parent)

  \param parent Parent widget.
 */
OutputFormat::OutputFormat(QObject *parent): QObject(parent)
{
    this->m_suffix = "";
    this->m_vcodec = "";
    this->m_vbitrate = 0;
    this->m_acodec = "";
    this->m_abitrate = 0;
    this->m_oformat = "";
    this->m_sameq = false;
}

/*!
  \fn OutputFormat::OutputFormat(const OutputFormat &object)

  \param object Another OutputFormat object.
 */
OutputFormat::OutputFormat(const OutputFormat &object):
    QObject(object.parent()),
    m_suffix(object.m_suffix),
    m_vcodec(object.m_vcodec),
    m_vbitrate(object.m_vbitrate),
    m_acodec(object.m_acodec),
    m_abitrate(object.m_abitrate),
    m_oformat(object.m_oformat),
    m_sameq(object.m_sameq)
{
}

/*!
  \fn OutputFormat::OutputFormat(QString suffix,
                                 QString vcodec,
                                 qint32 vbitrate,
                                 QString acodec,
                                 qint32 abitrate,
                                 QString oformat,
                                 bool sameq)

  \param suffix The name of the output format.
  \param vcodec Video codec.
  \param vbitrate Video bitrate.
  \param acodec Audio codec.
  \param abitrate Audio bitrate.
  \param oformat Output format, i.e.: ogv, webm, etc..
  \param sameq Use -sameq parameter for ffmpeg. Increases FPS at expense of losing quality.
 */
OutputFormat::OutputFormat(QString suffix,
                           QString vcodec,
                           qint32 vbitrate,
                           QString acodec,
                           qint32 abitrate,
                           QString oformat,
                           bool sameq):
    m_suffix(suffix),
    m_vcodec(vcodec),
    m_vbitrate(vbitrate),
    m_acodec(acodec),
    m_abitrate(abitrate),
    m_oformat(oformat),
    m_sameq(sameq)
{
}

/*!
  \fn OutputFormat& OutputFormat::operator =(const OutputFormat &other)

  \param other Another OutputFormat object.
 */
OutputFormat& OutputFormat::operator =(const OutputFormat &other)
{
    if (this != &other)
    {
        this->m_suffix = other.m_suffix;
        this->m_vcodec = other.m_vcodec;
        this->m_vbitrate = other.m_vbitrate;
        this->m_acodec = other.m_acodec;
        this->m_abitrate = other.m_abitrate;
        this->m_oformat = other.m_oformat;
        this->m_sameq = other.m_sameq;
    }

    return *this;
}

/*!
  \fn QStringList OutputFormat::toStringList(qint32 fps, qint32 width, qint32 height)

  \param fps Frames Per Second.
  \param width Width of the output frame.
  \param height Height of the output frame.

  \return Returns a string list of output parameters.
 */
QStringList OutputFormat::toStringList(qint32 fps, qint32 width, qint32 height)
{
    QStringList arguments;

    arguments << "-vcodec" << this->m_vcodec
              << "-b" << QString::number(this->m_vbitrate)
              << "-r" << QString::number(fps)
              << "-s" << QString("%1x%2").arg(width).arg(height);

    if (this->m_sameq)
        arguments << "-sameq";

    arguments << "-acodec" << this->m_acodec << "-ab" << QString::number(this->m_abitrate)
              << "-f" << this->m_oformat;

    return arguments;
}

/*!
  \property OutputFormat::suffix

  \brief The name of the output format.
 */
QString OutputFormat::suffix()
{
    return this->m_suffix;
}

/*!
  \property OutputFormat::vcodec

  \brief Video codec.
 */
QString OutputFormat::vcodec()
{
    return this->m_vcodec;
}

/*!
  \property OutputFormat::vbitrate

  \brief Video bitrate.
 */
qint32 OutputFormat::vbitrate()
{
    return this->m_vbitrate;
}

/*!
  \property OutputFormat::acodec

  \brief Audio codec.
 */
QString OutputFormat::acodec()
{
    return this->m_acodec;
}

/*!
  \property OutputFormat::abitrate

  \brief Audio bitrate.
 */
qint32 OutputFormat::abitrate()
{
    return this->m_abitrate;
}

/*!
  \property OutputFormat::oformat

  \brief Output format.
 */
QString OutputFormat::oformat()
{
    return this->m_oformat;
}

/*!
  \property OutputFormat::sameq

  \brief Use \b -sameq parameter for FFmpeg.
 */
bool OutputFormat::sameq()
{
    return this->m_sameq;
}

/*!
  \fn void OutputFormat::setSuffix(QString value)

  \param value The output format suffix.

  \brief Set the output format suffix.
 */
void OutputFormat::setSuffix(QString value)
{
    this->m_suffix = value;
}

/*!
  \fn void OutputFormat::setVcodec(QString value)

  \param value Video codec.

  \brief Set the video codec.
 */
void OutputFormat::setVcodec(QString value)
{
    this->m_vcodec = value;
}

/*!
  \fn void OutputFormat::setVbitrate(qint32 value)

  \param value Video bitrate.

  \brief Set the video bitrate.
 */
void OutputFormat::setVbitrate(qint32 value)
{
    this->m_vbitrate = value;
}

/*!
  \fn void OutputFormat::setAcodec(QString value)

  \param value Audio codec.

  \brief Set the audio codec.
 */
void OutputFormat::setAcodec(QString value)
{
    this->m_acodec = value;
}

/*!
  \fn void OutputFormat::setAbitrate(qint32 value)

  \param value Audio bitrate.

  \brief Set the audio bitrate.
 */
void OutputFormat::setAbitrate(qint32 value)
{
    this->m_abitrate = value;
}

/*!
  \fn void OutputFormat::setOformat(QString value)

  \param value Output format.

  \brief Set the output format.
 */
void OutputFormat::setOformat(QString value)
{
    this->m_oformat = value;
}

/*!
  \fn void OutputFormat::setSameq(bool value)

  \param value \b true if use -sameq, else \b false.

  \brief Set -sameq parameter for ffmpeg.
 */
void OutputFormat::setSameq(bool value)
{
    this->m_sameq = value;
}

/*!
  \fn void OutputFormat::resetSuffix()

  \brief Reset OutputFormat::suffix to "".
 */
void OutputFormat::resetSuffix()
{
    this->m_suffix = "";
}

/*!
  \fn void OutputFormat::resetVcodec()

  \brief Reset OutputFormat::vcodec to "".
 */
void OutputFormat::resetVcodec()
{
    this->m_vcodec = "";
}

/*!
  \fn void OutputFormat::resetVbitrate()

  \brief Reset OutputFormat::vbitrate to 0.
 */
void OutputFormat::resetVbitrate()
{
    this->m_vbitrate = 0;
}

/*!
  \fn void OutputFormat::resetAcodec()

  \brief Reset OutputFormat::acodec to "".
 */
void OutputFormat::resetAcodec()
{
    this->m_acodec = "";
}

/*!
  \fn void OutputFormat::resetAbitrate()

  \brief Reset OutputFormat::abitrate to 0.
 */
void OutputFormat::resetAbitrate()
{
    this->m_abitrate = 0;
}

/*!
  \fn void OutputFormat::resetOformat()

  \brief Reset OutputFormat::oformat to "".
 */
void OutputFormat::resetOformat()
{
    this->m_oformat = "";
}

/*!
  \fn void OutputFormat::resetSameq()

  \brief Reset OutputFormat::sameq to false.
 */
void OutputFormat::resetSameq()
{
    this->m_sameq = false;
}
