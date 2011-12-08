#ifndef CONFIG_H
#define CONFIG_H

#include <QDialog>

#include "ui_config.h"

class Config: public QDialog, private Ui::Config
{
    Q_OBJECT
    Q_PROPERTY(QStringList *imageDevices READ imageDevices WRITE setImageDevices RESET resetImageDevices)

    public:
        explicit Config(QWidget *parent = 0);
        QStringList *imageDevices();

    private:
        QStringList *m_imageDevices;

        void setFiles(QStringList files);

    public slots:
        void setImageDevices(QStringList *imageDevices);
        void resetImageDevices();

    protected:
        void changeEvent(QEvent *e);

    private slots:
        void on_btnAdd_clicked();
        void on_btnRemove_clicked();
};

#endif // CONFIG_H
