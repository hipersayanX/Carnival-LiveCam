#include <cmath>
#include <QSet>

#include "../../include/space/spacemodel.h"

SpaceModel::SpaceModel(QObject *parent): QObject(parent)
{
    this->m_size = QSize(0, 0);
    this->m_pointRef = QPoint(0, 0);
    this->m_spaceIdRef = "";
    this->m_snapping = false;
    this->m_nParts = 1;
    this->m_snappingPT = 0;
    this->m_snappingRT = 0;
}

void SpaceModel::setSnapping(bool snapping, int nParts, qreal snappingPT, qreal snappingRT)
{
    this->m_snapping = snapping;
    this->m_nParts = nParts;
    this->m_snappingPT = snappingPT;
    this->m_snappingRT = snappingRT;

    for (int space = 0; space < this->m_spaces.count(); space++)
        this->m_spaces[space].setSnapping(snapping, nParts, snappingPT, snappingRT);
}

void SpaceModel::addSpace(QString spaceId, QSizeF size)
{
    QPointF center(this->m_size.width(), this->m_size.height());

    Space space(spaceId, center / 2, size, 1, 0);

    space.setSnapping(this->m_snapping, this->m_nParts, this->m_snappingPT, this->m_snappingRT);

    this->m_spaces << space;

    this->updateSize();
}

void SpaceModel::addSpace(Space space)
{
    space.setSnapping(this->m_snapping, this->m_nParts, this->m_snappingPT, this->m_snappingRT);

    this->m_spaces << space;

    this->updateSize();
}

void SpaceModel::removeSpace(QString spaceId)
{
    foreach (Space space, this->m_spaces)
        if (space.spaceId() == spaceId)
        {
            this->m_spaces.removeOne(space);

            if (this->m_spaceIdRef == spaceId)
                this->m_spaceIdRef = "";

            return;
        }

    this->updateSize();
}

template <typename T> QList<T> SpaceModel::reversed(const QList<T> &list)
{
    QList<T> result;

    result.reserve(list.size());

    std::reverse_copy(list.begin(), list.end(), std::back_inserter(result));

    return result;
}

void SpaceModel::selectSpace(QString spaceId)
{
    foreach (Space space, this->m_spaces)
        if (space.spaceId() == spaceId)
        {
            space.setRef();
            this->m_spaces.removeOne(space);
            this->m_spaces << space;
            this->m_spaceIdRef = space.spaceId();

            return;
        }

    this->m_spaceIdRef = "";
}

void SpaceModel::selectSpace(QPointF point)
{
    this->m_pointRef = point;

    foreach (Space space, this->reversed(this->m_spaces))
        if (space.contains(point))
        {
            space.setRef();
            this->m_spaces.removeOne(space);
            this->m_spaces << space;
            this->m_spaceIdRef = space.spaceId();

            return;
        }

    this->m_spaceIdRef = "";
}

template <typename T> void SpaceModel::cleanAndSort(QList<T> &list)
{
    QList<T> set;

    foreach (T element, list)
        if (!set.contains(element))
            set << element;

    list.clear();
    list << set;
    qSort(list);
}

template <typename T> bool SpaceModel::snapLines(QList<T> &hLines, QList<T> &vLines)
{
    if (this->m_spaceIdRef == "")
        return false;

    hLines.clear();
    vLines.clear();

    foreach (Space space, this->m_spaces)
        if (space.spaceId() != this->m_spaceIdRef)
        {
            hLines << space.hLines();
            vLines << space.vLines();
        }

    this->cleanAndSort(hLines);
    this->cleanAndSort(vLines);

    return true;
}

void SpaceModel::toggleMaximizedSpace()
{
    QList<qreal> hLines, vLines;

    if (!this->snapLines(hLines, vLines))
        return;

    for (int space = 0; space < this->m_spaces.count(); space++)
        if (this->m_spaces[space].spaceId() == this->m_spaceIdRef)
        {
            this->m_spaces[space].toggleMaximized(hLines, vLines);

            break;
        }
}

qreal SpaceModel::calculateAngle(QPointF point)
{
    qreal angle = atan2(point.y(), point.x());

    return (angle > 0)? angle: 2 * M_PI - angle;
}

void SpaceModel::scaleSpace(QPointF to)
{
    QList<qreal> hLines, vLines;

    if (!this->snapLines(hLines, vLines))
        return;

    for (int space = 0; space < this->m_spaces.count(); space++)
        if (this->m_spaces[space].spaceId() == this->m_spaceIdRef)
        {
            this->m_spaces[space].resetStatus();
            QPointF center = this->m_spaces[space].center();
            QPointF pi = this->m_pointRef - center;
            QPointF pf = to - center;
            qreal factor = sqrt(pow(pf.x(), 2) + pow(pf.y(), 2)) / sqrt(pow(pi.x(), 2) + pow(pi.y(), 2));
            this->m_spaces[space].setScale(factor, hLines, vLines);

            break;
        }

    this->updateSize();
}

