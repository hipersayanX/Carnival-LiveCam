#include "include/config.h"
#include <QtDebug>

Config::Config(QWidget *parent): QDialog(parent)
{
    this->setupUi(this);
    this->m_snow = NULL;
}

void Config::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);

    switch (e->type())
    {
        case QEvent::LanguageChange:
            this->retranslateUi(this);
        break;

        default:
        break;
    }
}

void Config::showEvent(QShowEvent *e)
{
    QDialog::showEvent(e);
    this->cbxSpaceId->clear();

    foreach (QString spaceId, this->m_snow->keys())
        this->cbxSpaceId->addItem(spaceId, spaceId);

    this->updateControls();
}

void Config::updateControls()
{
    QString spaceId = this->cbxSpaceId->itemData(this->cbxSpaceId->currentIndex()).toString();

    this->sldNFlakes->setValue((*this->m_snow)[spaceId].nFlakes());
    this->sldAcceleration->setValue((*this->m_snow)[spaceId].acceleration());
    this->sldDirection->setValue((*this->m_snow)[spaceId].direction());
    this->sldRandFactor->setValue((*this->m_snow)[spaceId].randFactor());
    this->sldBorder->setValue((*this->m_snow)[spaceId].border());
    this->sldMinZ->setValue((*this->m_snow)[spaceId].minZ());
    this->sldMaxZ->setValue((*this->m_snow)[spaceId].maxZ());
    this->sldMinScale->setValue((*this->m_snow)[spaceId].minScale());
    this->sldMaxScale->setValue((*this->m_snow)[spaceId].maxScale());
}

QHash<QString, Snow> *Config::snow()
{
    return this->m_snow;
}

void Config::setSnow(QHash<QString, Snow> *snow)
{
    this->m_snow = snow;
}

void Config::resetSnow()
{
    this->m_snow = NULL;
}

void Config::on_cbxSpaceId_currentIndexChanged(int index)
{
    Q_UNUSED(index)

    this->updateControls();
}

void Config::on_sldNFlakes_sliderMoved(int value)
{
    if (this->m_snow)
    {
        QString spaceId = this->cbxSpaceId->itemData(this->cbxSpaceId->currentIndex()).toString();

        (*this->m_snow)[spaceId].setNFlakes(value);
        (*this->m_snow)[spaceId].reset();
    }
}

void Config::on_sldAcceleration_sliderMoved(int value)
{
    this->spbAcceleration->setValue(value / 10.0);

    if (this->m_snow)
    {
        QString spaceId = this->cbxSpaceId->itemData(this->cbxSpaceId->currentIndex()).toString();

        (*this->m_snow)[spaceId].setAcceleration(value / 10.0);
        (*this->m_snow)[spaceId].reset();
    }
}

void Config::on_sldDirection_sliderMoved(int value)
{
    if (this->m_snow)
    {
        QString spaceId = this->cbxSpaceId->itemData(this->cbxSpaceId->currentIndex()).toString();

        (*this->m_snow)[spaceId].setDirection(value);
        (*this->m_snow)[spaceId].reset();
    }
}

void Config::on_sldRandFactor_sliderMoved(int value)
{
    this->spbRandFactor->setValue(value / 10.0);

    if (this->m_snow)
    {
        QString spaceId = this->cbxSpaceId->itemData(this->cbxSpaceId->currentIndex()).toString();

        (*this->m_snow)[spaceId].setRandFactor(value / 10.0);
        (*this->m_snow)[spaceId].reset();
    }
}

void Config::on_sldBorder_sliderMoved(int value)
{
    if (this->m_snow)
    {
        QString spaceId = this->cbxSpaceId->itemData(this->cbxSpaceId->currentIndex()).toString();

        (*this->m_snow)[spaceId].setBorder(value);
        (*this->m_snow)[spaceId].reset();
    }
}

void Config::on_sldMinZ_sliderMoved(int value)
{
    this->spbMinZ->setValue(value / 10.0);

    if (this->m_snow)
    {
        QString spaceId = this->cbxSpaceId->itemData(this->cbxSpaceId->currentIndex()).toString();

        (*this->m_snow)[spaceId].setMinZ(value / 10.0);
        (*this->m_snow)[spaceId].reset();
    }
}

