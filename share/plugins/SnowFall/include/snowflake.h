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

#ifndef SNOWFLAKE_H
#define SNOWFLAKE_H

#include <QImage>

class SnowFlake: public QObject
{
    Q_OBJECT

    Q_PROPERTY(int x READ x WRITE setX RESET resetX)
    Q_PROPERTY(int y READ y WRITE setY RESET resetY)
    Q_PROPERTY(float z READ z WRITE setZ RESET resetZ)
    Q_PROPERTY(int t READ t WRITE setT RESET resetT)
    Q_PROPERTY(int width READ width WRITE setWidth RESET resetWidth)
    Q_PROPERTY(int height READ height WRITE setHeight RESET resetHeight)
    Q_PROPERTY(int minX READ minX WRITE setMinX RESET resetMinX)
    Q_PROPERTY(int minY READ minY WRITE setMinY RESET resetMinY)
    Q_PROPERTY(float minZ READ minZ WRITE setMinZ RESET resetMinZ)
    Q_PROPERTY(int maxX READ maxX WRITE setMaxX RESET resetMaxX)
    Q_PROPERTY(int maxY READ maxY WRITE setMaxY RESET resetMaxY)
    Q_PROPERTY(float maxZ READ maxZ WRITE setMaxZ RESET resetMaxZ)
    Q_PROPERTY(float acceleration READ acceleration WRITE setAcceleration RESET resetAcceleration)
    Q_PROPERTY(float direction READ direction WRITE setDirection RESET resetDirection)
    Q_PROPERTY(float scale READ scale WRITE setScale RESET resetScale)
    Q_PROPERTY(float randFactor READ randFactor WRITE setRandFactor RESET resetRandFactor)
    Q_PROPERTY(QImage flake READ flake WRITE setFlake RESET resetFlake)

    public:
        explicit SnowFlake(QObject *parent = 0);
        SnowFlake(const SnowFlake &object);

        SnowFlake(int x,
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
                  const QImage &flake);

        SnowFlake& operator =(const SnowFlake &other);
        int x();
        int y();
        float z();
        int t();
        int width();
        int height();
        int minX();
        int minY();
        float minZ();
        int maxX();
        int maxY();
        float maxZ();
        float acceleration();
        float direction();
        float scale();
        float randFactor();
        QImage flake();

    private:
        int x0;
        int m_x;
        int m_y;
        float m_z;
        int m_t;
        int m_width;
        int m_height;
        int m_minX;
        int m_minY;
        float m_minZ;
        int m_maxX;
        int m_maxY;
        float m_maxZ;
        float m_acceleration;
        float m_direction;
        float m_scale;
        float m_randFactor;
        QImage m_flake;

        float randPercent();

    public slots:
        void reset();
        void step();
        void next();
        void setX(int value);
        void setY(int value);
        void setZ(float value);
        void setT(int value);
        void setWidth(int value);
        void setHeight(int value);
        void setMinX(int value);
        void setMinY(int value);
        void setMinZ(float value);
        void setMaxX(int value);
        void setMaxY(int value);
        void setMaxZ(float value);
        void setAcceleration(float value);
        void setDirection(float value);
        void setScale(float value);
        void setRandFactor(float value);
        void setFlake(const QImage &flake);
        void resetX();
        void resetY();
        void resetZ();
        void resetT();
        void resetWidth();
        void resetHeight();
        void resetMinX();
        void resetMinY();
        void resetMinZ();
        void resetMaxX();
        void resetMaxY();
        void resetMaxZ();
        void resetAcceleration();
        void resetDirection();
        void resetScale();
        void resetRandFactor();
        void resetFlake();
};

#endif // SNOWFLAKE_H
