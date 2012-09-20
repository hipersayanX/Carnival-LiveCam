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

#ifndef MEDIARECORDER_H
#define MEDIARECORDER_H

#include "plugin.h"
#include "mediarecorderelement.h"

class MediaRecorder: public QObject, public Plugin
{
    Q_OBJECT
    Q_INTERFACES(Plugin)

    public:
        QString pluginId();
        QString name();
        QString version();
        QString summary();
        QString type();
        QString category();
        QString thumbnail();
        QString license();
        QString author();
        QString website();
        QString mail();
        bool isConfigurable();

        Element *newElement();

        ~MediaRecorder();
};

#endif // MEDIARECORDER_H
