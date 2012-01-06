#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsProxyWidget>
#include <QMoveEvent>

#include "../../include/space/spaceview.h"

SpaceView::SpaceView(QObject *parent): QObject(parent)
{
    this->move = false;
    this->scaleAndRotate = false;
    this->m_viewPortSize = QSize(0, 0);
    this->mainSpace.setBackgroundBrush(Qt::black);
    this->m_toggleMaximizedButton = NULL;
    this->m_scaleAndRotateButton = NULL;
    this->m_editMode = false;
}

SpaceView::~SpaceView()
{
    if (this->m_toggleMaximizedButton)
        delete this->m_toggleMaximizedButton;

    if (this->m_scaleAndRotateButton)
        delete this->m_scaleAndRotateButton;

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

void SpaceView::setControlButtons(QPushButton *toggleMaximizedButton, QPushButton *scaleAndRotateButton)
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

QPoint SpaceView::mapToMainSpace(const QPoint &pos, const QSize &viewportSize)
{
    QPoint posSpace(pos.x() * this->mainSpace.width() / viewportSize.width(),
                    pos.y() * this->mainSpace.height() / viewportSize.height());

    return posSpace;
}

QWidget *SpaceView::sendMouseEvent(QEvent::Type type,
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

void SpaceView::setSpace(QString spaceId, const QImage &frame)
{
    if (this->spacesWidgets.contains(spaceId))
        this->spacesWidgets[spaceId]->spacePixmap.setPixmap(QPixmap::fromImage(frame));
    else
    {
        this->spaceModel.addSpace(spaceId, frame.size());
        this->spacesWidgets[spaceId] = new SpaceWidget(frame);
        this->spacesWidgets[spaceId]->setControlButtons(this->m_toggleMaximizedButton, this->m_scaleAndRotateButton);
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

QSize SpaceView::viewPortSize()
{
    return this->m_viewPortSize;
}

bool SpaceView::editMode()
{
    return this->m_editMode;
}

void SpaceView::setViewPortSize(QSize size)
{
    this->m_viewPortSize = size;
}

void SpaceView::setEditMode(bool value)
{
    this->m_editMode = value;
}

void SpaceView::resetViewPortSize()
{
    this->m_viewPortSize = QSize(0, 0);
}

void SpaceView::resetEditMode()
{
    this->m_editMode = false;
}

void SpaceView::selectSpace(QString spaceId)
{
    this->spaceModel.selectSpace(spaceId);
}

void SpaceView::mouseDoubleClickEvent(QMouseEvent *event)
{
    this->spaceModel.selectSpace(this->mapToMainSpace(event->pos(), this->m_viewPortSize));

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

    if (this->scaleAndRotate)
        this->spaceModel.scaleAndRotateSpace(this->mapToMainSpace(event->pos(), this->m_viewPortSize));

    if (this->move)
        this->spaceModel.moveSpace(this->mapToMainSpace(event->pos(), this->m_viewPortSize));
}

void SpaceView::mousePressEvent(QMouseEvent *event)
{
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
}

void SpaceView::mouseReleaseEvent(QMouseEvent *event)
{
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
}
