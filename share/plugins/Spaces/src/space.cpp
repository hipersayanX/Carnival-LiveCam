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

#include "space.h"

class SpacesWidget;

Space::Space(QWidget *parent): QWidget(parent)
{
    this->setupUi(this);
    this->setLayout(this->gridLayout);

    this->btnScaleAndRotate->installEventFilter(this);
    this->btnScaleAndRotate->hide();
    this->lblFrame->installEventFilter(this);

    this->m_proxy = nullptr;

    this->m_move = false;
    this->m_rotateScale = false;
    this->m_editMode = false;
    this->m_fstFrame = true;

    this->resetEditMode();
    this->resetSnapping();
    this->resetNParts();
    this->resetSnappingPT();
    this->resetSnappingRT();
    this->resetButtonText();
    this->resetButtonIcon();
    this->resetButtonStyleSheet();
}

bool Space::editMode()
{
    return this->m_editMode;
}

bool Space::snapping()
{
    return this->m_snapping;
}

int Space::nParts()
{
    return this->m_snapAngles.length();
}

float Space::snappingPT()
{
    return this->m_snappingPT;
}

float Space::snappingRT()
{
    return this->m_snappingRT;
}

QString Space::buttonText()
{
    return this->btnScaleAndRotate->text();
}

QString Space::buttonIcon()
{
    return this->m_buttonIconFileName;
}

QString Space::buttonStyleSheet()
{
    return this->btnScaleAndRotate->styleSheet();
}

void Space::setSpaceId(QString spaceId)
{
    this->setProperty("spaceId", spaceId);
    this->setStyleSheet(QString("QWidget[spaceId=\"%1\"]{background-color: rgba(0, 0, 0, 0);}").arg(spaceId));
}

void Space::setProxy(QGraphicsProxyWidget *proxy)
{
    this->m_proxy = proxy;

    this->m_proxy->setFlags(QGraphicsItem::ItemIsMovable |
                            QGraphicsItem::ItemIsSelectable |
                            QGraphicsItem::ItemIsFocusable);
}

void Space::setFrame(const QImage &frame)
{
    if (this->m_fstFrame)
    {
        this->resize(frame.size());
        this->lblFrame->resize(frame.size());

        this->m_fstFrame = false;
    }
    else if (this->lblFrame->pixmap()->size() != frame.size())
    {
        QSize size = frame.size();

        size.scale(this->size(), Qt::KeepAspectRatio);

        QPointF widgetSceneCenter = this->m_proxy->mapToScene(this->m_proxy->rect().center());
        QPointF pos = widgetSceneCenter - 0.5 * QPointF(size.width(), size.height());

        this->m_proxy->setPos(pos);
        this->m_proxy->resize(QSizeF(size));
        this->lblFrame->resize(size);
    }

    this->lblFrame->setPixmap(QPixmap::fromImage(frame));
}

void Space::snapLines(QList<float> *hLines, QList<float> *vLines)
{
    if (hLines)
        hLines->clear();

    if (hLines)
        vLines->clear();

    foreach (QGraphicsItem *space, this->m_proxy->scene()->items())
    {
        QRectF boundingRect = space->mapRectToParent(space->boundingRect());

        if (hLines)
        {
            float top = boundingRect.top();

            if (!hLines->contains(top))
                hLines->append(top);

            float bottom = boundingRect.bottom();

            if (!hLines->contains(bottom))
                hLines->append(bottom);
        }

        if (vLines)
        {
            float left = boundingRect.left();

            if (!vLines->contains(left))
                vLines->append(left);

            float right = boundingRect.right();

            if (!vLines->contains(right))
                vLines->append(right);
        }
    }

    if (hLines)
        qSort(hLines->begin(), hLines->end());

    if (vLines)
        qSort(vLines->begin(), vLines->end());
}

float Space::calculateAngle(QPoint point)
{
    float angle;

    if (point.x() >= 0 && point.y() <= 0)
        angle = atan2(-point.y(), point.x());
    else if (point.x() <= 0 && point.y() <= 0)
        angle = atan2(-point.x(), -point.y()) + M_PI / 2.0;
    else if (point.x() <= 0 && point.y() >= 0)
        angle = atan2(point.y(), -point.x()) + M_PI;
    else
        angle = atan2(point.x(), point.y()) + 3.0 * M_PI / 2.0;

    return 180.0 * angle / M_PI;
}

