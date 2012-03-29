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
#include <QSet>
#include <QtDebug>

#include "../../include/space/spacemodel.h"

SpaceModel::SpaceModel(QObject *parent): QObject(parent)
{
    this->m_currentSelectedSpace = "";
    this->m_rect = QRectF(0, 0, 0, 0);
    this->m_pointRef = QPoint(0, 0);
    this->m_snapping = false;
    this->m_nParts = 1;
    this->m_snappingPT = 0;
    this->m_snappingRT = 0;
}

void SpaceModel::setSnapping(bool snapping, qint32 nParts, qreal snappingPT, qreal snappingRT)
{
    this->m_snapping = snapping;
    this->m_nParts = nParts;
    this->m_snappingPT = snappingPT;
    this->m_snappingRT = snappingRT;

    for (qint32 space = 0; space < this->m_spaces.count(); space++)
        this->m_spaces[space].setSnapping(snapping, nParts, snappingPT, snappingRT);
}

Space SpaceModel::setSpace(QString spaceId, QSizeF size)
{
    for (qint32 mspace = 0; mspace < this->m_spaces.count(); mspace++)
        if (this->m_spaces[mspace].spaceId() == spaceId)
        {
            this->m_spaces[mspace].setSize(size);

            return this->m_spaces[mspace];
        }

    Space space(spaceId, this->m_rect.center(), size, 1, 0);

    space.setSnapping(this->m_snapping, this->m_nParts, this->m_snappingPT, this->m_snappingRT);

    this->m_spaces << space;

    return space;
}

void SpaceModel::removeSpace(QString spaceId)
{
    foreach (Space space, this->m_spaces)
        if (space.spaceId() == spaceId)
        {
            this->m_spaces.removeOne(space);

            if (this->m_currentSelectedSpace == spaceId)
                this->m_currentSelectedSpace = "";

            return;
        }
}

template <typename T> QList<T> SpaceModel::removeDuplicates(QList<T> &list)
{
    QList<T> newList;

    foreach (T element, this->reversed(list))
        if (!newList.contains(element))
            newList << element;

    return this->reversed(newList);
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
    this->m_currentSelectedSpace = "";

    for (qint32 space = this->m_spaces.count() - 1; space >= 0; space--)
        if (this->m_spaces[space].spaceId() == spaceId)
        {
            this->m_spaces[space].setRef();
            this->m_spaces << this->m_spaces.takeAt(space);
            this->m_spaces = this->removeDuplicates(this->m_spaces);
            this->m_currentSelectedSpace = this->m_spaces[space].spaceId();
            emit spaceMoved(space, this->m_spaces.count() - 1);

            break;
        }
}

void SpaceModel::selectSpace(QPointF point)
{
    this->m_pointRef = point;
    this->m_currentSelectedSpace = "";

    for (qint32 space = this->m_spaces.count() - 1; space >= 0; space--)
        if (this->m_spaces[space].contains(point))
        {
            this->m_spaces[space].setRef();
            this->m_currentSelectedSpace = this->m_spaces[space].spaceId();
            this->m_spaces = this->removeDuplicates(this->m_spaces);
            this->m_spaces << this->m_spaces.takeAt(space);
            emit spaceMoved(space, this->m_spaces.count() - 1);

            break;
        }
}

template <typename T> void SpaceModel::removeDuplicatesAndSort(QList<T> &list)
{
    QList<T> set = this->removeDuplicates(list);

    list.clear();
    list << set;
    qSort(list);
}

template <typename T> bool SpaceModel::snapLines(QList<T> &hLines, QList<T> &vLines)
{
    if (this->m_currentSelectedSpace == "")
        return false;

    hLines.clear();
    vLines.clear();

    foreach (Space space, this->m_spaces)
        if (space.spaceId() != this->m_currentSelectedSpace)
        {
            hLines << space.hLines();
            vLines << space.vLines();
        }

    this->removeDuplicatesAndSort(hLines);
    this->removeDuplicatesAndSort(vLines);

    return true;
}

void SpaceModel::toggleMaximizedSpace()
{
    QList<qreal> hLines, vLines;

    if (!this->snapLines(hLines, vLines))
        return;

    for (qint32 space = 0; space < this->m_spaces.count(); space++)
        if (this->m_spaces[space].spaceId() == this->m_currentSelectedSpace)
        {
            this->m_spaces[space].toggleMaximized(hLines, vLines);

            break;
        }
}

