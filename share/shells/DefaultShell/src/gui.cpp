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

#include <QDeclarativeEngine>
#include <QDesktopWidget>
#include <QDebug>

#include "../include/gui.h"

Gui::Gui(QWidget *parent): QDeclarativeView(parent)
{
    this->currentFrame = 0;
    this->webcamImageProvider = new WebcamImageProvider;
    this->engine()->addImageProvider("webcam", this->webcamImageProvider);

    setSource(QUrl::fromLocalFile("share/shells/DefaultShell/share/qml/main.qml"));
    setResizeMode(QDeclarativeView::SizeRootObjectToView);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setStyleSheet("background:transparent;");
    setMinimumSize(320, 240);

    QRect frect = this->frameGeometry();
    QDesktopWidget desktop_widget;

    frect.moveCenter(desktop_widget.availableGeometry().center());
    this->move(frect.topLeft());

    this->root = (QObject *)this->rootObject();

    this->windowControls = this->root->findChild<QDeclarativeItem *>("WindowControls");
    this->windowBackground = this->root->findChild<QDeclarativeItem *>("WindowBackground");

    connect(this->windowControls, SIGNAL(enteredMove()), this, SLOT(onEnteredMove()));
    connect(this->windowControls, SIGNAL(beginMove()), this, SLOT(onBeginMove()));
    connect(this->windowControls, SIGNAL(move()), this, SLOT(onMove()));
    connect(this->windowControls, SIGNAL(exitedMove()), this, SLOT(onExitedMove()));

    connect(this->windowControls, SIGNAL(stayOnTop()), this, SLOT(onStayOnTop()));
    connect(this->windowControls, SIGNAL(minimize()), this, SLOT(onMinimize()));
    connect(this->windowControls, SIGNAL(maximize()), this, SLOT(onMaximize()));
    connect(this->windowControls, SIGNAL(close()), this, SLOT(onClose()));

    connect(this->root, SIGNAL(viewPortSizeChanged(int, int)), this, SLOT(onViewPortSizeChanged(int, int)));

    connect(this->root, SIGNAL(mouseDoubleClicked(qreal, qreal, QVariant)), this, SLOT(onMouseDoubleClicked(qreal, qreal, QVariant)));
    connect(this->root, SIGNAL(mousePositionChanged(qreal, qreal, QVariant)), this, SLOT(onMousePositionChanged(qreal, qreal, QVariant)));
    connect(this->root, SIGNAL(mousePressed(qreal, qreal, QVariant)), this, SLOT(onMousePressed(qreal, qreal, QVariant)));
    connect(this->root, SIGNAL(mouseReleased(qreal, qreal, QVariant)), this, SLOT(onMouseReleased(qreal, qreal, QVariant)));

    connect(this->root, SIGNAL(enteredResizeTopLeft()), this, SLOT(onEnteredResizeTopLeft()));
    connect(this->root, SIGNAL(beginResizeTopLeft()), this, SLOT(onBeginResizeTopLeft()));
    connect(this->root, SIGNAL(resizeTopLeft()), this, SLOT(onResizeTopLeft()));
    connect(this->root, SIGNAL(exitedResizeTopLeft()), this, SLOT(onExitedResizeTopLeft()));

    connect(this->root, SIGNAL(enteredResizeBottomLeft()), this, SLOT(onEnteredResizeBottomLeft()));
    connect(this->root, SIGNAL(beginResizeBottomLeft()), this, SLOT(onBeginResizeBottomLeft()));
    connect(this->root, SIGNAL(resizeBottomLeft()), this, SLOT(onResizeBottomLeft()));
    connect(this->root, SIGNAL(exitedResizeBottomLeft()), this, SLOT(onExitedResizeBottomLeft()));

    connect(this->root, SIGNAL(enteredResizeBottomRight()), this, SLOT(onEnteredResizeBottomRight()));
    connect(this->root, SIGNAL(beginResizeBottomRight()), this, SLOT(onBeginResizeBottomRight()));
    connect(this->root, SIGNAL(resizeBottomRight()), this, SLOT(onResizeBottomRight()));
    connect(this->root, SIGNAL(exitedResizeBottomRight()), this, SLOT(onExitedResizeBottomRight()));

    connect(this->root, SIGNAL(enteredResizeLeft()), this, SLOT(onEnteredResizeLeft()));
    connect(this->root, SIGNAL(beginResizeLeft()), this, SLOT(onBeginResizeLeft()));
    connect(this->root, SIGNAL(resizeLeft()), this, SLOT(onResizeLeft()));
    connect(this->root, SIGNAL(exitedResizeLeft()), this, SLOT(onExitedResizeLeft()));

    connect(this->root, SIGNAL(enteredResizeRight()), this, SLOT(onEnteredResizeRight()));
    connect(this->root, SIGNAL(beginResizeRight()), this, SLOT(onBeginResizeRight()));
    connect(this->root, SIGNAL(resizeRight()), this, SLOT(onResizeRight()));
    connect(this->root, SIGNAL(exitedResizeRight()), this, SLOT(onExitedResizeRight()));

    connect(this->root, SIGNAL(enteredResizeTop()), this, SLOT(onEnteredResizeTop()));
    connect(this->root, SIGNAL(beginResizeTop()), this, SLOT(onBeginResizeTop()));
    connect(this->root, SIGNAL(resizeTop()), this, SLOT(onResizeTop()));
    connect(this->root, SIGNAL(exitedResizeTop()), this, SLOT(onExitedResizeTop()));

    connect(this->root, SIGNAL(enteredResizeBottom()), this, SLOT(onEnteredResizeBottom()));
    connect(this->root, SIGNAL(beginResizeBottom()), this, SLOT(onBeginResizeBottom()));
    connect(this->root, SIGNAL(resizeBottom()), this, SLOT(onResizeBottom()));
    connect(this->root, SIGNAL(exitedResizeBottom()), this, SLOT(onExitedResizeBottom()));

    this->iconBar = this->root->findChild<QDeclarativeItem *>("IconBar");

    connect(this->iconBar, SIGNAL(clicked(int)), this, SLOT(iconClicked(int)));

    this->devices = this->root->findChild<QDeclarativeItem *>("Devices");

    connect(devices, SIGNAL(enabledDeviceMoved(int, int)), this, SLOT(onEnabledDeviceMoved(int, int)));
    connect(devices, SIGNAL(deviceEnable(QString)), this, SLOT(onDeviceEnable(QString)));
    connect(devices, SIGNAL(deviceDisable(QString)), this, SLOT(onDeviceDisable(QString)));
    connect(devices, SIGNAL(configureDevice(QString)), this, SLOT(onDeviceConfigureClicked(QString)));

    this->effects = this->root->findChild<QDeclarativeItem *>("Effects");

    connect(this->effects, SIGNAL(setEffect(QString, QString)), this, SLOT(onSetEffect(QString, QString)));
    connect(this->effects, SIGNAL(unsetEffect(QString, QString)), this, SLOT(onUnsetEffect(QString, QString)));
    connect(this->effects, SIGNAL(pluginMoved(QString, int, int)), this, SLOT(onPluginMoved(QString, int, int)));
    connect(this->effects, SIGNAL(pluginConfigureClicked(QString)), this, SLOT(onPluginConfigureClicked(QString)));
}

