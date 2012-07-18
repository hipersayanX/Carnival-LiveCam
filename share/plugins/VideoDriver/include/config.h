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

#ifndef CONFIG_H
#define CONFIG_H

#include <QDialog>

#include "ui_config.h"

class Config: public QDialog, private Ui::Config
{
    Q_OBJECT
    Q_PROPERTY(QStringList *videoDevices READ videoDevices WRITE setVideoDevices RESET resetVideoDevices)

    public:
        explicit Config(QWidget *parent = 0);
        ~Config();
        QStringList *videoDevices();

    private:
        QStringList *m_videoDevices;

        void setFiles(QStringList files);
        QString makeThumbnail(QString fileName);

    public slots:
        void setVideoDevices(QStringList *videoDevices);
        void resetVideoDevices();

    protected:
        void changeEvent(QEvent *e);

    private slots:
        void on_btnAdd_clicked();
        void on_btnRemove_clicked();
};

#endif // CONFIG_H
