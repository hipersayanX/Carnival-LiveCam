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
{
    // Simple actions signals.
    QObject::connect(&this->m_qmlShellGui, &QmlShellGui::closed, this, &QmlShellElement::closed);
    QObject::connect(&this->m_qmlShellGui, &QmlShellGui::streamStateChanged, this, &QmlShellElement::streamStateChanged);
    QObject::connect(&this->m_qmlShellGui, &QmlShellGui::takePicture, this, &QmlShellElement::takePicture);
    QObject::connect(&this->m_qmlShellGui, &QmlShellGui::startVideoRecord, this, &QmlShellElement::startVideoRecord);
    QObject::connect(&this->m_qmlShellGui, &QmlShellGui::stopVideoRecord, this, &QmlShellElement::stopVideoRecord);
    QObject::connect(&this->m_qmlShellGui, &QmlShellGui::editModeChanged, this, &QmlShellElement::editModeChanged);

    // Spaces related signals.
    QObject::connect(&this->m_qmlShellGui, &QmlShellGui::addSpace, this, &QmlShellElement::addSpace);
    QObject::connect(&this->m_qmlShellGui, &QmlShellGui::removeSpace, this, &QmlShellElement::removeSpace);
    QObject::connect(&this->m_qmlShellGui, &QmlShellGui::spaceZIndexChanged, this, &QmlShellElement::spaceZIndexChanged);
    QObject::connect(&this->m_qmlShellGui, &QmlShellGui::requestSpaceControls, this, &QmlShellElement::requestSpaceControls);
    QObject::connect(&this->m_qmlShellGui, &QmlShellGui::setupSpaceControls, this, &QmlShellElement::setupSpaceControls);

    // Effects related signals.
    QObject::connect(&this->m_qmlShellGui, &QmlShellGui::addFx, this, &QmlShellElement::addFx);
    QObject::connect(&this->m_qmlShellGui, &QmlShellGui::removeFx, this, &QmlShellElement::removeFx);
    QObject::connect(&this->m_qmlShellGui, &QmlShellGui::fxIndexChanged, this, &QmlShellElement::fxIndexChanged);
    QObject::connect(&this->m_qmlShellGui, &QmlShellGui::requestFxInfo, this, &QmlShellElement::requestFxInfo);
    QObject::connect(&this->m_qmlShellGui, &QmlShellGui::openURL, this, &QmlShellElement::openURL);
    QObject::connect(&this->m_qmlShellGui, &QmlShellGui::mailTo, this, &QmlShellElement::mailTo);
    QObject::connect(&this->m_qmlShellGui, &QmlShellGui::requestFxUpdate, this, &QmlShellElement::requestFxUpdate);
    QObject::connect(&this->m_qmlShellGui, &QmlShellGui::fxPreviewStateChanged, this, &QmlShellElement::fxPreviewStateChanged);
    QObject::connect(&this->m_qmlShellGui, &QmlShellGui::requestFxControls, this, &QmlShellElement::requestFxControls);
    QObject::connect(&this->m_qmlShellGui, &QmlShellGui::setupFxControls, this, &QmlShellElement::setupFxControls);

    this->m_qmlShellGui.show();

    return true;
}

