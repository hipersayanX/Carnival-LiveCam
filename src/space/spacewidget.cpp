#include "../../include/space/spacewidget.h"

SpaceWidget::SpaceWidget(QWidget *parent): QWidget(parent)
{
}

SpaceWidget::SpaceWidget(const QImage &frame)
{
    this->setGeometry(0, 0, frame.width(), frame.height());

    this->spacePixmap.setGeometry(0, 0, frame.width(), frame.height());
    this->spacePixmap.setScaledContents(true);
    this->spacePixmap.setPixmap(QPixmap::fromImage(frame));
    this->spacePixmap.setParent(this);

    this->spaceControls.setGeometry(0, 0, frame.width(), frame.height());
    this->spaceControls.setParent(this);
}
