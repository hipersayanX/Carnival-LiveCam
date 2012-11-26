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

#ifndef SPACESELEMENT_H
#define SPACESELEMENT_H

#include <QtWidgets>

#include "element.h"
#include "spaceswidget.h"

class SpacesElement: public Element
{
    Q_OBJECT

    Q_PROPERTY(QStringList spaces READ spaces WRITE setSpaces RESET resetSpaces)
    Q_PROPERTY(bool editMode READ editMode WRITE setEditMode RESET resetEditMode)
    Q_PROPERTY(bool snapping READ snapping WRITE setSnapping RESET resetSnapping)
    Q_PROPERTY(int nParts READ nParts WRITE setNParts RESET resetNParts)
    Q_PROPERTY(float snappingPT READ snappingPT WRITE setSnappingPT RESET resetSnappingPT)
    Q_PROPERTY(float snappingRT READ snappingRT WRITE setSnappingRT RESET resetSnappingRT)

    Q_PROPERTY(QString rotateButtonStyleSheet
               READ rotateButtonStyleSheet
               WRITE setRotateButtonStyleSheet
               RESET resetRotateButtonStyleSheet)

    Q_PROPERTY(QString rotateButtonText
               READ rotateButtonText
               WRITE setRotateButtonText
               RESET resetRotateButtonText)

    public:
        explicit SpacesElement();
        ~SpacesElement();

        QStringList spaces();
        bool editMode();
        bool snapping();
        int nParts();
        float snappingPT();
        float snappingRT();
        QString rotateButtonStyleSheet();
        QString rotateButtonText();

        Q_INVOKABLE bool start();
        Q_INVOKABLE bool stop();

    private:
        QStringList m_spaces;
        bool m_editMode;
        bool m_snapping;
        qint32 m_nParts;
        qreal m_snappingPT;
        qreal m_snappingRT;
        QString m_rotateButtonStyleSheet;
        QString m_rotateButtonText;

        bool m_move;
        bool m_scaleAndRotate;
        SpacesWidget m_spaceWidget;
        QList<Element *> m_srcs;
        QList<Element *> m_sinks;
        QByteArray m_bFrame;

        QImage byteArrayToImage(QByteArray *ba);
        void imageToByteArray(QImage *image, QByteArray *ba);

        void updateButtonsSize();
        void sendHoverEvent(QWidget *receiver, const QPoint &position);

        QWidget *sendMouseEvent(QEvent::Type type,
                                const QPointF &position,
                                Qt::MouseButton button,
                                Qt::MouseButtons buttons,
                                Qt::KeyboardModifiers modifiers);

        QPointF mapViewPortToModel(const QPoint &pos, const QSize &viewportSize);
        QStringList activeSpaces();

    private slots:
        void onSpaceMoved(qint32 from, qint32 to);

    public slots:
        // Input Channels
        void iStream(QByteArray *data);
        void iEvent(QEvent *event);
        void setPipeline(Pipeline *pipeline);
        void setPeers(QList<Element *> srcs, QList<Element *> sinks);

        void setSpaces(QStringList spaces);
        void setEditMode(bool value);
        void setSnapping(bool snapping);
        void setNParts(int nParts);
        void setSnappingPT(float snappingPT);
        void setSnappingRT(float snappingRT);
        void setRotateButtonStyleSheet(QString rotateButtonStyleSheet);
        void setRotateButtonText(QString rotateButtonText);
        void resetSpaces();
        void resetEditMode();
        void resetSnapping();
        void resetNParts();
        void resetSnappingPT();
        void resetSnappingRT();
        void resetRotateButtonStyleSheet();
        void resetRotateButtonText();

        void removeSpace(QString spaceId);
        void updateSpaces(const QList<QVariant> &devices);
        void moveSpace(qint32 from, qint32 to);
        void selectSpace(QString spaceId);
};

#endif // SPACESELEMENT_H
