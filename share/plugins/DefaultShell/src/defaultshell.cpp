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

#include "../include/defaultshell.h"

QString DefaultShell::id()
{
    return "shell.DefaultShell";
}

QString DefaultShell::name()
{
    return "Default Shell";
}

QString DefaultShell::version()
{
    return "1.0.0";
}

QString DefaultShell::summary()
{
    return "Default Shell";
}

QString DefaultShell::type()
{
    return "QML shell";
}

QString DefaultShell::thumbnail()
{
    return "";
}

QString DefaultShell::license()
{
    return "GPLv3";
}

QString DefaultShell::author()
{
    return "hipersayan_x";
}

QString DefaultShell::website()
{
    return "hipersayanx.blogspot.com";
}

QString DefaultShell::mail()
{
    return "hipersayan.x@gmail.com";
}

bool DefaultShell::isConfigurable()
{
    return false;
}

void DefaultShell::begin()
{
    this->gui = new Gui();

    connect(this->gui, SIGNAL(viewPortSizeChanged(QSize)), this, SLOT(onViewPortSizeChanged(QSize)));
    connect(this->gui, SIGNAL(sMouseDoubleClicked(QMouseEvent *)), this, SLOT(onMouseDoubleClicked(QMouseEvent *)));
    connect(this->gui, SIGNAL(sMousePositionChanged(QMouseEvent *)), this, SLOT(onMousePositionChanged(QMouseEvent *)));
    connect(this->gui, SIGNAL(sMousePressed(QMouseEvent *)), this, SLOT(onMousePressed(QMouseEvent *)));
    connect(this->gui, SIGNAL(sMouseReleased(QMouseEvent *)), this, SLOT(onMouseReleased(QMouseEvent *)));
    connect(this->gui, SIGNAL(toggleEditMode()), this, SLOT(onToggleEditMode()));
    connect(this->gui, SIGNAL(takePicture()), this, SLOT(onTakePicture()));
    connect(this->gui, SIGNAL(startStopRecord()), this, SLOT(onStartStopRecord()));
    connect(this->gui, SIGNAL(enabledDeviceMoved(qint32, qint32)), this, SLOT(onEnabledDeviceMoved(qint32, qint32)));
    connect(this->gui, SIGNAL(deviceEnable(QString)), this, SLOT(onDeviceEnable(QString)));
    connect(this->gui, SIGNAL(deviceDisable(QString)), this, SLOT(onDeviceDisable(QString)));
    connect(this->gui, SIGNAL(setEffect(QString, QString)), this, SLOT(onSetEffect(QString, QString)));
    connect(this->gui, SIGNAL(unsetEffect(QString, QString)), this, SLOT(onUnsetEffect(QString, QString)));
    connect(this->gui, SIGNAL(pluginMoved(QString, qint32, qint32)), this, SLOT(onPluginMoved(QString, qint32, qint32)));
    connect(this->gui, SIGNAL(pluginConfigureClicked(QString)), this, SLOT(onPluginConfigureClicked(QString)));
    connect(this->gui, SIGNAL(deviceConfigureClicked(QString)), this, SLOT(onDeviceConfigureClicked(QString)));
    connect(this->gui, SIGNAL(closed()), this, SLOT(onClosed()));
}

void DefaultShell::end()
{
    disconnect(this->gui, SIGNAL(viewPortSizeChanged(QSize)), this, SLOT(onViewPortSizeChanged(QSize)));
    disconnect(this->gui, SIGNAL(sMouseDoubleClicked(QMouseEvent *)), this, SLOT(onMouseDoubleClicked(QMouseEvent *)));
    disconnect(this->gui, SIGNAL(sMousePositionChanged(QMouseEvent *)), this, SLOT(onMousePositionChanged(QMouseEvent *)));
    disconnect(this->gui, SIGNAL(sMousePressed(QMouseEvent *)), this, SLOT(onMousePressed(QMouseEvent *)));
    disconnect(this->gui, SIGNAL(sMouseReleased(QMouseEvent *)), this, SLOT(onMouseReleased(QMouseEvent *)));
    disconnect(this->gui, SIGNAL(toggleEditMode()), this, SLOT(onToggleEditMode()));
    disconnect(this->gui, SIGNAL(takePicture()), this, SLOT(onTakePicture()));
    disconnect(this->gui, SIGNAL(startStopRecord()), this, SLOT(onStartStopRecord()));
    disconnect(this->gui, SIGNAL(enabledDeviceMoved(qint32, qint32)), this, SLOT(onEnabledDeviceMoved(qint32, qint32)));
    disconnect(this->gui, SIGNAL(deviceEnable(QString)), this, SLOT(onDeviceEnable(QString)));
    disconnect(this->gui, SIGNAL(deviceDisable(QString)), this, SLOT(onDeviceDisable(QString)));
    disconnect(this->gui, SIGNAL(setEffect(QString, QString)), this, SLOT(onSetEffect(QString, QString)));
    disconnect(this->gui, SIGNAL(unsetEffect(QString, QString)), this, SLOT(onUnsetEffect(QString, QString)));
    disconnect(this->gui, SIGNAL(pluginMoved(QString, qint32, qint32)), this, SLOT(onPluginMoved(QString, qint32, qint32)));
    disconnect(this->gui, SIGNAL(pluginConfigureClicked(QString)), this, SLOT(onPluginConfigureClicked(QString)));
    disconnect(this->gui, SIGNAL(deviceConfigureClicked(QString)), this, SLOT(onDeviceConfigureClicked(QString)));
    disconnect(this->gui, SIGNAL(closed()), this, SLOT(onClosed()));

    delete this->gui;
    this->gui = NULL;
}

