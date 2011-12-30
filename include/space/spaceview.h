#ifndef SPACEVIEW_H
#define SPACEVIEW_H

#include <QObject>
#include <QImage>

#include "spacemodel.h"

class SpaceView: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QImage scaleAndRotateIcon READ scaleAndRotateIcon WRITE setScaleAndRotateIcon RESET resetScaleAndRotateIcon)

    public:
        explicit SpaceView(QObject *parent = 0);
        Q_INVOKABLE QImage render();
        Q_INVOKABLE void setSpace(QString spaceId, const QImage &frame);
        Q_INVOKABLE void removeSpace(QString spaceId);
        Q_INVOKABLE void setSnapping(bool snapping, int nParts, qreal snappingPT, qreal snappingRT);
        Q_INVOKABLE void setScaleAndRotateIcon(const QImage &icon);

    private:
        SpaceModel spaceModel;
        QHash<QString, QImage> framesTable;

    public slots:
        void viewPortSize(QSize size);
        void selectSpace(QString spaceId);
        void selectSpace(QPoint point);
        void toggleMaximizedSpace();
        void scaleSpace(QPoint to);
        void rotateSpace(QPoint to);
        void scaleAndRotateSpace(QPoint to);
        void moveSpace(QPoint to);
        void mouseMoved(QPoint mousePos);
        void mousePressed();
        void mouseReleased();
};

#endif // SPACEVIEW_H
