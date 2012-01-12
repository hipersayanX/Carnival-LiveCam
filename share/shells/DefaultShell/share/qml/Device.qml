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
    id: recDevice
    width: 256
    height: 32
    color: "#00000000"
    radius: 10
    clip: true

    property string deviceId: ""
    property string driverId: ""
    property bool isEnabled: false
    property string summary: ""
    property string icon: ""
    property bool isConfigurable: false
    property color borderColorNormal: "#00000000"
    property color borderColorHover: "#7f7fff"
    property color borderColorPressed: "#ffffff"

    signal clicked
    signal configure

    Rectangle
    {
        id: recHighlight
        radius: 10
        visible: recDevice.isEnabled
        anchors.fill: parent

        gradient: Gradient
        {
            GradientStop
            {
                position: 0
                color: "#007fff"
            }

            GradientStop
            {
                position: 1
                color: "#000000"
            }
        }
    }

    Image
    {
        id: imgIcon
        width: recDevice.height
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        source: recDevice.icon
    }

    Text
    {
        id: txtSummary
        color: "#ffffff"
        text: recDevice.summary
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }

    Rectangle
    {
        id: rectangle1
        color: "#00000000"
        radius: 10
        anchors.fill: parent
        border.width: 2
        border.color: recDevice.borderColorNormal
    }

    MouseArea
    {
        id: msaDevice
        anchors.fill: parent
        hoverEnabled: true

        onClicked: recDevice.clicked()
        onEntered: rectangle1.border.color = recDevice.borderColorHover
        onExited: rectangle1.border.color = recDevice.borderColorNormal
        onPressed: rectangle1.border.color = recDevice.borderColorPressed
        onReleased: rectangle1.border.color = recDevice.borderColorHover
    }

    Button
    {
        id: btnConfigure
        visible: recDevice.isConfigurable && recDevice.isEnabled
        width: recDevice.height - 4
        anchors.rightMargin: 2
        anchors.bottomMargin: 2
        anchors.topMargin: 2
        icon: "../images/icons/configure.svg"
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        anchors.right: parent.right

        onClicked: recDevice.configure()
        onEntered: rectangle1.border.color = recDevice.borderColorHover
        onExited: rectangle1.border.color = recDevice.borderColorNormal
    }


}
