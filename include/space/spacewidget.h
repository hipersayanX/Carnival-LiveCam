#ifndef SPACEWIDGET_H
#define SPACEWIDGET_H

#include <QWidget>
#include <QLabel>

#include "spacecontrols.h"

class SpaceWidget: public QWidget
{
    Q_OBJECT

    public:
        SpaceControls spaceControls;
        QLabel spacePixmap;

        explicit SpaceWidget(QWidget *parent = 0);
        SpaceWidget(const QImage &frame);
};

#endif // SPACEWIDGET_H
