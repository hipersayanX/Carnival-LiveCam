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
    id: recCandy
    width: 136
    height: 104
    color: "#000000"
    radius: 4

    property bool moving: false
    property bool isStacked: true
    property bool isExpanded: false
    property bool isActivated: false
    property bool is3D: false
    property bool isConfigurable: true
    property string pluginId: ""
    property url thumbnail: ""
    property string name: ""
    property string version: ""
    property string summary: ""
    property string category: ""
    property string license: ""
    property string author: ""
    property string website: ""
    property string mail: ""
    property int maxHeight1: recPluginThumbnail.height + 4
    property int maxHeight2: txtName.height + txtSummary.height + imgCategory.height + imgLicense.height + imgAuthor.height + 32

    signal enteredMove
    signal beginMove(int mouseX, int mouseY)
    signal move(int mouseX, int mouseY)
    signal endMove
    signal exitedMove

    signal expandedClicked
    signal configureClicked
    signal activated
    signal deactivated

    Rectangle
    {
        id: recBackground
        rotation: 90
        width: parent.height
        height: parent.width
        radius: 4
        anchors.centerIn: parent

        gradient: Gradient
        {
            GradientStop
            {
                position: 0
                color: "#000000"
            }

            GradientStop
            {
                position: 1
                color: "#3f3f3f"
            }
        }
    }

    Rectangle
    {
        id: recPluginThumbnail
        width: 128
        height: 96
        color: "#00000000"
        anchors.right: parent.right
        anchors.rightMargin: 4
        anchors.verticalCenter: parent.verticalCenter
        border.color: recCandy.isActivated? "#00ff00": "#ff0000"

        Image
        {
            id: imgPluginThumbnail
            opacity: 0.75
            anchors.fill: parent
            source: recCandy.thumbnail

            MouseArea
            {
                id: msaPluginThumbnail
                anchors.fill: parent
                hoverEnabled: true
                onEntered: imgPluginThumbnail.opacity = 1
                onExited: imgPluginThumbnail.opacity = 0.75

                onClicked:
                {
                    recCandy.isActivated = !recCandy.isActivated
                    recPluginThumbnail.border.color = recCandy.isActivated? "#00ff00": "#ff0000"

                    if (recCandy.isActivated)
                        recCandy.activated()
                    else
                        recCandy.deactivated()
                }
            }

            Rectangle
            {
                id: recIs3D
                width: 20
                height: 20
                color: "#000000"
                anchors.right: parent.right
                anchors.top: parent.top

                Text
                {
                    id: txtIs3D
                    color: "#ffffff"
                    text: recCandy.is3D? "3D": "2D"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    anchors.fill: parent
                    font.bold: true
                }
            }

            Button
            {
                id: btnConfigure
                width: 64 / 3
                height: 64 / 3
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                icon: "../images/icons/configure.svg"
                visible: recCandy.isConfigurable && recCandy.isActivated
                onClicked: recCandy.configureClicked()
                onEntered: imgPluginThumbnail.opacity = 1
                onExited: imgPluginThumbnail.opacity = 0.75
            }

            Button
            {
                id: btnAbout
                width: 64 / 3
                height: 64 / 3
                anchors.left: parent.left
                anchors.bottom: parent.bottom
                icon: "../images/icons/about.svg"

                onClicked:
                {
                    recCandy.isExpanded = !recCandy.isExpanded

                    recCandy.expandedClicked()
                }

                onEntered: imgPluginThumbnail.opacity = 1
                onExited: imgPluginThumbnail.opacity = 0.75
            }

            Button
            {
                id: btnMove
                icon: "../images/icons/move.svg"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                opacity: 0.01
                visible: recCandy.isStacked && recCandy.isActivated

                //onClicked: recCandy.move(btnMove.mouseX, btnMove.mouseY)

                onEntered:
                {
                    imgPluginThumbnail.opacity = 1
                    btnMove.opacity = 1
                    recCandy.enteredMove()
                }

                onExited:
                {
                    btnMove.opacity = 0.01
                    recCandy.exitedMove()
                }

                onPressed:
                {
                    recCandy.beginMove(btnMove.mouseX, btnMove.mouseY)
                    recCandy.moving = true
                }

                onPositionChanged:
                {
                    if (recCandy.moving)
                        recCandy.move(btnMove.mouseX, btnMove.mouseY)
                }

                onReleased:
                {
                    if (recCandy.moving)
                    {
                        recCandy.moving = false
                        recCandy.endMove()
                    }
                }
            }
        }
    }


    Item
    {
        id: itmPluginInfo
        anchors.rightMargin: 4
        opacity: 0
        anchors.right: recPluginThumbnail.left
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.top: parent.top

        Text
        {
            id: txtName
            color: "#ffffff"
            text: recCandy.name
            font.bold: true
            anchors.top: parent.top
            anchors.topMargin: 4
            anchors.left: parent.left
            anchors.leftMargin: 4
        }

        Text
        {
            id: txtVersion
            color: "#ffffff"
            text: "(" + recCandy.version + ")"
            verticalAlignment: Text.AlignVCenter
            anchors.left: txtName.right
            anchors.leftMargin: 4
            anchors.verticalCenter: txtName.verticalCenter
        }

        Text
        {
            id: txtSummary
            color: "#ffffff"
            text: qsTr(recCandy.summary)
            anchors.leftMargin: 4
            anchors.right: parent.right
            anchors.topMargin: 8
            anchors.left: parent.left
            wrapMode: Text.WordWrap
            anchors.top: txtName.bottom
        }

        Image
        {
            id: imgCategory
            anchors.left: parent.left
            anchors.leftMargin: 4
            anchors.top: txtSummary.bottom
            anchors.topMargin: 8
            source: "../images/icons/category.svg"
        }

        Text
        {
            id: txtCategory
            color: "#ffffff"
            text: qsTr(recCandy.category)
            anchors.leftMargin: 4
            verticalAlignment: Text.AlignVCenter
            anchors.left: imgCategory.right
            anchors.verticalCenter: imgCategory.verticalCenter
        }

        Image
        {
            id: imgLicense
            anchors.left: parent.left
            anchors.leftMargin: 4
            anchors.top: imgCategory.bottom
            anchors.topMargin: 2
            source: "../images/icons/license.svg"
        }

        Text
        {
            id: txtLicense
            color: "#ffffff"
            text: recCandy.license
            anchors.left: imgLicense.right
            anchors.leftMargin: 4
            anchors.verticalCenter: imgLicense.verticalCenter
            verticalAlignment: Text.AlignVCenter
        }

        Image
        {
            id: imgAuthor
            x: 0
            y: 4
            anchors.top: imgLicense.bottom
            anchors.topMargin: 4
            anchors.left: parent.left
            anchors.leftMargin: 4
            source: "../images/icons/author.svg"
        }

        Text
        {
            id: txtAuthor
            color: "#ffffff"
            text: recCandy.author
            anchors.left: imgAuthor.right
            anchors.leftMargin: 4
            anchors.verticalCenter: imgAuthor.verticalCenter
            verticalAlignment: Text.AlignVCenter
        }

        Button
        {
            id: btnWeb
            width: recCandy.website != ""? 64 / 3: 0
            height: 64 / 3
            backSecondColor: "#00000000"
            backFirstColor: "#00000000"
            anchors.leftMargin: recCandy.website != ""? 4: 0
            anchors.left: txtAuthor.right
            anchors.verticalCenter: imgAuthor.verticalCenter
            icon: "../images/icons/web.svg"
            onClicked: Qt.openUrlExternally(recCandy.website)
            visible: recCandy.website != ""
        }

        Button
        {
            id: btnMail
            width: 64 / 3
            height: 64 / 3
            backSecondColor: "#00000000"
            backFirstColor: "#00000000"
            anchors.leftMargin: 4
            anchors.left: btnWeb.right
            anchors.verticalCenter: imgAuthor.verticalCenter
            icon: "../images/icons/mail.svg"
            onClicked: Qt.openUrlExternally(recCandy.mail)
            visible: recCandy.mail != ""
        }
    }

    states:
    [
        State
        {
            name: "onExpanded"
            when: recCandy.isExpanded == true

            PropertyChanges
            {
                target: recCandy
                width: 350
                height: recCandy.maxHeight1 > recCandy.maxHeight2? recCandy.maxHeight1: recCandy.maxHeight2
            }

            PropertyChanges
            {
                target: itmPluginInfo
                opacity: 1
            }

            PropertyChanges
            {
                target: txtSummary
                opacity: 1
            }
        }
    ]
}