void Space::bringToFront()
{
    QList<QGraphicsItem *> spaces = this->m_proxy->scene()->items();

    foreach (QGraphicsItem *space, spaces)
        if (space != this->m_proxy && space->zValue() > this->m_proxy->zValue())
        {
            int from = space->zValue();
            int to = space->zValue() - 1;

            space->setZValue(to);

            emit(static_cast<Space *>(static_cast<QGraphicsProxyWidget *>(space)->widget())->spaceMoved(from, to));
        }

    int from = this->m_proxy->zValue();
    int to = spaces.length() - 1;

    this->m_proxy->setZValue(to);
    emit(this->spaceMoved(from, to));
}

bool Space::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == this->btnScaleAndRotate ||
        watched == this->lblFrame)
    {
        if (event->type() == QEvent::MouseButtonDblClick ||
            event->type() == QEvent::MouseButtonPress ||
            event->type() == QEvent::MouseButtonRelease ||
            event->type() == QEvent::MouseMove)
        {
            if (watched == this->btnScaleAndRotate &&
                event->type() == QEvent::MouseButtonDblClick)
                return QWidget::eventFilter(watched, event);

            if (watched == this->btnScaleAndRotate &&
                event->type() == QEvent::MouseButtonPress)
                this->btnScaleAndRotate->setDown(true);

            if (watched == this->btnScaleAndRotate &&
                event->type() == QEvent::MouseButtonRelease)
                this->btnScaleAndRotate->setDown(false);

            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            QWidget *widget = static_cast<QWidget *>(watched);
            QPoint pos = widget->mapToParent(mouseEvent->pos());
            QMouseEvent mEvent(event->type(), pos, mouseEvent->button(), mouseEvent->button(), mouseEvent->modifiers());

            if (event->type() == QEvent::MouseButtonDblClick)
                this->mouseDoubleClickEvent(&mEvent);
            else if (event->type() == QEvent::MouseButtonPress)
                this->mousePressEvent(&mEvent);
            else if (event->type() == QEvent::MouseButtonRelease)
                this->mouseReleaseEvent(&mEvent);
            else if (event->type() == QEvent::MouseMove)
                this->mouseMoveEvent(&mEvent);
        }

        return false;
    }

    return QWidget::eventFilter(watched, event);
}

bool Space::resendMouseEvent(QMouseEvent *event)
{
    QCoreApplication *coreApplication = QCoreApplication::instance();

    if (!coreApplication)
        return false;

    QObject *element = coreApplication->findChild<QObject *>(this->property("spaceId").toString());

    if (!element)
        return false;

    int x = event->x() * (this->lblFrame->pixmap()->width() - 1) / (float) (this->width() - 1);
    int y = event->y() * (this->lblFrame->pixmap()->height() - 1) / (float) (this->height() - 1);

    QMouseEvent mEvent(event->type(), QPoint(x, y), event->button(), event->button(), event->modifiers());

    return QCoreApplication::sendEvent(element, &mEvent);
}

void Space::rescaleButton(float factor)
{
    this->btnScaleAndRotate->resize(factor * this->btnScaleAndRotate->size());
    this->btnScaleAndRotate->setIconSize(factor * this->btnScaleAndRotate->iconSize());
    this->btnScaleAndRotate->setMaximumSize(factor * this->btnScaleAndRotate->maximumSize());
    this->btnScaleAndRotate->setMinimumSize(factor * this->btnScaleAndRotate->minimumSize());
}

void Space::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    if (this->m_editMode)
    {
        QPointF center = this->m_proxy->mapToScene(this->m_proxy->rect().center());

        this->m_proxy->setTransformOriginPoint(this->m_proxy->rect().center());

        QSize size = this->lblFrame->pixmap()->size();
        QSize minimumSize = this->minimumSize();

        if (size.width() < minimumSize.width() || size.height() < minimumSize.height())
            size.scale(minimumSize, Qt::KeepAspectRatioByExpanding);

        QPointF pos = QPointF(center) - 0.5 * QPointF(size.width(), size.height());

        this->m_proxy->setPos(pos);
        this->m_proxy->setRotation(0);
        this->m_proxy->resize(QSizeF(size));
        this->lblFrame->resize(size);
    }
    else
        this->resendMouseEvent(event);
}

