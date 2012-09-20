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

#ifndef PARTICLE_H
#define PARTICLE_H

#include <QtGui>

class Particle: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QPoint pos READ pos WRITE setPos RESET resetPos)
    Q_PROPERTY(QRect rect READ rect WRITE setRect RESET resetRect)
    Q_PROPERTY(float minSpeed READ minSpeed WRITE setMinSpeed RESET resetMinSpeed)
    Q_PROPERTY(float maxSpeed READ maxSpeed WRITE setMaxSpeed RESET resetMaxSpeed)
    Q_PROPERTY(float minDirection READ minDirection WRITE setMinDirection RESET resetMinDirection)
    Q_PROPERTY(float maxDirection READ maxDirection WRITE setMaxDirection RESET resetMaxDirection)
    Q_PROPERTY(QSize minSize READ minSize WRITE setMinSize RESET resetMinSize)
    Q_PROPERTY(QSize maxSize READ maxSize WRITE setMaxSize RESET resetMaxSize)
    Q_PROPERTY(const QList<QImage> *sprites READ sprites WRITE setSprites RESET resetSprites)
    Q_PROPERTY(QImage sprite READ sprite WRITE setSprite RESET resetSprite)
    Q_PROPERTY(float inc READ inc WRITE setInc RESET resetInc)

    public:
        explicit Particle(QObject *parent = 0);
        Particle(const Particle &object);

        Particle(QRect rect,
                 float minSpeed,
                 float maxSpeed,
                 float minDirection,
                 float maxDirection,
                 QSize minSize,
                 QSize maxSize,
                 const QList<QImage> *sprites,
                 float inc);

        Particle& operator =(const Particle &other);
        QPoint pos();
        QRect rect();
        float minSpeed();
        float maxSpeed();
        float minDirection();
        float maxDirection();
        QSize minSize();
        QSize maxSize();
        const QList<QImage> *sprites();
        QImage sprite();
        float inc();

        Particle operator ++(int);

    private:
        QPoint m_pos;
        QRect m_rect;
        float m_minSpeed;
        float m_maxSpeed;
        float m_speed;
        float m_minDirection;
        float m_maxDirection;
        float m_direction;
        QSize m_minSize;
        QSize m_maxSize;
        const QList<QImage> *m_sprites;
        QImage m_sprite;
        float m_inc;

        int randr(int min, int max);
        float randr(float min, float max);

    public slots:
        void setPos(QPoint pos);
        void setRect(QRect rect);
        void setMinSpeed(float minSpeed);
        void setMaxSpeed(float maxSpeed);
        void setMinDirection(float minDirection);
        void setMaxDirection(float maxDirection);
        void setMinSize(QSize minSize);
        void setMaxSize(QSize maxSize);
        void setSprites(const QList<QImage> *sprites);
        void setSprite(const QImage &sprite);
        void setInc(float inc);
        void resetPos();
        void resetRect();
        void resetMinSpeed();
        void resetMaxSpeed();
        void resetMinDirection();
        void resetMaxDirection();
        void resetMinSize();
        void resetMaxSize();
        void resetSprites();
        void resetSprite();
        void resetInc();
};

#endif // PARTICLE_H
