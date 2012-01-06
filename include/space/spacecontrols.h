#ifndef SPACECONTROLS_H
#define SPACECONTROLS_H

#include <QWidget>

#include "ui_spacecontrols.h"

class SpaceControls: public QWidget, public Ui::SpaceControls
{
    Q_OBJECT

    public:
        explicit SpaceControls(QWidget *parent = 0);

    protected:
        void changeEvent(QEvent *e);
};

#endif // SPACECONTROLS_H
