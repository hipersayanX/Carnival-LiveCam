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
    id: recSlider
    width: 16
    height: 256
    radius: width / 2
    property real minValue: 0
    property real maxValue: 99
    property real value: 0
    property bool showUpDown: false

    signal beginMove

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

    function updateValue()
    {
        var k = (recSliderArea.height - btnSlider.height) / (recSlider.maxValue - recSlider.minValue)

        if (recSlider.value < recSlider.minValue)
            recSlider.value = recSlider.minValue

        if (recSlider.value > recSlider.maxValue)
            recSlider.value = recSlider.maxValue

        btnSlider.y = Math.round(k * (recSlider.value - recSlider.minValue))
    }

    function setValue(value)
    {
        recSlider.value = value

        if (recSlider.value < recSlider.minValue)
            recSlider.value = recSlider.minValue

        if (recSlider.value > recSlider.maxValue)
            recSlider.value = recSlider.maxValue

        var k = (recSliderArea.height - btnSlider.height) / (recSlider.maxValue - recSlider.minValue)
        btnSlider.y = Math.round(k * (recSlider.value - recSlider.minValue))
    }

    signal valueChanged(int value)

    Timer
    {
        id: tmrSlider
        interval: 100
        repeat: true
        triggeredOnStart: true

        onTriggered:
        {
            var tmpValue = 0
            var k = (recSliderArea.height - btnSlider.height) / (recSlider.maxValue - recSlider.minValue)

            if (btnUp.isPressed)
            {
                tmpValue = recSlider.value - 1

                if (tmpValue >= recSlider.minValue && tmpValue <= recSlider.maxValue)
                    recSlider.value = tmpValue
                else
                    return

                btnSlider.y = Math.round(k * (recSlider.value - recSlider.minValue))
                recSlider.valueChanged(recSlider.value)
            }

            if (btnDown.isPressed)
            {
                tmpValue = recSlider.value + 1

                if (tmpValue >= recSlider.minValue && tmpValue <= recSlider.maxValue)
                    recSlider.value = tmpValue
                else
                    return

                btnSlider.y = Math.round(k * (recSlider.value - recSlider.minValue))
                recSlider.valueChanged(recSlider.value)
            }
        }
    }

    Button
    {
        id: btnUp
        height: recSlider.showUpDown? width: 0
        smooth: true
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.left: parent.left
        radius: width / 2
        visible: recSlider.showUpDown

        onPressed:
        {
            tmrSlider.start()
            recSlider.beginMove()
        }

        onReleased: tmrSlider.stop()
    }

    Button
    {
        id: btnDown
        height: recSlider.showUpDown? width: 0
        smooth: true
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        radius: width / 2
        visible: recSlider.showUpDown

        onPressed:
        {
            tmrSlider.start()
            recSlider.beginMove()
        }

        onReleased: tmrSlider.stop()
    }

    Rectangle
    {
        id: recSliderArea
        color: "#00000000"
        anchors.bottom: btnDown.top
        anchors.top: btnUp.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        onHeightChanged: recSlider.updateValue()

        MouseArea
        {
            id: msaSliderArea
            anchors.fill: parent

            onClicked:
            {
                var k = (recSliderArea.height - btnSlider.height) / (recSlider.maxValue - recSlider.minValue)
                var tmpValue = Math.round(mouseY / k + recSlider.minValue)

                if (tmpValue >= recSlider.minValue && tmpValue <= recSlider.maxValue)
                    recSlider.value = tmpValue
                else
                    return

                btnSlider.y = Math.round(k * (recSlider.value - recSlider.minValue))
                recSlider.valueChanged(recSlider.value)
            }
        }

        Button
        {
            id: btnSlider
            height: getHeight()
            smooth: true
            anchors.right: parent.right
            anchors.left: parent.left
            radius: width / 2
            property color backFirstColor: "#bfbfbf"
            property color backSecondColor: "#7f7f7f"
            property real oldMouseY: 0

            function getHeight()
            {
                var height = recSliderArea.height / (recSlider.maxValue - recSlider.minValue + 1)

                if (height < btnSlider.width)
                    height = btnSlider.width

                return height
            }

            Component.onCompleted: recSlider.updateValue()

            onPressed:
            {
                btnSlider.oldMouseY = mouseY
                recSlider.beginMove()
            }

            onPositionChanged:
            {
                if (!isPressed)
                    return

                var k = (recSliderArea.height - btnSlider.height) / (recSlider.maxValue - recSlider.minValue)
                var dy = mouseY - btnSlider.oldMouseY
                var dvalue = Math.round(dy / k)
                var tmpValue = recSlider.value + dvalue

                if (tmpValue >= recSlider.minValue && tmpValue <= recSlider.maxValue)
                    recSlider.value = tmpValue
                else
                    return

                btnSlider.y = Math.round(k * (recSlider.value - recSlider.minValue))
                recSlider.valueChanged(recSlider.value)
            }
        }
    }
}
