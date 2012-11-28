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

#ifndef PARTICLEFALLELEMENT_H
#define PARTICLEFALLELEMENT_H

#include "element.h"
#include "particle.h"

class ParticleFallElement: public Element
{
    Q_OBJECT

    Q_PROPERTY(int nParticles READ nParticles WRITE setNParticles RESET resetNParticles)
    Q_PROPERTY(int padding READ padding WRITE setPadding RESET resetPadding)
    Q_PROPERTY(float minSpeed READ minSpeed WRITE setMinSpeed RESET resetMinSpeed)
    Q_PROPERTY(float maxSpeed READ maxSpeed WRITE setMaxSpeed RESET resetMaxSpeed)
    Q_PROPERTY(float minDirection READ minDirection WRITE setMinDirection RESET resetMinDirection)
    Q_PROPERTY(float maxDirection READ maxDirection WRITE setMaxDirection RESET resetMaxDirection)
    Q_PROPERTY(QSize minSize READ minSize WRITE setMinSize RESET resetMinSize)
    Q_PROPERTY(QSize maxSize READ maxSize WRITE setMaxSize RESET resetMaxSize)
    Q_PROPERTY(QStringList sprites READ sprites WRITE setSprites RESET resetSprites)
    Q_PROPERTY(float inc READ inc WRITE setInc RESET resetInc)

    public:
        explicit ParticleFallElement();

        int nParticles();
        int padding();
        float minSpeed();
        float maxSpeed();
        float minDirection();
        float maxDirection();
        QSize minSize();
        QSize maxSize();
        QStringList sprites();
        float inc();

        bool event(QEvent *event);

        Q_INVOKABLE bool start();
        Q_INVOKABLE bool stop();

    private:
        int m_nParticles;
        int m_padding;
        float m_minSpeed;
        float m_maxSpeed;
        float m_minDirection;
        float m_maxDirection;
        QSize m_minSize;
        QSize m_maxSize;
        QStringList m_sprites;
        float m_inc;
        QList<QImage> m_pixmaps;
        QList<Particle> m_particles;
        QImage m_oFrame;
        QSize m_curFrameSize;
        QList<Element *> m_srcs;
        QList<Element *> m_sinks;

    public slots:
        void setNParticles(int nParticles);
        void setPadding(int padding);
        void setMinSpeed(float minSpeed);
        void setMaxSpeed(float maxSpeed);
        void setMinDirection(float minDirection);
        void setMaxDirection(float maxDirection);
        void setMinSize(QSize minSize);
        void setMaxSize(QSize maxSize);
        void setSprites(QStringList sprites);
        void setInc(float inc);
        void resetNParticles();
        void resetPadding();
        void resetMinSpeed();
        void resetMaxSpeed();
        void resetMinDirection();
        void resetMaxDirection();
        void resetMinSize();
        void resetMaxSize();
        void resetSprites();
        void resetInc();

        void iStream(const void *data, int datalen, QString dataType);
        void setPipeline(Pipeline *pipeline);
        void setPeers(QList<Element *> srcs, QList<Element *> sinks);
};

#endif // PARTICLEFALLELEMENT_H
