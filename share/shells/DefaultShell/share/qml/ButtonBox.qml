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
    id: recButtonBox
    color: "#00000000"
    width: 256
    height: 128

    property real markSize: 8
    signal deviceSelected(string deviceId)
    signal configureDevice(string deviceId)
    signal escapePressed

    function updateDevices(devices)
    {
        lsmDevices.clear()
        var index = 0

        for (var device in devices)
        {
            var newDevice = {}

            if (devices[device].isEnabled)
                index = device

            for (var prop in devices[device])
                newDevice["prop" + prop.charAt(0).toUpperCase() + prop.slice(1)] = devices[device][prop]

            lsmDevices.append(newDevice)
        }

        lsvDevices.currentIndex = index
        recButtonBox.updateHeight()
    }

    function updateHeight()
    {
        recButtonBox.height = 1.1 * lsvDevices.currentItem.children[0].height * lsvDevices.count
    }

    Rectangle
    {
        id: recMark
        width: recButtonBox.markSize * Math.SQRT2
        height: recButtonBox.markSize * Math.SQRT2
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
        anchors.bottomMargin: recButtonBox.markSize * Math.SQRT1_2
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

        ListView
        {
            id: lsvDevices
            anchors.fill: parent
            focus: true
            interactive: false
            Keys.onDownPressed: incrementCurrentIndex()
            Keys.onUpPressed: decrementCurrentIndex()
            Keys.onEnterPressed: recButtonBox.deviceSelected(lsvDevices.currentItem.children[0].deviceId)
            Keys.onReturnPressed: recButtonBox.deviceSelected(lsvDevices.currentItem.children[0].deviceId)
            Keys.onEscapePressed: recButtonBox.escapePressed()

            model: ListModel
            {
                id: lsmDevices
            }

            highlight: Component
            {
                Rectangle
                {
                    radius: 10
                    width: recButtonBoxContainer.width
                    height: recButtonBoxContainer.height / lsmDevices.count

                    Behavior on y
                    {
                        SpringAnimation
                        {
                            spring: 0
                            damping: 0
                        }
                    }

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
            }

            delegate: Component
            {
                Device
                {
                    id: dvcDevice
                    width: recButtonBoxContainer.width
                    deviceId: propDeviceId
                    driverId: propDriverId
                    isEnabled: propIsEnabled
                    summary: propSummary
                    icon: propIcon
                    isConfigurable: propIsConfigurable

                    onConfigure: recButtonBox.configureDevice(dvcDevice.deviceId)

                    onClicked:
                    {
                        lsvDevices.currentItem.isEnabled = false

                        for (var index = 0; index < lsmDevices.count; index++)
                            if (lsmDevices.get(index).propDeviceId == dvcDevice.deviceId)
                                break

                        lsvDevices.currentIndex = index
                        lsvDevices.currentItem.isEnabled = true
                        recButtonBox.deviceSelected(dvcDevice.deviceId)
                    }
                }
            }
        }
    }
}
