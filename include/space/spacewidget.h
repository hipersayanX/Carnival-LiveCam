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

        Q_INVOKABLE void setControlButtons(QPushButton *toggleMaximizedButton = NULL,
                                           QPushButton *scaleAndRotateButton = NULL);

        bool editMode();

    private:
        bool m_editMode;

    public slots:
        void setEditMode(bool value);
        void resetEditMode();
};

#endif // SPACEWIDGET_H
