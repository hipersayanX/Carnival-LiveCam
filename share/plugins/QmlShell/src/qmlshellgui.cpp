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

#include "qmlshellgui.h"

QmlShellGui::QmlShellGui(QWidget *parent): QQuickView(parent)
{
    this->m_currentFrame = 0;
    this->m_imageProvider = new ImageProvider;
    this->engine()->addImageProvider("webcam", this->m_imageProvider);

    this->setSource(QUrl::fromLocalFile(":/QmlShell/share/qml/main.qml"));
    this->setResizeMode(QQuickView::SizeRootObjectToView);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->setStyleSheet("background:transparent;");
    this->setMinimumSize(QSize(320, 240));

    QRect frect = this->frameGeometry();
    QDesktopWidget desktop_widget;

    frect.moveCenter(desktop_widget.availableGeometry().center());
    this->move(frect.topLeft());

    this->m_root = (QObject *)this->rootObject();

    this->m_windowControls = this->m_root->findChild<QQuickItem *>("WindowControls");
    this->m_windowBackground = this->m_root->findChild<QQuickItem *>("WindowBackground");

    connect(this->m_windowControls, SIGNAL(enteredMove()), this, SLOT(onEnteredMove()));
    connect(this->m_windowControls, SIGNAL(beginMove()), this, SLOT(onBeginMove()));
    connect(this->m_windowControls, SIGNAL(move()), this, SLOT(onMove()));
    connect(this->m_windowControls, SIGNAL(exitedMove()), this, SLOT(onExitedMove()));

    connect(this->m_windowControls, SIGNAL(stayOnTop()), this, SLOT(onStayOnTop()));
    connect(this->m_windowControls, SIGNAL(minimize()), this, SLOT(onMinimize()));
    connect(this->m_windowControls, SIGNAL(maximize()), this, SLOT(onMaximize()));
    connect(this->m_windowControls, SIGNAL(close()), this, SLOT(onClose()));

    connect(this->m_root, SIGNAL(viewPortSizeChanged(int, int)), this, SLOT(onViewPortSizeChanged(int, int)));

    connect(this->m_root, SIGNAL(mouseDoubleClicked(qreal, qreal, QVariant)), this, SLOT(onMouseDoubleClicked(qreal, qreal, QVariant)));
    connect(this->m_root, SIGNAL(mousePositionChanged(qreal, qreal, QVariant)), this, SLOT(onMousePositionChanged(qreal, qreal, QVariant)));
    connect(this->m_root, SIGNAL(mousePressed(qreal, qreal, QVariant)), this, SLOT(onMousePressed(qreal, qreal, QVariant)));
    connect(this->m_root, SIGNAL(mouseReleased(qreal, qreal, QVariant)), this, SLOT(onMouseReleased(qreal, qreal, QVariant)));

    connect(this->m_root, SIGNAL(enteredResizeTopLeft()), this, SLOT(onEnteredResizeTopLeft()));
    connect(this->m_root, SIGNAL(beginResizeTopLeft()), this, SLOT(onBeginResizeTopLeft()));
    connect(this->m_root, SIGNAL(resizeTopLeft()), this, SLOT(onResizeTopLeft()));
    connect(this->m_root, SIGNAL(exitedResizeTopLeft()), this, SLOT(onExitedResizeTopLeft()));

    connect(this->m_root, SIGNAL(enteredResizeBottomLeft()), this, SLOT(onEnteredResizeBottomLeft()));
    connect(this->m_root, SIGNAL(beginResizeBottomLeft()), this, SLOT(onBeginResizeBottomLeft()));
    connect(this->m_root, SIGNAL(resizeBottomLeft()), this, SLOT(onResizeBottomLeft()));
    connect(this->m_root, SIGNAL(exitedResizeBottomLeft()), this, SLOT(onExitedResizeBottomLeft()));

    connect(this->m_root, SIGNAL(enteredResizeBottomRight()), this, SLOT(onEnteredResizeBottomRight()));
    connect(this->m_root, SIGNAL(beginResizeBottomRight()), this, SLOT(onBeginResizeBottomRight()));
    connect(this->m_root, SIGNAL(resizeBottomRight()), this, SLOT(onResizeBottomRight()));
    connect(this->m_root, SIGNAL(exitedResizeBottomRight()), this, SLOT(onExitedResizeBottomRight()));

    connect(this->m_root, SIGNAL(enteredResizeLeft()), this, SLOT(onEnteredResizeLeft()));
    connect(this->m_root, SIGNAL(beginResizeLeft()), this, SLOT(onBeginResizeLeft()));
    connect(this->m_root, SIGNAL(resizeLeft()), this, SLOT(onResizeLeft()));
    connect(this->m_root, SIGNAL(exitedResizeLeft()), this, SLOT(onExitedResizeLeft()));

    connect(this->m_root, SIGNAL(enteredResizeRight()), this, SLOT(onEnteredResizeRight()));
    connect(this->m_root, SIGNAL(beginResizeRight()), this, SLOT(onBeginResizeRight()));
    connect(this->m_root, SIGNAL(resizeRight()), this, SLOT(onResizeRight()));
    connect(this->m_root, SIGNAL(exitedResizeRight()), this, SLOT(onExitedResizeRight()));

    connect(this->m_root, SIGNAL(enteredResizeTop()), this, SLOT(onEnteredResizeTop()));
    connect(this->m_root, SIGNAL(beginResizeTop()), this, SLOT(onBeginResizeTop()));
    connect(this->m_root, SIGNAL(resizeTop()), this, SLOT(onResizeTop()));
    connect(this->m_root, SIGNAL(exitedResizeTop()), this, SLOT(onExitedResizeTop()));

    connect(this->m_root, SIGNAL(enteredResizeBottom()), this, SLOT(onEnteredResizeBottom()));
    connect(this->m_root, SIGNAL(beginResizeBottom()), this, SLOT(onBeginResizeBottom()));
    connect(this->m_root, SIGNAL(resizeBottom()), this, SLOT(onResizeBottom()));
    connect(this->m_root, SIGNAL(exitedResizeBottom()), this, SLOT(onExitedResizeBottom()));

    this->m_iconBar = this->m_root->findChild<QQuickItem *>("IconBar");

    connect(this->m_iconBar, SIGNAL(clicked(int)), this, SLOT(iconClicked(int)));

    this->m_devices = this->m_root->findChild<QQuickItem *>("Devices");

    connect(m_devices, SIGNAL(enabledDeviceMoved(int, int)), this, SLOT(onEnabledDeviceMoved(int, int)));
    connect(m_devices, SIGNAL(deviceEnable(QString)), this, SLOT(onDeviceEnable(QString)));
    connect(m_devices, SIGNAL(deviceDisable(QString)), this, SLOT(onDeviceDisable(QString)));
    connect(m_devices, SIGNAL(configureDevice(QString)), this, SLOT(onDeviceConfigureClicked(QString)));

    this->m_effects = this->m_root->findChild<QQuickItem *>("Effects");

    connect(this->m_effects, SIGNAL(setEffect(QString, QString)), this, SLOT(onSetEffect(QString, QString)));
    connect(this->m_effects, SIGNAL(unsetEffect(QString, QString)), this, SLOT(onUnsetEffect(QString, QString)));
    connect(this->m_effects, SIGNAL(pluginMoved(QString, int, int)), this, SLOT(onPluginMoved(QString, int, int)));
    connect(this->m_effects, SIGNAL(pluginConfigureClicked(QString)), this, SLOT(onPluginConfigureClicked(QString)));
}

