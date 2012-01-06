#include <QtDebug>

#include "../../include/space/spacecontrols.h"

SpaceControls::SpaceControls(QWidget *parent): QWidget(parent)
{
    this->setupUi(this);
}

void SpaceControls::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);

    switch (e->type())
    {
        case QEvent::LanguageChange:
            this->retranslateUi(this);
        break;

        default:
        break;
    }
}
