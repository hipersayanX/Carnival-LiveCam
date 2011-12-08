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

    Q_PROPERTY(QString suffix READ suffix WRITE setSuffix RESET resetSuffix)
    Q_PROPERTY(QString vcodec READ vcodec WRITE setVcodec RESET resetVcodec)
    Q_PROPERTY(int vbitrate READ vbitrate WRITE setVbitrate RESET resetVbitrate)
    Q_PROPERTY(QString acodec READ acodec WRITE setAcodec RESET resetAcodec)
    Q_PROPERTY(int abitrate READ abitrate WRITE setAbitrate RESET resetAbitrate)
    Q_PROPERTY(QString oformat READ oformat WRITE setOformat RESET resetOformat)
    Q_PROPERTY(bool sameq READ sameq WRITE setSameq RESET resetSameq)

    public:
        explicit OutputFormat(QObject *parent = 0);
        explicit OutputFormat(const OutputFormat &object);
        OutputFormat(QString suffix, QString vcodec, int vbitrate, QString acodec, int abitrate, QString oformat, bool sameq);
        OutputFormat& operator =(const OutputFormat &other);

        Q_INVOKABLE QStringList toStringList(int fps, int width, int height);

        QString suffix();
        QString vcodec();
        int vbitrate();
        QString acodec();
        int abitrate();
        QString oformat();
        bool sameq();

    private:
        QString m_suffix;
        QString m_vcodec;
        int m_vbitrate;
        QString m_acodec;
        int m_abitrate;
        QString m_oformat;
        bool m_sameq;

    public slots:
        void setSuffix(QString value);
        void setVcodec(QString value);
        void setVbitrate(int value);
        void setAcodec(QString value);
        void setAbitrate(int value);
        void setOformat(QString value);
        void setSameq(bool value);
        void resetSuffix();
        void resetVcodec();
        void resetVbitrate();
        void resetAcodec();
        void resetAbitrate();
        void resetOformat();
        void resetSameq();
};

#endif // OUTPUTFORMAT_H
