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
#include <QProcess>
#include <QtDebug>

#include "include/config.h"

/*!
  \class Config

  \brief Video driver configuration dialog.
 */

/*!
  \fn Config::Config(QWidget *parent)

  \param parent Parent widget.
 */
Config::Config(QWidget *parent): QDialog(parent)
{
    this->setupUi(this);

    this->m_videoDevices = NULL;
}

/*!
  \internal

  \fn Config::~Config()
 */
Config::~Config()
{
    if (!this->m_videoDevices)
        return;

    QDir dir;

    foreach (QString video, *this->m_videoDevices)
        dir.remove(this->makeThumbnail(video));
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
  \property Config::videoDevices

  \brief A pointer to the devices list.

  This property is used for add an remove new video files.
 */
QStringList *Config::videoDevices()
{
    return this->m_videoDevices;
}

/*!
  \fn void Config::setVideoDevices(QStringList *videoDevices)

  \param videoDevices A pointer to the devices list.

  \brief This slot setup the video devices list.
 */
void Config::setVideoDevices(QStringList *videoDevices)
{
    this->m_videoDevices = videoDevices;

    if (!this->m_videoDevices || this->m_videoDevices->isEmpty())
        return;

    this->setFiles(*this->m_videoDevices);
}

/*!
  \fn void Config::resetVideoDevices()

  \brief Set Config::videoDevices to \b NULL.
 */
void Config::resetVideoDevices()
{
    this->m_videoDevices = NULL;
}

/*!
  \internal

  \fn void Config::on_btnAdd_clicked()

  \brief This slot is called when the user does click on the add video button.
 */
void Config::on_btnAdd_clicked()
{
    if (!this->m_videoDevices)
        return;

    QStringList videos = QFileDialog::getOpenFileNames(this, "Add videos", "");//, "Videos (*.png *.jpg *.bmp *.gif)");

    if (videos.isEmpty())
        return;

    this->m_videoDevices->append(videos);
    this->setFiles(videos);
}

/*!
  \internal

  \fn void Config::on_btnRemove_clicked()

  \brief This slot is called when the user does click on the remove video button.
 */
void Config::on_btnRemove_clicked()
{
    if (!this->m_videoDevices)
        return;

    QDir dir;

    foreach (QListWidgetItem *video, this->lswVideos->selectedItems())
    {
        int row = this->lswVideos->row(video);

        dir.remove(this->makeThumbnail(this->m_videoDevices->at(row)));
        delete this->lswVideos->takeItem(row);
        this->m_videoDevices->removeAt(row);
    }
}

/*!
  \internal

  \fn void Config::setFiles(QStringList files)

  \param files List of video files.

  \brief Updates the video list.
 */
void Config::setFiles(QStringList files)
{
    this->lswVideos->addItems(files);

    for (qint32 i = 0; i < this->lswVideos->count(); i++)
    {
        QString thumbnail = this->makeThumbnail(this->m_videoDevices->at(i));
        QStringList arguments;

        arguments << "-s" << "128" << "-i" << this->m_videoDevices->at(i) << "-o" << thumbnail;

        QProcess::execute("ffmpegthumbnailer", arguments);

        this->lswVideos->item(i)->setIcon(QIcon(thumbnail));
        this->lswVideos->item(i)->setText("");
    }
}

/*!
  \internal

  \fn QString Config::makeThumbnail(QString fileName)

  \param fileName List of video files.

  \return Returns the thumbnail file name.

  \brief Converts a video file name in a thumbnail image filename.
 */
QString Config::makeThumbnail(QString fileName)
{
    QFileInfo fileInfo(fileName);

    return QDir::tempPath() + QDir::separator() + fileInfo.baseName() + "-thumb.png";
}
