#ifndef SPACE_H
#define SPACE_H

#include <QObject>
#include <QImage>

class Space: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QImage maskImage READ maskImage WRITE setMaskImage RESET resetMaskImage)
    Q_PROPERTY(QSize frameSize READ frameSize WRITE setFrameSize RESET resetFrameSize)

    public:
        explicit Space(QObject *parent = 0);
        Space(const Space &object);

        Space(QImage maskImage,
              QSize frameSize);

        Space& operator =(const Space &other);

        QImage maskImage();
        QSize frameSize();

    private:
        QImage m_maskImage;
        QSize m_frameSize;

    public slots:
        void setMaskImage(QImage value);
        void setFrameSize(QSize value);
        void resetMaskImage();
        void resetFrameSize();
};

#endif // SPACE_H