void Space::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    if (this->m_editMode)
    {
        this->bringToFront();

        if (this->btnScaleAndRotate->isDown())
        {
            this->m_mousePos0 = QCursor::pos();
            this->m_widgetGlobalCenter = this->m_proxy->scene()->views()[0]->mapToGlobal(this->m_proxy->scene()->views()[0]->mapFromScene(this->m_proxy->mapToScene(this->m_proxy->rect().center())));
            this->m_widgetSceneCenter = this->m_proxy->mapToScene(this->m_proxy->rect().center());
            this->snapLines(&this->m_hLines0, &this->m_vLines0);

            this->m_rotateScale = true;
        }
        else
        {
            this->m_mousePos0 = QCursor::pos();
            this->m_pos0 = this->m_proxy->pos();
            this->snapLines(&this->m_hLines0, &this->m_vLines0);

            this->m_move = true;
        }
    }
    else
        this->resendMouseEvent(event);
}

void Space::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    if (this->m_editMode)
    {
        this->m_move = false;
        this->m_rotateScale = false;
        this->m_mousePos0 = QPoint();
        this->m_widgetGlobalCenter = QPoint();
        this->m_widgetSceneCenter = QPointF();
    }
    else
        this->resendMouseEvent(event);
}

void Space::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    if (this->m_editMode)
    {
        if (this->m_rotateScale)
        {
            QPoint mousePos1 = QCursor::pos();

            QPoint pi = this->m_mousePos0 - this->m_widgetGlobalCenter;
            QPoint pf = mousePos1 - this->m_widgetGlobalCenter;

            float factor = sqrt(pow(pf.x(), 2) + pow(pf.y(), 2));

            if (pi.x() == 0 && pi.y() == 0)
                factor /= 0.5;
            else
                factor /= sqrt(pow(pi.x(), 2) + pow(pi.y(), 2));

            this->m_proxy->setTransformOriginPoint(this->m_proxy->rect().center());
            QSizeF size = factor * this->m_proxy->size();
            QSize minimumSize = this->minimumSize();

            if (size.width() < minimumSize.width() || size.height() < minimumSize.height())
                size.scale(QSizeF(minimumSize), Qt::KeepAspectRatioByExpanding);

            QPointF pos = this->m_widgetSceneCenter - 0.5 * QPointF(size.width(), size.height());
            float rotation = this->m_proxy->rotation() - this->calculateAngle(pf) + this->calculateAngle(pi);

            if (this->m_snapping)
            {
                while (rotation >= 360)
                    rotation -= 360;

                while (rotation < 0)
                    rotation += 360;

                foreach (float angle, this->m_snapAngles)
                    if (fabs(rotation - angle) <= this->m_snappingRT)
                    {
                        rotation = angle;

                        break;
                    }
            }

            this->m_proxy->setRotation(rotation);
            this->m_proxy->setPos(pos);
            this->m_proxy->resize(size);
            this->lblFrame->resize(size.toSize());

            if (this->m_snapping)
            {
                QRectF boundingRect = this->m_proxy->mapRectToParent(this->m_proxy->boundingRect());
                QList<float> lines;
                bool snapped = false;

                foreach (float hLine, this->m_hLines0)
                {
                    lines << boundingRect.top() << boundingRect.bottom();

                    foreach (float line, lines)
                        if (fabs(line - hLine) <= this->m_snappingPT)
                        {
                            float factor = 1 + 2 * (line - hLine) / this->m_proxy->boundingRect().size().height();
                            QSizeF size = factor * this->m_proxy->size();
                            QSize minimumSize = this->minimumSize();

                            if (size.width() < minimumSize.width() || size.height() < minimumSize.height())
                                size.scale(QSizeF(minimumSize), Qt::KeepAspectRatioByExpanding);

                            QPointF pos = this->m_widgetSceneCenter - 0.5 * QPointF(size.width(), size.height());

                            this->m_proxy->setPos(pos);
                            this->m_proxy->resize(size);
                            this->lblFrame->resize(size.toSize());

                            snapped = true;

                            break;
                        }

                    if (snapped)
                        break;
                }

                lines.clear();
                snapped = false;

                foreach (float vLine, this->m_vLines0)
                {
                    lines << boundingRect.left() << boundingRect.right();

                    foreach (float line, lines)
                        if (fabs(line - vLine) <= this->m_snappingPT)
                        {
                            float factor = 1 + 2 * (line - vLine) / this->m_proxy->boundingRect().size().width();
                            QSizeF size = factor * this->m_proxy->size();
                            QSize minimumSize = this->minimumSize();

                            if (size.width() < minimumSize.width() || size.height() < minimumSize.height())
                                size.scale(QSizeF(minimumSize), Qt::KeepAspectRatioByExpanding);

                            QPointF pos = this->m_widgetSceneCenter - 0.5 * QPointF(size.width(), size.height());

                            this->m_proxy->setPos(pos);
                            this->m_proxy->resize(size);
                            this->lblFrame->resize(size.toSize());

                            snapped = true;

                            break;
                        }

                    if (snapped)
                        break;
                }
            }

            this->m_mousePos0 = mousePos1;
        }
        else if (this->m_move)
        {
            QPoint mousePos1 = QCursor::pos();

            this->m_proxy->setPos(this->m_proxy->pos() +
                                this->m_proxy->scene()->views()[0]->mapToScene(this->m_proxy->scene()->views()[0]->mapFromGlobal(mousePos1)) -
                                this->m_proxy->scene()->views()[0]->mapToScene(this->m_proxy->scene()->views()[0]->mapFromGlobal(this->m_mousePos0)));

            if (this->m_snapping)
            {
                QPointF snapDiff(0, 0);

                QRectF boundingRect = this->m_proxy->mapRectToParent(this->m_proxy->boundingRect());
                QList<float> lines;
                bool snapped = false;

                foreach (float hLine, this->m_hLines0)
                {
                    lines << boundingRect.top() << boundingRect.bottom();

                    foreach (float line, lines)
                        if (fabs(line - hLine) <= this->m_snappingPT)
                        {
                            snapDiff += QPointF(0, hLine - line);
                            snapped = true;

                            break;
                        }

                    if (snapped)
                        break;
                }

                lines.clear();
                snapped = false;

                foreach (float vLine, this->m_vLines0)
                {
                    lines << boundingRect.left() << boundingRect.right();

                    foreach (float line, lines)
                        if (fabs(line - vLine) <= this->m_snappingPT)
                        {
                            snapDiff += QPointF(vLine - line, 0);
                            snapped = true;

                            break;
                        }

                    if (snapped)
                        break;
                }

                this->m_proxy->setPos(this->m_proxy->pos() + snapDiff);
            }

            this->m_mousePos0 = mousePos1;
        }
    }
    else
        this->resendMouseEvent(event);
}

