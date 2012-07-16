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

#include "snow.h"
#include "ui_config.h"

class Config: public QDialog, public Ui::Config
{
    Q_OBJECT

    public:
        explicit Config(QWidget *parent = 0);
        Q_INVOKABLE QHash<QString, Snow> *snow();

    private:
        QHash<QString, Snow> *m_snow;

        void updateControls();

    public slots:
        void setSnow(QHash<QString, Snow> *snow);
        void resetSnow();

    protected:
        void changeEvent(QEvent *e);
        void showEvent(QShowEvent *e);

    private slots:
        void on_cbxSpaceId_currentIndexChanged(int index);
        void on_sldNFlakes_sliderMoved(int value);
        void on_sldAcceleration_sliderMoved(int value);
        void on_sldDirection_sliderMoved(int value);
        void on_sldRandFactor_sliderMoved(int value);
        void on_sldBorder_sliderMoved(int value);
        void on_sldMinZ_sliderMoved(int value);
        void on_sldMaxZ_sliderMoved(int value);
        void on_sldMinScale_sliderMoved(int value);
        void on_sldMaxScale_sliderMoved(int value);
        void on_spbNFlakes_valueChanged(int value);
        void on_spbAcceleration_valueChanged(double value);
        void on_spbDirection_valueChanged(int value);
        void on_spbRandFactor_valueChanged(double value);
        void on_spbBorder_valueChanged(int value);
        void on_spbMinZ_valueChanged(double value);
        void on_spbMaxZ_valueChanged(double value);
        void on_spbMinScale_valueChanged(double value);
        void on_spbMaxScale_valueChanged(double value);
};

#endif // CONFIG_H
