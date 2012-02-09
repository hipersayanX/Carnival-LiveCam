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

import QtQuick 1.1

Window
{
    id: wdgMainWidget
    radius: 15
    width: 640
    height: 480
    color: "#e6000000"
    property bool showEffectBar: false

    onMousePressed:
    {
        webcams.visible = false
        about.visible = false
    }

    EffectBar
    {
        id: cdbEffectBar
        objectName: "EffectBar"
        visible: wdgMainWidget.showEffectBar
        anchors.rightMargin: 1
        anchors.bottomMargin: 1
        anchors.topMargin: 1
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
    }

    IconBar
    {
        id: iconbar
        objectName: "IconBar"
        opacity: 0.5
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        Component.onCompleted: updateItems({"Set a Device": "../images/icons/webcam.svg", "Take a Picture": "../images/icons/picture.svg", "Record Video": "../images/icons/video.svg", "Apply Effects": "../images/icons/effects.svg", "Edit Spaces": "../images/icons/spaces.svg", "Fullscreen": "../images/icons/fullscreen.svg", "About": "../images/icons/about.svg"})

        onEntered: iconbar.opacity = 1
        onExited: iconbar.opacity = 0.5

        onClicked:
        {
            switch(index)
            {
                case 0:
                {
                    about.visible = false
                    webcams.visible = !webcams.visible
                }
                break

                case 2:
                {
                    about.visible = false
                    webcams.visible = false

                    if(getIconSrc(2) == "../images/icons/video.svg")
                        setIconSrc(2, "../images/icons/stoprec.svg")
                    else
                        setIconSrc(2, "../images/icons/video.svg")
                }
                break

                case 3:
                {
                    about.visible = false
                    webcams.visible = false
                    wdgMainWidget.showEffectBar = !wdgMainWidget.showEffectBar
                }
                break

                case 4:
                {
                    about.visible = false
                    webcams.visible = false
                    wdgMainWidget.showEffectBar = false
                }
                break

                case 5:
                {
                    about.visible = false
                    webcams.visible = false

                    if(getIconSrc(5) == "../images/icons/fullscreen.svg")
                        setIconSrc(5, "../images/icons/windowed.svg")
                    else
                        setIconSrc(5, "../images/icons/fullscreen.svg")
                }
                break

                case 6:
                {
                    webcams.visible = false
                    about.visible = !about.visible
                    wdgMainWidget.showEffectBar = false
                }
                break

                default:
                {
                    about.visible = false
                    webcams.visible = false
                    wdgMainWidget.showEffectBar = false
                }
                break
            }
        }
    }

    Devices
    {
        id: webcams
        anchors.bottomMargin: 5
        anchors.rightMargin: -(webcams.width + iconbar.iconSize) / 2
        anchors.right: iconbar.left
        objectName: "bbxWebcams"
        opacity: 0.95
        visible: false
        anchors.bottom: iconbar.top
        onEscapePressed: visible = false
    }

    WindowControls
    {
        id: wctWindowControls
        objectName: "WindowControls"
        opacity: 0.5
        anchors.top: parent.top
        anchors.right: parent.right

        onEntered: wctWindowControls.opacity = 1
        onExited: wctWindowControls.opacity = 0.5
    }

    About
    {
        id: about
        visible: false
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }
}