QString QmlShellGui::showPreview()
{
    return this->m_effects->isVisible()? this->m_effects->property("currentDeviceId").toString(): "";
}

void QmlShellGui::iconClicked(int index)
{
    switch (index)
    {
        case 1:
            emit takePicture();
        break;

        case 2:
            emit startStopRecord();
        break;

        case 4:
            emit toggleEditMode();
        break;

        case 5:
            if (this->isFullScreen())
                this->showNormal();
            else
                this->showFullScreen();
        break;
    }
}

void QmlShellGui::onEnabledDeviceMoved(int from, int to)
{
    emit enabledDeviceMoved(from, to);
}

void QmlShellGui::onDeviceEnable(QString deviceId)
{
    emit deviceEnable(deviceId);
}

void QmlShellGui::onDeviceDisable(QString deviceId)
{
    emit deviceDisable(deviceId);
}

void QmlShellGui::onSetEffect(QString pluginId, QString spaceId)
{
    emit setEffect(pluginId, spaceId);
}

void QmlShellGui::onUnsetEffect(QString pluginId, QString spaceId)
{
    emit unsetEffect(pluginId, spaceId);
}

void QmlShellGui::onPluginMoved(QString spaceId, int from, int to)
{
    emit pluginMoved(spaceId, from, to);
}

void QmlShellGui::onPluginConfigureClicked(QString pluginId)
{
    emit pluginConfigureClicked(pluginId);
}

void QmlShellGui::onDeviceConfigureClicked(QString deviceId)
{
    emit deviceConfigureClicked(deviceId);
}

void QmlShellGui::updateDevices(const QList<QVariant> &devices, const QStringList &activeSpaces)
{
    this->m_devices->setProperty("activeDevices", activeSpaces);
    this->m_devices->setProperty("devices", devices);
}

void QmlShellGui::updatePlugins(const QList<QVariant> &plugins)
{
    this->m_effects->setProperty("effects", plugins);
}