void DefaultShell::configure()
{
}

QVariant DefaultShell::configs()
{
    return QVariant();
}

void DefaultShell::setConfigs(QVariant configs)
{
    Q_UNUSED(configs)
}

QWidget *DefaultShell::widget()
{
    return this->gui;
}

QSize DefaultShell::viewPortSize()
{
    return this->gui->size();
}

QString DefaultShell::showPreview()
{
    return this->gui->showPreview();
}

void DefaultShell::setFrame(const QImage &frame)
{
    this->gui->setFrame(frame);
}

void DefaultShell::setPreview(const QImage &frame)
{
    this->gui->setPreview(frame);
}

void DefaultShell::updateDevices(const QList<QVariant> &devices, const QStringList &activeSpaces)
{
    this->gui->updateDevices(devices, activeSpaces);
}

void DefaultShell::updatePlugins(const QList<QVariant> &plugins)
{
    this->gui->updatePlugins(plugins);
}

void DefaultShell::setControlButtons(QPushButton *toggleMaximizedButton, QPushButton *scaleAndRotateButton)
{
    QString style = "QPushButton"
                    "{"
                    "    background-color: rgb(0, 0, 0);"
                    "    border: 1px solid none;"
                    "    border-radius: 6px;"
                    "}"
                    "QPushButton:hover"
                    "{"
                    "    background-color: rgb(15, 15, 15);"
                    "    border: 1px solid rgb(127, 127, 255);"
                    "}"
                    "QPushButton:pressed"
                    "{"
                    "    background-color: rgb(31, 31, 31);"
                    "    border: 1px solid rgb(255, 255, 255);"
                    "}";

    toggleMaximizedButton->setHidden(false);
    toggleMaximizedButton->setHidden(false);
    toggleMaximizedButton->setIcon(QIcon("share/shells/DefaultShell/share/images/icons/maxizespace.svg"));
    toggleMaximizedButton->setIconSize(QSize(32, 32));
    toggleMaximizedButton->setMaximumSize(QSize(48, 48));
    toggleMaximizedButton->setMinimumSize(QSize(48, 48));
    toggleMaximizedButton->setStyleSheet(style);

    scaleAndRotateButton->setHidden(false);
    scaleAndRotateButton->setIcon(QIcon("share/shells/DefaultShell/share/images/icons/scalerotate.svg"));
    scaleAndRotateButton->setIconSize(QSize(32, 32));
    scaleAndRotateButton->setMaximumSize(QSize(48, 48));
    scaleAndRotateButton->setMinimumSize(QSize(48, 48));
    scaleAndRotateButton->setStyleSheet(style);
}

void DefaultShell::moveDevice(qint32 from, qint32 to)
{
    this->gui->moveDevice(from, to);
}

void DefaultShell::onViewPortSizeChanged(QSize size)
{
    emit viewPortSizeChanged(size);
}

void DefaultShell::onMouseDoubleClicked(QMouseEvent *event)
{
    emit mouseDoubleClicked(event);
}

void DefaultShell::onMousePositionChanged(QMouseEvent *event)
{
    emit mousePositionChanged(event);
}

void DefaultShell::onMousePressed(QMouseEvent *event)
{
    emit mousePressed(event);
}

void DefaultShell::onMouseReleased(QMouseEvent *event)
{
    emit mouseReleased(event);
}

void DefaultShell::onToggleEditMode()
{
    emit toggleEditMode();
}

void DefaultShell::onTakePicture()
{
    emit takePicture();
}

void DefaultShell::onStartStopRecord()
{
    emit startStopRecord();
}

void DefaultShell::onEnabledDeviceMoved(qint32 from, qint32 to)
{
    emit enabledDeviceMoved(from, to);
}

void DefaultShell::onDeviceEnable(QString deviceId)
{
    emit deviceEnable(deviceId);
}

void DefaultShell::onDeviceDisable(QString deviceId)
{
    emit deviceDisable(deviceId);
}

void DefaultShell::onSetEffect(QString pluginId, QString spaceId)
{
    emit setEffect(pluginId, spaceId);
}

void DefaultShell::onUnsetEffect(QString pluginId, QString spaceId)
{
    emit unsetEffect(pluginId, spaceId);
}

void DefaultShell::onPluginMoved(QString spaceId, qint32 from, qint32 to)
{
    emit pluginMoved(spaceId, from, to);
}

void DefaultShell::onPluginConfigureClicked(QString pluginId)
{
    emit pluginConfigureClicked(pluginId);
}

void DefaultShell::onDeviceConfigureClicked(QString deviceId)
{
    emit deviceConfigureClicked(deviceId);
}

void DefaultShell::onClosed()
{
    emit closed();
}