QString Gui::showPreview()
{
    return this->effects->isVisible()? this->effects->property("currentDeviceId").toString(): "";
}

void Gui::iconClicked(int index)
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

void Gui::onEnabledDeviceMoved(int from, int to)
{
    emit enabledDeviceMoved(from, to);
}

void Gui::onDeviceEnable(QString deviceId)
{
    emit deviceEnable(deviceId);
}

void Gui::onDeviceDisable(QString deviceId)
{
    emit deviceDisable(deviceId);
}

void Gui::onSetEffect(QString pluginId, QString spaceId)
{
    emit setEffect(pluginId, spaceId);
}

void Gui::onUnsetEffect(QString pluginId, QString spaceId)
{
    emit unsetEffect(pluginId, spaceId);
}

void Gui::onPluginMoved(QString spaceId, int from, int to)
{
    emit pluginMoved(spaceId, from, to);
}

void Gui::onPluginConfigureClicked(QString pluginId)
{
    emit pluginConfigureClicked(pluginId);
}

void Gui::onDeviceConfigureClicked(QString deviceId)
{
    emit deviceConfigureClicked(deviceId);
}

void Gui::updateDevices(const QList<QVariant> &devices, const QStringList &activeSpaces)
{
    this->devices->setProperty("activeDevices", activeSpaces);
    this->devices->setProperty("devices", devices);
}

void Gui::updatePlugins(const QList<QVariant> &plugins)
{
    this->effects->setProperty("effects", plugins);
}

