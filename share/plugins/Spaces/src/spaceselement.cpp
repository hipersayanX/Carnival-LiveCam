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

#include "spaceselement.h"

SpacesElement::SpacesElement(): Element()
{
    this->resetSpaces();
    this->resetEditMode();
    this->resetSnapping();
    this->resetNParts();
    this->resetSnappingPT();
    this->resetSnappingRT();
    this->resetRotateButtonStyleSheet();
    this->resetRotateButtonText();

    this->m_move = false;
    this->m_scaleAndRotate = false;
    this->mainSpace.setBackgroundBrush(Qt::black);
    this->oldReceiver = NULL;

    QObject::connect(&this->m_spaceWidget, SIGNAL(spaceMoved(qint32, qint32)), this, SLOT(onSpaceMoved(qint32, qint32)));
}

SpacesElement::~SpacesElement()
{
    foreach(QString spaceId, this->spacesWidgets.keys())
        this->removeSpace(spaceId);
}

QStringList SpacesElement::spaces()
{
    return this->m_spaces;
}

bool SpacesElement::editMode()
{
    return this->m_editMode;
}

bool SpacesElement::snapping()
{
    return this->m_snapping;
}

int SpacesElement::nParts()
{
    return this->m_nParts;
}

float SpacesElement::snappingPT()
{
    return this->m_snappingPT;
}

float SpacesElement::snappingRT()
{
    return this->m_snappingRT;
}

QString SpacesElement::rotateButtonStyleSheet()
{
    return this->m_rotateButtonStyleSheet;
}

QString SpacesElement::rotateButtonText()
{
    return this->m_rotateButtonText;
}

bool SpacesElement::start()
{
    return true;
}

bool SpacesElement::stop()
{
    return true;
}

QPointF SpacesElement::mapViewPortToModel(const QPoint &pos, const QSize &viewportSize)
{
    QPointF posSpace(pos.x() * (this->m_spaceWidget.rect().right() - this->m_spaceWidget.rect().left()) /
                    viewportSize.width() + this->m_spaceWidget.rect().left(),
                    pos.y() * (this->m_spaceWidget.rect().bottom() - this->m_spaceWidget.rect().top()) /
                    viewportSize.height() + this->m_spaceWidget.rect().top());

    return posSpace;
}

QStringList SpacesElement::activeSpaces()
{
    QStringList spaces;

    foreach (Space space, this->m_spaceWidget.spaces())
        spaces << space.spaceId();

    return spaces;
}

QImage SpacesElement::byteArrayToImage(QByteArray *ba)
{
    if (!ba)
        return QImage();

    QDataStream iDataStream(ba, QIODevice::ReadOnly);
    int type;

    iDataStream >> type;

    if (type != ARGB32)
        return QImage();

    int width;
    int height;

    iDataStream >> width >> height;

    QByteArray pixels(4 * width * height, 0);
    iDataStream.readRawData(pixels.data(), pixels.size());

    return QImage((const uchar *) pixels.constData(), width, height, QImage::Format_ARGB32);
}

void SpacesElement::imageToByteArray(QImage *image, QByteArray *ba)
{
    if (!image || !ba)
        return;

    QDataStream oDataStream(ba, QIODevice::WriteOnly);

    oDataStream << ARGB32 << image->width() << image->height();
    oDataStream.writeRawData((const char *) image->constBits(), image->byteCount());
}

void SpacesElement::updateButtonsSize()
{
    QRectF spaceModelRect = this->m_spaceWidget.rect();

    for (qint32 space =0; space < this->m_spaceWidget.spaces().count(); space++)
    {
        Space spaceItem = this->m_spaceWidget.spaces()[space];

        this->spacesWidgets[spaceItem.spaceId()]->rescaleButtons(spaceModelRect.size(),
                                                     this->m_viewPortSize,
                                                     spaceItem.scale());
    }
}

void SpacesElement::sendHoverEvent(QWidget *receiver, const QPoint &position)
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

