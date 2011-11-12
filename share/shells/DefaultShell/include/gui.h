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

#ifndef GUI_H
#define GUI_H

#include <QDeclarativeView>
#include <QDeclarativeItem>

#include "webcamimageprovider.h"

class Gui: public QDeclarativeView
{
    Q_OBJECT

    public:
        explicit Gui(QWidget *parent=0);

    private:
        WebcamImageProvider *webcamImageProvider;
        QObject *root;
        QDeclarativeItem *bbxWebcams;
        QDeclarativeItem *iconBar;
        QDeclarativeItem *candyBar;
        QDeclarativeItem *candyView;
        QDeclarativeItem *windowControls;
        QDeclarativeItem *windowBackground;
        QPoint windowPos0;
        QPoint mousePos0;
        QSize windowSize0;
        char currentFrame;

    signals:
        void takePicture();
        void startStopRecord();
        void deviceSelected(QString deviceId);
        void pluginActivated(QString pluginId);
        void pluginDeactivated(QString pluginId);
        void pluginMoved(int from, int to);
        void pluginConfigureClicked(QString pluginId);
        void deviceConfigureClicked(QString deviceId);
        void closed();

    public slots:
        void setFrame(const QImage &frame);
        void updateDevices(const QList<QVariant> &devices);
        void updatePlugins(const QList<QVariant> &plugins);

    private slots:
        void iconClicked(int index=0);
        void onDeviceSelected(QString deviceId);
        void onPluginActivated(QString pluginId);
        void onPluginDeactivated(QString pluginId);
        void onPluginMoved(int from, int to);
        void onPluginConfigureClicked(QString pluginId);
        void onDeviceConfigureClicked(QString deviceId);

        void onEnteredMove();
        void onBeginMove();
        void onMove();
        void onExitedMove();
        void onMinimize();
        void onStayOnTop();
        void onMaximize();
        void onClose();
        void onEnteredResizeTopLeft();
        void onBeginResizeTopLeft();
        void onResizeTopLeft();
        void onExitedResizeTopLeft();
        void onEnteredResizeBottomLeft();
        void onBeginResizeBottomLeft();
        void onResizeBottomLeft();
        void onExitedResizeBottomLeft();
        void onEnteredResizeBottomRight();
        void onBeginResizeBottomRight();
        void onResizeBottomRight();
        void onExitedResizeBottomRight();
        void onEnteredResizeLeft();
        void onBeginResizeLeft();
        void onResizeLeft();
        void onExitedResizeLeft();
        void onEnteredResizeRight();
        void onBeginResizeRight();
        void onResizeRight();
        void onExitedResizeRight();
        void onEnteredResizeTop();
        void onBeginResizeTop();
        void onResizeTop();
        void onExitedResizeTop();
        void onEnteredResizeBottom();
        void onBeginResizeBottom();
        void onResizeBottom();
        void onExitedResizeBottom();
};

#endif // GUI_H
