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

#ifndef SPACE_H
#define SPACE_H

#include <QtWidgets>

#include "ui_space.h"

class Space: public QWidget, public Ui::Space
{
    Q_OBJECT

    Q_PROPERTY(bool editMode READ editMode WRITE setEditMode RESET resetEditMode)
    Q_PROPERTY(bool snapping READ snapping WRITE setSnapping RESET resetSnapping)
    Q_PROPERTY(int nParts READ nParts WRITE setNParts RESET resetNParts)
    Q_PROPERTY(float snappingPT READ snappingPT WRITE setSnappingPT RESET resetSnappingPT)
    Q_PROPERTY(float snappingRT READ snappingRT WRITE setSnappingRT RESET resetSnappingRT)
    Q_PROPERTY(QString buttonText READ buttonText WRITE setButtonText RESET resetButtonText)
    Q_PROPERTY(QString buttonIcon READ buttonIcon WRITE setButtonIcon RESET resetButtonIcon)
    Q_PROPERTY(QString buttonStyleSheet READ buttonStyleSheet WRITE setButtonStyleSheet RESET resetButtonStyleSheet)

    public:
        explicit Space(QWidget *parent = 0);

        bool editMode();
        bool snapping();
        int nParts();
        float snappingPT();
        float snappingRT();
        QString buttonText();
        QString buttonIcon();
        QString buttonStyleSheet();

        Q_INVOKABLE void setSpaceId(QString spaceId);
        Q_INVOKABLE void setProxy(QGraphicsProxyWidget *proxy);
        Q_INVOKABLE void setFrame(const QImage &frame);
        Q_INVOKABLE void rescaleButton(float factor);

    private:
        bool m_editMode;
        bool m_snapping;
        float m_snappingPT;
        float m_snappingRT;
        QGraphicsProxyWidget *m_proxy;
        QString m_buttonIconFileName;
        bool m_move;
        bool m_rotateScale;
        bool m_fstFrame;
        QList<float> m_snapAngles;
        QPointF m_pos0;
        QPoint m_mousePos0;
        QPoint m_widgetGlobalCenter;
        QPointF m_widgetSceneCenter;
        QList<float> m_hLines0;
        QList<float> m_vLines0;

        void snapLines(QList<float> *hLines, QList<float> *vLines);
        float calculateAngle(QPoint point);
        void bringToFront();
        bool eventFilter(QObject *watched, QEvent *event);
        bool resendMouseEvent(QMouseEvent *event);

    protected:
        void mouseDoubleClickEvent(QMouseEvent *event);
        void mousePressEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);

    signals:
        void spaceMoved(int from, int to);

    public slots:
        void setEditMode(bool editable);
        void setSnapping(bool enable);
        void setNParts(int nParts);
        void setSnappingPT(float snappingPT);
        void setSnappingRT(float snappingRT);
        void setButtonText(QString text);
        void setButtonIcon(QString icon);
        void setButtonStyleSheet(QString styleSheet);
        void resetEditMode();
        void resetSnapping();
        void resetNParts();
        void resetSnappingPT();
        void resetSnappingRT();
        void resetButtonText();
        void resetButtonIcon();
        void resetButtonStyleSheet();
};

#endif // SPACE_H