bool QmlShellElement::stop()
{
    this->m_qmlShellGui.hide();

    // Simple actions signals.
    QObject::disconnect(&this->m_qmlShellGui, &QmlShellGui::closed, this, &QmlShellElement::closed);
    QObject::disconnect(&this->m_qmlShellGui, &QmlShellGui::streamStateChanged, this, &QmlShellElement::streamStateChanged);
    QObject::disconnect(&this->m_qmlShellGui, &QmlShellGui::takePicture, this, &QmlShellElement::takePicture);
    QObject::disconnect(&this->m_qmlShellGui, &QmlShellGui::startVideoRecord, this, &QmlShellElement::startVideoRecord);
    QObject::disconnect(&this->m_qmlShellGui, &QmlShellGui::stopVideoRecord, this, &QmlShellElement::stopVideoRecord);
    QObject::disconnect(&this->m_qmlShellGui, &QmlShellGui::editModeChanged, this, &QmlShellElement::editModeChanged);

    // Spaces related signals.
    QObject::disconnect(&this->m_qmlShellGui, &QmlShellGui::addSpace, this, &QmlShellElement::addSpace);
    QObject::disconnect(&this->m_qmlShellGui, &QmlShellGui::removeSpace, this, &QmlShellElement::removeSpace);
    QObject::disconnect(&this->m_qmlShellGui, &QmlShellGui::spaceZIndexChanged, this, &QmlShellElement::spaceZIndexChanged);
    QObject::disconnect(&this->m_qmlShellGui, &QmlShellGui::requestSpaceControls, this, &QmlShellElement::requestSpaceControls);
    QObject::disconnect(&this->m_qmlShellGui, &QmlShellGui::setupSpaceControls, this, &QmlShellElement::setupSpaceControls);

    // Effects related signals.
    QObject::disconnect(&this->m_qmlShellGui, &QmlShellGui::addFx, this, &QmlShellElement::addFx);
    QObject::disconnect(&this->m_qmlShellGui, &QmlShellGui::removeFx, this, &QmlShellElement::removeFx);
    QObject::disconnect(&this->m_qmlShellGui, &QmlShellGui::fxIndexChanged, this, &QmlShellElement::fxIndexChanged);
    QObject::disconnect(&this->m_qmlShellGui, &QmlShellGui::requestFxInfo, this, &QmlShellElement::requestFxInfo);
    QObject::disconnect(&this->m_qmlShellGui, &QmlShellGui::openURL, this, &QmlShellElement::openURL);
    QObject::disconnect(&this->m_qmlShellGui, &QmlShellGui::mailTo, this, &QmlShellElement::mailTo);
    QObject::disconnect(&this->m_qmlShellGui, &QmlShellGui::requestFxUpdate, this, &QmlShellElement::requestFxUpdate);
    QObject::disconnect(&this->m_qmlShellGui, &QmlShellGui::fxPreviewStateChanged, this, &QmlShellElement::fxPreviewStateChanged);
    QObject::disconnect(&this->m_qmlShellGui, &QmlShellGui::requestFxControls, this, &QmlShellElement::requestFxControls);
    QObject::disconnect(&this->m_qmlShellGui, &QmlShellGui::setupFxControls, this, &QmlShellElement::setupFxControls);

    return true;
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
    this->m_qmlShellGui.showError(message);
}

void QmlShellElement::setStreamState(ElementState state)
{
    this->m_qmlShellGui.setStreamState(state);
}

void QmlShellElement::setEditMode(bool enabled)
{
    this->m_qmlShellGui.setEditMode(enabled);
}

void QmlShellElement::setRecordingState(bool recording)
{
    this->m_qmlShellGui.setRecordingState(recording);
}

void QmlShellElement::setAvailableSpaceTypes(QStringList spaceTypes)
{
    this->m_qmlShellGui.setAvailableSpaceTypes(spaceTypes);
}

void QmlShellElement::setSpaces(QStringList spaces)
{
    this->m_qmlShellGui.setSpaces(spaces);
}

void QmlShellElement::setSpaceIndex(QString spaceId, int index)
{
    this->m_qmlShellGui.setSpaceIndex(spaceId, index);
}

void QmlShellElement::setSpaceControls(QString spaceId, QVariantList controls)
{
    this->m_qmlShellGui.setSpaceControls(spaceId, controls);
}

void QmlShellElement::setAvailableFxCategories(QStringList categories)
{
    this->m_qmlShellGui.setAvailableFxCategories(categories);
}

void QmlShellElement::setAvailableFx(QStringList fxs)
{
    this->m_qmlShellGui.setAvailableFx(fxs);
}

void QmlShellElement::setFxs(QStringList fxs)
{
    this->m_qmlShellGui.setFxs(fxs);
}

void QmlShellElement::setFxIndex(QString fxId, int index)
{
    this->m_qmlShellGui.setFxIndex(fxId, index);
}

void QmlShellElement::setFxInfo(QString fxId, QVariantList controls)
{
    this->m_qmlShellGui.setFxInfo(fxId, controls);
}

void QmlShellElement::setFxControls(QString fxId, QVariantList controls)
{
    this->m_qmlShellGui.setFxControls(fxId, controls);
}

void QmlShellElement::iStream(const void *data, int datalen, QString dataType)
{/*
    this->m_qmlShellGui->setFrame(frame);
    this->m_qmlShellGui->setPreview(frame);
    return this->m_qmlShellGui->showPreview();*/
}

void QmlShellElement::setPipeline(Pipeline *pipeline)
{
    Q_UNUSED(pipeline)
}

void QmlShellElement::setPeers(QList<Element *> srcs, QList<Element *> sinks)
{
    this->m_srcs = srcs;
    this->m_sinks = sinks;
}
