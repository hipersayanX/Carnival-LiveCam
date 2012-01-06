#ifndef SPACEVIEW_H
#define SPACEVIEW_H

#include <QObject>
#include <QImage>
#include <QHash>
#include <QGraphicsScene>

#include "spacemodel.h"
#include "spacewidget.h"

class SpaceView: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QImage scaleAndRotateIcon READ scaleAndRotateIcon WRITE setScaleAndRotateIcon RESET resetScaleAndRotateIcon)
    Q_PROPERTY(QImage toggleMaximizeIcon READ toggleMaximizeIcon WRITE setToggleMaximizeIcon RESET resetToggleMaximizeIcon)
    Q_PROPERTY(QSize viewPortSize READ viewPortSize WRITE setViewPortSize RESET resetViewPortSize)
    Q_PROPERTY(QPoint mousePosition READ mousePosition WRITE setMousePosition RESET resetMousePosition)

    public:
        explicit SpaceView(QObject *parent = 0);
        ~SpaceView();
        Q_INVOKABLE QImage render();
        Q_INVOKABLE void setSpace(QString spaceId, const QImage &frame);
        Q_INVOKABLE void removeSpace(QString spaceId);
        Q_INVOKABLE void setSnapping(bool snapping, int nParts, qreal snappingPT, qreal snappingRT);
        Q_INVOKABLE QPoint mapToMainSpace(const QPoint &pos, const QSize &viewportSize);

        QImage scaleAndRotateIcon();
        QImage toggleMaximizeIcon();
        QSize viewPortSize();
        QPoint mousePosition();

    private:
        QImage m_scaleAndRotateIcon;
        QImage m_toggleMaximizeIcon;
        QSize m_viewPortSize;
        QPoint m_mousePosition;
        SpaceModel spaceModel;
        QGraphicsScene mainSpace;
        QHash<QString, SpaceWidget *> spacesWidgets;
        QHash<QString, QGraphicsProxyWidget *> proxySpacesWidgets;

        void sendMouseEvent(QEvent::Type type,
                            const QPoint &position,
                            Qt::MouseButton button,
                            Qt::MouseButtons buttons,
                            Qt::KeyboardModifiers modifiers);

    public slots:
        void setScaleAndRotateIcon(const QImage &icon);
        void setToggleMaximizeIcon(const QImage &icon);
        void setViewPortSize(QSize size);
        void setMousePosition(QPoint mousePos);
        void resetScaleAndRotateIcon();
        void resetToggleMaximizeIcon();
        void resetViewPortSize();
        void resetMousePosition();
        void selectSpace(QString spaceId);
        void mouseDoubleClickEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
        void mousePressEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);
};

#endif // SPACEVIEW_H
