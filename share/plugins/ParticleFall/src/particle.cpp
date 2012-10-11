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

#include <cstdlib>
#include <cmath>

#include "particle.h"

using namespace std;

Particle::Particle(QObject *parent): QObject(parent)
{
    this->m_speed = 0;
    this->m_direction = 0;

    this->resetPos();
    this->resetRect();
    this->resetMinSpeed();
    this->resetMaxSpeed();
    this->resetMinDirection();
    this->resetMaxDirection();
    this->resetMinSize();
    this->resetMaxSize();
    this->resetSprites();
    this->resetSprite();
    this->resetInc();
}

Particle::Particle(const Particle &object):
    QObject(object.parent()),
    m_pos(object.m_pos),
    m_rect(object.m_rect),
    m_minSpeed(object.m_minSpeed),
    m_maxSpeed(object.m_maxSpeed),
    m_speed(object.m_speed),
    m_minDirection(object.m_minDirection),
    m_maxDirection(object.m_maxDirection),
    m_direction(object.m_direction),
    m_minSize(object.m_minSize),
    m_maxSize(object.m_maxSize),
    m_sprites(object.m_sprites),
    m_sprite(object.m_sprite),
    m_inc(object.m_inc)
{
}

Particle::Particle(QRect rect,
                   float minSpeed,
                   float maxSpeed,
                   float minDirection,
                   float maxDirection,
                   QSize minSize,
                   QSize maxSize,
                   const QList<QImage> *sprites,
                   float inc):
    m_rect(rect),
    m_minSpeed(minSpeed),
    m_maxSpeed(maxSpeed),
    m_minDirection(minDirection),
    m_maxDirection(maxDirection),
    m_minSize(minSize),
    m_maxSize(maxSize),
    m_sprites(sprites),
    m_inc(inc)
{
    this->m_pos = QPoint(this->randr(this->m_rect.left(), this->m_rect.right()),
                         this->randr(this->m_rect.top(), this->m_rect.bottom()));

    this->m_speed = this->randr(this->m_minSpeed, this->m_maxSpeed);
    this->m_direction = this->randr(this->m_minDirection, this->m_maxDirection);

    QSize size(this->randr(this->m_minSize.width(), this->m_maxSize.width()),
               this->randr(this->m_minSize.height(), this->m_maxSize.height()));

    if (this->m_sprites)
        this->setSprite(this->m_sprites->at(rand() % this->m_sprites->length()).scaled(size, Qt::KeepAspectRatio));
    else
        this->resetSprite();
}

Particle& Particle::operator =(const Particle &other)
{
    if (this != &other)
    {
        this->m_pos = other.m_pos;
        this->m_rect = other.m_rect;
        this->m_minSpeed = other.m_minSpeed;
        this->m_maxSpeed = other.m_maxSpeed;
        this->m_speed = other.m_speed;
        this->m_direction = other.m_direction;
        this->m_minDirection = other.m_minDirection;
        this->m_maxDirection = other.m_maxDirection;
        this->m_minSize = other.m_minSize;
        this->m_maxSize = other.m_maxSize;
        this->m_sprites = other.m_sprites;
        this->m_sprite = other.m_sprite;
        this->m_inc = other.m_inc;
    }

    return *this;
}

QPoint Particle::pos()
{
    return this->m_pos;
}

QRect Particle::rect()
{
    return this->m_rect;
}

float Particle::minSpeed()
{
    return this->m_minSpeed;
}

float Particle::maxSpeed()
{
    return this->m_maxSpeed;
}

float Particle::minDirection()
{
    return this->m_minDirection;
}

float Particle::maxDirection()
{
    return this->m_maxDirection;
}

QSize Particle::minSize()
{
    return this->m_minSize;
}

QSize Particle::maxSize()
{
    return this->m_maxSize;
}

const QList<QImage> *Particle::sprites()
{
    return this->m_sprites;
}

QImage Particle::sprite()
{
    return this->m_sprite;
}

float Particle::inc()
{
    return this->m_inc;
}

