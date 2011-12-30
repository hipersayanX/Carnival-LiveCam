#include "../../include/space/spaceview.h"

SpaceView::SpaceView(QObject *parent): QObject(parent)
{
}

QImage SpaceView::render()
{
}

void SpaceView::setSpace(QString spaceId, const QImage &frame)
{
}

void SpaceView::removeSpace(QString spaceId)
{
}

void SpaceView::setSnapping(bool snapping, int nParts, qreal snappingPT, qreal snappingRT)
{
    spaceModel.setSnapping(snapping, nParts, snappingPT, snappingRT);
}

void SpaceView::setScaleAndRotateIcon(const QImage &icon)
{
}

void SpaceView::viewPortSize(QSize size)
{
}

void SpaceView::selectSpace(QString spaceId)
{
}

void SpaceView::selectSpace(QPoint point)
{
}

void SpaceView::toggleMaximizedSpace()
{
}

void SpaceView::scaleSpace(QPoint to)
{
}

void SpaceView::rotateSpace(QPoint to)
{
}

void SpaceView::scaleAndRotateSpace(QPoint to)
{
}

void SpaceView::moveSpace(QPoint to)
{
}

void SpaceView::mouseMoved(QPoint mousePos)
{
}

void SpaceView::mousePressed()
{
}

void SpaceView::mouseReleased()
{
}
