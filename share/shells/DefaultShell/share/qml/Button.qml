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

import QtQuick 1.0

Rectangle
{
    id: recButton
    width: 32
    height: 32
    radius: Math.sqrt(Math.pow(width, 2) + Math.pow(height, 2)) / (5 * Math.SQRT2)
    smooth: true

    property url icon: ""
    property color borderColorNormal: "#00000000"
    property color borderColorHover: "#7f7fff"
    property color borderColorPressed: "#ffffff"
    property color backFirstColor: "#3f3f3f"
    property color backSecondColor: "#000000"
    property real mouseX: 0
    property real mouseY: 0
    property bool isPressed: false

    border.color: borderColorNormal

    gradient: Gradient
    {
        GradientStop
        {
            id: gradientstop1
            position: 0
            color: recButton.backFirstColor
        }

        GradientStop
        {
            id: gradientstop2
            position: 1
            color: recButton.backSecondColor
        }
    }

    signal canceled
    signal clicked
    signal doubleClicked
    signal entered
    signal exited
    signal positionChanged
    signal pressAndHold
    signal pressed
    signal released

    MouseArea
    {
        id: msaIcon
        anchors.fill: parent
        hoverEnabled: true

        onCanceled:
        {
            recButton.mouseX = mouseX
            recButton.mouseY = mouseY
            recButton.canceled()
        }

        onClicked:
        {
            recButton.mouseX = mouseX
            recButton.mouseY = mouseY
            recButton.clicked()
        }

        onDoubleClicked:
        {
            recButton.mouseX = mouseX
            recButton.mouseY = mouseY
            recButton.doubleClicked()
        }

        onEntered:
        {
            recButton.mouseX = mouseX
            recButton.mouseY = mouseY
            recButton.border.color = recButton.borderColorHover
            recButton.entered()
        }

        onExited:
        {
            recButton.mouseX = mouseX
            recButton.mouseY = mouseY
            recButton.border.color = recButton.borderColorNormal
            recButton.exited()
        }

        onPositionChanged:
        {
            recButton.mouseX = mouseX
            recButton.mouseY = mouseY
            recButton.positionChanged(mouse)
        }

        onPressAndHold:
        {
            recButton.mouseX = mouseX
            recButton.mouseY = mouseY
            recButton.pressAndHold(mouse)
        }

        onPressed:
        {
            recButton.mouseX = mouseX
            recButton.mouseY = mouseY
            recButton.isPressed = true
            recButton.border.color = recButton.borderColorPressed
            recButton.pressed()
        }

        onReleased:
        {
            recButton.mouseX = mouseX
            recButton.mouseY = mouseY
            recButton.isPressed = false
            recButton.border.color = recButton.borderColorHover
            recButton.released()
        }
    }

    Image
    {
        id: imgIcon
        width: 0.75 * recButton.width
        height: 0.75 * recButton.height
        smooth: true
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        source: recButton.icon
    }

    states:
    [
        State
        {
            name: "Pressed"
            when: msaIcon.pressed == true

            PropertyChanges
            {
                target: gradientstop1
                position: 0
                color: recButton.backSecondColor
            }

            PropertyChanges
            {
                target: gradientstop2
                position: 1
                color: recButton.backFirstColor
            }

            PropertyChanges
            {
                target: msaIcon
            }

            PropertyChanges
            {
                target: imgIcon
                scale: 0.75
            }
        }
    ]
}
