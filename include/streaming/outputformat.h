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

#ifndef OUTPUTFORMAT_H
#define OUTPUTFORMAT_H

#include <QObject>
#include <QStringList>

class OutputFormat: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString suffix READ suffix WRITE setSuffix RESET resetSuffix)
    Q_PROPERTY(QString vcodec READ vcodec WRITE setVcodec RESET resetVcodec)
    Q_PROPERTY(qint32 vbitrate READ vbitrate WRITE setVbitrate RESET resetVbitrate)
    Q_PROPERTY(QString acodec READ acodec WRITE setAcodec RESET resetAcodec)
    Q_PROPERTY(qint32 abitrate READ abitrate WRITE setAbitrate RESET resetAbitrate)
    Q_PROPERTY(QString oformat READ oformat WRITE setOformat RESET resetOformat)
    Q_PROPERTY(bool sameq READ sameq WRITE setSameq RESET resetSameq)

    public:
        explicit OutputFormat(QObject *parent = 0);
        explicit OutputFormat(const OutputFormat &object);
        OutputFormat(QString suffix, QString vcodec, qint32 vbitrate, QString acodec, qint32 abitrate, QString oformat, bool sameq);
        OutputFormat& operator =(const OutputFormat &other);

        Q_INVOKABLE QStringList toStringList(qint32 fps, qint32 width, qint32 height);

        QString suffix();
        QString vcodec();
        qint32 vbitrate();
        QString acodec();
        qint32 abitrate();
        QString oformat();
        bool sameq();

    private:
        QString m_suffix;
        QString m_vcodec;
        qint32 m_vbitrate;
        QString m_acodec;
        qint32 m_abitrate;
        QString m_oformat;
        bool m_sameq;

    public slots:
        void setSuffix(QString value);
        void setVcodec(QString value);
        void setVbitrate(qint32 value);
        void setAcodec(QString value);
        void setAbitrate(qint32 value);
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
