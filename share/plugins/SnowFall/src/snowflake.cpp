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
#include <cmath>

#include "../include/snowflake.h"

using namespace std;

SnowFlake::SnowFlake(QObject *parent): QObject(parent)
{
    this->m_x = 0;
    this->m_y = 0;
    this->m_z = 0;
    this->m_t = 0;
    this->m_width = 0;
    this->m_height = 0;
    this->m_minX = 0;
    this->m_minY = 0;
    this->m_minZ = 0;
    this->m_maxX = 0;
    this->m_maxY = 0;
    this->m_maxZ = 0;
    this->m_acceleration = 0;
    this->m_direction = 0;
    this->m_scale = 1;
    this->m_randFactor = 0;
    this->m_flake = QImage();

    this->reset();
}

SnowFlake::SnowFlake(const SnowFlake &object):
    QObject(object.parent()),
    m_x(object.m_x),
    m_y(object.m_y),
    m_z(object.m_z),
    m_t(object.m_t),
    m_width(object.m_width),
    m_height(object.m_height),
    m_minX(object.m_minX),
    m_minY(object.m_minY),
    m_minZ(object.m_minZ),
    m_maxX(object.m_maxX),
    m_maxY(object.m_maxY),
    m_maxZ(object.m_maxZ),
    m_acceleration(object.m_acceleration),
    m_direction(object.m_direction),
    m_scale(object.m_scale),
    m_randFactor(object.m_randFactor),
    m_flake(object.m_flake)
{
    this->reset();
}

SnowFlake::SnowFlake(qint32 x,
                     qint32 y,
                     qreal z,
                     qint32 t,
                     qint32 width,
                     qint32 height,
                     qint32 minX,
                     qint32 minY,
                     qreal minZ,
                     qint32 maxX,
                     qint32 maxY,
                     qreal maxZ,
                     qreal acceleration,
                     qreal direction,
                     qreal scale,
                     qreal randFactor,
                     const QImage &flake):
    m_x(x),
    m_y(y),
    m_z(z),
    m_t(t),
    m_width(width),
    m_height(height),
    m_minX(minX),
    m_minY(minY),
    m_minZ(minZ),
    m_maxX(maxX),
    m_maxY(maxY),
    m_maxZ(maxZ),
    m_acceleration(acceleration),
    m_direction(direction),
    m_scale(scale),
    m_randFactor(randFactor),
    m_flake(flake)
{
    this->reset();
}

SnowFlake& SnowFlake::operator =(const SnowFlake &other)
{
    if (this != &other)
    {
        this->m_x = other.m_x;
        this->m_y = other.m_y;
        this->m_z = other.m_z;
        this->m_t = other.m_t;
        this->m_width = other.m_width;
        this->m_height = other.m_height;
        this->m_minX = other.m_minX;
        this->m_minY = other.m_minY;
        this->m_minZ = other.m_minZ;
        this->m_maxX = other.m_maxX;
        this->m_maxY = other.m_maxY;
        this->m_maxZ = other.m_maxZ;
        this->m_acceleration = other.m_acceleration;
        this->m_direction = other.m_direction;
        this->m_scale = other.m_scale;
        this->m_randFactor = other.m_randFactor;
        this->m_flake = other.m_flake;
    }

    return *this;
}

qint32 SnowFlake::x()
{
    return this->m_x;
}

qint32 SnowFlake::y()
{
    return this->m_y;
}

qreal SnowFlake::z()
{
    return this->m_z;
}

qint32 SnowFlake::t()
{
    return this->m_t;
}

qint32 SnowFlake::width()
{
    return this->m_width;
}

qint32 SnowFlake::height()
{
    return this->m_height;
}

qint32 SnowFlake::minX()
{
    return this->m_minX;
}

qint32 SnowFlake::minY()
{
    return this->m_minY;
}

qreal SnowFlake::minZ()
{
    return this->m_minZ;
}

qint32 SnowFlake::maxX()
{
    return this->m_maxX;
}

qint32 SnowFlake::maxY()
{
    return this->m_maxY;
}

qreal SnowFlake::maxZ()
{
    return this->m_maxZ;
}

qreal SnowFlake::acceleration()
{
    return this->m_acceleration;
}

qreal SnowFlake::direction()
{
    return this->m_direction;
}

qreal SnowFlake::scale()
{
    return this->m_scale;
}

