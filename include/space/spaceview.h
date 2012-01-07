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

#ifndef SPACEVIEW_H
#define SPACEVIEW_H

#include <QObject>
#include <QImage>
#include <QHash>
#include <QGraphicsScene>

#include "spacemodel.h"
#include "spacewidget.h"

class SpaceView: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QSize viewPortSize READ viewPortSize WRITE setViewPortSize RESET resetViewPortSize)
    Q_PROPERTY(bool editMode READ editMode WRITE setEditMode RESET resetEditMode)

    public:
        explicit SpaceView(QObject *parent = 0);
        ~SpaceView();
        Q_INVOKABLE QImage render();
        Q_INVOKABLE void setSpace(QString spaceId, const QImage &frame);
        Q_INVOKABLE void removeSpace(QString spaceId);
        Q_INVOKABLE void setSnapping(bool snapping, int nParts, qreal snappingPT, qreal snappingRT);
        Q_INVOKABLE QPoint mapToMainSpace(const QPoint &pos, const QSize &viewportSize);

        Q_INVOKABLE void setControlButtons(QPushButton *toggleMaximizedButton = NULL,
                                           QPushButton *scaleAndRotateButton = NULL);

        QSize viewPortSize();
        bool editMode();

    private:
        bool move;
        bool scaleAndRotate;
        QSize m_viewPortSize;
        SpaceModel spaceModel;
        QGraphicsScene mainSpace;
        QHash<QString, SpaceWidget *> spacesWidgets;
        QHash<QString, QGraphicsProxyWidget *> proxySpacesWidgets;
        QPushButton *m_toggleMaximizedButton;
        QPushButton *m_scaleAndRotateButton;
        bool m_editMode;

        QWidget *sendMouseEvent(QEvent::Type type,
                                const QPoint &position,
                                Qt::MouseButton button,
                                Qt::MouseButtons buttons,
                                Qt::KeyboardModifiers modifiers);

    public slots:
        void setViewPortSize(QSize size);
        void setEditMode(bool value);
        void resetViewPortSize();
        void resetEditMode();
        void toggleEditMode();
        void selectSpace(QString spaceId);
        void mouseDoubleClickEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
        void mousePressEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);
};

#endif // SPACEVIEW_H
