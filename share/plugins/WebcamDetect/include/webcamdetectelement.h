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

    Q_PROPERTY(QString devicesPath READ devicesPath WRITE setDevicesPath RESET resetDevicesPath)

    public:
        WebcamDetectElement();
        QString devicesPath();
        Q_INVOKABLE bool start();
        Q_INVOKABLE bool stop();

    private:
        QFileSystemWatcher *m_fsWatcher;
        QList<QStringList> m_webcams;
        QString m_devicesPath;

        QList<QStringList> webcams(QString dir);
        template <typename T>  QList<T> substractList(QList<T> a, QList<T> b);

    signals:
        void webcamsUpdated(QList<QStringList> webcams);
        void webcamsAdded(QList<QStringList> webcams);
        void webcamsRemoved(QList<QStringList> webcams);

    public slots:
        // Input Channels
        void iStream(const void *data, int datalen, QString dataType);
        void setPipeline(Pipeline *pipeline);
        void setPeers(QList<Element *> srcs, QList<Element *> sinks);

        void updateWebcams();

        void setDevicesPath(QString devicesPath);
        void resetDevicesPath();

    private slots:
        void devicesChanged(QString path);
};

#endif // WEBCAMDETECTELEMENT_H
