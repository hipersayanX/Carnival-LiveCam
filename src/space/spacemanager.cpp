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
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsProxyWidget>
#include <QMoveEvent>
#include <QtDebug>

#include "../../include/space/spacemanager.h"

SpaceManager::SpaceManager(QObject *parent): QObject(parent)
{
    this->move = false;
    this->scaleAndRotate = false;
    this->m_viewPortSize = QSize(0, 0);
    this->mainSpace.setBackgroundBrush(Qt::black);
    this->m_toggleMaximizedButton = NULL;
    this->m_scaleAndRotateButton = NULL;
    this->m_editMode = false;
    this->oldReceiver = NULL;
    this->m_snapping = false;
    this->m_nParts = 1;
    this->m_snappingPT = 0;
    this->m_snappingRT = 0;
}

SpaceManager::~SpaceManager()
{
    foreach(QString spaceId, this->spacesWidgets.keys())
        this->removeSpace(spaceId);
}

QImage SpaceManager::render()
{
    this->spaceModel.updateRect();

    QRectF modelRect = this->spaceModel.rect();

    if (!modelRect.isValid())
    {
        QImage nullImg(1, 1, QImage::Format_RGB888);

        nullImg.fill(0);

        return nullImg;
    }

    QImage mainFrame(modelRect.size().toSize(), QImage::Format_RGB888);

    mainFrame.fill(0);

    QPainter mainPainter(&mainFrame);

    for (int space = 0; space < this->spaceModel.spaces().count(); space++)
    {
        Space spaceItem = this->spaceModel.spaces()[space];

        this->proxySpacesWidgets[spaceItem.spaceId()]->setZValue(space);
        this->proxySpacesWidgets[spaceItem.spaceId()]->setTransformOriginPoint(this->proxySpacesWidgets[spaceItem.spaceId()]->rect().center());
        this->proxySpacesWidgets[spaceItem.spaceId()]->setRotation(180.0 * spaceItem.rotation() / M_PI);
        this->proxySpacesWidgets[spaceItem.spaceId()]->setScale(spaceItem.scale());
        this->proxySpacesWidgets[spaceItem.spaceId()]->setPos(spaceItem.pos());
    }

    this->mainSpace.render(&mainPainter, QRectF(), modelRect);

    return mainFrame;
}

void SpaceManager::setControlButtons(QPushButton *toggleMaximizedButton, QPushButton *scaleAndRotateButton)
{
    this->m_toggleMaximizedButton = toggleMaximizedButton;
    this->m_scaleAndRotateButton = scaleAndRotateButton;
    this->m_toggleMaximizedButtonVisible = toggleMaximizedButton->isHidden();
    this->m_scaleAndRotateButtonVisible =  scaleAndRotateButton->isHidden();

    foreach (SpaceWidget *spaceWidget, this->spacesWidgets)
        spaceWidget->setControlButtons(toggleMaximizedButton, scaleAndRotateButton);

    this->m_toggleMaximizedButton->setHidden(true);
    this->m_scaleAndRotateButton->setHidden(true);
}

QPointF SpaceManager::mapViewPortToModel(const QPoint &pos, const QSize &viewportSize)
{
    QPointF posSpace(pos.x() * (this->spaceModel.rect().right() - this->spaceModel.rect().left()) /
                    viewportSize.width() + this->spaceModel.rect().left(),
                    pos.y() * (this->spaceModel.rect().bottom() - this->spaceModel.rect().top()) /
                    viewportSize.height() + this->spaceModel.rect().top());

    return posSpace;
}

void SpaceManager::updateButtonsSize()
{
    QRectF spaceModelRect = this->spaceModel.rect();

    for (int space =0; space < this->spaceModel.spaces().count(); space++)
    {
        Space spaceItem = this->spaceModel.spaces()[space];

        this->spacesWidgets[spaceItem.spaceId()]->rescaleButtons(spaceModelRect.size(),
                                                     this->m_viewPortSize,
                                                     spaceItem.scale());
    }
}