void Config::on_sldMaxZ_sliderMoved(int value)
{
    this->spbMaxZ->setValue(value / 10.0);

    if (this->m_snow)
    {
        QString spaceId = this->cbxSpaceId->itemData(this->cbxSpaceId->currentIndex()).toString();

        (*this->m_snow)[spaceId].setMaxZ(value / 10.0);
        (*this->m_snow)[spaceId].reset();
    }
}

void Config::on_sldMinScale_sliderMoved(int value)
{
    this->spbMinScale->setValue(value / 10.0);

    if (this->m_snow)
    {
        QString spaceId = this->cbxSpaceId->itemData(this->cbxSpaceId->currentIndex()).toString();

        (*this->m_snow)[spaceId].setMinScale(value / 10.0);
        (*this->m_snow)[spaceId].reset();
    }
}

void Config::on_sldMaxScale_sliderMoved(int value)
{
    this->spbMaxScale->setValue(value / 10.0);

    if (this->m_snow)
    {
        QString spaceId = this->cbxSpaceId->itemData(this->cbxSpaceId->currentIndex()).toString();

        (*this->m_snow)[spaceId].setMaxScale(value / 10.0);
        (*this->m_snow)[spaceId].reset();
    }
}

void Config::on_spbNFlakes_valueChanged(int value)
{
    if (this->m_snow)
    {
        QString spaceId = this->cbxSpaceId->itemData(this->cbxSpaceId->currentIndex()).toString();

        (*this->m_snow)[spaceId].setNFlakes(value);
        (*this->m_snow)[spaceId].reset();
    }
}

void Config::on_spbAcceleration_valueChanged(double value)
{
    this->sldAcceleration->setValue(10 * value);

    if (this->m_snow)
    {
        QString spaceId = this->cbxSpaceId->itemData(this->cbxSpaceId->currentIndex()).toString();

        (*this->m_snow)[spaceId].setAcceleration(value);
        (*this->m_snow)[spaceId].reset();
    }
}

void Config::on_spbDirection_valueChanged(int value)
{
    if (this->m_snow)
    {
        QString spaceId = this->cbxSpaceId->itemData(this->cbxSpaceId->currentIndex()).toString();

        (*this->m_snow)[spaceId].setDirection(value);
        (*this->m_snow)[spaceId].reset();
    }
}

void Config::on_spbRandFactor_valueChanged(double value)
{
    this->sldRandFactor->setValue(10 * value);

    if (this->m_snow)
    {
        QString spaceId = this->cbxSpaceId->itemData(this->cbxSpaceId->currentIndex()).toString();

        (*this->m_snow)[spaceId].setRandFactor(value);
        (*this->m_snow)[spaceId].reset();
    }
}

void Config::on_spbBorder_valueChanged(int value)
{
    if (this->m_snow)
    {
        QString spaceId = this->cbxSpaceId->itemData(this->cbxSpaceId->currentIndex()).toString();

        (*this->m_snow)[spaceId].setBorder(value);
        (*this->m_snow)[spaceId].reset();
    }
}

void Config::on_spbMinZ_valueChanged(double value)
{
    this->sldMinZ->setValue(10 * value);

    if (this->m_snow)
    {
        QString spaceId = this->cbxSpaceId->itemData(this->cbxSpaceId->currentIndex()).toString();

        (*this->m_snow)[spaceId].setMinZ(value);
        (*this->m_snow)[spaceId].reset();
    }
}

void Config::on_spbMaxZ_valueChanged(double value)
{
    this->sldMaxZ->setValue(10 * value);

    if (this->m_snow)
    {
        QString spaceId = this->cbxSpaceId->itemData(this->cbxSpaceId->currentIndex()).toString();

        (*this->m_snow)[spaceId].setMaxZ(value);
        (*this->m_snow)[spaceId].reset();
    }
}

void Config::on_spbMinScale_valueChanged(double value)
{
    this->sldMinScale->setValue(value);

    if (this->m_snow)
    {
        QString spaceId = this->cbxSpaceId->itemData(this->cbxSpaceId->currentIndex()).toString();

        (*this->m_snow)[spaceId].setMinScale(value);
        (*this->m_snow)[spaceId].reset();
    }
}

void Config::on_spbMaxScale_valueChanged(double value)
{
    this->sldMaxScale->setValue(10 * value);

    if (this->m_snow)
    {
        QString spaceId = this->cbxSpaceId->itemData(this->cbxSpaceId->currentIndex()).toString();

        (*this->m_snow)[spaceId].setMaxScale(value);
        (*this->m_snow)[spaceId].reset();
    }
}