void Gui::setFrame(const QImage &frame)
{
    this->webcamImageProvider->setFrame(frame);
    this->windowBackground->setProperty("source", "image://webcam/" + QString::number(this->currentFrame));
    this->currentFrame++;
}

void Gui::setPreview(const QImage &frame)
{
    this->webcamImageProvider->setFrame(frame);
    this->effects->setProperty("preview", "image://webcam/" + QString::number(this->currentFrame));
    this->currentFrame++;
}

void Gui::moveDevice(qint32 from, qint32 to)
{
    QMetaObject::invokeMethod(this->devices, "moveDevice", Q_ARG(QVariant, from), Q_ARG(QVariant, to));
}

void Gui::onViewPortSizeChanged(int width, int height)
{
    emit viewPortSizeChanged(QSize(width, height));
}

void Gui::onMouseDoubleClicked(qreal mouseX, qreal mouseY, QVariant pressedButtons)
{
    QMouseEvent *event = new QMouseEvent(QEvent::MouseButtonDblClick,
                                         QPoint(mouseX, mouseY),
                                         (Qt::MouseButton) pressedButtons.toInt(),
                                         (Qt::MouseButtons) pressedButtons.toInt(),
                                         Qt::NoModifier);

    emit sMouseDoubleClicked(event);
}

void Gui::onMousePositionChanged(qreal mouseX, qreal mouseY, QVariant pressedButtons)
{
    QMouseEvent *event = new QMouseEvent(QEvent::MouseMove,
                                         QPoint(mouseX, mouseY),
                                         (Qt::MouseButton) pressedButtons.toInt(),
                                         (Qt::MouseButtons) pressedButtons.toInt(),
                                         Qt::NoModifier);

    emit sMousePositionChanged(event);
}

void Gui::onMousePressed(qreal mouseX, qreal mouseY, QVariant pressedButtons)
{
    QMouseEvent *event = new QMouseEvent(QEvent::MouseButtonPress,
                                         QPoint(mouseX, mouseY),
                                         (Qt::MouseButton) pressedButtons.toInt(),
                                         (Qt::MouseButtons) pressedButtons.toInt(),
                                         Qt::NoModifier);

    emit sMousePressed(event);
}

void Gui::onMouseReleased(qreal mouseX, qreal mouseY, QVariant pressedButtons)
{
    QMouseEvent *event = new QMouseEvent(QEvent::MouseButtonRelease,
                                         QPoint(mouseX, mouseY),
                                         (Qt::MouseButton) pressedButtons.toInt(),
                                         (Qt::MouseButtons) pressedButtons.toInt(),
                                         Qt::NoModifier);

    emit sMouseReleased(event);
}

void Gui::onEnteredMove()
{
    this->setCursor(Qt::SizeAllCursor);
}

void Gui::onBeginMove()
{
    this->windowPos0 = this->pos();
    this->mousePos0 = QCursor::pos();
}

void Gui::onMove()
{
    this->move(this->windowPos0 + QCursor::pos() - this->mousePos0);
}

void Gui::onExitedMove()
{
    this->unsetCursor();
}

void Gui::onMinimize()
{
    this->showMinimized();
}

void Gui::onStayOnTop()
{
    if (this->windowFlags() & Qt::WindowStaysOnTopHint)
        this->setWindowFlags(Qt::FramelessWindowHint);
    else
        this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    this->show();
}

void Gui::onMaximize()
{
    if (this->isMaximized())
        this->showNormal();
    else
        this->showMaximized();
}

void Gui::onClose()
{
    this->close();

    emit closed();
}

void Gui::onEnteredResizeTopLeft()
{
    this->setCursor(Qt::SizeFDiagCursor);
}

void Gui::onBeginResizeTopLeft()
{
    this->windowPos0 = this->pos();
    this->windowSize0 = this->size();
    this->mousePos0 = QCursor::pos();
}

void Gui::onResizeTopLeft()
{
    qint32 dpx = QCursor::pos().x() - this->mousePos0.x();
    qint32 dpy = QCursor::pos().y() - this->mousePos0.y();
    qint32 dsx = -dpx;
    qint32 dsy = -dpy;

    if (this->size().width() == this->minimumSize().width())
        dpx = 0;

    if (this->size().height() == this->minimumSize().height())
        dpy = 0;

    this->setGeometry(this->windowPos0.x() + dpx,
                      this->windowPos0.y() + dpy,
                      this->windowSize0.width() + dsx,
                      this->windowSize0.height() + dsy);
}

