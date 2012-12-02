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

#include "qmlshellelement.h"

QmlShellElement::QmlShellElement()
{
    this->resetSpacesBoard();
    this->resetSpacePreview();
}

QString QmlShellElement::spacesBoard()
{
    return this->m_spacesBoard;
}

QString QmlShellElement::spacePreview()
{
    return this->m_spacePreview;
}

bool QmlShellElement::start()
{/*
    connect(this->m_qmlShellGui, SIGNAL(viewPortSizeChanged(QSize)), this, SLOT(onViewPortSizeChanged(QSize)));
    connect(this->m_qmlShellGui, SIGNAL(sMouseDoubleClicked(QMouseEvent *)), this, SLOT(onMouseDoubleClicked(QMouseEvent *)));
    connect(this->m_qmlShellGui, SIGNAL(sMousePositionChanged(QMouseEvent *)), this, SLOT(onMousePositionChanged(QMouseEvent *)));
    connect(this->m_qmlShellGui, SIGNAL(sMousePressed(QMouseEvent *)), this, SLOT(onMousePressed(QMouseEvent *)));
    connect(this->m_qmlShellGui, SIGNAL(sMouseReleased(QMouseEvent *)), this, SLOT(onMouseReleased(QMouseEvent *)));
    connect(this->m_qmlShellGui, SIGNAL(toggleEditMode()), this, SLOT(onToggleEditMode()));
    connect(this->m_qmlShellGui, SIGNAL(takePicture()), this, SLOT(onTakePicture()));
    connect(this->m_qmlShellGui, SIGNAL(startStopRecord()), this, SLOT(onStartStopRecord()));
    connect(this->m_qmlShellGui, SIGNAL(enabledDeviceMoved(qint32, qint32)), this, SLOT(onEnabledDeviceMoved(qint32, qint32)));
    connect(this->m_qmlShellGui, SIGNAL(deviceEnable(QString)), this, SLOT(onDeviceEnable(QString)));
    connect(this->m_qmlShellGui, SIGNAL(deviceDisable(QString)), this, SLOT(onDeviceDisable(QString)));
    connect(this->m_qmlShellGui, SIGNAL(setEffect(QString, QString)), this, SLOT(onSetEffect(QString, QString)));
    connect(this->m_qmlShellGui, SIGNAL(unsetEffect(QString, QString)), this, SLOT(onUnsetEffect(QString, QString)));
    connect(this->m_qmlShellGui, SIGNAL(pluginMoved(QString, qint32, qint32)), this, SLOT(onPluginMoved(QString, qint32, qint32)));
    connect(this->m_qmlShellGui, SIGNAL(pluginConfigureClicked(QString)), this, SLOT(onPluginConfigureClicked(QString)));
    connect(this->m_qmlShellGui, SIGNAL(deviceConfigureClicked(QString)), this, SLOT(onDeviceConfigureClicked(QString)));
    connect(this->m_qmlShellGui, SIGNAL(closed()), this, SLOT(onClosed()));*/
}