qreal SnowFlake::randFactor()
{
    return this->m_randFactor;
}

QImage SnowFlake::flake()
{
    return this->m_flake;
}

qreal SnowFlake::randPercent()
{
    return 2 * this->m_randFactor * (qreal) rand() / (qreal) RAND_MAX - this->m_randFactor + 1;
}

void SnowFlake::reset()
{
    this->x0 = (qreal) rand() * (this->m_maxX - this->m_minX) / (qreal) RAND_MAX + this->m_minX;
    this->y0 = this->m_minY;
    this->m_x = this->x0;
    this->m_y = this->m_minY;
    this->m_z = (qreal) rand() * (this->m_maxZ - this->m_minZ) / (qreal) RAND_MAX + this->m_minZ;
    this->m_t = 0;
    this->m_width = this->m_z * this->m_scale * this->m_flake.width();
    this->m_height = this->m_z * this->m_scale * this->m_flake.height();
}

void SnowFlake::step()
{
    qreal angle = M_PI * this->m_direction / 180.0;

    this->m_x = this->x0 + this->randPercent() * this->m_z * this->m_acceleration * this->m_t * this->m_t * sin(angle) / 2;
    this->m_y = this->y0 + this->m_z * this->m_acceleration * this->m_t * this->m_t * cos(angle) / 2;
    this->m_t++;
}

void SnowFlake::next()
{
    this->step();

    if (this->m_x < this->m_minX ||
        this->m_x > this->m_maxX ||
        this->m_y < this->m_minY ||
        this->m_y > this->m_maxY)
        this->reset();
}

void SnowFlake::setX(qint32 value)
{
    this->m_x = value;
}

void SnowFlake::setY(qint32 value)
{
    this->m_y = value;
}

void SnowFlake::setZ(qreal value)
{
    this->m_z = value;
}

void SnowFlake::setT(qint32 value)
{
    this->m_t = value;
}

void SnowFlake::setWidth(qint32 value)
{
    this->m_width = value;
}

void SnowFlake::setHeight(qint32 value)
{
    this->m_height = value;
}

void SnowFlake::setMinX(qint32 value)
{
    this->m_minX = value;
}

void SnowFlake::setMinY(qint32 value)
{
    this->m_minY = value;
}

void SnowFlake::setMinZ(qreal value)
{
    this->m_minZ = value;
}

void SnowFlake::setMaxX(qint32 value)
{
    this->m_maxX = value;
}

void SnowFlake::setMaxY(qint32 value)
{
    this->m_maxY = value;
}

void SnowFlake::setMaxZ(qreal value)
{
    this->m_maxZ = value;
}

void SnowFlake::setAcceleration(qreal value)
{
    this->m_acceleration = value;
}

void SnowFlake::setDirection(qreal value)
{
    this->m_direction = value;
}

void SnowFlake::setScale(qreal value)
{
    this->m_scale = value;
}

void SnowFlake::setRandFactor(qreal value)
{
    this->m_randFactor = value;
}

void SnowFlake::setFlake(const QImage &flake)
{
    this->m_flake = flake;
}

void SnowFlake::resetX()
{
    this->m_x = 0;
}

void SnowFlake::resetY()
{
    this->m_y = 0;
}

void SnowFlake::resetZ()
{
    this->m_z = 0;
}

void SnowFlake::resetT()
{
    this->m_t = 0;
}

void SnowFlake::resetWidth()
{
    this->m_width = 0;
}

void SnowFlake::resetHeight()
{
    this->m_height = 0;
}

void SnowFlake::resetMinX()
{
    this->m_minX = 0;
}

void SnowFlake::resetMinY()
{
    this->m_minY = 0;
}

void SnowFlake::resetMinZ()
{
    this->m_minZ = 0;
}

void SnowFlake::resetMaxX()
{
    this->m_maxX = 0;
}

void SnowFlake::resetMaxY()
{
    this->m_maxY = 0;
}

void SnowFlake::resetMaxZ()
{
    this->m_maxZ = 0;
}

void SnowFlake::resetAcceleration()
{
    this->m_acceleration = 0;
}

void SnowFlake::resetDirection()
{
    this->m_direction = 0;
}

void SnowFlake::resetScale()
{
    this->m_scale = 1;
}

void SnowFlake::resetRandFactor()
{
    this->m_randFactor = 1;
}

void SnowFlake::resetFlake()
{
    this->m_flake = QImage();
}
