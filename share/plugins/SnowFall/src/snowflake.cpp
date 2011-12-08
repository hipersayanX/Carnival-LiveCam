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

SnowFlake::SnowFlake(int x,
                     int y,
                     float z,
                     int t,
                     int width,
                     int height,
                     int minX,
                     int minY,
                     float minZ,
                     int maxX,
                     int maxY,
                     float maxZ,
                     float acceleration,
                     float direction,
                     float scale,
                     float randFactor,
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

int SnowFlake::x()
{
    return this->m_x;
}

int SnowFlake::y()
{
    return this->m_y;
}

float SnowFlake::z()
{
    return this->m_z;
}

int SnowFlake::t()
{
    return this->m_t;
}

int SnowFlake::width()
{
    return this->m_width;
}

int SnowFlake::height()
{
    return this->m_height;
}

int SnowFlake::minX()
{
    return this->m_minX;
}

int SnowFlake::minY()
{
    return this->m_minY;
}

float SnowFlake::minZ()
{
    return this->m_minZ;
}

int SnowFlake::maxX()
{
    return this->m_maxX;
}

int SnowFlake::maxY()
{
    return this->m_maxY;
}

float SnowFlake::maxZ()
{
    return this->m_maxZ;
}

float SnowFlake::acceleration()
{
    return this->m_acceleration;
}

float SnowFlake::direction()
{
    return this->m_direction;
}

float SnowFlake::scale()
{
    return this->m_scale;
}

float SnowFlake::randFactor()
{
    return this->m_randFactor;
}

QImage SnowFlake::flake()
{
    return this->m_flake;
}

float SnowFlake::randPercent()
{
    return 2 * this->m_randFactor * (float) rand() / (float) RAND_MAX - this->m_randFactor + 1;
}

void SnowFlake::reset()
{
    this->x0 = (float) rand() * (this->m_maxX - this->m_minX) / (float) RAND_MAX + this->m_minX;
    this->y0 = this->m_minY;
    this->m_x = this->x0;
    this->m_y = this->m_minY;
    this->m_z = (float) rand() * (this->m_maxZ - this->m_minZ) / (float) RAND_MAX + this->m_minZ;
    this->m_t = 0;
    this->m_width = this->m_z * this->m_scale * this->m_flake.width();
    this->m_height = this->m_z * this->m_scale * this->m_flake.height();
}

void SnowFlake::step()
{
    float angle = M_PI * this->m_direction / 180.0;

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

void SnowFlake::setX(int value)
{
    this->m_x = value;
}

void SnowFlake::setY(int value)
{
    this->m_y = value;
}

void SnowFlake::setZ(float value)
{
    this->m_z = value;
}

void SnowFlake::setT(int value)
{
    this->m_t = value;
}

void SnowFlake::setWidth(int value)
{
    this->m_width = value;
}

void SnowFlake::setHeight(int value)
{
    this->m_height = value;
}

void SnowFlake::setMinX(int value)
{
    this->m_minX = value;
}

void SnowFlake::setMinY(int value)
{
    this->m_minY = value;
}

void SnowFlake::setMinZ(float value)
{
    this->m_minZ = value;
}

void SnowFlake::setMaxX(int value)
{
    this->m_maxX = value;
}

void SnowFlake::setMaxY(int value)
{
    this->m_maxY = value;
}

void SnowFlake::setMaxZ(float value)
{
    this->m_maxZ = value;
}

void SnowFlake::setAcceleration(float value)
{
    this->m_acceleration = value;
}

void SnowFlake::setDirection(float value)
{
    this->m_direction = value;
}

void SnowFlake::setScale(float value)
{
    this->m_scale = value;
}

void SnowFlake::setRandFactor(float value)
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
