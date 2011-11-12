#include <QFileDialog>
#include <QtDebug>

#include "include/config.h"

Config::Config(QWidget *parent): QDialog(parent)
{
    this->setupUi(this);

    this->m_imageDevices = NULL;
}

void Config::changeEvent(QEvent *e)
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

QStringList *Config::imageDevices()
{
    return this->m_imageDevices;
}

void Config::setImageDevices(QStringList *imageDevices)
{
    this->m_imageDevices = imageDevices;

    if (!this->m_imageDevices || this->m_imageDevices->isEmpty())
        return;

    this->lswImages->addItems(*this->m_imageDevices);
}

void Config::resetImageDevices()
{
    this->m_imageDevices = NULL;
}

void Config::on_btnAdd_clicked()
{
    if (!this->m_imageDevices)
        return;

    QStringList images = QFileDialog::getOpenFileNames(this, "Add images", "", "Images (*.png *.jpg *.bmp *.gif)");

    if (images.isEmpty())
        return;

    this->m_imageDevices->append(images);
    this->lswImages->addItems(images);

    for (int i = 0; i < this->lswImages->count(); i++)
    {
        this->lswImages->item(i)->setIcon(QIcon(this->m_imageDevices->at(i)));
        this->lswImages->item(i)->setText("");
    }
}

void Config::on_btnRemove_clicked()
{
    if (!this->m_imageDevices)
        return;

    foreach (QListWidgetItem *image, this->lswImages->selectedItems())
    {
        int row = this->lswImages->row(image);

        delete this->lswImages->takeItem(row);
        this->m_imageDevices->removeAt(row);
    }
}