QWidget *SpacesElement::sendMouseEvent(QEvent::Type type,
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

void SpacesElement::onSpaceMoved(qint32 from, qint32 to)
{
    emit spaceMoved(from, to);
}

void SpacesElement::iStream(QByteArray *data)
{
    QString spaceId = this->sender()->objectName();
    QImage frame(this->byteArrayToImage(data));

    if (this->spacesWidgets.contains(spaceId))
    {
        this->m_spaceWidget.setSpace(spaceId, frame.size());
        this->spacesWidgets[spaceId]->setFrame(frame);
        this->m_spaceWidget.updateRect();

        QRectF modelRect = this->m_spaceWidget.rect();

        if (!modelRect.isValid())
        {
            QImage nullImg(1, 1, QImage::Format_ARGB32);
            nullImg.fill(0);
            this->imageToByteArray(&nullImg, &this->m_bFrame);
            emit(oStream(&this->m_bFrame));
        }

        QImage mainFrame(modelRect.size().toSize(), QImage::Format_ARGB32);
        mainFrame.fill(0);
        QPainter mainPainter(&mainFrame);

        for (qint32 space = 0; space < this->m_spaceWidget.spaces().count(); space++)
        {
            Space spaceItem = this->m_spaceWidget.spaces()[space];

            this->proxySpacesWidgets[spaceItem.spaceId()]->setZValue(space);
            this->proxySpacesWidgets[spaceItem.spaceId()]->setTransformOriginPoint(this->proxySpacesWidgets[spaceItem.spaceId()]->rect().center());
            this->proxySpacesWidgets[spaceItem.spaceId()]->setRotation(180.0 * spaceItem.rotation() / M_PI);
            this->proxySpacesWidgets[spaceItem.spaceId()]->setScale(spaceItem.scale());
            this->proxySpacesWidgets[spaceItem.spaceId()]->setPos(spaceItem.pos());
        }

        this->mainSpace.render(&mainPainter, QRectF(), modelRect);
        this->imageToByteArray(&mainFrame, &this->m_bFrame);
        emit(oStream(&this->m_bFrame));
    }
}

void SpacesElement::iEvent(QEvent *event)
{
    // bool QGraphicsScene::sendEvent ( QGraphicsItem * item, QEvent * event )
    switch (event->type())
    {
        case QEvent::MouseMove:
            QPointF modelMousePos = this->mapViewPortToModel(event->pos(), this->m_viewPortSize);

            if (!this->m_editMode)
            {
                QString spaceId;
                QPointF pos = this->m_spaceWidget.mapToLocal(modelMousePos, &spaceId);

                if (spaceId != "")
                {
                    QSizeF size = this->m_spaceWidget.spaceSize(spaceId);
                    QPointF npos = pos + QPointF(size.width(), size.height()) / 2;

                    QMouseEvent mouseEvent(QEvent::MouseMove,
                                           npos.toPoint(),
                                           event->button(),
                                           event->buttons(),
                                           Qt::NoModifier);

                    emit mouseMove(spaceId, &mouseEvent);
                }
            }
            else
            {
                this->sendMouseEvent(QEvent::MouseMove,
                                     modelMousePos,
                                     event->button(),
                                     event->buttons(),
                                     Qt::NoModifier);

                if (this->m_scaleAndRotate)
                {
                    this->m_spaceWidget.scaleAndRotateSpace(modelMousePos);
                    this->updateButtonsSize();
                }

                if (this->m_move)
                    this->m_spaceWidget.moveSpace(modelMousePos);
            }

            delete event;
        break;

        case QEvent::MouseButtonPress:
            QPointF modelMousePos = this->mapViewPortToModel(event->pos(), this->m_viewPortSize);

            if (!this->m_editMode)
            {
                QString spaceId;
                QPointF pos = this->m_spaceWidget.mapToLocal(modelMousePos, &spaceId);

                if (spaceId != "")
                {
                    QSizeF size = this->m_spaceWidget.spaceSize(spaceId);
                    QPointF npos = pos + QPointF(size.width(), size.height()) / 2;

                    QMouseEvent mouseEvent(QEvent::MouseButtonPress,
                                           npos.toPoint(),
                                           event->button(),
                                           event->buttons(),
                                           Qt::NoModifier);

                    emit mousePress(spaceId, &mouseEvent);
                }
            }
            else
            {
                this->m_spaceWidget.selectSpace(modelMousePos);

                QWidget *widget = this->sendMouseEvent(QEvent::MouseButtonPress,
                                                       modelMousePos,
                                                       event->button(),
                                                       event->buttons(),
                                                       Qt::NoModifier);

                if (widget && widget->objectName() == "btnScaleAndRotate" && event->button() == Qt::LeftButton)
                    this->m_scaleAndRotate = true;
                else if (this->m_spaceWidget.currentSelectedSpace() != "")
                    this->m_move = true;
            }

            delete event;
        break;

        case QEvent::MouseButtonRelease:
            QPointF modelMousePos = this->mapViewPortToModel(event->pos(), this->m_viewPortSize);

            if (!this->m_editMode)
            {
                QString spaceId;
                QPointF pos = this->m_spaceWidget.mapToLocal(modelMousePos, &spaceId);

                if (spaceId != "")
                {
                    QSizeF size = this->m_spaceWidget.spaceSize(spaceId);
                    QPointF npos = pos + QPointF(size.width(), size.height()) / 2;

                    QMouseEvent mouseEvent(QEvent::MouseButtonRelease,
                                           npos.toPoint(),
                                           event->button(),
                                           event->buttons(),
                                           Qt::NoModifier);

                    emit mouseRelease(spaceId, &mouseEvent);
                }
            }
            else
            {
                this->sendMouseEvent(QEvent::MouseButtonRelease,
                                     modelMousePos,
                                     event->button(),
                                     event->buttons(),
                                     Qt::NoModifier);

                if (event->button() == Qt::LeftButton)
                {
                    this->m_move = false;
                    this->m_scaleAndRotate = false;
                }
            }

            delete event;
        break;

        case QEvent::HoverEnter:
        break;

        case QEvent::HoverLeave:
        break;

        default:
            foreach (Element *element, this->m_srcs)
                element->iEvent(event);
        break;
    }
}

void SpacesElement::setPipeline(Pipeline *pipeline)
{
    Q_UNUSED(pipeline)
}

void SpacesElement::setPeers(QList<Element *> srcs, QList<Element *> sinks)
{
    this->m_srcs = srcs;
    this->m_sinks = sinks;

    if (this->spacesWidgets.contains(spaceId))
    {
        this->m_spaceWidget.setSpace(spaceId, frame.size());
        this->spacesWidgets[spaceId]->setFrame(frame);
    }
    else
    {
        this->m_spaceWidget.setSpace(spaceId, frame.size());
        this->spacesWidgets[spaceId] = new SpaceWidget(frame);
        this->spacesWidgets[spaceId]->setEditMode(this->m_editMode);

        this->spacesWidgets[spaceId]->setControlButtons(this->m_toggleMaximizedButton, this->m_scaleAndRotateButton);
        this->proxySpacesWidgets[spaceId] = this->mainSpace.addWidget(this->spacesWidgets[spaceId]);
    }
}

void SpacesElement::setSpaces(QStringList spaces)
{
    this->m_spaces = spaces;
}

void SpacesElement::setEditMode(bool value)
{
    this->m_editMode = value;

    foreach (SpaceWidget *spaceWidget, this->spacesWidgets)
        spaceWidget->setEditMode(value);
}

void SpacesElement::setSnapping(bool snapping)
{
    this->m_snapping = snapping;
}

void SpacesElement::setNParts(int nParts)
{
    this->m_nParts = nParts;
}

void SpacesElement::setSnappingPT(float snappingPT)
{
    this->m_snappingPT = snappingPT;
}

void SpacesElement::setSnappingRT(float snappingRT)
{
    this->m_snappingRT = snappingRT;
}

void SpacesElement::setRotateButtonStyleSheet(QString rotateButtonStyleSheet)
{
    this->m_rotateButtonStyleSheet = rotateButtonStyleSheet;
}

void SpacesElement::setRotateButtonText(QString rotateButtonText)
{
    this->m_rotateButtonText = rotateButtonText;
}

void SpacesElement::resetSpaces()
{
    this->setSpaces(QStringList());
}

void SpacesElement::resetEditMode()
{
    this->setEditMode(false);

    foreach (SpaceWidget *spaceWidget, this->spacesWidgets)
        spaceWidget->setEditMode(false);
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

void SpacesElement::resetRotateButtonStyleSheet()
{
    this->setRotateButtonStyleSheet("");
}

void SpacesElement::resetRotateButtonText()
{
    this->setRotateButtonText("");
}

void SpacesElement::removeSpace(QString spaceId)
{
    if (this->spacesWidgets.contains(spaceId))
    {
        this->oldReceiver = NULL;
        this->m_spaceWidget.removeSpace(spaceId);
        this->mainSpace.removeItem(this->proxySpacesWidgets[spaceId]);
        delete this->spacesWidgets[spaceId];
        this->spacesWidgets.remove(spaceId);
        this->proxySpacesWidgets.remove(spaceId);
    }
}

void SpacesElement::updateSpaces(const QList<QVariant> &devices)
{
    QStringList devicesId;
    QStringList orphanDevices;

    this->oldReceiver = NULL;

    foreach (QVariant device, devices)
        devicesId << device.toMap()["deviceId"].toString();

    foreach (Space space, this->m_spaceWidget.spaces())
        if (!devicesId.contains(space.spaceId()))
            orphanDevices << space.spaceId();

    foreach (QString orphanDevice, orphanDevices)
        this->removeSpace(orphanDevice);
}

void SpacesElement::moveSpace(qint32 from, qint32 to)
{
    this->m_spaceWidget.moveSpace(from, to);
}

void SpacesElement::selectSpace(QString spaceId)
{
    this->m_spaceWidget.selectSpace(spaceId);
}
