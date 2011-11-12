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

#ifndef SNOW_H
#define SNOW_H

#include <QImage>

#include "snowflake.h"

class Snow: public QObject
{
    Q_OBJECT

    Q_PROPERTY(int width READ width WRITE setWidth RESET resetWidth)
    Q_PROPERTY(int height READ height WRITE setHeight RESET resetHeight)
    Q_PROPERTY(int nFlakes READ nFlakes WRITE setNFlakes RESET resetNFlakes)
    Q_PROPERTY(float acceleration READ acceleration WRITE setAcceleration RESET resetAcceleration)
    Q_PROPERTY(float direction READ direction WRITE setDirection RESET resetDirection)
    Q_PROPERTY(float randFactor READ randFactor WRITE setRandFactor RESET resetRandFactor)
    Q_PROPERTY(int border READ border WRITE setBorder RESET resetBorder)
    Q_PROPERTY(float minZ READ minZ WRITE setMinZ RESET resetMinZ)
    Q_PROPERTY(float maxZ READ maxZ WRITE setMaxZ RESET resetMaxZ)
    Q_PROPERTY(float minScale READ minScale WRITE setMinScale RESET resetMinScale)
    Q_PROPERTY(float maxScale READ maxScale WRITE setMaxScale RESET resetMaxScale)

    public:
        explicit Snow(QObject *parent = 0);

        Snow(int width,
             int height,
             int nFlakes,
             float acceleration,
             float direction,
             float randFactor,
             int border,
             float minZ,
             float maxZ,
             float minScale,
             float maxScale);

        int width();
        int height();
        int nFlakes();
        float acceleration();
        float direction();
        float randFactor();
        int border();
        float minZ();
        float maxZ();
        float minScale();
        float maxScale();

        QImage render(const QImage &frame);

    private:
        int m_width;
        int m_height;
        int m_nFlakes;
        float m_acceleration;
        float m_direction;
        float m_randFactor;
        int m_border;
        float m_minZ;
        float m_maxZ;
        float m_minScale;
        float m_maxScale;
        QList<QImage> flakes;
        QList<SnowFlake> snowFlakes;

    public slots:
        void updateFlakes();
        void resize(int width, int height);
        void reset();
        void next();
        void setWidth(int value);
        void setHeight(int value);
        void setNFlakes(int value);
        void setAcceleration(float value);
        void setDirection(float value);
        void setRandFactor(float value);
        void setBorder(int value);
        void setMinZ(float value);
        void setMaxZ(float value);
        void setMinScale(float value);
        void setMaxScale(float value);
        void resetWidth();
        void resetHeight();
        void resetNFlakes();
        void resetAcceleration();
        void resetDirection();
        void resetRandFactor();
        void resetBorder();
        void resetMinZ();
        void resetMaxZ();
        void resetMinScale();
        void resetMaxScale();
};

#endif // SNOW_H
