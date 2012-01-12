/*
 * Carnival LiveCam, Augmented reality made easy.
 * Copyright (C) 2011  Gonzalo Exequiel Pedone
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with This program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Email   : hipersayan DOT x AT gmail DOT com
 * Web-Site: http://hipersayanx.blogspot.com/
 *
 * QML shell plugin
 */

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

    this->bbxWebcams = this->root->findChild<QDeclarativeItem *>("bbxWebcams");

    connect(bbxWebcams, SIGNAL(deviceEnable(QString)), this, SLOT(onDeviceEnable(QString)));
    connect(bbxWebcams, SIGNAL(deviceDisable(QString)), this, SLOT(onDeviceDisable(QString)));
    connect(bbxWebcams, SIGNAL(configureDevice(QString)), this, SLOT(onDeviceConfigureClicked(QString)));

    this->candyBar = this->root->findChild<QDeclarativeItem *>("CandyBar");

    this->candyView = this->root->findChild<QDeclarativeItem *>("CandyView");

    connect(this->candyView, SIGNAL(pluginActivated(QString)), this, SLOT(onPluginActivated(QString)));
    connect(this->candyView, SIGNAL(pluginDeactivated(QString)), this, SLOT(onPluginDeactivated(QString)));
    connect(this->candyView, SIGNAL(pluginMoved(int, int)), this, SLOT(onPluginMoved(int, int)));
    connect(this->candyView, SIGNAL(pluginConfigureClicked(QString)), this, SLOT(onPluginConfigureClicked(QString)));
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

void Gui::onDeviceEnable(QString deviceId)
{
    emit deviceEnable(deviceId);
}

void Gui::onDeviceDisable(QString deviceId)
{
    emit deviceDisable(deviceId);
}

void Gui::onPluginActivated(QString pluginId)
{
    emit pluginActivated(pluginId);
}

void Gui::onPluginDeactivated(QString pluginId)
{
    emit pluginDeactivated(pluginId);
}

void Gui::onPluginMoved(int from, int to)
{
    emit pluginMoved(from, to);
}

void Gui::onPluginConfigureClicked(QString pluginId)
{
    emit pluginConfigureClicked(pluginId);
}

void Gui::onDeviceConfigureClicked(QString deviceId)
{
    emit deviceConfigureClicked(deviceId);
}

void Gui::updateDevices(const QList<QVariant> &devices)
{
    QMetaObject::invokeMethod(this->bbxWebcams, "updateDevices", Q_ARG(QVariant, devices));
}

void Gui::updatePlugins(const QList<QVariant> &plugins)
{
    QMetaObject::invokeMethod(this->candyBar, "updateCandys", Q_ARG(QVariant, plugins));
}

void Gui::setFrame(const QImage &frame)
{
    this->webcamImageProvider->setFrame(frame);
    this->windowBackground->setProperty("source", "image://webcam/" + QString(this->currentFrame));;
    this->currentFrame++;
}

void Gui::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)

    emit viewPortSizeChanged(this->windowBackground->childrenRect().size().toSize());
}

void Gui::onMouseDoubleClicked(qreal mouseX, qreal mouseY, QVariant pressedButtons)
{
    QMouseEvent *event = new QMouseEvent(QEvent::MouseButtonDblClick,
                                         QPoint(mouseX, mouseY),
                                         (Qt::MouseButton) pressedButtons.toInt(),
                                         (Qt::MouseButtons) pressedButtons.toInt(),
                                         Qt::NoModifier);

    emit mouseDoubleClicked(event);
}

void Gui::onMousePositionChanged(qreal mouseX, qreal mouseY, QVariant pressedButtons)
{
    QMouseEvent *event = new QMouseEvent(QEvent::MouseMove,
                                         QPoint(mouseX, mouseY),
                                         (Qt::MouseButton) pressedButtons.toInt(),
                                         (Qt::MouseButtons) pressedButtons.toInt(),
                                         Qt::NoModifier);

    emit mousePositionChanged(event);
}

void Gui::onMousePressed(qreal mouseX, qreal mouseY, QVariant pressedButtons)
{
    QMouseEvent *event = new QMouseEvent(QEvent::MouseButtonPress,
                                         QPoint(mouseX, mouseY),
                                         (Qt::MouseButton) pressedButtons.toInt(),
                                         (Qt::MouseButtons) pressedButtons.toInt(),
                                         Qt::NoModifier);

    emit mousePressed(event);
}

void Gui::onMouseReleased(qreal mouseX, qreal mouseY, QVariant pressedButtons)
{
    QMouseEvent *event = new QMouseEvent(QEvent::MouseButtonRelease,
                                         QPoint(mouseX, mouseY),
                                         (Qt::MouseButton) pressedButtons.toInt(),
                                         (Qt::MouseButtons) pressedButtons.toInt(),
                                         Qt::NoModifier);

    emit mouseReleased(event);
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
    int dpx = QCursor::pos().x() - this->mousePos0.x();
    int dpy = QCursor::pos().y() - this->mousePos0.y();
    int dsx = -dpx;
    int dsy = -dpy;

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
    int dpx = QCursor::pos().x() - this->mousePos0.x();
    int dsx = -dpx;
    int dsy = QCursor::pos().y() - this->mousePos0.y();

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
    int dsx = QCursor::pos().x() - this->mousePos0.x();
    int dsy = QCursor::pos().y() - this->mousePos0.y();

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
    int dp = QCursor::pos().x() - this->mousePos0.x();
    int ds = -dp;

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
    int dp = QCursor::pos().y() - this->mousePos0.y();
    int ds = -dp;

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