bool QmlShellElement::stop()
{/*
    disconnect(this->m_qmlShellGui, SIGNAL(viewPortSizeChanged(QSize)), this, SLOT(onViewPortSizeChanged(QSize)));
    disconnect(this->m_qmlShellGui, SIGNAL(sMouseDoubleClicked(QMouseEvent *)), this, SLOT(onMouseDoubleClicked(QMouseEvent *)));
    disconnect(this->m_qmlShellGui, SIGNAL(sMousePositionChanged(QMouseEvent *)), this, SLOT(onMousePositionChanged(QMouseEvent *)));
    disconnect(this->m_qmlShellGui, SIGNAL(sMousePressed(QMouseEvent *)), this, SLOT(onMousePressed(QMouseEvent *)));
    disconnect(this->m_qmlShellGui, SIGNAL(sMouseReleased(QMouseEvent *)), this, SLOT(onMouseReleased(QMouseEvent *)));
    disconnect(this->m_qmlShellGui, SIGNAL(toggleEditMode()), this, SLOT(onToggleEditMode()));
    disconnect(this->m_qmlShellGui, SIGNAL(takePicture()), this, SLOT(onTakePicture()));
    disconnect(this->m_qmlShellGui, SIGNAL(startStopRecord()), this, SLOT(onStartStopRecord()));
    disconnect(this->m_qmlShellGui, SIGNAL(enabledDeviceMoved(qint32, qint32)), this, SLOT(onEnabledDeviceMoved(qint32, qint32)));
    disconnect(this->m_qmlShellGui, SIGNAL(deviceEnable(QString)), this, SLOT(onDeviceEnable(QString)));
    disconnect(this->m_qmlShellGui, SIGNAL(deviceDisable(QString)), this, SLOT(onDeviceDisable(QString)));
    disconnect(this->m_qmlShellGui, SIGNAL(setEffect(QString, QString)), this, SLOT(onSetEffect(QString, QString)));
    disconnect(this->m_qmlShellGui, SIGNAL(unsetEffect(QString, QString)), this, SLOT(onUnsetEffect(QString, QString)));
    disconnect(this->m_qmlShellGui, SIGNAL(pluginMoved(QString, qint32, qint32)), this, SLOT(onPluginMoved(QString, qint32, qint32)));
    disconnect(this->m_qmlShellGui, SIGNAL(pluginConfigureClicked(QString)), this, SLOT(onPluginConfigureClicked(QString)));
    disconnect(this->m_qmlShellGui, SIGNAL(deviceConfigureClicked(QString)), this, SLOT(onDeviceConfigureClicked(QString)));
    disconnect(this->m_qmlShellGui, SIGNAL(closed()), this, SLOT(onClosed()));

    delete this->m_qmlShellGui;
    this->m_qmlShellGui = NULL;*/
}

void QmlShellElement::setSpacesBoard(QString spacesBoard)
{
    this->m_spacesBoard = spacesBoard;
}

void QmlShellElement::setSpacePreview(QString spacePreview)
{
    this->m_spacePreview = spacePreview;
}

void QmlShellElement::resetSpacesBoard()
{
    this->setSpacesBoard("");
}

void QmlShellElement::resetSpacePreview()
{
    this->setSpacePreview("");
}

void QmlShellElement::showError(QString message)
{
}

void QmlShellElement::setStreamState(ElementState state)
{
}

void QmlShellElement::setEditMode(bool enabled)
{
}

void QmlShellElement::setRecordingState(bool recording)
{
}

void QmlShellElement::setAvailableSpaceTypes(QStringList spaceTypes)
{
}

void QmlShellElement::setSpaces(QStringList spaces)
{
}

void QmlShellElement::setSpaceIndex(QString spaceId, int index)
{
}

void QmlShellElement::setSpaceControls(QString spaceId, QVariantList controls)
{
}

void QmlShellElement::setAvailableFxCategories(QStringList categories)
{
}

void QmlShellElement::setAvailableFx(QStringList fxs)
{
}

void QmlShellElement::setFxs(QStringList fxs)
{
}

void QmlShellElement::setFxIndex(QString fxId, int index)
{
}

void QmlShellElement::setFxInfo(QString fxId, QVariantList controls)
{
}

void QmlShellElement::setFxControls(QString fxId, QVariantList controls)
{
}

void QmlShellElement::iStream(const void *data, int datalen, QString dataType)
{
}

void QmlShellElement::setPipeline(Pipeline *pipeline)
{
}

void QmlShellElement::setPeers(QList<Element *> srcs, QList<Element *> sinks)
{
}
/*
QString QmlShellElement::showPreview()
{
    return this->m_qmlShellGui->showPreview();
}

void QmlShellElement::setFrame(const QImage &frame)
{
    this->m_qmlShellGui->setFrame(frame);
}

void QmlShellElement::setPreview(const QImage &frame)
{
    this->m_qmlShellGui->setPreview(frame);
}

void QmlShellElement::updateDevices(const QList<QVariant> &devices, const QStringList &activeSpaces)
{
    this->m_qmlShellGui->updateDevices(devices, activeSpaces);
}

void QmlShellElement::updatePlugins(const QList<QVariant> &plugins)
{
    this->m_qmlShellGui->updatePlugins(plugins);
}

void QmlShellElement::moveDevice(qint32 from, qint32 to)
{
    this->m_qmlShellGui->moveDevice(from, to);
}
*/