void Space::setEditMode(bool editable)
{
    this->m_editMode = editable;
    this->btnScaleAndRotate->setVisible(editable);
}

void Space::setSnapping(bool enable)
{
    this->m_snapping = enable;
}

void Space::setNParts(int nParts)
{
    this->m_snapAngles.clear();

    if (nParts <= 0)
        return;

    float angle = 0;
    float inc = 360.0 / (float) nParts;

    while (angle < 360)
    {
        this->m_snapAngles << angle;
        angle += inc;
    }
}

void Space::setSnappingPT(float snappingPT)
{
    this->m_snappingPT = snappingPT;
}

void Space::setSnappingRT(float snappingRT)
{
    this->m_snappingRT = snappingRT;
}

void Space::setButtonText(QString text)
{
    this->btnScaleAndRotate->setText(text);
}

void Space::setButtonIcon(QString icon)
{
    this->m_buttonIconFileName = icon;

    this->btnScaleAndRotate->setIcon(QIcon(icon));
}

void Space::setButtonStyleSheet(QString styleSheet)
{
    this->btnScaleAndRotate->setStyleSheet(styleSheet);
}

void Space::resetEditMode()
{
    this->setEditMode(false);
}

void Space::resetSnapping()
{
    this->setSnapping(false);
}

void Space::resetNParts()
{
    this->setNParts(0);
}

void Space::resetSnappingPT()
{
    this->setSnappingPT(0);
}

void Space::resetSnappingRT()
{
    this->setSnappingRT(0);
}

void Space::resetButtonText()
{
    this->setButtonText("");
}

void Space::resetButtonIcon()
{
    this->setButtonIcon("");
}

void Space::resetButtonStyleSheet()
{
    this->setButtonStyleSheet("");
}
