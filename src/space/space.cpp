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
#include <QtDebug>
#include <QtAlgorithms>

#include "../../include/space/space.h"

Space::Space(QObject *parent): QObject(parent)
{
    this->m_spaceId = "";
    this->m_nParts = 1;
    this->m_center = QPointF(0, 0);
    this->m_CenterRef = QPointF(0, 0);
    this->m_size = QSizeF(0, 0);
    this->m_sizeRef = QSizeF(0, 0);
    this->m_scale = 1;
    this->m_scaleRef = 1;
    this->m_rotation = 0;
    this->m_rotationRef = 0;
    this->m_maximized = false;

    this->setSnapping(false, 1, 0, 0);
}

Space::Space(const Space &object):
    QObject(object.parent()),
    m_snapAngles(object.m_snapAngles),
    m_spaceId(object.m_spaceId),
    m_nParts(object.m_nParts),
    m_center(object.m_center),
    m_CenterRef(object.m_CenterRef),
    m_size(object.m_size),
    m_sizeRef(object.m_sizeRef),
    m_snapping(object.m_snapping),
    m_snappingPT(object.m_snappingPT),
    m_snappingRT(object.m_snappingRT),
    m_scale(object.m_scale),
    m_scaleRef(object.m_scaleRef),
    m_rotation(object.m_rotation),
    m_rotationRef(object.m_rotationRef),
    m_maximized(object.m_maximized)
{
}

Space::Space(QString spaceId,
             QPointF center,
             QSizeF size,
             qreal scale,
             qreal rotation):
                m_spaceId(spaceId),
                m_center(center),
                m_CenterRef(center),
                m_size(size),
                m_sizeRef(size),
                m_scale(scale),
                m_scaleRef(scale),
                m_rotation(rotation),
                m_rotationRef(rotation),
                m_maximized(false)
{
    this->setSnapping(false, 1, 0, 0);
}

Space& Space::operator =(const Space &other)
{
    if (this != &other)
    {
        this->m_snapAngles = other.m_snapAngles;
        this->m_spaceId = other.m_spaceId;
        this->m_nParts = other.m_nParts;
        this->m_center = other.m_center;
        this->m_CenterRef = other.m_CenterRef;
        this->m_size = other.m_size;
        this->m_sizeRef = other.m_sizeRef;
        this->m_snapping = other.m_snapping;
        this->m_snappingPT = other.m_snappingPT;
        this->m_snappingRT = other.m_snappingRT;
        this->m_scale = other.m_scale,
        this->m_scaleRef = other.m_scaleRef,
        this->m_rotation = other.m_rotation;
        this->m_rotationRef = other.m_rotationRef;
        this->m_maximized = other.m_maximized;
    }

    return *this;
}

bool Space::operator ==(const Space &other) const
{
    return (this->m_snapAngles == other.m_snapAngles &&
            this->m_spaceId == other.m_spaceId &&
            this->m_nParts == other.m_nParts &&
            this->m_center == other.m_center &&
            this->m_CenterRef == other.m_CenterRef &&
            this->m_size == other.m_size &&
            this->m_sizeRef == other.m_sizeRef &&
            this->m_snapping == other.m_snapping &&
            this->m_snappingPT == other.m_snappingPT &&
            this->m_snappingRT == other.m_snappingRT &&
            this->m_scale == other.m_scale &&
            this->m_scaleRef == other.m_scaleRef &&
            this->m_rotation == other.m_rotation &&
            this->m_rotationRef == other.m_rotationRef &&
            this->m_maximized == other.m_maximized)? true: false;
}

bool Space::isMaximized()
{
    return this->m_maximized;
}

template <typename T> T Space::min(const QList<T> &list)
{
    QList<T> l = list;

    qSort(l.begin(), l.end(), qLess<T>());

    return l[0];
}

template <typename T> T Space::max(const QList<T> &list)
{
    QList<T> l = list;

    qSort(l.begin(), l.end(), qGreater<T>());

    return l[0];
}

void Space::toggleMaximized(const QList<qreal> &hLines, const QList<qreal> &vLines)
{
    this->m_maximized = !this->m_maximized;

    if (this->m_maximized)
    {
        this->m_rotation = 0;

        qreal left = (vLines.isEmpty())? -this->m_size.width() / 2: this->min(vLines);
        qreal right = (vLines.isEmpty())? this->m_size.width() / 2: this->max(vLines);
        qreal top = (vLines.isEmpty())? -this->m_size.height() / 2: this->min(hLines);
        qreal bottom = (vLines.isEmpty())? this->m_size.height() / 2: this->max(hLines);

        qreal width = right - left;
        qreal height = bottom - top;

        QSizeF size = this->m_size;
        size.scale(width, height, Qt::KeepAspectRatio);

        this->m_scale = size.width() / this->m_size.width();
        this->m_center = QPointF(left + right, top + bottom) / 2;
    }
    else
        this->resetStatus();
}

