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
 *
 * Snow fall plugin
 */

#include <cstdlib>

#include <QPainter>
#include <QtDebug>

#include "../include/snow.h"

Snow::Snow(QObject *parent): QObject(parent)
{
    this->m_width = 0;
    this->m_height = 0;
    this->m_nFlakes = 0;
    this->m_acceleration = 0;
    this->m_direction = 0;
    this->m_randFactor = 0;
    this->m_border = 0;
    this->m_minZ = 0;
    this->m_maxZ = 0;
    this->m_minScale = 0;
    this->m_maxScale = 0;

    this->updateFlakes();
    this->reset();
}

Snow::Snow(const Snow &object):
    QObject(object.parent()),
    m_width(object.m_width),
    m_height(object.m_height),
    m_nFlakes(object.m_nFlakes),
    m_acceleration(object.m_acceleration),
    m_direction(object.m_direction),
    m_randFactor(object.m_randFactor),
    m_border(object.m_border),
    m_minZ(object.m_minZ),
    m_maxZ(object.m_maxZ),
    m_minScale(object.m_minScale),
    m_maxScale(object.m_maxScale)
{
    this->updateFlakes();
    this->reset();
}

Snow::Snow(qint32 width,
           qint32 height,
           qint32 nFlakes,
           qreal acceleration,
           qreal direction,
           qreal randFactor,
           qint32 border,
           qreal minZ,
           qreal maxZ,
           qreal minScale,
           qreal maxScale):
    m_width(width),
    m_height(height),
    m_nFlakes(nFlakes),
    m_acceleration(acceleration),
    m_direction(direction),
    m_randFactor(randFactor),
    m_border(border),
    m_minZ(minZ),
    m_maxZ(maxZ),
    m_minScale(minScale),
    m_maxScale(maxScale)
{
    this->updateFlakes();
    this->reset();
}

Snow& Snow::operator =(const Snow &other)
{
    if (this != &other)
    {
        this->m_width = other.m_width;
        this->m_height = other.m_height;
        this->m_nFlakes = other.m_nFlakes;
        this->m_acceleration = other.m_acceleration;
        this->m_direction = other.m_direction;
        this->m_randFactor = other.m_randFactor;
        this->m_border = other.m_border;
        this->m_minZ = other.m_minZ;
        this->m_maxZ = other.m_maxZ;
        this->m_minScale = other.m_minScale;
        this->m_maxScale = other.m_maxScale;
    }

    this->updateFlakes();
    this->reset();

    return *this;
}

qint32 Snow::width()
{
    return this->m_width;
}

qint32 Snow::height()
{
    return this->m_height;
}

qint32 Snow::nFlakes()
{
    return this->m_nFlakes;
}

qreal Snow::acceleration()
{
    return this->m_acceleration;
}

qreal Snow::direction()
{
    return this->m_direction;
}

qreal Snow::randFactor()
{
    return this->m_randFactor;
}

qint32 Snow::border()
{
    return this->m_border;
}

qreal Snow::minZ()
{
    return this->m_minZ;
}

qreal Snow::maxZ()
{
    return this->m_maxZ;
}

qreal Snow::minScale()
{
    return this->m_minScale;
}

qreal Snow::maxScale()
{
    return this->m_maxScale;
}

void Snow::updateFlakes()
{
    this->flakes.clear();

    for (qint32 imgFlake = 0; imgFlake < 4; imgFlake++)
        this->flakes << QImage("share/plugins/SnowFall/share/flakes/flake" + QString::number(imgFlake) + ".png");
}

QImage Snow::render(const QImage &frame)
{
    QImage tmpFrame(frame);
    QPainter painter;

    painter.begin(&tmpFrame);

    for (qint32 flake = 0; flake < this->m_nFlakes; flake++)
        painter.drawImage(this->snowFlakes[flake].x(),
                          this->snowFlakes[flake].y(),
                          this->snowFlakes[flake].flake().scaled(this->snowFlakes[flake].width(),
                                                                 this->snowFlakes[flake].height()));

    painter.end();
    this->next();

    return tmpFrame;
}

void Snow::reset()
{
    this->snowFlakes.clear();

    for (qint32 flake = 0; flake < this->m_nFlakes; flake++)
        this->snowFlakes << SnowFlake(0,
                                      0,
                                      0,
                                      0,
                                      0,
                                      0,
                                      -this->m_border,
                                      -this->m_border,
                                      this->m_minZ,
                                      this->m_width + this->m_border,
                                      this->m_height + this->m_border,
                                      this->m_maxZ,
                                      this->m_acceleration,
                                      this->m_direction,
                                      0.05,
                                      this->m_randFactor,
                                      this->flakes[rand() % 4]);
}

void Snow::next()
{
    for (qint32 flake = 0; flake < this->m_nFlakes; flake++)
        this->snowFlakes[flake].next();
}

void Snow::setWidth(qint32 value)
{
    this->m_width = value;
}

void Snow::setHeight(qint32 value)
{
    this->m_height = value;
}

void Snow::setNFlakes(qint32 value)
{
    this->m_nFlakes = value;
}

void Snow::setAcceleration(qreal value)
{
    this->m_acceleration = value;
}

void Snow::setDirection(qreal value)
{
    this->m_direction = value;
}

void Snow::setRandFactor(qreal value)
{
    this->m_randFactor = value;
}

void Snow::setBorder(qint32 value)
{
    this->m_border = value;
}

void Snow::setMinZ(qreal value)
{
    this->m_minZ = value;
}

void Snow::setMaxZ(qreal value)
{
    this->m_maxZ = value;
}

void Snow::setMinScale(qreal value)
{
    this->m_minScale = value;
}

void Snow::setMaxScale(qreal value)
{
    this->m_maxScale = value;
}

void Snow::resetWidth()
{
    this->m_width = 0;
}

void Snow::resetHeight()
{
    this->m_height = 0;
}

void Snow::resetNFlakes()
{
    this->m_nFlakes = 0;
}

void Snow::resetAcceleration()
{
    this->m_acceleration = 0;
}

void Snow::resetDirection()
{
    this->m_direction = 0;
}

void Snow::resetRandFactor()
{
    this->m_randFactor = 0;
}

void Snow::resetBorder()
{
    this->m_border = 0;
}

void Snow::resetMinZ()
{
    this->m_minZ = 0;
}

void Snow::resetMaxZ()
{
    this->m_maxZ = 0;
}

void Snow::resetMinScale()
{
    this->m_minScale = 0;
}

void Snow::resetMaxScale()
{
    this->m_maxScale = 0;
}