void SpaceManager::sendHoverEvent(QWidget *receiver, const QPoint &position)
{
    if (receiver != this->oldReceiver)
    {
        if (this->oldReceiver)
        {
            QHoverEvent hoverLeaveEvent(QEvent::Leave,
                                        QPoint(-1, -1),
                                        position);

            QApplication::sendEvent(this->oldReceiver, &hoverLeaveEvent);
        }

        if (receiver)
        {
            QHoverEvent hoverEnterEvent(QEvent::Enter,
                                        position,
                                        QPoint(-1, -1));

            QApplication::sendEvent(receiver, &hoverEnterEvent);
        }

        this->oldReceiver = receiver;
    }
}

QWidget *SpaceManager::sendMouseEvent(QEvent::Type type,
                                   const QPointF &position,
                                   Qt::MouseButton button,
                                   Qt::MouseButtons buttons,
                                   Qt::KeyboardModifiers modifiers)
{
    QGraphicsProxyWidget *proxyWidget = qgraphicsitem_cast<QGraphicsProxyWidget *>(this->mainSpace.itemAt(position, QTransform()));

    if (proxyWidget == NULL)
    {
        this->oldReceiver = NULL;

        return NULL;
    }

    QPoint proxyWidgetLocalPoint = proxyWidget->mapFromScene(position).toPoint();
    QWidget *widget = proxyWidget->widget();
    QWidget *controlWidget = widget->childAt(proxyWidgetLocalPoint);

    if (!controlWidget)
    {
        this->oldReceiver = widget;

        return widget;
    }

    QPoint controlWidgetLocalPoint = controlWidget->mapFromParent(proxyWidgetLocalPoint);

    this->sendHoverEvent(controlWidget, controlWidgetLocalPoint);

    QMouseEvent mouseEvent(type,
                      controlWidgetLocalPoint,
                      button,
                      buttons,
                      modifiers);

    QApplication::sendEvent(controlWidget, &mouseEvent);

    return controlWidget;
}

void SpaceManager::setSpace(QString spaceId, const QImage &frame)
{
    if (this->spacesWidgets.contains(spaceId))
    {
        this->spaceModel.setSpace(spaceId, frame.size());
        this->spacesWidgets[spaceId]->setFrame(frame);
    }
    else
    {
        this->spaceModel.setSpace(spaceId, frame.size());
        this->spacesWidgets[spaceId] = new SpaceWidget(frame);
        this->spacesWidgets[spaceId]->setEditMode(this->m_editMode);

        if (this->m_toggleMaximizedButton)
            this->m_toggleMaximizedButton->setHidden(this->m_toggleMaximizedButtonVisible);

        if (this->m_scaleAndRotateButton)
            this->m_scaleAndRotateButton->setHidden(this->m_scaleAndRotateButtonVisible);

        this->spacesWidgets[spaceId]->setControlButtons(this->m_toggleMaximizedButton, this->m_scaleAndRotateButton);

        if (this->m_toggleMaximizedButton)
            this->m_toggleMaximizedButton->setHidden(true);

        if (this->m_scaleAndRotateButton)
            this->m_scaleAndRotateButton->setHidden(true);

        this->proxySpacesWidgets[spaceId] = this->mainSpace.addWidget(this->spacesWidgets[spaceId]);
    }
}

void SpaceManager::removeSpace(QString spaceId)
{
    if (this->spacesWidgets.contains(spaceId))
    {
        this->oldReceiver = NULL;
        this->spaceModel.removeSpace(spaceId);
        this->mainSpace.removeItem(this->proxySpacesWidgets[spaceId]);
        delete this->spacesWidgets[spaceId];
        this->spacesWidgets.remove(spaceId);
        this->proxySpacesWidgets.remove(spaceId);
    }
}

void SpaceManager::updateSpaces(const QList<QVariant> &devices)
{
    QStringList devicesId;
    QStringList orphanDevices;

    this->oldReceiver = NULL;

    foreach (QVariant device, devices)
        devicesId << device.toMap()["deviceId"].toString();

    foreach (Space space, this->spaceModel.spaces())
        if (!devicesId.contains(space.spaceId()))
            orphanDevices << space.spaceId();

    foreach (QString orphanDevice, orphanDevices)
        this->removeSpace(orphanDevice);
}

void SpaceManager::setSnapping(bool snapping, int nParts, qreal snappingPT, qreal snappingRT)
{
    this->m_snapping = snapping;
    this->m_nParts = nParts;
    this->m_snappingPT = snappingPT;
    this->m_snappingRT = snappingRT;

    this->spaceModel.setSnapping(snapping,
                                 nParts,
                                 snappingPT * this->spaceModel.rect().width()/ this->m_viewPortSize.width(),
                                 snappingRT);
}

