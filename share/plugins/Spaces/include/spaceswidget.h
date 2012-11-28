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

#ifndef SPACESWIDGET_H
#define SPACESWIDGET_H

#include <QtWidgets>

class SpacesWidget: public QGraphicsView
{
    Q_OBJECT

    Q_PROPERTY(QStringList spaces READ spaces WRITE setSpaces RESET resetSpaces)
    Q_PROPERTY(bool editMode READ editMode WRITE setEditMode RESET resetEditMode)
    Q_PROPERTY(bool snapping READ snapping WRITE setSnapping RESET resetSnapping)
    Q_PROPERTY(int nParts READ nParts WRITE setNParts RESET resetNParts)
    Q_PROPERTY(float snappingPT READ snappingPT WRITE setSnappingPT RESET resetSnappingPT)
    Q_PROPERTY(float snappingRT READ snappingRT WRITE setSnappingRT RESET resetSnappingRT)
    Q_PROPERTY(QString buttonText READ buttonText WRITE setButtonText RESET resetButtonText)
    Q_PROPERTY(QString buttonIcon READ buttonIcon WRITE setButtonIcon RESET resetButtonIcon)
    Q_PROPERTY(QString buttonStyleSheet READ buttonStyleSheet WRITE setButtonStyleSheet RESET resetButtonStyleSheet)

    public:
        explicit SpacesWidget(QWidget *parent = 0);

        QStringList spaces();
        bool editMode();
        bool snapping();
        int nParts();
        float snappingPT();
        float snappingRT();
        QString buttonText();
        QString buttonIcon();
        QString buttonStyleSheet();

        Q_INVOKABLE void setFrame(QString spaceId, const QImage &frame);

    private:
        bool m_editMode;
        bool m_snapping;
        int m_nParts;
        int m_snappingPT;
        int m_snappingRT;
        QString m_buttonText;
        QString m_buttonIcon;
        QString m_buttonStyleSheet;
        QMap<QString, QGraphicsProxyWidget *> m_proxySpaces;
        QGraphicsScene m_graphicsScene;

    protected:
        void resizeEvent(QResizeEvent *event);

    signals:
        void spaceMoved(int from, int to);

    public slots:
        void addSpace(QString spaceId);
        void removeSpace(QString spaceId);
        void setSpaces(QStringList spaces);
        void setEditMode(bool editable);
        void setSnapping(bool enable);
        void setNParts(int nParts);
        void setSnappingPT(float snappingPT);
        void setSnappingRT(float snappingRT);
        void setButtonText(QString text);
        void setButtonIcon(QString icon);
        void setButtonStyleSheet(QString styleSheet);
        void resetSpaces();
        void resetEditMode();
        void resetSnapping();
        void resetNParts();
        void resetSnappingPT();
        void resetSnappingRT();
        void resetButtonText();
        void resetButtonIcon();
        void resetButtonStyleSheet();

    private slots:
        void on_changed(const QList<QRectF> &region);
};

#endif // SPACESWIDGET_H
