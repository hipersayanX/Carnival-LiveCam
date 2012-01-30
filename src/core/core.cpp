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

#include <cmath>
#include <QWidget>
#include <QtDebug>

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
    this->shellManager.setShell("shell.DefaultShell");
    this->deviceManager.deviceEnable("/dev/video0");
//    this->pluginManager.resize(this->deviceManager.frameSize('/dev/video0'));
    this->spaceManager.setSpace("/dev/video0", QImage());
    this->spaceManager.setSnapping(true, 24, 5, 3.0 * M_PI / 180.0);
    this->spaceManager.setViewPortSize(this->shellManager.viewPortSize("shell.DefaultShell"));

    this->shellManager.setControlButtons(&this->toggleMaximizedButton, &this->scaleAndRotateButton);
    this->spaceManager.setControlButtons(&this->toggleMaximizedButton, &this->scaleAndRotateButton);
    this->toggleMaximizedButton.setHidden(true);
    this->scaleAndRotateButton.setHidden(true);

    connect(&this->deviceManager, SIGNAL(devicesModified()), this, SLOT(devicesModified()));

    this->shellManager.widget()->show();

    this->shellManager.updateDevices(this->deviceManager.devicesInfoList());
    this->shellManager.updatePlugins(this->pluginManager.pluginsInfoList());

    connect(&this->shellManager, SIGNAL(deviceEnable(QString)), this, SLOT(deviceEnable(QString)));
    connect(&this->shellManager, SIGNAL(deviceDisable(QString)), this, SLOT(deviceDisable(QString)));

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

    connect(&this->shellManager, SIGNAL(viewPortSizeChanged(QSize)), &this->spaceManager, SLOT(setViewPortSize(QSize)));
    connect(&this->shellManager, SIGNAL(toggleEditMode()), &this->spaceManager, SLOT(toggleEditMode()));
    connect(&this->shellManager, SIGNAL(mouseDoubleClicked(QMouseEvent *)), &this->spaceManager, SLOT(mouseDoubleClickEvent(QMouseEvent *)));
    connect(&this->shellManager, SIGNAL(mousePositionChanged(QMouseEvent *)), &this->spaceManager, SLOT(mouseMoveEvent(QMouseEvent *)));
    connect(&this->shellManager, SIGNAL(mousePressed(QMouseEvent *)), &this->spaceManager, SLOT(mousePressEvent(QMouseEvent *)));
    connect(&this->shellManager, SIGNAL(mouseReleased(QMouseEvent *)), &this->spaceManager, SLOT(mouseReleaseEvent(QMouseEvent *)));

    connect(&this->mediaStreaming, SIGNAL(captureFrame()), this, SLOT(captureFrame()));
}

/*!
  \internal

  \fn void Core::devicesModified()

  This slot is called when a device is added or removed.
 */
void Core::devicesModified()
{
    this->shellManager.updateDevices(this->deviceManager.devicesInfoList());
    this->spaceManager.updateSpaces(this->deviceManager.devicesInfoList());
}

/*!
  \internal

  \fn void Core::deviceSelected(QString deviceId)

  \param deviceId The unique device identifier.

  This slot is called when the user select a device to be used to capture from.
 */
void Core::deviceEnable(QString deviceId)
{
    this->deviceManager.deviceEnable(deviceId);
//    this->pluginManager.resize(this->deviceManager.frameSize());
    this->spaceManager.setSpace(deviceId, QImage());
}

void Core::deviceDisable(QString deviceId)
{
    this->deviceManager.deviceDisable(deviceId);
//    this->pluginManager.resize(this->deviceManager.frameSize());
    this->spaceManager.removeSpace(deviceId);
}

/*!
  \internal

  \fn void Core::captureFrame()

  This slot is called when a frame is captured.
 */
void Core::captureFrame()
{
    // Capture a frame from DeviceManager, send it to PluginManager to apply the effects,
    // and return the frame whit the effects applied.
    /*QImage frame = this->pluginManager.getFrame(this->deviceManager.captureFrame());*/

    foreach (QString deviceId, this->deviceManager.activeDevices())
        this->spaceManager.setSpace(deviceId, this->deviceManager.captureFrame(deviceId));

    QImage frame = this->spaceManager.render();

    // Send the frame to MediaStreamming for save it to a video or image file.
    this->mediaStreaming.setFrame(frame);

    // And send it to the current shell.
    this->shellManager.setFrame(frame);
}
