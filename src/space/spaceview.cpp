#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsProxyWidget>
#include <QMoveEvent>

#include "../../include/space/spaceview.h"

SpaceView::SpaceView(QObject *parent): QObject(parent)
{
    this->m_viewPortSize = QSize(0, 0);
    this->m_mousePosition = QPoint(0, 0);
    this->mainSpace.setBackgroundBrush(Qt::black);
}

SpaceView::~SpaceView()
{
    foreach(QString spaceId, this->spacesWidgets.keys())
        this->removeSpace(spaceId);
}

QImage SpaceView::render()
{
    QImage mainFrame(this->mainSpace.width(), this->mainSpace.height(), QImage::Format_RGB888);

    mainFrame.fill(0);

    QPainter mainPainter(&mainFrame);

    foreach (Space space, this->spaceModel.spaces())
    {/*
        spacePainter.scale(space.scale() * space.size().width(), space.scale() * space.size().height());
        spacePainter.rotate(space.rotation());

        this->proxySpacesWidgets[space.spaceId()]->setTransform(QTransform()
                                                       .translate(r.width() / 2, r.height() / 2)
                                                       .rotate(step * 30, Qt::XAxis)
                                                       .rotate(step * 10, Qt::YAxis)
                                                       .rotate(step * 5, Qt::ZAxis)
                                                       .scale(0.8, 0.8)
                                                       .translate(-r.width() / 2, -r.height() / 2));*/
    }

    this->mainSpace.render(&mainPainter);

    return mainFrame;
}

QPoint SpaceView::mapToMainSpace(const QPoint &pos, const QSize &viewportSize)
{
    QPoint posSpace(pos.x() * this->mainSpace.width() / viewportSize.width(),
                    pos.y() * this->mainSpace.height() / viewportSize.height());

    return posSpace;
}

void SpaceView::sendMouseEvent(QEvent::Type type,
                                const QPoint &position,
                                Qt::MouseButton button,
                                Qt::MouseButtons buttons,
                                Qt::KeyboardModifiers modifiers)
{
    QGraphicsProxyWidget *proxyWidget = qgraphicsitem_cast<QGraphicsProxyWidget *>(this->mainSpace.itemAt(position, QTransform()));

    if (proxyWidget == NULL)
        return;

    QPoint proxyWidgetLocalPoint = proxyWidget->mapFromScene(position).toPoint();
    QWidget *widget = proxyWidget->widget()->childAt(proxyWidgetLocalPoint);

    if (!widget)
        return;

    QMouseEvent event(type,
                      widget->mapFromParent(proxyWidgetLocalPoint),
                      button,
                      buttons,
                      modifiers);

    QApplication::sendEvent(widget, &event);
}

void SpaceView::setSpace(QString spaceId, const QImage &frame)
{
    if (this->spacesWidgets.contains(spaceId))
        this->spacesWidgets[spaceId]->spacePixmap.setPixmap(QPixmap::fromImage(frame));
    else
    {
        this->spaceModel.addSpace(spaceId, frame.size());
        this->spacesWidgets[spaceId] = new SpaceWidget(QImage("/home/hipersayan_x/Imagenes/Agent Aika/846ae317d5a8237e6a5e0c6bd3c88d42.jpg"));
        this->proxySpacesWidgets[spaceId] = this->mainSpace.addWidget(this->spacesWidgets[spaceId]);
    }
}

void SpaceView::removeSpace(QString spaceId)
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

void SpaceView::setSnapping(bool snapping, int nParts, qreal snappingPT, qreal snappingRT)
{
    this->spaceModel.setSnapping(snapping, nParts, snappingPT, snappingRT);
}

QImage SpaceView::scaleAndRotateIcon()
{
    return this->m_scaleAndRotateIcon;
}

QImage SpaceView::toggleMaximizeIcon()
{
    return this->m_toggleMaximizeIcon;
}

QSize SpaceView::viewPortSize()
{
    return this->m_viewPortSize;
}

QPoint SpaceView::mousePosition()
{
    return this->m_mousePosition;
}

void SpaceView::setScaleAndRotateIcon(const QImage &icon)
{
    this->m_scaleAndRotateIcon = icon;
}

void SpaceView::setToggleMaximizeIcon(const QImage &icon)
{
    this->m_toggleMaximizeIcon = icon;
}

void SpaceView::setViewPortSize(QSize size)
{
    this->m_viewPortSize = size;
}

void SpaceView::setMousePosition(QPoint mousePos)
{
    this->m_mousePosition = mousePos;
}

void SpaceView::resetScaleAndRotateIcon()
{
    this->m_scaleAndRotateIcon = QImage();
}

void SpaceView::resetToggleMaximizeIcon()
{
    this->m_toggleMaximizeIcon = QImage();
}

void SpaceView::resetViewPortSize()
{
    this->m_viewPortSize = QSize(0, 0);
}

void SpaceView::resetMousePosition()
{
    this->m_mousePosition = QPoint(0, 0);
}

void SpaceView::selectSpace(QString spaceId)
{
    this->spaceModel.selectSpace(spaceId);
}

void SpaceView::mouseDoubleClickEvent(QMouseEvent *event)
{
    this->sendMouseEvent(QEvent::MouseButtonDblClick,
                         this->mapToMainSpace(event->pos(), this->m_viewPortSize),
                         event->button(),
                         event->buttons(),
                         Qt::NoModifier);
}

void SpaceView::mouseMoveEvent(QMouseEvent *event)
{
    this->sendMouseEvent(QEvent::MouseMove,
                         this->mapToMainSpace(event->pos(), this->m_viewPortSize),
                         event->button(),
                         event->buttons(),
                         Qt::NoModifier);
}

void SpaceView::mousePressEvent(QMouseEvent *event)
{
    this->sendMouseEvent(QEvent::MouseButtonPress,
                         this->mapToMainSpace(event->pos(), this->m_viewPortSize),
                         event->button(),
                         event->buttons(),
                         Qt::NoModifier);
}

void SpaceView::mouseReleaseEvent(QMouseEvent *event)
{
    this->sendMouseEvent(QEvent::MouseButtonRelease,
                         this->mapToMainSpace(event->pos(), this->m_viewPortSize),
                         event->button(),
                         event->buttons(),
                         Qt::NoModifier);
}
