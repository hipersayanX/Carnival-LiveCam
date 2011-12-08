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