QSize SpaceManager::viewPortSize()
{
    return this->m_viewPortSize;
}

bool SpaceManager::editMode()
{
    return this->m_editMode;
}

void SpaceManager::setViewPortSize(QSize size)
{
    this->m_viewPortSize = size;

    this->spaceModel.setSnapping(this->m_snapping,
                                 this->m_nParts,
                                 this->m_snappingPT * this->spaceModel.rect().width()/ this->m_viewPortSize.width(),
                                 this->m_snappingRT);

    this->updateButtonsSize();
}

void SpaceManager::setEditMode(bool value)
{
    this->m_editMode = value;

    foreach (SpaceWidget *spaceWidget, this->spacesWidgets)
        spaceWidget->setEditMode(value);
}

void SpaceManager::resetViewPortSize()
{
    this->m_viewPortSize = QSize(0, 0);
}

void SpaceManager::resetEditMode()
{
    this->m_editMode = false;

    foreach (SpaceWidget *spaceWidget, this->spacesWidgets)
        spaceWidget->setEditMode(false);
}

void SpaceManager::toggleEditMode()
{
    this->m_editMode = !this->m_editMode;

    foreach (SpaceWidget *spaceWidget, this->spacesWidgets)
        spaceWidget->setEditMode(this->m_editMode);
}

void SpaceManager::selectSpace(QString spaceId)
{
    this->spaceModel.selectSpace(spaceId);
}

void SpaceManager::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (!event)
        return;

    if (!this->m_editMode)
    {
        delete event;

        return;
    }

//    this->spaceModel.selectSpace(this->mapToMainSpace(event->pos(), this->m_viewPortSize));

    this->sendMouseEvent(QEvent::MouseButtonDblClick,
                         this->mapViewPortToModel(event->pos(), this->m_viewPortSize),
                         event->button(),
                         event->buttons(),
                         Qt::NoModifier);

    delete event;
}

void SpaceManager::mouseMoveEvent(QMouseEvent *event)
{
    if (!event)
        return;

    if (!this->m_editMode)
    {
        delete event;

        return;
    }

    QPointF modelMousePos = this->mapViewPortToModel(event->pos(), this->m_viewPortSize);

    this->sendMouseEvent(QEvent::MouseMove,
                         modelMousePos,
                         event->button(),
                         event->buttons(),
                         Qt::NoModifier);

    if (this->scaleAndRotate)
    {
        this->spaceModel.scaleAndRotateSpace(modelMousePos);
        this->updateButtonsSize();
    }

    if (this->move)
        this->spaceModel.moveSpace(modelMousePos);

    delete event;
}

void SpaceManager::mousePressEvent(QMouseEvent *event)
{
    if (!event)
        return;

    if (!this->m_editMode)
    {
        delete event;

        return;
    }

    QPointF modelMousePos = this->mapViewPortToModel(event->pos(), this->m_viewPortSize);

    this->spaceModel.selectSpace(modelMousePos);

    QWidget *widget = this->sendMouseEvent(QEvent::MouseButtonPress,
                                           modelMousePos,
                                           event->button(),
                                           event->buttons(),
                                            Qt::NoModifier);

    if (widget && widget->objectName() == "btnToggleMaximize")
        this->spaceModel.toggleMaximizedSpace();
    else if (widget && widget->objectName() == "btnScaleAndRotate" && event->button() == Qt::LeftButton)
        this->scaleAndRotate = true;
    else if (this->spaceModel.currentSelectedSpace() != "")
        this->move = true;

    delete event;
}

void SpaceManager::mouseReleaseEvent(QMouseEvent *event)
{
    if (!event)
        return;

    if (!this->m_editMode)
    {
        delete event;

        return;
    }

    QPointF modelMousePos = this->mapViewPortToModel(event->pos(), this->m_viewPortSize);

//    this->spaceModel.selectSpace(this->mapToMainSpace(event->pos(), this->m_viewPortSize));

    this->sendMouseEvent(QEvent::MouseButtonRelease,
                         modelMousePos,
                         event->button(),
                         event->buttons(),
                         Qt::NoModifier);

    if (event->button() == Qt::LeftButton)
    {
        this->move = false;
        this->scaleAndRotate = false;
    }

    delete event;
}
