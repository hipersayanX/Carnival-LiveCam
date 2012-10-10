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

#ifndef PLUGININFO_H
#define PLUGININFO_H

#include "plugin.h"

class PluginInfo: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString fileName READ fileName WRITE setFileName RESET resetFileName)
    Q_PROPERTY(QMap metaData READ metaData WRITE setMetaData RESET resetMetaData)

    public:
        explicit PluginInfo(QObject *parent = 0);
        PluginInfo(const PluginInfo &object);

        PluginInfo(QString fileName,
                   QMap<QString, QVariant> metaData);

        PluginInfo& operator =(const PluginInfo &other);

        Q_INVOKABLE QMap<QString, QVariant> toMap();

        QString fileName();
        QMap<QString, QVariant> metaData();

    private:
        QString m_fileName;
        QMap<QString, QVariant> m_metaData;

    public slots:
        void setFileName(QString fileName);
        void setMetaData(QMap<QString, QVariant> metaData);
        void resetFileName();
        void resetMetaData();
};

#endif // PLUGININFO_H