void SpaceModel::rotateSpace(QPointF to)
{
    QList<qreal> hLines, vLines;

    if (!this->snapLines(hLines, vLines))
        return;

    for (int space = 0; space < this->m_spaces.count(); space++)
        if (this->m_spaces[space].spaceId() == this->m_spaceIdRef)
        {
            this->m_spaces[space].resetStatus();
            QPointF center = this->m_spaces[space].center();
            qreal angle = this->calculateAngle(to - center) - this->calculateAngle(this->m_pointRef - center);
            this->m_spaces[space].setRotation(this->m_spaces[space].rotation() + angle);

            break;
        }

    this->updateSize();
}

void SpaceModel::scaleAndRotateSpace(QPointF to)
{
    QList<qreal> hLines, vLines;

    if (!this->snapLines(hLines, vLines))
        return;

    for (int space = 0; space < this->m_spaces.count(); space++)
        if (this->m_spaces[space].spaceId() == this->m_spaceIdRef)
        {
            this->m_spaces[space].resetStatus();
            QPointF center = this->m_spaces[space].center();

            QPointF pi = this->m_pointRef - center;
            QPointF pf = to - center;
            qreal factor = sqrt(pow(pf.x(), 2) + pow(pf.y(), 2)) / sqrt(pow(pi.x(), 2) + pow(pi.y(), 2));
            qreal angle = this->calculateAngle(to - center) - this->calculateAngle(this->m_pointRef - center);

            this->m_spaces[space].scaleAndRotate(this->m_spaces[space].scale() * factor, this->m_spaces[space].rotation() + angle, hLines, vLines);

            break;
        }

    this->updateSize();
}

void SpaceModel::moveSpace(QPointF to)
{
    QList<qreal> hLines, vLines;

    if (!this->snapLines(hLines, vLines))
        return;

    for (int space = 0; space < this->m_spaces.count(); space++)
        if (this->m_spaces[space].spaceId() == this->m_spaceIdRef)
        {
            this->m_spaces[space].resetStatus();
            this->m_spaces[space].move(this->m_spaces[space].center() + to - this->m_pointRef, hLines, vLines);

            break;
        }

    this->updateSize();
}

void SpaceModel::updateSize()
{
    qreal minX = 0, maxX = 0, minY = 0, maxY = 0;
    QList<qreal> v, h;
    bool fst = true;

    foreach (Space space, this->m_spaces)
        if (fst)
        {
            v = space.vLines();

            minX = v[0];
            maxX = v[1];

            h = space.hLines();

            minY = h[0];
            maxY = h[1];

            fst = false;
        }
        else
        {
            v = space.vLines();

            if (v[0] < minX)
                minX = v[0];

            if (v[1] > maxX)
                maxX = v[1];

            h = space.hLines();

            if (h[0] < minY)
                minY = h[0];

            if (h[1] > maxY)
                maxY = h[1];
        }

    QPointF diff(minX, minY);

    for (int space = 0; space < this->m_spaces.count(); space++)
    {
        this->m_spaces[space].move(this->m_spaces[space].center() - diff);
        this->m_spaces[space].setRef();
    }

    this->m_size = QSize(maxX - minX + 1, maxY - minY + 1);
}

QSizeF SpaceModel::size()
{
    return this->m_size;
}

QList<Space> SpaceModel::spaces()
{
    return this->m_spaces;
}

bool SpaceModel::snapping()
{
    return this->m_snapping;
}

int SpaceModel::nParts()
{
    return this->m_nParts;
}

qreal SpaceModel::snappingPT()
{
    return this->m_snappingPT;
}

qreal SpaceModel::snappingRT()
{
    return this->m_snappingRT;
}

void SpaceModel::setSize(QSizeF value)
{
    this->m_size = value;
}

void SpaceModel::setSpaces(QList<Space> value)
{
    this->m_spaces = value;
}

void SpaceModel::setSnapping(bool value)
{
    this->m_snapping = value;
}

void SpaceModel::setNParts(int value)
{
    this->m_nParts = value;
}

void SpaceModel::setSnappingPT(qreal value)
{
    this->m_snappingPT = value;
}

void SpaceModel::setSnappingRT(qreal value)
{
    this->m_snappingRT = value;
}

void SpaceModel::resetSize()
{
    this->m_size = QSizeF(0, 0);
}

void SpaceModel::resetSpaces()
{
    this->m_spaces.clear();
}

void SpaceModel::resetSnapping()
{
    this->m_snapping = false;
}

void SpaceModel::resetNParts()
{
    this->m_nParts = 1;
}

void SpaceModel::resetSnappingPT()
{
    this->m_snappingPT = 0;
}

void SpaceModel::resetSnappingRT()
{
    this->m_snappingRT = 0;
}
