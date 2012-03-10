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
    id: recEffects
    width: 800
    height: 480
    color: "#000000"
    radius: 2 * recEffects.borderSize
    border.width: 1
    border.color: "#7f7f7f"

    property variant devices: []
    property variant effects: []
    property variant effectsStack: []
    property variant selected: []
    property real borderSize: 8
    property string currentDeviceId: ""

    signal setEffect(string pluginId, string spaceId)
    signal unsetEffect(string pluginId, string spaceId)
    signal pluginMoved(string spaceId, int from, int to)
    signal pluginConfigureClicked(string pluginId)

    function sortAlphaNoCase(a, b)
    {
        if (a.toLowerCase() < b.toLowerCase())
            return -1

        if (a.toLowerCase() > b.toLowerCase())
            return 1

        return 0;
    }

    function listCategories()
    {
        var categories = []

        for (var effect in recEffects.effects)
            if (categories.indexOf(recEffects.effects[effect].category) < 0)
                categories.push(recEffects.effects[effect].category)

        categories.sort(recEffects.sortAlphaNoCase)

        return ["All"].concat(categories)
    }

    onDevicesChanged:
    {
        var devices = []

        for (var device in recEffects.devices)
            if (recEffects.devices[device].isEnabled)
                devices.push(recEffects.devices[device].summary)

        devices.sort(recEffects.sortAlphaNoCase)
        cbxDevice.updateOptions(devices)
    }

    onEffectsChanged:
    {
        cbxEffectsCategory.updateOptions(recEffects.listCategories())
        lsmEffects.clear()

        for (var effect in effects)
        {
            var newEffect = {}

            for (var prop in effects[effect])
                newEffect["prop" + prop.charAt(0).toUpperCase() + prop.slice(1)] = effects[effect][prop]

            lsmEffects.append(newEffect)
        }

        grvEffects.currentIndex = 0
    }

    Component
    {
        id: cmpEffectDelegate

        Item
        {
            Rectangle
            {
                x: 10
                y: 10
                width: 128
                height: 96
                color: "#000000"
                border.color: (recEffects.selected.indexOf(propPluginId) != -1)? "#7f7fff": "#00000000"
                border.width: 8

                Image
                {
                    anchors.fill: parent
                    source: propThumbnail
                    opacity: 0.75

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
                            text: propIs3D? "3D": "2D"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            anchors.fill: parent
                            font.bold: true
                        }
                    }
                }

                MouseArea
                {
                    anchors.fill: parent

                    onClicked:
                    {
                    }

                    onEntered:
                    {
                    }

                    onExited:
                    {
                    }

                    onPressed:
                    {
                    }

                    onReleased:
                    {
                    }
                }
            }
        }
    }

    Rectangle
    {
        id: recEffectsContainer
        color: "#00000000"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 16
        anchors.right: cbxDevice.left
        anchors.rightMargin: 8
        anchors.top: cbxEffectsCategory.bottom
        anchors.topMargin: 8
        anchors.left: parent.left
        anchors.leftMargin: 16

        Rectangle
        {
            id: recEffectsGrid
            radius: 4
            border.color: "#3f3f3f"
            anchors.right: recEffectsControls.left
            anchors.rightMargin: 8
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.top: parent.top

            gradient: Gradient
            {
                GradientStop
                {
                    position: 0
                    color: "#1f1f1f"
                }

                GradientStop
                {
                    position: 1
                    color: "#000000"
                }
            }

            GridView
            {
                id: grvEffects
                clip: true
                anchors.right: sldEffects.left
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.top: parent.top
                cellWidth: 136
                cellHeight: 104

                delegate: cmpEffectDelegate

                model: ListModel
                {
                    id: lsmEffects
                }
            }

            Slider
            {
                id: sldEffects
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.top: parent.top
            }
        }

        Rectangle
        {
            id: recEffectsControls
            x: 202
            y: 43
            width: 32
            height: 80
            color: "#00000000"
            anchors.right: recStack.left
            anchors.rightMargin: 8
            anchors.verticalCenter: parent.verticalCenter

            Button
            {
                id: btnAddEffect
                icon: "../images/icons/arrow-right.svg"
                anchors.top: parent.top
            }

            Button
            {
                id: btnRemoveEffect
                icon: "../images/icons/arrow-left.svg"
                anchors.bottom: parent.bottom
            }
        }

        Rectangle
        {
            id: recStack
            width: 144
            radius: 4
            border.color: "#3f3f3f"
            anchors.bottom: parent.bottom
            anchors.top: parent.top
            anchors.right: parent.right

            gradient: Gradient
            {
                GradientStop
                {
                    position: 0
                    color: "#1f1f1f"
                }

                GradientStop
                {
                    position: 1
                    color: "#000000"
                }
            }

            ListView
            {
                id: lsvStack
                clip: true
                anchors.right: sldStack.left
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.top: parent.top

                delegate: cmpEffectDelegate

                model: ListModel
                {
                    id: lsmStack
                }
            }

            Slider
            {
                id: sldStack
                anchors.bottom: parent.bottom
                anchors.top: parent.top
                anchors.right: parent.right
            }
        }
    }

    ComboBox
    {
        id: cbxEffectsCategory
        height: 32
        anchors.top: parent.top
        anchors.topMargin: 16
        anchors.right: cbxDevice.left
        anchors.rightMargin: 8
        anchors.left: parent.left
        anchors.leftMargin: 16
    }

    ComboBox
    {
        id: cbxDevice
        x: 556
        width: 256
        height: 32
        anchors.top: parent.top
        anchors.topMargin: 16
        anchors.right: parent.right
        anchors.rightMargin: 16
    }

    Image
    {
        id: imgLivePreview
        width: 256
        height: 175
        fillMode: Image.PreserveAspectFit
        anchors.top: cbxDevice.bottom
        anchors.topMargin: 8
        anchors.horizontalCenter: cbxDevice.horizontalCenter
        source: ""
    }

    Rectangle
    {
        id: recEffectInfo
        x: 556
        width: 256
        color: "#00000000"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 16
        anchors.top: imgLivePreview.bottom
        anchors.topMargin: 8
        anchors.horizontalCenter: cbxDevice.horizontalCenter

        Text
        {
            id: txtName
            color: "#ffffff"
            anchors.left: parent.left
            anchors.top: parent.top
            font.bold: true
        }

        Text
        {
            id: txtVersion
            color: "#ffffff"
            anchors.leftMargin: 8
            anchors.top: parent.top
            anchors.left: txtName.right
        }

        Text
        {
            id: txtSummary
            color: "#ffffff"
            anchors.topMargin: 16
            anchors.top: txtName.bottom
            anchors.right: parent.right
            anchors.left: parent.left
            wrapMode: Text.WordWrap
        }

        Image
        {
            id: imgCategory
            anchors.topMargin: 16
            anchors.top: txtSummary.bottom
            anchors.left: parent.left
            source: "../images/icons/category.svg"
        }

        Text
        {
            id: txtCategory
            y: 71
            color: "#ffffff"
            anchors.left: imgCategory.right
            anchors.leftMargin: 8
            anchors.verticalCenter: imgCategory.verticalCenter
            verticalAlignment: Text.AlignVCenter
        }

        Image
        {
            id: imgLicense
            anchors.top: imgCategory.bottom
            anchors.topMargin: 8
            anchors.left: parent.left
            source: "../images/icons/license.svg"
        }

        Text
        {
            id: txtLicense
            y: 98
            color: "#ffffff"
            anchors.left: imgLicense.right
            anchors.leftMargin: 8
            anchors.verticalCenter: imgLicense.verticalCenter
            verticalAlignment: Text.AlignVCenter
        }

        Image
        {
            id: imgAuthor
            anchors.top: imgLicense.bottom
            anchors.topMargin: 8
            anchors.left: parent.left
            source: "../images/icons/author.svg"
        }

        Text
        {
            id: txtAuthor
            y: 129
            color: "#ffffff"
            anchors.left: imgAuthor.right
            anchors.leftMargin: 8
            anchors.verticalCenter: imgAuthor.verticalCenter
            verticalAlignment: Text.AlignVCenter
        }

        Rectangle
        {
            id: recContact
            width: 128
            height: 32
            color: "#00000000"
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter

            Button
            {
                id: btnConfigure
                anchors.left: parent.left
                icon: "../images/icons/configure.svg"
            }

            Button
            {
                id: btnWeb
                anchors.horizontalCenter: parent.horizontalCenter
                icon: "../images/icons/web.svg"
            }

            Button
            {
                id: btnMail
                anchors.right: parent.right
                icon: "../images/icons/mail.svg"
            }
        }
    }
}
