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

    Q_PROPERTY(qint32 width READ width WRITE setWidth RESET resetWidth)
    Q_PROPERTY(qint32 height READ height WRITE setHeight RESET resetHeight)
    Q_PROPERTY(qint32 nFlakes READ nFlakes WRITE setNFlakes RESET resetNFlakes)
    Q_PROPERTY(qreal acceleration READ acceleration WRITE setAcceleration RESET resetAcceleration)
    Q_PROPERTY(qreal direction READ direction WRITE setDirection RESET resetDirection)
    Q_PROPERTY(qreal randFactor READ randFactor WRITE setRandFactor RESET resetRandFactor)
    Q_PROPERTY(qint32 border READ border WRITE setBorder RESET resetBorder)
    Q_PROPERTY(qreal minZ READ minZ WRITE setMinZ RESET resetMinZ)
    Q_PROPERTY(qreal maxZ READ maxZ WRITE setMaxZ RESET resetMaxZ)
    Q_PROPERTY(qreal minScale READ minScale WRITE setMinScale RESET resetMinScale)
    Q_PROPERTY(qreal maxScale READ maxScale WRITE setMaxScale RESET resetMaxScale)

    public:
        explicit Snow(QObject *parent = 0);
        Snow(const Snow &object);

        Snow(qint32 width,
             qint32 height,
             qint32 nFlakes,
             qreal acceleration,
             qreal direction,
             qreal randFactor,
             qint32 border,
             qreal minZ,
             qreal maxZ,
             qreal minScale,
             qreal maxScale);

        Snow& operator =(const Snow &other);

        qint32 width();
        qint32 height();
        qint32 nFlakes();
        qreal acceleration();
        qreal direction();
        qreal randFactor();
        qint32 border();
        qreal minZ();
        qreal maxZ();
        qreal minScale();
        qreal maxScale();

        QImage render(const QImage &frame);

    private:
        qint32 m_width;
        qint32 m_height;
        qint32 m_nFlakes;
        qreal m_acceleration;
        qreal m_direction;
        qreal m_randFactor;
        qint32 m_border;
        qreal m_minZ;
        qreal m_maxZ;
        qreal m_minScale;
        qreal m_maxScale;
        QList<QImage> flakes;
        QList<SnowFlake> snowFlakes;

    public slots:
        void updateFlakes();
        void reset();
        void next();
        void setWidth(qint32 value);
        void setHeight(qint32 value);
        void setNFlakes(qint32 value);
        void setAcceleration(qreal value);
        void setDirection(qreal value);
        void setRandFactor(qreal value);
        void setBorder(qint32 value);
        void setMinZ(qreal value);
        void setMaxZ(qreal value);
        void setMinScale(qreal value);
        void setMaxScale(qreal value);
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
