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
    id: recDevices
    color: "#00000000"
    width: 256
    height: 128

    property real markSize: 8
    property variant devices: []

    signal deviceEnable(string deviceId)
    signal deviceDisable(string deviceId)
    signal configureDevice(string deviceId)
    signal escapePressed

    onDevicesChanged:
    {
        lsmDisabledDevices.clear()
        lsmEnabledDevices.clear()

        for (var device in recDevices.devices)
        {
            var newDevice = {}

            for (var prop in recDevices.devices[device])
                newDevice["prop" + prop.charAt(0).toUpperCase() + prop.slice(1)] = recDevices.devices[device][prop]

            if (recDevices.devices[device]["isEnabled"])
                lsmEnabledDevices.append(newDevice)
            else
                lsmDisabledDevices.append(newDevice)
        }

        txtEnabled.visible = (lsmEnabledDevices.count > 0)? true: false
        txtEnabled.height = (lsmEnabledDevices.count > 0)? 20: 0

        lsvEnabledDevices.height = (lsvEnabledDevices.currentItem)? lsvEnabledDevices.currentItem.children[0].height * lsmEnabledDevices.count: 0

        txtDisabled.visible = (lsmDisabledDevices.count > 0)? true: false
        txtDisabled.height = (lsmDisabledDevices.count > 0)? 20: 0
        lsvDisabledDevices.height = (lsvDisabledDevices.currentItem)? lsvDisabledDevices.currentItem.children[0].height * lsmDisabledDevices.count: 0

        recDevices.height = Math.round(1.1 * (lsvEnabledDevices.height + txtEnabled.height + lsvDisabledDevices.height + txtDisabled.height))
    }

    Rectangle
    {
        id: recMark
        width: recDevices.markSize * Math.SQRT2
        height: recDevices.markSize * Math.SQRT2
        color: "#1f1f1f"
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        rotation: 45
    }

    Rectangle
    {
        id: recButtonBoxContainer
        radius: 10
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.bottomMargin: recDevices.markSize * Math.SQRT1_2
        anchors.top: parent.top
        border.width: 4
        border.color: "#1f1f1f"

        gradient: Gradient
        {
            GradientStop
            {
                position: 0
                color: "#3f3f3f"
            }

            GradientStop
            {
                position: 1
                color: "#000000"
            }
        }

        Text
        {
            id: txtEnabled
            height: 20
            color: "#ffffff"
            text: qsTr("Enabled")
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: 10
            font.bold: true
            verticalAlignment: Text.AlignBottom
        }

        ListView
        {
            id: lsvEnabledDevices
            height: 47
            anchors.top: txtEnabled.bottom
            anchors.right: parent.right
            anchors.left: parent.left
            focus: true
            interactive: false
            Keys.onEscapePressed: recDevices.escapePressed()

            model: ListModel
            {
                id: lsmEnabledDevices
            }

            delegate: Component
            {
                Device
                {
                    id: dvcEnabledDevice
                    width: recButtonBoxContainer.width
                    deviceId: propDeviceId
                    driverId: propDriverId
                    isEnabled: propIsEnabled
                    summary: propSummary
                    icon: propIcon
                    isConfigurable: propIsConfigurable

                    onConfigure: recDevices.configureDevice(dvcEnabledDevice.deviceId)

                    onClicked:
                    {
                        var devices = []

                        for (var d in recDevices.devices)
                        {
                            var device = {}

                            for (var prop in recDevices.devices[d])
                                device[prop] = (recDevices.devices[d].deviceId == dvcEnabledDevice.deviceId && prop == "isEnabled")? false: recDevices.devices[d][prop]

                            devices.push(device)
                        }

                        recDevices.deviceDisable(dvcEnabledDevice.deviceId)
                        recDevices.devices = devices
                    }
                }
            }
        }

        Text
        {
            id: txtDisabled
            height: 20
            color: "#ffffff"
            text: qsTr("Disabled")
            anchors.top: lsvEnabledDevices.bottom
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.leftMargin: 10
            font.bold: true
            verticalAlignment: Text.AlignBottom
        }

        ListView
        {
            id: lsvDisabledDevices
            anchors.top: txtDisabled.bottom
            anchors.right: parent.right
            anchors.left: parent.left
            focus: true
            interactive: false
            Keys.onEscapePressed: recDevices.escapePressed()

            model: ListModel
            {
                id: lsmDisabledDevices
            }

            delegate: Component
            {
                Device
                {
                    id: dvcDisabledDevice
                    width: recButtonBoxContainer.width
                    deviceId: propDeviceId
                    driverId: propDriverId
                    isEnabled: propIsEnabled
                    summary: propSummary
                    icon: propIcon
                    isConfigurable: propIsConfigurable

                    onConfigure: recDevices.configureDevice(dvcDisabledDevice.deviceId)

                    onClicked:
                    {
                        var devices = []

                        for (var d in recDevices.devices)
                        {
                            var device = {}

                            for (var prop in recDevices.devices[d])
                                device[prop] = (recDevices.devices[d].deviceId == dvcDisabledDevice.deviceId && prop == "isEnabled")? true: recDevices.devices[d][prop]

                            devices.push(device)
                        }

                        recDevices.deviceEnable(dvcDisabledDevice.deviceId)
                        recDevices.devices = devices
                    }
                }
            }
        }
    }
}