void Space::setSnapping(bool snapping, int nParts, qreal snappingPT, qreal snappingRT)
{
    this->m_snapping = snapping;
    this->m_nParts = nParts;
    this->m_snappingPT = snappingPT;
    this->m_snappingRT = snappingRT;

    this->m_snapAngles.clear();

    for (qreal angle = 0; angle < 2 * M_PI; angle += 2 * M_PI / nParts)
        this->m_snapAngles << angle;
}

void Space::setRef()
{
    this->m_CenterRef = this->m_center;
    this->m_sizeRef = this->m_size;
    this->m_rotationRef = this->m_rotation;
    this->m_scaleRef = this->m_scale;
}

void Space::resetStatus()
{
    this->m_center = this->m_CenterRef;
    this->m_size = this->m_sizeRef;
    this->m_rotation = this->m_rotationRef;
    this->m_scale = this->m_scaleRef;
}

QList<qreal> Space::hLines()
{
    QRectF rect = this->boundingRect();
    QList<qreal> lines;

    lines << rect.top() << rect.bottom();

    return lines;
}

QList<qreal> Space::vLines()
{
    QRectF rect = this->boundingRect();
    QList<qreal> lines;

    lines << rect.left() << rect.right();

    return lines;
}

void Space::scaleAndRotate(qreal factor, qreal rotation, const QList<qreal> &hLines, const QList<qreal> &vLines)
{
    this->m_scale = factor;

    while (true)
    {
        if (rotation > 2 * M_PI)
            rotation -= 2 * M_PI;
        else if (rotation < -2 * M_PI)
            rotation += 2 * M_PI;
        else
            break;
    }

    this->m_rotation = (rotation < 0)? 2 * M_PI + rotation: rotation;

    if (!this->m_snapping)
        return;

    if (!this->m_snapAngles.contains(this->m_rotation))
        foreach (qreal angle, this->m_snapAngles)
            if (fabs(this->m_rotation - angle) <= this->m_snappingRT)
            {
                this->m_rotation = angle;

                break;
            }

    QRectF boundingBox = this->boundingRect();
    QSizeF internalRect;

    bool snapped = false;

    foreach (qreal hLine, hLines)
    {
        foreach (qreal line, this->hLines())
            if (fabs(line - hLine) <= this->m_snappingPT)
            {
                internalRect = this->internalRectSize(QSizeF(boundingBox.width(), boundingBox.height() + hLine - line));
                this->m_scale = internalRect.width() / this->m_size.width();
                snapped = true;

                break;
            }

        if (snapped)
            break;
    }

    snapped = false;

    foreach (qreal vLine, vLines)
    {
        foreach (qreal line, this->vLines())
            if (fabs(line - vLine) <= this->m_snappingPT)
            {
                internalRect = this->internalRectSize(QSizeF(boundingBox.width() + vLine - line, boundingBox.height()));
                this->m_scale = internalRect.width() / this->m_size.width();
                snapped = true;

                break;
            }

        if (snapped)
            break;
    }
}

void Space::setScale(qreal factor, const QList<qreal> &hLines, const QList<qreal> &vLines)
{
    this->m_scale = factor;

    if (!this->m_snapping)
        return;

    QRectF boundingBox = this->boundingRect();
    QSizeF internalRect;

    bool snapped = false;

    foreach (qreal hLine, hLines)
    {
        foreach (qreal line, this->hLines())
            if (fabs(line - hLine) <= this->m_snappingPT)
            {
                internalRect = this->internalRectSize(QSizeF(boundingBox.width(), boundingBox.height() + hLine - line));
                this->m_scale = internalRect.width() / this->m_size.width();
                snapped = true;

                break;
            }

        if (snapped)
            break;
    }

    snapped = false;

    foreach (qreal vLine, vLines)
    {
        foreach (qreal line, this->vLines())
            if (fabs(line - vLine) <= this->m_snappingPT)
            {
                internalRect = this->internalRectSize(QSizeF(boundingBox.width() + vLine - line, boundingBox.height()));
                this->m_scale = internalRect.width() / this->m_size.width();
                snapped = true;

                break;
            }

        if (snapped)
            break;
    }
}

void Space::move(QPointF pos, const QList<qreal> &hLines, const QList<qreal> &vLines)
{
    this->m_center = pos;

    if (!this->m_snapping)
        return;

    bool snapped = false;

    foreach (qreal hLine, hLines)
    {
        foreach (qreal line, this->hLines())
            if (fabs(line - hLine) <= this->m_snappingPT)
            {
                this->m_center += QPointF(0, hLine - line);
                snapped = true;

                break;
            }

        if (snapped)
            break;
    }

    snapped = false;

    foreach (qreal vLine, vLines)
    {
        foreach (qreal line, this->vLines())
            if (fabs(line - vLine) <= this->m_snappingPT)
            {
                this->m_center += QPointF(vLine - line, 0);
                snapped = true;

                break;
            }

        if (snapped)
            break;
    }
}