void QmlShellGui::setFrame(const QImage &frame)
{
    this->m_imageProvider->setFrame(frame);
    this->m_windowBackground->setProperty("source", "image://webcam/" + QString::number(this->m_currentFrame));
    this->m_currentFrame++;
}

void QmlShellGui::setPreview(const QImage &frame)
{
    this->m_imageProvider->setFrame(frame);
    this->m_effects->setProperty("preview", "image://webcam/" + QString::number(this->m_currentFrame));
    this->m_currentFrame++;
}

void QmlShellGui::moveDevice(qint32 from, qint32 to)
{
    QMetaObject::invokeMethod(this->m_devices, "moveDevice", Q_ARG(QVariant, from), Q_ARG(QVariant, to));
}

void QmlShellGui::onViewPortSizeChanged(int width, int height)
{
    emit viewPortSizeChanged(QSize(width, height));
}

void QmlShellGui::onMouseDoubleClicked(qreal mouseX, qreal mouseY, QVariant pressedButtons)
{
    QMouseEvent *event = new QMouseEvent(QEvent::MouseButtonDblClick,
                                         QPoint(mouseX, mouseY),
                                         (Qt::MouseButton) pressedButtons.toInt(),
                                         (Qt::MouseButtons) pressedButtons.toInt(),
                                         Qt::NoModifier);

    emit sMouseDoubleClicked(event);
}

void QmlShellGui::onMousePositionChanged(qreal mouseX, qreal mouseY, QVariant pressedButtons)
{
    QMouseEvent *event = new QMouseEvent(QEvent::MouseMove,
                                         QPoint(mouseX, mouseY),
                                         (Qt::MouseButton) pressedButtons.toInt(),
                                         (Qt::MouseButtons) pressedButtons.toInt(),
                                         Qt::NoModifier);

    emit sMousePositionChanged(event);
}

void QmlShellGui::onMousePressed(qreal mouseX, qreal mouseY, QVariant pressedButtons)
{
    QMouseEvent *event = new QMouseEvent(QEvent::MouseButtonPress,
                                         QPoint(mouseX, mouseY),
                                         (Qt::MouseButton) pressedButtons.toInt(),
                                         (Qt::MouseButtons) pressedButtons.toInt(),
                                         Qt::NoModifier);

    emit sMousePressed(event);
}

void QmlShellGui::onMouseReleased(qreal mouseX, qreal mouseY, QVariant pressedButtons)
{
    QMouseEvent *event = new QMouseEvent(QEvent::MouseButtonRelease,
                                         QPoint(mouseX, mouseY),
                                         (Qt::MouseButton) pressedButtons.toInt(),
                                         (Qt::MouseButtons) pressedButtons.toInt(),
                                         Qt::NoModifier);

    emit sMouseReleased(event);
}

void QmlShellGui::onEnteredMove()
{
    this->setCursor(Qt::SizeAllCursor);
}

void QmlShellGui::onBeginMove()
{
    this->m_windowPos0 = this->pos();
    this->m_mousePos0 = QCursor::pos();
}

void QmlShellGui::onMove()
{
    this->move(this->m_windowPos0 + QCursor::pos() - this->m_mousePos0);
}

void QmlShellGui::onExitedMove()
{
    this->unsetCursor();
}

void QmlShellGui::onMinimize()
{
    this->showMinimized();
}

void QmlShellGui::onStayOnTop()
{
    if (this->windowFlags() & Qt::WindowStaysOnTopHint)
        this->setWindowFlags(Qt::FramelessWindowHint);
    else
        this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    this->show();
}

void QmlShellGui::onMaximize()
{
    if (this->isMaximized())
        this->showNormal();
    else
        this->showMaximized();
}

void QmlShellGui::onClose()
{
    this->close();

    emit closed();
}

void QmlShellGui::onEnteredResizeTopLeft()
{
    this->setCursor(Qt::SizeFDiagCursor);
}

void QmlShellGui::onBeginResizeTopLeft()
{
    this->m_windowPos0 = this->pos();
    this->m_windowSize0 = this->size();
    this->m_mousePos0 = QCursor::pos();
}

void QmlShellGui::onResizeTopLeft()
{
    qint32 dpx = QCursor::pos().x() - this->m_mousePos0.x();
    qint32 dpy = QCursor::pos().y() - this->m_mousePos0.y();
    qint32 dsx = -dpx;
    qint32 dsy = -dpy;

    if (this->size().width() == this->minimumSize().width())
        dpx = 0;

    if (this->size().height() == this->minimumSize().height())
        dpy = 0;

    this->setGeometry(this->m_windowPos0.x() + dpx,
                      this->m_windowPos0.y() + dpy,
                      this->m_windowSize0.width() + dsx,
                      this->m_windowSize0.height() + dsy);
}

