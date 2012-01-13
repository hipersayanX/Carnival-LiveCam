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
 */

#ifndef SPACEMODEL_H
#define SPACEMODEL_H

#include <QObject>

#include "space.h"

class SpaceModel: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QSizeF size READ size WRITE setSize RESET resetSize)
    Q_PROPERTY(QList<Space> spaces READ spaces WRITE setSpaces RESET resetSpaces)
    Q_PROPERTY(bool snapping READ snapping WRITE setSnapping RESET resetSnapping)
    Q_PROPERTY(int nParts READ nParts WRITE setNParts RESET resetNParts)
    Q_PROPERTY(qreal snappingPT READ snappingPT WRITE setSnappingPT RESET resetSnappingPT)
    Q_PROPERTY(qreal snappingRT READ snappingRT WRITE setSnappingRT RESET resetSnappingRT)

    public:
        explicit SpaceModel(QObject *parent = 0);
        Q_INVOKABLE void setSnapping(bool snapping, int nParts, qreal snappingPT, qreal snappingRT);
        Q_INVOKABLE void setSpace(QString spaceId, QSizeF size);
        Q_INVOKABLE void removeSpace(QString spaceId);
        Q_INVOKABLE void selectSpace(QString spaceId);
        Q_INVOKABLE void selectSpace(QPointF point);
        Q_INVOKABLE void toggleMaximizedSpace();
        Q_INVOKABLE bool isMaximized(QString spaceId);

        QSizeF size();
        QList<Space> spaces();
        bool snapping();
        int nParts();
        qreal snappingPT();
        qreal snappingRT();

    private:
        QSizeF m_size;
        QList<Space> m_spaces;
        QPointF m_pointRef;
        QString m_spaceIdRef;
        bool m_snapping;
        int m_nParts;
        qreal m_snappingPT;
        qreal m_snappingRT;

        template <typename T> void cleanAndSort(QList<T> &list);
        template <typename T> QList<T> reversed(const QList<T> &list);
        template <typename T> bool snapLines(QList<T> &hLines, QList<T> &vLines);
        qreal calculateAngle(QPointF point);
        void updateSize();

    public slots:
        void scaleSpace(QPointF to);
        void rotateSpace(QPointF to);
        void scaleAndRotateSpace(QPointF to);
        void moveSpace(QPointF to);
        void setSize(QSizeF value);
        void setSpaces(QList<Space> value);
        void setSnapping(bool value);
        void setNParts(int value);
        void setSnappingPT(qreal value);
        void setSnappingRT(qreal value);
        void resetSize();
        void resetSpaces();
        void resetSnapping();
        void resetNParts();
        void resetSnappingPT();
        void resetSnappingRT();
};

#endif // SPACEMODEL_H
