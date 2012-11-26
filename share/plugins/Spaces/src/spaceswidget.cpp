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

#include "spaceswidget.h"
#include "space.h"

SpacesWidget::SpacesWidget(QWidget *parent): QGraphicsView(parent)
{
    this->resetEditMode();
    this->resetSnapping();
    this->resetNParts();
    this->resetSnappingPT();
    this->resetSnappingRT();
    this->resetButtonText();
    this->resetButtonIcon();
    this->resetButtonStyleSheet();

    this->m_graphicsScene.setParent(this);
    this->setScene(&this->m_graphicsScene);

    QObject::connect(&this->m_graphicsScene, &QGraphicsScene::changed, this, &SpacesWidget::on_changed);
}

bool SpacesWidget::editMode()
{
    return this->m_editMode;
}

bool SpacesWidget::snapping()
{
    return this->m_snapping;
}

int SpacesWidget::nParts()
{
    return this->m_nParts;
}

int SpacesWidget::snappingPT()
{
    return this->m_snappingPT;
}

int SpacesWidget::snappingRT()
{
    return this->m_snappingRT;
}

QString SpacesWidget::buttonText()
{
    return this->m_buttonText;
}

QString SpacesWidget::buttonIcon()
{
    return this->m_buttonIcon;
}

QString SpacesWidget::buttonStyleSheet()
{
    return this->m_buttonStyleSheet;
}

void SpacesWidget::setFrame(QString spaceId, const QImage &frame)
{
    Space *space = qobject_cast<Space *>(this->m_proxySpaces[spaceId]->widget());

    space->setFrame(frame);
}

void SpacesWidget::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);

    QRectF boundingRect = this->scene()->itemsBoundingRect();
    this->scene()->setSceneRect(boundingRect);
    this->fitInView(boundingRect, Qt::KeepAspectRatio);

    event->accept();
}

void SpacesWidget::addSpace(QString spaceId)
{
    Space *space = new Space();

    this->m_proxySpaces[spaceId] = this->m_graphicsScene.addWidget(space);
    space->setSpaceId(spaceId);
    space->setProxy(this->m_proxySpaces[spaceId]);
    space->setEditMode(this->m_editMode);
    space->setSnapping(this->m_snapping);
    space->setNParts(this->m_nParts);
    space->setSnappingPT(this->m_snappingPT);
    space->setSnappingRT(this->m_snappingRT);
    space->setButtonText(this->m_buttonText);
    space->setButtonIcon(this->m_buttonIcon);
    space->setButtonStyleSheet(this->m_buttonStyleSheet);
}

void SpacesWidget::removeSpace(QString spaceId)
{
    this->m_graphicsScene.removeItem(this->m_proxySpaces[spaceId]);
    this->m_proxySpaces.remove(spaceId);
}

void SpacesWidget::setEditMode(bool editable)
{
    this->m_editMode = editable;

    foreach (QString spaceId, this->m_proxySpaces.keys())
    {
        Space *space = qobject_cast<Space *>(this->m_proxySpaces[spaceId]->widget());

        space->setEditMode(editable);
    }
}

void SpacesWidget::setSnapping(bool enable)
{
    this->m_snapping = enable;

    foreach (QString spaceId, this->m_proxySpaces.keys())
    {
        Space *space = qobject_cast<Space *>(this->m_proxySpaces[spaceId]->widget());

        space->setSnapping(enable);
    }
}

void SpacesWidget::setNParts(int nParts)
{
    this->m_nParts = nParts;

    foreach (QString spaceId, this->m_proxySpaces.keys())
    {
        Space *space = qobject_cast<Space *>(this->m_proxySpaces[spaceId]->widget());

        space->setNParts(nParts);
    }
}

void SpacesWidget::setSnappingPT(float snappingPT)
{
    this->m_snappingPT = snappingPT;

    foreach (QString spaceId, this->m_proxySpaces.keys())
    {
        Space *space = qobject_cast<Space *>(this->m_proxySpaces[spaceId]->widget());

        space->setSnappingPT(snappingPT);
    }
}

void SpacesWidget::setSnappingRT(float snappingRT)
{
    this->m_snappingRT = snappingRT;

    foreach (QString spaceId, this->m_proxySpaces.keys())
    {
        Space *space = qobject_cast<Space *>(this->m_proxySpaces[spaceId]->widget());

        space->setSnappingRT(snappingRT);
    }
}

void SpacesWidget::setButtonText(QString text)
{
    this->m_buttonText = text;

    foreach (QString spaceId, this->m_proxySpaces.keys())
    {
        Space *space = qobject_cast<Space *>(this->m_proxySpaces[spaceId]->widget());

        space->setButtonText(text);
    }
}

void SpacesWidget::setButtonIcon(QString icon)
{
    this->m_buttonIcon = icon;

    foreach (QString spaceId, this->m_proxySpaces.keys())
    {
        Space *space = qobject_cast<Space *>(this->m_proxySpaces[spaceId]->widget());

        space->setButtonIcon(icon);
    }
}

void SpacesWidget::setButtonStyleSheet(QString styleSheet)
{
    this->m_buttonStyleSheet = styleSheet;

    foreach (QString spaceId, this->m_proxySpaces.keys())
    {
        Space *space = qobject_cast<Space *>(this->m_proxySpaces[spaceId]->widget());

        space->setButtonStyleSheet(styleSheet);
    }
}

void SpacesWidget::resetEditMode()
{
    this->setEditMode(false);
}

void SpacesWidget::resetSnapping()
{
    this->setSnapping(false);
}

void SpacesWidget::resetNParts()
{
    this->setNParts(0);
}

void SpacesWidget::resetSnappingPT()
{
    this->setSnappingPT(0);
}

void SpacesWidget::resetSnappingRT()
{
    this->setSnappingRT(0);
}

void SpacesWidget::resetButtonText()
{
    this->setButtonText("");
}

void SpacesWidget::resetButtonIcon()
{
    this->setButtonIcon("");
}

void SpacesWidget::resetButtonStyleSheet()
{
    this->setButtonStyleSheet("");
}

void SpacesWidget::on_changed(const QList<QRectF> &region)
{
    Q_UNUSED(region)

    QRectF boundingRect = this->scene()->itemsBoundingRect();
    this->scene()->setSceneRect(boundingRect);
    this->fitInView(boundingRect, Qt::KeepAspectRatio);
}