Particle Particle::operator ++(int)
{
    float angle = M_PI * this->m_direction / 180.0;

    this->m_pos += QPoint(this->m_speed * sin(angle) * this->m_inc,
                          this->m_speed * cos(angle) * this->m_inc);

    if (this->m_rect.contains(this->m_pos))
        return *this;

    this->m_pos = QPoint(this->randr(this->m_rect.left(), this->m_rect.right()),
                         this->m_rect.top());

    this->m_speed = this->randr(this->m_minSpeed, this->m_maxSpeed);
    this->m_direction = this->randr(this->m_minDirection, this->m_maxDirection);

    QSize size(this->randr(this->m_minSize.width(), this->m_maxSize.width()),
               this->randr(this->m_minSize.height(), this->m_maxSize.height()));

    if (this->m_sprites)
        this->setSprite(this->m_sprites->at(rand() % this->m_sprites->length()).scaled(size, Qt::KeepAspectRatio));
    else
        this->resetSprite();

    return *this;
}

int Particle::randr(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

float Particle::randr(float min, float max)
{
    return (max - min) * (float) rand() / (float) RAND_MAX + min;
}

void Particle::setInc(float inc)
{
    this->m_inc = inc;
}

void Particle::setPos(QPoint x)
{
    this->m_pos = x;
}

void Particle::setRect(QRect rect)
{
    this->m_rect = rect;
}

void Particle::setMinSpeed(float minSpeed)
{
    this->m_minSpeed = minSpeed;

    if (this->m_speed < this->m_minSpeed)
        this->m_speed = this->randr(this->m_minSpeed, this->m_maxSpeed);
}

void Particle::setMaxSpeed(float maxSpeed)
{
    this->m_maxSpeed = maxSpeed;

    if (this->m_speed > this->m_maxSpeed)
        this->m_speed = this->randr(this->m_minSpeed, this->m_maxSpeed);
}

void Particle::setMinDirection(float minDirection)
{
    this->m_minDirection = minDirection;

    if (this->m_direction < this->m_minDirection)
        this->m_direction = this->randr(this->m_minDirection, this->m_maxDirection);
}

void Particle::setMaxDirection(float maxDirection)
{
    this->m_maxDirection = maxDirection;

    if (this->m_direction > this->m_maxDirection)
        this->m_direction = this->randr(this->m_minDirection, this->m_maxDirection);
}

void Particle::setMinSize(QSize minSize)
{
    this->m_minSize = minSize;

    if (this->m_sprite.size().width() < this->m_minSize.width() ||
        this->m_sprite.size().height() < this->m_minSize.height())
    {
        QSize size(this->randr(this->m_minSize.width(), this->m_maxSize.width()),
                   this->randr(this->m_minSize.height(), this->m_maxSize.height()));

        this->setSprite(this->m_sprites->at(rand() % this->m_sprites->length()).scaled(size, Qt::KeepAspectRatio));
    }
}

void Particle::setMaxSize(QSize maxSize)
{
    this->m_maxSize = maxSize;

    if (this->m_sprite.size().width() > this->m_maxSize.width() ||
        this->m_sprite.size().height() > this->m_maxSize.height())
    {
        QSize size(this->randr(this->m_minSize.width(), this->m_maxSize.width()),
                   this->randr(this->m_minSize.height(), this->m_maxSize.height()));

        this->setSprite(this->m_sprites->at(rand() % this->m_sprites->length()).scaled(size, Qt::KeepAspectRatio));
    }
}

void Particle::setSprites(const QList<QImage> *sprites)
{
    this->m_sprites = sprites;

    if (this->m_sprites)
    {
        QSize size(this->randr(this->m_minSize.width(), this->m_maxSize.width()),
                   this->randr(this->m_minSize.height(), this->m_maxSize.height()));

        this->setSprite(this->m_sprites->at(rand() % this->m_sprites->length()).scaled(size, Qt::KeepAspectRatio));
    }
    else
        this->resetSprite();
}

void Particle::setSprite(const QImage &sprite)
{
    this->m_sprite = sprite;
}

void Particle::resetPos()
{
    this->setPos(QPoint());
}

void Particle::resetRect()
{
    this->setRect(QRect());
}

void Particle::resetMinSpeed()
{
    this->setMinSpeed(0);
}

void Particle::resetMaxSpeed()
{
    this->setMaxSpeed(0);
}

void Particle::resetMinDirection()
{
    this->setMinDirection(0);
}

void Particle::resetMaxDirection()
{
    this->setMaxDirection(0);
}

void Particle::resetMinSize()
{
    this->setMinSize(QSize());
}

void Particle::resetMaxSize()
{
    this->setMaxSize(QSize());
}

void Particle::resetSprites()
{
    this->setSprites(NULL);
}

void Particle::resetSprite()
{
    this->setSprite(QImage());
}

void Particle::resetInc()
{
    this->setInc(0);
}
