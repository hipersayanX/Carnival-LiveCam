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

#ifndef OUTPUTFORMAT_H
#define OUTPUTFORMAT_H

#include <QObject>
#include <QStringList>

class OutputFormat: public QObject
{
    Q_OBJECT

    public:
        QString suffix;

        QString vcodec;
        int vbitrate;

        QString acodec;
        int abitrate;

        QString oformat;
        bool sameq;

        explicit OutputFormat(QObject *parent = 0);
        explicit OutputFormat(const OutputFormat &object);
        OutputFormat(QString suffix, QString vcodec, int vbitrate, QString acodec, int abitrate, QString oformat, bool sameq);
        OutputFormat& operator =(const OutputFormat &other);

        QStringList toStringList(int fps, int width, int height);
};

#endif // OUTPUTFORMAT_H