bool Space::contains(QPointF point)
{
    QPointF p = point - this->m_center;

    qreal x = p.x() *  cos(this->m_rotation) + p.y() * sin(this->m_rotation);
    qreal y = p.x() * -sin(this->m_rotation) + p.y() * cos(this->m_rotation);

    QRectF rect(QPointF(0, 0), this->m_scale * this->m_size);
    rect.moveCenter(QPointF(0, 0));

    return rect.contains(x, y);
}

QSizeF Space::internalRectSize(QSizeF size)
{
    qreal rot = this->m_rotation;
    qreal d = cos(2 * rot);

    if (d == 0)
    {
        rot += 0.01 * M_PI / 180;
        d = cos(2 * rot);
    }

    qreal width = size.width() * fabs(cos(rot)) - size.height() * fabs(sin(rot));
    qreal height = size.height() * fabs(cos(rot)) - size.width() * fabs(sin(rot));

    return QSizeF(width, height) / d;
}

QRectF Space::boundingRect()
{
    qreal width = this->m_size.width() * fabs(cos(this->m_rotation)) + this->m_size.height() * fabs(sin(this->m_rotation));
    qreal height = this->m_size.width() * fabs(sin(this->m_rotation)) + this->m_size.height() * fabs(cos(this->m_rotation));

    QSizeF boundSize = this->m_scale * QSizeF(width, height);
    QPointF topLeft = this->m_center - QPointF(boundSize.width(), boundSize.height()) / 2;

    return QRectF(topLeft, boundSize);
}

QPointF Space::pos()
{
    return this->m_center - QPointF(this->m_size.width(), this->m_size.height()) / 2;
}

QString Space::spaceId()
{
    return this->m_spaceId;
}

int Space::nParts()
{
    return this->m_nParts;
}

QPointF Space::center()
{
    return this->m_center;
}

QSizeF Space::size()
{
    return this->m_size;
}

bool Space::snapping()
{
    return this->m_snapping;
}

qreal Space::snappingPT()
{
    return this->m_snappingPT;
}

qreal Space::snappingRT()
{
    return this->m_snappingRT;
}

qreal Space::scale()
{
    return this->m_scale;
}

qreal Space::rotation()
{
    return this->m_rotation;
}

bool Space::maximized()
{
    return this->m_maximized;
}

void Space::setSpaceId(QString value)
{
    this->m_spaceId = value;
}

void Space::setNParts(int value)
{
    this->m_nParts = value;
}

void Space::setCenter(QPointF value)
{
    this->m_center = value;
}

void Space::setSize(QSizeF value)
{
    this->m_size = value;
}

void Space::setSnapping(bool value)
{
    this->m_snapping = value;
}

void Space::setSnappingPT(qreal value)
{
    this->m_snappingPT = value;
}

void Space::setSnappingRT(qreal value)
{
    this->m_snappingRT = value;
}

void Space::setScale(qreal value)
{
    this->m_scale = value;
}

void Space::setRotation(qreal rotation)
{
    while (true)
    {
        if (rotation > 2 * M_PI)
            rotation -= 2 * M_PI;
        else if (rotation < -2 * M_PI)
            rotation += 2 * M_PI;
        else
            break;
    }

    this->m_rotation = (rotation < 0)? 2 * M_PI + rotation: rotation;

    if (this->m_snapping && !this->m_snapAngles.contains(this->m_rotation))
        foreach (qreal angle, this->m_snapAngles)
            if (fabs(this->m_rotation - angle) <= this->m_snappingRT)
            {
                this->m_rotation = angle;

                break;
            }
}

void Space::setMaximized(bool value)
{
    this->m_maximized = value;
}

void Space::resetSpaceId()
{
    this->m_spaceId = "";
}

void Space::resetNParts()
{
    this->m_nParts = 1;
}

void Space::resetCenter()
{
    this->m_center = QPointF(0, 0);
}

void Space::resetSize()
{
    this->m_size = QSizeF(0, 0);
}

void Space::resetSnapping()
{
    this->m_snapping = false;
}

void Space::resetSnappingPT()
{
    this->m_snappingPT = 0;
}

void Space::resetSnappingRT()
{
    this->m_snappingRT = 0;
}

void Space::resetScale()
{
    this->m_scale = 1;
}

void Space::resetRotation()
{
    this->m_rotation = 0;
}

void Space::resetMaximized()
{
    this->m_maximized = false;
}
