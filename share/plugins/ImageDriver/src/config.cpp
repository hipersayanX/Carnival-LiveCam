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

#include <QFileDialog>
#include <QtDebug>

#include "include/config.h"

/*!
  \class Config

  \brief Image driver configuration dialog.
 */

/*!
  \fn Config::Config(QWidget *parent)

  \param parent Parent widget.
 */
Config::Config(QWidget *parent): QDialog(parent)
{
    this->setupUi(this);

    this->m_imageDevices = NULL;
}

/*!
  \internal

  \fn void Config::changeEvent(QEvent *e)

  \param e The event.

  \brief This function is called when the user changes the sistem language.

  Automatically changes the UI language.
 */
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

/*!
  \property Config::imageDevices

  \brief A pointer to the devices list.

  This property is used for add an remove new images files.
 */
QStringList *Config::imageDevices()
{
    return this->m_imageDevices;
}

/*!
  \fn void Config::setImageDevices(QStringList *imageDevices)

  \param imageDevices A pointer to the devices list.

  \brief This slot setup the images devices list.
 */
void Config::setImageDevices(QStringList *imageDevices)
{
    this->m_imageDevices = imageDevices;

    if (!this->m_imageDevices || this->m_imageDevices->isEmpty())
        return;

    this->setFiles(*this->m_imageDevices);
}

/*!
  \fn void Config::resetImageDevices()

  \brief Set Config::imageDevices to \b NULL.
 */
void Config::resetImageDevices()
{
    this->m_imageDevices = NULL;
}

/*!
  \internal

  \fn void Config::on_btnAdd_clicked()

  \brief This slot is called when the user does click on the add images button.
 */
void Config::on_btnAdd_clicked()
{
    if (!this->m_imageDevices)
        return;

    QStringList images = QFileDialog::getOpenFileNames(this, "Add images", "", "Images (*.png *.jpg *.bmp *.gif)");

    if (images.isEmpty())
        return;

    this->m_imageDevices->append(images);
    this->setFiles(images);
}

/*!
  \internal

  \fn void Config::on_btnRemove_clicked()

  \brief This slot is called when the user does click on the remove images button.
 */
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

/*!
  \internal

  \fn void Config::setFiles(QStringList files)

  \param files List of image files.

  \brief Updates the image list.
 */
void Config::setFiles(QStringList files)
{
    this->lswImages->addItems(files);

    for (qint32 i = 0; i < this->lswImages->count(); i++)
    {
        this->lswImages->item(i)->setIcon(QIcon(this->m_imageDevices->at(i)));
        this->lswImages->item(i)->setText("");
    }
}