bool SpaceModel::isMaximized(QString spaceId)
{
    for (qint32 space = 0; space < this->m_spaces.count(); space++)
        if (this->m_spaces[space].spaceId() == spaceId)
            return this->m_spaces[space].maximized();

    return false;
}

QSizeF SpaceModel::spaceSize(QString spaceId)
{
    foreach (Space space, this->m_spaces)
        if (space.spaceId() == spaceId)
            return space.size();

    return QSizeF();
}

QPointF SpaceModel::mapToLocal(QPointF point, QString *spaceId)
{
    foreach (Space space, this->reversed(this->m_spaces))
        if (space.contains(point))
        {
            if (spaceId)
                *spaceId = space.spaceId();

            return space.mapToLocal(point);
        }

    return QPointF();
}

qreal SpaceModel::calculateAngle(QPointF point)
{
    if (point.x() == 0 && point.y() == 0)
        return 0;
    else if (point.x() > 0 && point.y() > 0)
        return atan2(point.y(), point.x());
    else if (point.x() <= 0 && point.y() > 0)
        return atan2(fabs(point.x()), point.y()) + M_PI / 2;
    else if (point.x() <= 0 && point.y() <= 0)
        return atan2(fabs(point.y()), fabs(point.x())) + M_PI;
    else if (point.x() > 0 && point.y() <= 0)
        return atan2(point.x(), fabs(point.y())) + 3 * M_PI / 2;

    return 0;
}

void SpaceModel::scaleAndRotateSpace(QPointF to)
{
    QList<qreal> hLines, vLines;

    if (!this->snapLines(hLines, vLines))
        return;

    for (qint32 space = 0; space < this->m_spaces.count(); space++)
        if (this->m_spaces[space].spaceId() == this->m_currentSelectedSpace)
        {
            this->m_spaces[space].resetStatus();
            QPointF center = this->m_spaces[space].center();

            QPointF pi = this->m_pointRef - center;
            QPointF pf = to - center;
            qreal factor = sqrt(pow(pf.x(), 2) + pow(pf.y(), 2)) / sqrt(pow(pi.x(), 2) + pow(pi.y(), 2));
            qreal angle = this->calculateAngle(to - center) - this->calculateAngle(this->m_pointRef - center);

            this->m_spaces[space].scaleAndRotate(this->m_spaces[space].scale() * factor,
                                                 this->m_spaces[space].rotation() + angle,
                                                 hLines, vLines);

            break;
        }
}

void SpaceModel::moveSpace(QPointF to)
{
    QList<qreal> hLines, vLines;

    if (!this->snapLines(hLines, vLines))
        return;

    for (qint32 space = 0; space < this->m_spaces.count(); space++)
        if (this->m_spaces[space].spaceId() == this->m_currentSelectedSpace)
        {
            this->m_spaces[space].resetStatus();
            this->m_spaces[space].move(this->m_spaces[space].center() + to - this->m_pointRef, hLines, vLines);

            break;
        }
}

void SpaceModel::moveSpace(qint32 from, qint32 to)
{
    this->m_spaces.move(from, to);
}

void SpaceModel::updateRect()
{
    QRectF modelRect;

    this->m_spaces = this->removeDuplicates(this->m_spaces);

    foreach (Space space, this->m_spaces)
        modelRect = (modelRect.isNull())? space.boundingRect(): modelRect.united(space.boundingRect());

    this->m_rect = modelRect;
}

QString SpaceModel::currentSelectedSpace()
{
    return this->m_currentSelectedSpace;
}

QRectF SpaceModel::rect()
{
    return this->m_rect;
}

QList<Space> SpaceModel::spaces()
{
    return this->m_spaces;
}

bool SpaceModel::snapping()
{
    return this->m_snapping;
}

qint32 SpaceModel::nParts()
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

void SpaceModel::setCurrentSelectedSpace(QString value)
{
    this->m_currentSelectedSpace = value;
}

void SpaceModel::setRect(QRectF value)
{
    this->m_rect = value;
}

void SpaceModel::setSpaces(QList<Space> value)
{
    this->m_spaces = value;
}

void SpaceModel::setSnapping(bool value)
{
    this->m_snapping = value;
}

void SpaceModel::setNParts(qint32 value)
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

void SpaceModel::resetCurrentSelectedSpace()
{
    this->m_currentSelectedSpace = "";
}

void SpaceModel::resetRect()
{
    this->m_rect = QRectF(0, 0, 0, 0);
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
