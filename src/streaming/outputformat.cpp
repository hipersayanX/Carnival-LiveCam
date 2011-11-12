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

#include "../../include/streaming/outputformat.h"

OutputFormat::OutputFormat(QObject *parent): QObject(parent)
{
}

OutputFormat::OutputFormat(const OutputFormat &object):
    QObject(object.parent()), suffix(object.suffix), vcodec(object.vcodec), vbitrate(object.vbitrate), acodec(object.acodec), abitrate(object.abitrate), oformat(object.oformat), sameq(object.sameq)
{
}

OutputFormat::OutputFormat(QString suffix, QString vcodec, int vbitrate, QString acodec, int abitrate, QString oformat, bool sameq):
    suffix(suffix), vcodec(vcodec), vbitrate(vbitrate), acodec(acodec), abitrate(abitrate), oformat(oformat), sameq(sameq)
{
}

OutputFormat& OutputFormat::operator =(const OutputFormat &other)
{
    if (this != &other)
    {
        this->suffix = other.suffix;
        this->vcodec = other.vcodec;
        this->vbitrate = other.vbitrate;
        this->acodec = other.acodec;
        this->abitrate = other.abitrate;
        this->oformat = other.oformat;
        this->sameq = other.sameq;
    }

    return *this;
}

QStringList OutputFormat::toStringList(int fps, int width, int height)
{
    QStringList arguments;

    arguments << "-vcodec" << vcodec << "-b" << QString::number(vbitrate) << "-r" << QString::number(fps) << "-s" << QString("%1x%2").arg(width).arg(height);

    if (sameq)
        arguments << "-sameq";

    arguments << "-acodec" << acodec << "-ab" << QString::number(abitrate)
              << "-f" << oformat;

    return arguments;
}
