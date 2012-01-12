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

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsProxyWidget>
#include <QMoveEvent>

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
}

SpaceManager::~SpaceManager()
{
    if (this->m_toggleMaximizedButton)
        delete this->m_toggleMaximizedButton;

    if (this->m_scaleAndRotateButton)
        delete this->m_scaleAndRotateButton;

    foreach(QString spaceId, this->spacesWidgets.keys())
        this->removeSpace(spaceId);
}

QImage SpaceManager::render()
{
    QImage mainFrame(this->mainSpace.width(), this->mainSpace.height(), QImage::Format_RGB888);

    mainFrame.fill(0);

    QPainter mainPainter(&mainFrame);

    for (int space = 0; space < this->spaceModel.spaces().count(); space++)
    {
        Space spaceItem = this->spaceModel.spaces()[space];
        this->proxySpacesWidgets[spaceItem.spaceId()]->setZValue(space);

        this->proxySpacesWidgets[spaceItem.spaceId()]->setTransform(QTransform()
                                                       .translate(spaceItem.size().width() / 2, spaceItem.size().height() / 2)
                                                       .rotate(-spaceItem.rotation(), Qt::ZAxis)
                                                       .scale(spaceItem.scale(), spaceItem.scale())
                                                       .translate(-spaceItem.size().width() / 2, -spaceItem.size().height() / 2));
    }

    this->mainSpace.render(&mainPainter);

    return mainFrame;
}

void SpaceManager::setControlButtons(QPushButton *toggleMaximizedButton, QPushButton *scaleAndRotateButton)
{
    if (this->m_toggleMaximizedButton)
        delete this->m_toggleMaximizedButton;

    if (this->m_scaleAndRotateButton)
        delete this->m_scaleAndRotateButton;

    this->m_toggleMaximizedButton = toggleMaximizedButton;
    this->m_scaleAndRotateButton = scaleAndRotateButton;

    foreach (SpaceWidget *spaceWidget, this->spacesWidgets)
        spaceWidget->setControlButtons(toggleMaximizedButton, scaleAndRotateButton);
}

QPoint SpaceManager::mapToMainSpace(const QPoint &pos, const QSize &viewportSize)
{
    QPoint posSpace(pos.x() * this->mainSpace.width() / viewportSize.width(),
                    pos.y() * this->mainSpace.height() / viewportSize.height());

    return posSpace;
}

QWidget *SpaceManager::sendMouseEvent(QEvent::Type type,
                                   const QPoint &position,
                                   Qt::MouseButton button,
                                   Qt::MouseButtons buttons,
                                   Qt::KeyboardModifiers modifiers)
{
    QGraphicsProxyWidget *proxyWidget = qgraphicsitem_cast<QGraphicsProxyWidget *>(this->mainSpace.itemAt(position, QTransform()));

    if (proxyWidget == NULL)
        return NULL;

    QPoint proxyWidgetLocalPoint = proxyWidget->mapFromScene(position).toPoint();
    QWidget *widget = proxyWidget->widget();
    QWidget *controlWidget = widget->childAt(proxyWidgetLocalPoint);

    if (!controlWidget)
        return widget;

    QMouseEvent event(type,
                      controlWidget->mapFromParent(proxyWidgetLocalPoint),
                      button,
                      buttons,
                      modifiers);

    QApplication::sendEvent(controlWidget, &event);

    return controlWidget;
}

void SpaceManager::setSpace(QString spaceId, const QImage &frame)
{
    if (this->spacesWidgets.contains(spaceId))
        this->spacesWidgets[spaceId]->setFrame(frame);
    else
    {
        this->spaceModel.addSpace(spaceId, frame.size());
        this->spacesWidgets[spaceId] = new SpaceWidget(frame);
        this->spacesWidgets[spaceId]->setControlButtons(this->m_toggleMaximizedButton, this->m_scaleAndRotateButton);
        this->proxySpacesWidgets[spaceId] = this->mainSpace.addWidget(this->spacesWidgets[spaceId]);
        this->proxySpacesWidgets[spaceId]->setTransformOriginPoint(this->spacesWidgets[spaceId]->width() / 2,
                                                                               this->spacesWidgets[spaceId]->height() / 2);
    }
}

void SpaceManager::removeSpace(QString spaceId)
{
    if (this->spacesWidgets.contains(spaceId))
    {
        this->spaceModel.removeSpace(spaceId);
        this->mainSpace.removeItem(this->proxySpacesWidgets[spaceId]);
        delete this->spacesWidgets[spaceId];
        this->spacesWidgets.remove(spaceId);
        this->proxySpacesWidgets.remove(spaceId);
    }
}

void SpaceManager::setSnapping(bool snapping, int nParts, qreal snappingPT, qreal snappingRT)
{
    this->spaceModel.setSnapping(snapping, nParts, snappingPT, snappingRT);
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
        spaceWidget->resetEditMode();
}

void SpaceManager::toggleEditMode()
{
    this->m_editMode = !this->m_editMode;

    foreach (SpaceWidget *spaceWidget, this->spacesWidgets)
        spaceWidget->toggleEditMode();
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

    this->spaceModel.selectSpace(this->mapToMainSpace(event->pos(), this->m_viewPortSize));

    this->sendMouseEvent(QEvent::MouseButtonDblClick,
                         this->mapToMainSpace(event->pos(), this->m_viewPortSize),
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

    this->sendMouseEvent(QEvent::MouseMove,
                         this->mapToMainSpace(event->pos(), this->m_viewPortSize),
                         event->button(),
                         event->buttons(),
                         Qt::NoModifier);

    if (this->scaleAndRotate)
        this->spaceModel.scaleAndRotateSpace(this->mapToMainSpace(event->pos(), this->m_viewPortSize));

    if (this->move)
        this->spaceModel.moveSpace(this->mapToMainSpace(event->pos(), this->m_viewPortSize));

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

    this->spaceModel.selectSpace(this->mapToMainSpace(event->pos(), this->m_viewPortSize));

    QWidget *widget = this->sendMouseEvent(QEvent::MouseButtonPress,
                                           this->mapToMainSpace(event->pos(), this->m_viewPortSize),
                                           event->button(),
                                           event->buttons(),
                                            Qt::NoModifier);

    if (!widget)
        return;
    else if (widget->objectName() == "wdgSpaceWidget")
        this->move = true;
    else if (widget->objectName() == "btnToggleMaximize")
        this->spaceModel.toggleMaximizedSpace();
    else if (widget->objectName() == "btnScaleAndRotate" && event->button() == Qt::LeftButton)
        this->scaleAndRotate = true;

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

    this->sendMouseEvent(QEvent::MouseButtonRelease,
                         this->mapToMainSpace(event->pos(), this->m_viewPortSize),
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