void Gui::onExitedResizeTopLeft()
{
    this->unsetCursor();
}

void Gui::onEnteredResizeBottomLeft()
{
    this->setCursor(Qt::SizeBDiagCursor);
}

void Gui::onBeginResizeBottomLeft()
{
    this->windowPos0 = this->pos();
    this->windowSize0 = this->size();
    this->mousePos0 = QCursor::pos();
}

void Gui::onResizeBottomLeft()
{
    qint32 dpx = QCursor::pos().x() - this->mousePos0.x();
    qint32 dsx = -dpx;
    qint32 dsy = QCursor::pos().y() - this->mousePos0.y();

    if (this->size().width() == this->minimumSize().width())
        dpx = 0;

    this->setGeometry(this->windowPos0.x() + dpx,
                      this->windowPos0.y(),
                      this->windowSize0.width() + dsx,
                      this->windowSize0.height() + dsy);
}

void Gui::onExitedResizeBottomLeft()
{
    this->unsetCursor();
}

void Gui::onEnteredResizeBottomRight()
{
    this->setCursor(Qt::SizeFDiagCursor);
}

void Gui::onBeginResizeBottomRight()
{
    this->windowPos0 = this->pos();
    this->windowSize0 = this->size();
    this->mousePos0 = QCursor::pos();
}

void Gui::onResizeBottomRight()
{
    qint32 dsx = QCursor::pos().x() - this->mousePos0.x();
    qint32 dsy = QCursor::pos().y() - this->mousePos0.y();

    this->setGeometry(this->windowPos0.x(),
                      this->windowPos0.y(),
                      this->windowSize0.width() + dsx,
                      this->windowSize0.height() + dsy);
}

void Gui::onExitedResizeBottomRight()
{
    this->unsetCursor();
}

void Gui::onEnteredResizeLeft()
{
    this->setCursor(Qt::SizeHorCursor);
}

void Gui::onBeginResizeLeft()
{
    this->windowPos0 = this->pos();
    this->windowSize0 = this->size();
    this->mousePos0 = QCursor::pos();
}

void Gui::onResizeLeft()
{
    qint32 dp = QCursor::pos().x() - this->mousePos0.x();
    qint32 ds = -dp;

    if (this->size().width() == this->minimumSize().width())
        dp = 0;

    this->setGeometry(this->windowPos0.x() + dp,
                      this->windowPos0.y(),
                      this->windowSize0.width() + ds,
                      this->windowSize0.height());
}

void Gui::onExitedResizeLeft()
{
    this->unsetCursor();
}

void Gui::onEnteredResizeRight()
{
    this->setCursor(Qt::SizeHorCursor);
}

void Gui::onBeginResizeRight()
{
    this->windowSize0 = this->size();
    this->mousePos0 = QCursor::pos();
}

void Gui::onResizeRight()
{
    this->resize(this->windowSize0 + QSize(QCursor::pos().x(), 0) - QSize(this->mousePos0.x(), 0));
}

void Gui::onExitedResizeRight()
{
    this->unsetCursor();
}

void Gui::onEnteredResizeTop()
{
    this->setCursor(Qt::SizeVerCursor);
}

void Gui::onBeginResizeTop()
{
    this->windowPos0 = this->pos();
    this->windowSize0 = this->size();
    this->mousePos0 = QCursor::pos();
}

void Gui::onResizeTop()
{
    qint32 dp = QCursor::pos().y() - this->mousePos0.y();
    qint32 ds = -dp;

    if (this->size().height() == this->minimumSize().height())
        dp = 0;

    this->setGeometry(this->windowPos0.x(),
                      this->windowPos0.y() + dp,
                      this->windowSize0.width(),
                      this->windowSize0.height() + ds);
}

void Gui::onExitedResizeTop()
{
    this->unsetCursor();
}

void Gui::onEnteredResizeBottom()
{
    this->setCursor(Qt::SizeVerCursor);
}

void Gui::onBeginResizeBottom()
{
    this->windowSize0 = this->size();
    this->mousePos0 = QCursor::pos();
}

void Gui::onResizeBottom()
{
    this->resize(this->windowSize0 + QSize(0, QCursor::pos().y()) - QSize(0, this->mousePos0.y()));
}

void Gui::onExitedResizeBottom()
{
    this->unsetCursor();
}
