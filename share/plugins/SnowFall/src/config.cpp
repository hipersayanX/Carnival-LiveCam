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

Snow *Config::snow()
{
    return this->m_snow;
}

void Config::setSnow(Snow *snow)
{
    this->m_snow = snow;
}

void Config::resetSnow()
{
    this->m_snow = NULL;
}

void Config::on_sldNFlakes_sliderMoved(int value)
{
    if (this->m_snow)
    {
        this->m_snow->setNFlakes(value);
        this->m_snow->reset();
    }
}

void Config::on_sldAcceleration_sliderMoved(int value)
{
    this->spbAcceleration->setValue(value / 10.0);

    if (this->m_snow)
    {
        this->m_snow->setAcceleration(value / 10.0);
        this->m_snow->reset();
    }
}

void Config::on_sldDirection_sliderMoved(int value)
{
    if (this->m_snow)
    {
        this->m_snow->setDirection(value);
        this->m_snow->reset();
    }
}

void Config::on_sldRandFactor_sliderMoved(int value)
{
    this->spbRandFactor->setValue(value / 10.0);

    if (this->m_snow)
    {
        this->m_snow->setRandFactor(value / 10.0);
        this->m_snow->reset();
    }
}

void Config::on_sldBorder_sliderMoved(int value)
{
    if (this->m_snow)
    {
        this->m_snow->setBorder(value);
        this->m_snow->reset();
    }
}

void Config::on_sldMinZ_sliderMoved(int value)
{
    this->spbMinZ->setValue(value / 10.0);

    if (this->m_snow)
    {
        this->m_snow->setMinZ(value / 10.0);
        this->m_snow->reset();
    }
}

void Config::on_sldMaxZ_sliderMoved(int value)
{
    this->spbMaxZ->setValue(value / 10.0);

    if (this->m_snow)
    {
        this->m_snow->setMaxZ(value / 10.0);
        this->m_snow->reset();
    }
}

void Config::on_sldMinScale_sliderMoved(int value)
{
    this->spbMinScale->setValue(value / 10.0);

    if (this->m_snow)
    {
        this->m_snow->setMinScale(value / 10.0);
        this->m_snow->reset();
    }
}

void Config::on_sldMaxScale_sliderMoved(int value)
{
    this->spbMaxScale->setValue(value / 10.0);

    if (this->m_snow)
    {
        this->m_snow->setMaxScale(value / 10.0);
        this->m_snow->reset();
    }
}

void Config::on_spbNFlakes_valueChanged(int value)
{
    if (this->m_snow)
    {
        this->m_snow->setNFlakes(value);
        this->m_snow->reset();
    }
}

void Config::on_spbAcceleration_valueChanged(double value)
{
    this->sldAcceleration->setValue(10 * value);

    if (this->m_snow)
    {
        this->m_snow->setAcceleration(value);
        this->m_snow->reset();
    }
}

void Config::on_spbDirection_valueChanged(int value)
{
    if (this->m_snow)
    {
        this->m_snow->setDirection(value);
        this->m_snow->reset();
    }
}

void Config::on_spbRandFactor_valueChanged(double value)
{
    this->sldRandFactor->setValue(10 * value);

    if (this->m_snow)
    {
        this->m_snow->setRandFactor(value);
        this->m_snow->reset();
    }
}

void Config::on_spbBorder_valueChanged(int value)
{
    if (this->m_snow)
    {
        this->m_snow->setBorder(value);
        this->m_snow->reset();
    }
}

void Config::on_spbMinZ_valueChanged(double value)
{
    this->sldMinZ->setValue(10 * value);

    if (this->m_snow)
    {
        this->m_snow->setMinZ(value);
        this->m_snow->reset();
    }
}

void Config::on_spbMaxZ_valueChanged(double value)
{
    this->sldMaxZ->setValue(10 * value);

    if (this->m_snow)
    {
        this->m_snow->setMaxZ(value);
        this->m_snow->reset();
    }
}

void Config::on_spbMinScale_valueChanged(double value)
{
    this->sldMinScale->setValue(value);

    if (this->m_snow)
    {
        this->m_snow->setMinScale(value);
        this->m_snow->reset();
    }
}

void Config::on_spbMaxScale_valueChanged(double value)
{
    this->sldMaxScale->setValue(10 * value);

    if (this->m_snow)
    {
        this->m_snow->setMaxScale(value);
        this->m_snow->reset();
    }
}
