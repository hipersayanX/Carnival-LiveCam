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
    id: recSoundSlider
    width: 64
    height: 208
    color: "#00000000"
    property int minValue: 0
    property int maxValue: 100
    property int oldValue: maxValue
    property bool soundIsOn: true
    property color frontColorMiddle: "#7f7fff"
    property color frontColorSide: "#0000ff"
    property color backColorMiddle: "#000000"
    property color backColorSide: "#3f3f3f"
    property color backgroundUp: "#3f3f3f"
    property color backgroundDown: "#000000"
    property url iconMicOn: "../images/icons/micon.svg"
    property url iconMicOff: "../images/icons/micoff.svg"
    property int borderSize: 5

    signal escapePressed
    signal valueChanged(int value)
    signal released
    signal soundOn
    signal soundOff

    Rectangle
    {
        id: recSoundSliderInt
        radius: 12
        border.width: recSoundSlider.borderSize
        border.color: "#1f1f1f"

        gradient: Gradient
        {
            GradientStop
            {
                position: 0
                color: recSoundSlider.backgroundUp
            }

            GradientStop
            {
                position: 1
                color: recSoundSlider.backgroundDown
            }
        }

        anchors.fill: parent

        Rectangle
        {
            id: recMicIcon
            x: 16
            y: 16
            width: 32
            height: 32
            radius: 5
            border.color: "#00000000"
            color: "#00000000"
            anchors.horizontalCenter: parent.horizontalCenter

            Image
            {
                id: imgMicIcon
                anchors.fill: parent
                source: recSoundSlider.iconMicOn
            }

            MouseArea
            {
                id: msaMicIcon
                anchors.fill: parent
                hoverEnabled: true

                onClicked:
                {
                    recSoundSlider.soundIsOn = !recSoundSlider.soundIsOn

                    if(recSoundSlider.soundIsOn)
                    {
                        imgMicIcon.source = recSoundSlider.iconMicOn
                        recSoundSlider.soundOn()
                    }
                    else
                    {
                        imgMicIcon.source = recSoundSlider.iconMicOff
                        recSoundSlider.soundOff()
                    }
                }
            }
        }
    }

    Rectangle
    {
        id: recSoundSliderFront
        anchors.bottomMargin: 16
        anchors.rightMargin: 24
        anchors.leftMargin: 24
        anchors.topMargin: 64
        anchors.fill: parent

        Rectangle
        {
            rotation: 270
            transformOrigin: Item.Top
            width: parent.height
            height: parent.width
            x: -width / 2
            y: width / 2

            gradient: Gradient
            {
                GradientStop
                {
                    position: 0
                    color: recSoundSlider.frontColorSide
                }

                GradientStop
                {
                    position: 0.5
                    color: recSoundSlider.frontColorMiddle
                }

                GradientStop
                {
                    position: 1
                    color: recSoundSlider.frontColorSide
                }
            }
        }

        MouseArea
        {
            anchors.fill: parent
            onPressed: updateSlider()
            onPositionChanged: updateSlider()
            onReleased: recSoundSlider.released()
            Keys.onEscapePressed: escapePressed()

            function updateSlider()
            {
                if(mouseY >= 0 && mouseY <= recSoundSliderFront.height)
                {
                    recSoundSliderBack.width = mouseY
                    var k = (recSoundSlider.minValue - recSoundSlider.maxValue) / parent.height
                    var value = k * mouseY + recSoundSlider.maxValue
                    var int_value = Math.round(value)

                    if(int_value != recSoundSlider.oldValue)
                    {
                        recSoundSlider.valueChanged(int_value)
                        recSoundSlider.oldValue = int_value
                    }
                }
            }
        }

        Rectangle
        {
            id: recSoundSliderBack
            rotation: 270
            transformOrigin: Item.Top
            width: 0
            x: -width / 2
            y: width / 2
            height: parent.width

            gradient: Gradient
            {
                GradientStop
                {
                    position: 0
                    color: recSoundSlider.backColorSide
                }

                GradientStop
                {
                    position: 0.5
                    color: recSoundSlider.backColorMiddle
                }

                GradientStop
                {
                    position: 1
                    color: recSoundSlider.backColorSide
                }
            }
        }
    }

    Rectangle
    {
        id: recMark
        width: recSoundSliderInt.border.width * Math.SQRT2
        height: recSoundSliderInt.border.width * Math.SQRT2
        color: "#1f1f1f"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: -recSoundSliderInt.border.width
        anchors.horizontalCenter: parent.horizontalCenter
        rotation: 45
    }

    states:
    [
        State
        {
            name: "onHover"
            when: msaMicIcon.containsMouse == true && msaMicIcon.pressed == false

            PropertyChanges
            {
                target: recMicIcon
                border.color: "#7f7fff"
            }
        },

        State
        {
            name: "onPressed"
            when: msaMicIcon.pressed == true

            PropertyChanges
            {
                target: recMicIcon
                border.color: "#ffffff"
            }
        }
    ]
}
