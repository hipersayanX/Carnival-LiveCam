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

#include "spaceselement.h"

SpacesElement::SpacesElement(): Element()
{
    this->resetEditMode();
    this->resetSnapping();
    this->resetNParts();
    this->resetSnappingPT();
    this->resetSnappingRT();
    this->resetButtonText();
    this->resetButtonIcon();
    this->resetButtonStyleSheet();

    this->m_move = false;
    this->m_scaleAndRotate = false;
    this->m_spacesWidget.setBackgroundBrush(Qt::black);

    QObject::connect(&this->m_spacesWidget, SIGNAL(spaceMoved(int, int)), this, SIGNAL(spaceMoved(int, int)));
}

SpacesElement::~SpacesElement()
{
    this->m_spacesWidget.resetSpaces();
}

bool SpacesElement::editMode()
{
    return this->m_spacesWidget.editMode();
}

bool SpacesElement::snapping()
{
    return this->m_spacesWidget.snapping();
}

int SpacesElement::nParts()
{
    return this->m_spacesWidget.nParts();
}

float SpacesElement::snappingPT()
{
    return this->m_spacesWidget.snappingPT();
}

float SpacesElement::snappingRT()
{
    return this->m_spacesWidget.snappingRT();
}

QString SpacesElement::buttonText()
{
    return this->m_spacesWidget.buttonText();
}

QString SpacesElement::buttonIcon()
{
    return this->m_spacesWidget.buttonIcon();
}

QString SpacesElement::buttonStyleSheet()
{
    return this->m_spacesWidget.buttonStyleSheet();
}

bool SpacesElement::start()
{
    emit(this->oStream((const void *) &this->m_spacesWidget, 0, "QWidget"));

    return true;
}

bool SpacesElement::stop()
{
    return true;
}

void SpacesElement::iStream(const void *data, int datalen, QString dataType)
{
    Q_UNUSED(datalen)

    QString spaceId = this->sender()->objectName();

    if (dataType != "QImage")
        return;

    QImage *iFrame = (QImage *) data;

    this->m_spacesWidget.setFrame(spaceId, *iFrame);
}

void SpacesElement::setPipeline(Pipeline *pipeline)
{
    Q_UNUSED(pipeline)
}

void SpacesElement::setPeers(QList<Element *> srcs, QList<Element *> sinks)
{
    this->m_srcs = srcs;
    this->m_sinks = sinks;

    QStringList spaces;

    foreach (Element *spaceId, srcs)
        spaces << spaceId->objectName();

    this->m_spacesWidget.setSpaces(spaces);
}

void SpacesElement::setEditMode(bool editMode)
{
    this->m_spacesWidget.setEditMode(editMode);
}

void SpacesElement::setSnapping(bool snapping)
{
    this->m_spacesWidget.setSnapping(snapping);
}

void SpacesElement::setNParts(int nParts)
{
    this->m_spacesWidget.setNParts(nParts);
}

void SpacesElement::setSnappingPT(float snappingPT)
{
    this->m_spacesWidget.setSnappingPT(snappingPT);
}

void SpacesElement::setSnappingRT(float snappingRT)
{
    this->m_spacesWidget.setSnappingRT(snappingRT);
}

void SpacesElement::setButtonText(QString buttonText)
{
    this->m_spacesWidget.setButtonText(buttonText);
}

void SpacesElement::setButtonIcon(QString buttonIcon)
{
    this->m_spacesWidget.setButtonIcon(buttonIcon);
}

void SpacesElement::setButtonStyleSheet(QString buttonStyleSheet)
{
    this->m_spacesWidget.setButtonStyleSheet(buttonStyleSheet);
}

void SpacesElement::resetEditMode()
{
    this->setEditMode(false);
}

void SpacesElement::resetSnapping()
{
    this->setSnapping(true);
}

void SpacesElement::resetNParts()
{
    this->setNParts(24);
}

void SpacesElement::resetSnappingPT()
{
    this->setSnappingPT(10);
}

void SpacesElement::resetSnappingRT()
{
    this->setSnappingRT(3.0 * M_PI / 180.0);
}

void SpacesElement::resetButtonText()
{
    this->setButtonText("");
}

void SpacesElement::resetButtonIcon()
{
    this->setButtonIcon("");
}

void SpacesElement::resetButtonStyleSheet()
{
    this->setButtonStyleSheet("");
}
