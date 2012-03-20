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
