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

#ifndef SPACEWIDGET_H
#define SPACEWIDGET_H

#include <QWidget>
#include <QLabel>

#include "spacecontrols.h"

class SpaceWidget: public QWidget
{
    Q_OBJECT

    Q_PROPERTY(bool editMode READ editMode WRITE setEditMode RESET resetEditMode)

    public:
        SpaceControls spaceControls;
        QLabel spacePixmap;

        explicit SpaceWidget(QWidget *parent = 0);
        SpaceWidget(const QImage &frame);
        Q_INVOKABLE void setFrame(const QImage &frame);

        Q_INVOKABLE void setControlButtons(QPushButton *toggleMaximizedButton = NULL,
                                           QPushButton *scaleAndRotateButton = NULL);

        bool editMode();

    private:
        bool m_editMode;

    public slots:
        void setEditMode(bool value);
        void resetEditMode();
        void toggleEditMode();
};

#endif // SPACEWIDGET_H
