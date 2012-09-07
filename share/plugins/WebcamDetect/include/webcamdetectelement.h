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

#ifndef WEBCAMDETECTELEMENT_H
#define WEBCAMDETECTELEMENT_H

#include <QFileSystemWatcher>

#include "element.h"

class WebcamDetectElement: public Element
{
    Q_OBJECT

    public:
        QVariant configs();

    signals:
        void webcamsUpdated(QList<QStringList> webcams);
        void webcamsAdded(QList<QStringList> webcams);
        void webcamsRemoved(QList<QStringList> webcams);

    public slots:
        // Input Channels
        void iVideo(QImage *frame);
        void iAudio(QByteArray *frame);

        void begin();
        void end();

        void configure();
        void setConfigs(const QVariant &configs);
        void resetConfigs();

        void setPluginList(QList<QVariant> list);

        void updateWebcams();

    private slots:
        void devicesChanged(QString path);

    private:
        QFileSystemWatcher *m_fsWatcher;
        QList<QStringList> m_webcams;
        QString m_devicesPath;

        QList<QStringList> webcams(QString dir);
        template <typename T>  QList<T> substractList(QList<T> a, QList<T> b);
};

#endif // WEBCAMDETECTELEMENT_H
