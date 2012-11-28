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

    Q_PROPERTY(bool editMode READ editMode WRITE setEditMode RESET resetEditMode)
    Q_PROPERTY(bool snapping READ snapping WRITE setSnapping RESET resetSnapping)
    Q_PROPERTY(int nParts READ nParts WRITE setNParts RESET resetNParts)
    Q_PROPERTY(float snappingPT READ snappingPT WRITE setSnappingPT RESET resetSnappingPT)
    Q_PROPERTY(float snappingRT READ snappingRT WRITE setSnappingRT RESET resetSnappingRT)
    Q_PROPERTY(QString buttonText READ buttonText WRITE setButtonText RESET resetButtonText)
    Q_PROPERTY(QString buttonIcon READ buttonIcon WRITE setButtonIcon RESET resetButtonIcon)
    Q_PROPERTY(QString buttonStyleSheet READ buttonStyleSheet WRITE setButtonStyleSheet RESET resetButtonStyleSheet)

    public:
        explicit SpacesElement();
        ~SpacesElement();

        bool editMode();
        bool snapping();
        int nParts();
        float snappingPT();
        float snappingRT();
        QString buttonText();
        QString buttonIcon();
        QString buttonStyleSheet();

        Q_INVOKABLE bool start();
        Q_INVOKABLE bool stop();

    private:
        bool m_move;
        bool m_scaleAndRotate;
        SpacesWidget m_spacesWidget;
        QList<Element *> m_srcs;
        QList<Element *> m_sinks;
        QByteArray m_bFrame;

    signals:
        void spaceMoved(int from, int to);

    public slots:
        // Input Channels
        void iStream(const void *data, int datalen, QString dataType);
        void setPipeline(Pipeline *pipeline);
        void setPeers(QList<Element *> srcs, QList<Element *> sinks);

        void setEditMode(bool editMode);
        void setSnapping(bool snapping);
        void setNParts(int nParts);
        void setSnappingPT(float snappingPT);
        void setSnappingRT(float snappingRT);
        void setButtonText(QString buttonText);
        void setButtonIcon(QString buttonIcon);
        void setButtonStyleSheet(QString buttonStyleSheet);
        void resetEditMode();
        void resetSnapping();
        void resetNParts();
        void resetSnappingPT();
        void resetSnappingRT();
        void resetButtonText();
        void resetButtonIcon();
        void resetButtonStyleSheet();
};

#endif // SPACESELEMENT_H
