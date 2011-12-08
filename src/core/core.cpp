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

#include <QWidget>

#include "../../include/core/core.h"

/*!
  \class Core

  \brief Main core class.

  This class manages and initialice the DeviceManager, ShellManager,
  PluginManager and MediaStreaming modules.
*/

/*!
  \fn Core::Core(QObject *parent)

  \param parent Parent widget.
 */
Core::Core(QObject *parent): QObject(parent)
{
    this->shellManager.setShell();
    this->deviceManager.setDevice();
    this->pluginManager.resize(this->deviceManager.frameSize());

    connect(&this->deviceManager, SIGNAL(devicesModified()), this, SLOT(devicesModified()));

    this->shellManager.widget()->show();

    this->shellManager.updateDevices(this->deviceManager.devicesToQml());
    this->shellManager.updatePlugins(this->pluginManager.pluginsToQml());

    connect(&this->shellManager, SIGNAL(deviceSelected(QString)), this, SLOT(deviceSelected(QString)));

    this->mediaStreaming.setFPS(10);
    this->mediaStreaming.addOutputFormat(OutputFormat("ogv", "libtheora", 500000, "libvorbis", 128000, "ogg", false));
    this->mediaStreaming.addOutputFormat(OutputFormat("webm", "libvpx", 500000, "libvorbis", 128000, "webm", false));

    connect(&this->shellManager, SIGNAL(pluginActivated(QString)), &this->pluginManager, SLOT(enablePlugin(QString)));
    connect(&this->shellManager, SIGNAL(pluginDeactivated(QString)), &this->pluginManager, SLOT(disablePlugin(QString)));
    connect(&this->shellManager, SIGNAL(pluginMoved(int, int)), &this->pluginManager, SLOT(movePlugin(int, int)));
    connect(&this->shellManager, SIGNAL(pluginConfigureClicked(QString)), &this->pluginManager, SLOT(configurePlugin(QString)));

    connect(&this->shellManager, SIGNAL(takePicture()), &this->mediaStreaming, SLOT(takePicture()));
    connect(&this->shellManager, SIGNAL(startStopRecord()), &this->mediaStreaming, SLOT(startStopRecord()));

    connect(&this->shellManager, SIGNAL(deviceConfigureClicked(QString)), &this->deviceManager, SLOT(configure(QString)));

    connect(&this->mediaStreaming, SIGNAL(captureFrame()), this, SLOT(captureFrame()));
}

/*!
  \internal

  \fn void Core::devicesModified()

  This slot is called when a device is added or removed.
 */
void Core::devicesModified()
{
    this->shellManager.updateDevices(this->deviceManager.devicesToQml());
}

/*!
  \internal

  \fn void Core::deviceSelected(QString deviceId)

  \param deviceId The unique device identifier.

  This slot is called when the user select a device to be used to capture from.
 */
void Core::deviceSelected(QString deviceId)
{
    this->deviceManager.setDevice(deviceId);
    this->pluginManager.resize(this->deviceManager.frameSize());
}

/*!
  \internal

  \fn void Core::captureFrame()

  This slot is called when a frame is captured.
 */
void Core::captureFrame()
{
    QImage frame = this->pluginManager.getFrame(this->deviceManager.captureFrame());

    this->mediaStreaming.setFrame(frame);
    this->shellManager.setFrame(frame);
}