void QmlShellGui::onExitedResizeTopLeft()
{
    this->unsetCursor();
}

void QmlShellGui::onEnteredResizeBottomLeft()
{
    this->setCursor(Qt::SizeBDiagCursor);
}

void QmlShellGui::onBeginResizeBottomLeft()
{
    this->m_windowPos0 = this->pos();
    this->m_windowSize0 = this->size();
    this->m_mousePos0 = QCursor::pos();
}

void QmlShellGui::onResizeBottomLeft()
{
    qint32 dpx = QCursor::pos().x() - this->m_mousePos0.x();
    qint32 dsx = -dpx;
    qint32 dsy = QCursor::pos().y() - this->m_mousePos0.y();

    if (this->size().width() == this->minimumSize().width())
        dpx = 0;

    this->setGeometry(this->m_windowPos0.x() + dpx,
                      this->m_windowPos0.y(),
                      this->m_windowSize0.width() + dsx,
                      this->m_windowSize0.height() + dsy);
}

void QmlShellGui::onExitedResizeBottomLeft()
{
    this->unsetCursor();
}

void QmlShellGui::onEnteredResizeBottomRight()
{
    this->setCursor(Qt::SizeFDiagCursor);
}

void QmlShellGui::onBeginResizeBottomRight()
{
    this->m_windowPos0 = this->pos();
    this->m_windowSize0 = this->size();
    this->m_mousePos0 = QCursor::pos();
}

void QmlShellGui::onResizeBottomRight()
{
    qint32 dsx = QCursor::pos().x() - this->m_mousePos0.x();
    qint32 dsy = QCursor::pos().y() - this->m_mousePos0.y();

    this->setGeometry(this->m_windowPos0.x(),
                      this->m_windowPos0.y(),
                      this->m_windowSize0.width() + dsx,
                      this->m_windowSize0.height() + dsy);
}

void QmlShellGui::onExitedResizeBottomRight()
{
    this->unsetCursor();
}

void QmlShellGui::onEnteredResizeLeft()
{
    this->setCursor(Qt::SizeHorCursor);
}

void QmlShellGui::onBeginResizeLeft()
{
    this->m_windowPos0 = this->pos();
    this->m_windowSize0 = this->size();
    this->m_mousePos0 = QCursor::pos();
}

void QmlShellGui::onResizeLeft()
{
    qint32 dp = QCursor::pos().x() - this->m_mousePos0.x();
    qint32 ds = -dp;

    if (this->size().width() == this->minimumSize().width())
        dp = 0;

    this->setGeometry(this->m_windowPos0.x() + dp,
                      this->m_windowPos0.y(),
                      this->m_windowSize0.width() + ds,
                      this->m_windowSize0.height());
}

void QmlShellGui::onExitedResizeLeft()
{
    this->unsetCursor();
}

void QmlShellGui::onEnteredResizeRight()
{
    this->setCursor(Qt::SizeHorCursor);
}

void QmlShellGui::onBeginResizeRight()
{
    this->m_windowSize0 = this->size();
    this->m_mousePos0 = QCursor::pos();
}

void QmlShellGui::onResizeRight()
{
    this->resize(this->m_windowSize0 + QSize(QCursor::pos().x(), 0) - QSize(this->m_mousePos0.x(), 0));
}

void QmlShellGui::onExitedResizeRight()
{
    this->unsetCursor();
}

void QmlShellGui::onEnteredResizeTop()
{
    this->setCursor(Qt::SizeVerCursor);
}

void QmlShellGui::onBeginResizeTop()
{
    this->m_windowPos0 = this->pos();
    this->m_windowSize0 = this->size();
    this->m_mousePos0 = QCursor::pos();
}

void QmlShellGui::onResizeTop()
{
    qint32 dp = QCursor::pos().y() - this->m_mousePos0.y();
    qint32 ds = -dp;

    if (this->size().height() == this->minimumSize().height())
        dp = 0;

    this->setGeometry(this->m_windowPos0.x(),
                      this->m_windowPos0.y() + dp,
                      this->m_windowSize0.width(),
                      this->m_windowSize0.height() + ds);
}

void QmlShellGui::onExitedResizeTop()
{
    this->unsetCursor();
}

void QmlShellGui::onEnteredResizeBottom()
{
    this->setCursor(Qt::SizeVerCursor);
}

void QmlShellGui::onBeginResizeBottom()
{
    this->m_windowSize0 = this->size();
    this->m_mousePos0 = QCursor::pos();
}

void QmlShellGui::onResizeBottom()
{
    this->resize(this->m_windowSize0 + QSize(0, QCursor::pos().y()) - QSize(0, this->m_mousePos0.y()));
}

void QmlShellGui::onExitedResizeBottom()
{
    this->unsetCursor();
}
