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

    Q_PROPERTY(qint32 x READ x WRITE setX RESET resetX)
    Q_PROPERTY(qint32 y READ y WRITE setY RESET resetY)
    Q_PROPERTY(qreal z READ z WRITE setZ RESET resetZ)
    Q_PROPERTY(qint32 t READ t WRITE setT RESET resetT)
    Q_PROPERTY(qint32 width READ width WRITE setWidth RESET resetWidth)
    Q_PROPERTY(qint32 height READ height WRITE setHeight RESET resetHeight)
    Q_PROPERTY(qint32 minX READ minX WRITE setMinX RESET resetMinX)
    Q_PROPERTY(qint32 minY READ minY WRITE setMinY RESET resetMinY)
    Q_PROPERTY(qreal minZ READ minZ WRITE setMinZ RESET resetMinZ)
    Q_PROPERTY(qint32 maxX READ maxX WRITE setMaxX RESET resetMaxX)
    Q_PROPERTY(qint32 maxY READ maxY WRITE setMaxY RESET resetMaxY)
    Q_PROPERTY(qreal maxZ READ maxZ WRITE setMaxZ RESET resetMaxZ)
    Q_PROPERTY(qreal acceleration READ acceleration WRITE setAcceleration RESET resetAcceleration)
    Q_PROPERTY(qreal direction READ direction WRITE setDirection RESET resetDirection)
    Q_PROPERTY(qreal scale READ scale WRITE setScale RESET resetScale)
    Q_PROPERTY(qreal randFactor READ randFactor WRITE setRandFactor RESET resetRandFactor)
    Q_PROPERTY(QImage flake READ flake WRITE setFlake RESET resetFlake)

    public:
        explicit SnowFlake(QObject *parent = 0);
        SnowFlake(const SnowFlake &object);

        SnowFlake(qint32 x,
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
                  const QImage &flake);

        SnowFlake& operator =(const SnowFlake &other);
        qint32 x();
        qint32 y();
        qreal z();
        qint32 t();
        qint32 width();
        qint32 height();
        qint32 minX();
        qint32 minY();
        qreal minZ();
        qint32 maxX();
        qint32 maxY();
        qreal maxZ();
        qreal acceleration();
        qreal direction();
        qreal scale();
        qreal randFactor();
        QImage flake();

    private:
        qint32 x0;
        qint32 y0;
        qint32 m_x;
        qint32 m_y;
        qreal m_z;
        qint32 m_t;
        qint32 m_width;
        qint32 m_height;
        qint32 m_minX;
        qint32 m_minY;
        qreal m_minZ;
        qint32 m_maxX;
        qint32 m_maxY;
        qreal m_maxZ;
        qreal m_acceleration;
        qreal m_direction;
        qreal m_scale;
        qreal m_randFactor;
        QImage m_flake;

        qreal randPercent();

    public slots:
        void reset();
        void step();
        void next();
        void setX(qint32 value);
        void setY(qint32 value);
        void setZ(qreal value);
        void setT(qint32 value);
        void setWidth(qint32 value);
        void setHeight(qint32 value);
        void setMinX(qint32 value);
        void setMinY(qint32 value);
        void setMinZ(qreal value);
        void setMaxX(qint32 value);
        void setMaxY(qint32 value);
        void setMaxZ(qreal value);
        void setAcceleration(qreal value);
        void setDirection(qreal value);
        void setScale(qreal value);
        void setRandFactor(qreal value);
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
