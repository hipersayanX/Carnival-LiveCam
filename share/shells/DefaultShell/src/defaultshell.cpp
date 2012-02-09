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
 *
 * QML shell plugin
 */

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
    connect(this->gui, SIGNAL(deviceEnable(QString)), this, SLOT(onDeviceEnable(QString)));
    connect(this->gui, SIGNAL(deviceDisable(QString)), this, SLOT(onDeviceDisable(QString)));
    connect(this->gui, SIGNAL(pluginActivated(QString)), this, SLOT(onPluginActivated(QString)));
    connect(this->gui, SIGNAL(pluginDeactivated(QString)), this, SLOT(onPluginDeactivated(QString)));
    connect(this->gui, SIGNAL(pluginMoved(int, int)), this, SLOT(onPluginMoved(int, int)));
    connect(this->gui, SIGNAL(pluginConfigureClicked(QString)), this, SLOT(onPluginConfigureClicked(QString)));
    connect(this->gui, SIGNAL(deviceConfigureClicked(QString)), this, SLOT(onDeviceConfigureClicked(QString)));
    connect(this->gui, SIGNAL(closed()), this, SLOT(onClosed()));
}

void DefaultShell::end()
{
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

void DefaultShell::setFrame(const QImage &frame)
{
    this->gui->setFrame(frame);
}

void DefaultShell::updateDevices(const QList<QVariant> &devices)
{
    this->gui->updateDevices(devices);
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

void DefaultShell::onDeviceEnable(QString deviceId)
{
    emit deviceEnable(deviceId);
}

void DefaultShell::onDeviceDisable(QString deviceId)
{
    emit deviceDisable(deviceId);
}

void DefaultShell::onPluginActivated(QString pluginId)
{
    emit pluginActivated(pluginId);
}

void DefaultShell::onPluginDeactivated(QString pluginId)
{
    emit pluginDeactivated(pluginId);
}

void DefaultShell::onPluginMoved(int from, int to)
{
    emit pluginMoved(from, to);
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
