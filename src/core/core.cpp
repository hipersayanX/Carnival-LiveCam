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

#include <cmath>
#include <QWidget>
#include <QtDebug>

#include "core/core.h"

/// \class Core
///
/// \brief Main core class.
///
/// This class manages and initialice the DeviceManager, ShellManager,
/// PluginManager and MediaStreaming modules.

/// \fn Core::Core(QObject *parent)
///
/// \param parent Parent widget.
Core::Core(QObject *parent): QObject(parent)
{
    this->pluginManager.setPipeline("WebcamDetect ! " \
                                    "WebcamSource device=/dev/video0 size=size(640, 480) fps=30 ! " \
                                    "MediaRecorder");
}
