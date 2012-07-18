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

    this->spaceManager.setSpace("/dev/video0", QImage());
    this->spaceManager.setViewPortSize(this->shellManager.viewPortSize("shell.DefaultShell"));
    this->spaceManager.setSnapping(true, 24, 10, 3.0 * M_PI / 180.0);

    this->shellManager.setControlButtons(&this->toggleMaximizedButton, &this->scaleAndRotateButton);
    this->spaceManager.setControlButtons(&this->toggleMaximizedButton, &this->scaleAndRotateButton);

    connect(&this->spaceManager, SIGNAL(spaceMoved(qint32, qint32)), &this->shellManager, SLOT(moveDevice(qint32, qint32)));
    connect(&this->deviceManager, SIGNAL(devicesModified()), this, SLOT(devicesModified()));

    connect(&this->spaceManager, SIGNAL(mouseDoubleClick(QString, QMouseEvent *)), &this->pluginManager, SLOT(mouseDoubleClickEvent(QString, QMouseEvent *)));
    connect(&this->spaceManager, SIGNAL(mouseMove(QString, QMouseEvent *)), &this->pluginManager, SLOT(mouseMoveEvent(QString, QMouseEvent *)));
    connect(&this->spaceManager, SIGNAL(mousePress(QString, QMouseEvent *)), &this->pluginManager, SLOT(mousePressEvent(QString, QMouseEvent *)));
    connect(&this->spaceManager, SIGNAL(mouseRelease(QString, QMouseEvent *)), &this->pluginManager, SLOT(mouseReleaseEvent(QString, QMouseEvent *)));

    this->shellManager.widget()->show();

    this->shellManager.updateDevices(this->deviceManager.devicesInfoList(), this->spaceManager.activeSpaces());
    this->shellManager.updatePlugins(this->pluginManager.toList());

    connect(&this->shellManager, SIGNAL(deviceEnable(QString)), this, SLOT(deviceEnable(QString)));
    connect(&this->shellManager, SIGNAL(deviceDisable(QString)), this, SLOT(deviceDisable(QString)));

    this->mediaStreaming.setFPS(10);
    this->mediaStreaming.addOutputFormat(OutputFormat("ogv", "libtheora", 500000, "libvorbis", 128000, "ogg", false));
    this->mediaStreaming.addOutputFormat(OutputFormat("webm", "libvpx", 500000, "libvorbis", 128000, "webm", false));

    connect(&this->shellManager, SIGNAL(setEffect(QString, QString)), this, SLOT(setEffect(QString, QString)));
    connect(&this->shellManager, SIGNAL(unsetEffect(QString, QString)), this, SLOT(unsetEffect(QString, QString)));
    connect(&this->shellManager, SIGNAL(pluginMoved(QString, qint32, qint32)), &this->pluginManager, SLOT(movePlugin(QString, qint32, qint32)));
    connect(&this->shellManager, SIGNAL(pluginConfigureClicked(QString)), &this->pluginManager, SLOT(configurePlugin(QString)));

    connect(&this->shellManager, SIGNAL(takePicture()), &this->mediaStreaming, SLOT(takePicture()));
    connect(&this->shellManager, SIGNAL(startStopRecord()), &this->mediaStreaming, SLOT(startStopRecord()));

    connect(&this->shellManager, SIGNAL(deviceConfigureClicked(QString)), &this->deviceManager, SLOT(configure(QString)));

    connect(&this->shellManager, SIGNAL(enabledDeviceMoved(qint32, qint32)), &this->spaceManager, SLOT(moveSpace(qint32, qint32)));
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
    this->spaceManager.updateSpaces(this->deviceManager.devicesInfoList());
    this->shellManager.updateDevices(this->deviceManager.devicesInfoList(), this->spaceManager.activeSpaces());
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
    this->spaceManager.setSpace(deviceId, QImage());
    this->shellManager.updateDevices(this->deviceManager.devicesInfoList(), this->spaceManager.activeSpaces());
    this->shellManager.updatePlugins(this->pluginManager.toList());
}

void Core::deviceDisable(QString deviceId)
{
    this->pluginManager.unsetEffects(deviceId);
    this->deviceManager.deviceDisable(deviceId);
    this->spaceManager.removeSpace(deviceId);
    this->shellManager.updateDevices(this->deviceManager.devicesInfoList(), this->spaceManager.activeSpaces());
    this->shellManager.updatePlugins(this->pluginManager.toList());
}

/*!
  \internal

  \fn void Core::captureFrame()

  This slot is called when a frame is captured.
 */
void Core::captureFrame()
{
    foreach (QString deviceId, this->deviceManager.activeDevices())
    {
        // Capture a frame from DeviceManager, send it to PluginManager to apply the effects,
        // and return the frame whit the effects applied.
        QImage frame = this->pluginManager.render(deviceId, this->deviceManager.captureFrame(deviceId));

        if (this->shellManager.showPreview() == deviceId)
            this->shellManager.setPreview(frame);

        this->spaceManager.setSpace(deviceId, frame);
    }

    QImage frame = this->spaceManager.render();

    // Send the frame to MediaStreamming for save it to a video or image file.
    this->mediaStreaming.setFrame(frame);

    // And send it to the current shell.
    this->shellManager.setFrame(frame);
}

void Core::setEffect(QString pluginId, QString spaceId)
{
    if (this->pluginManager.setEffect(pluginId, spaceId, this->deviceManager.frameSize(spaceId)))
    {
        this->deviceManager.setEffect(spaceId, pluginId);
        this->shellManager.updateDevices(this->deviceManager.devicesInfoList(), this->spaceManager.activeSpaces());
        this->shellManager.updatePlugins(this->pluginManager.toList());
    }
}

void Core::unsetEffect(QString pluginId, QString spaceId)
{
    if (this->pluginManager.unsetEffect(pluginId, spaceId))
    {
        this->deviceManager.unsetEffect(spaceId, pluginId);
        this->shellManager.updateDevices(this->deviceManager.devicesInfoList(), this->spaceManager.activeSpaces());
        this->shellManager.updatePlugins(this->pluginManager.toList());
    }
}
