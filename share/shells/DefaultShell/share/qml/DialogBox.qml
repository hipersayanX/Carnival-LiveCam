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

Rectangle
{
    id: recDialogBox
    width: 128
    height: 56
    color: "#00000000"
    property color backgroundUp: "#3f3f3f"
    property color backgroundDown: "#000000"
    property real markSize: 8
    property string text: ""

    function setText(text)
    {
        recDialogBox.text = text
        recDialogBox.width = txtTitle.width + recDialogBox.height - txtTitle.height
    }

    Rectangle
    {
        id: recMark
        width: recDialogBox.markSize * Math.SQRT2
        height: recDialogBox.markSize * Math.SQRT2
        color: "#1f1f1f"
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        rotation: 45
    }

    Rectangle
    {
        id: recTitle
        radius: 16
        anchors.bottomMargin: -recDialogBox.markSize * Math.SQRT1_2
        anchors.bottom: recMark.top
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.left: parent.left
        border.width: 4
        border.color: "#1f1f1f"

        gradient: Gradient
        {
            GradientStop
            {
                position: 0
                color: recDialogBox.backgroundUp
            }

            GradientStop
            {
                position: 1
                color: recDialogBox.backgroundDown
            }
        }

        Text
        {
            id: txtTitle
            text: recDialogBox.text
            color: "#ffffff"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}
