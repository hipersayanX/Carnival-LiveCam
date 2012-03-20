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
    id: recIconBar
    width: 224
    height: 32
    radius: 16

    property int iconSize: 32
    property color highlightUp: Qt.rgba(0, 0.5, 1, 1)
    property color highlightDown: Qt.rgba(0, 0, 0, 1)
    property color backgroundUp: Qt.rgba(0.25, 0.25, 0.25, 1)
    property color backgroundDown: Qt.rgba(0, 0, 0, 1)

    signal clicked(int index)
    signal entered
    signal exited

    function updateItems(newItems)
    {
        lsmIconBar.clear()

        for(var item in newItems)
            lsmIconBar.append({"title": item, "icon": newItems[item]})

        lsvIconBar.currentIndex = 0
        recIconBar.width = recIconBar.iconSize * lsmIconBar.count
        recIconBar.height = recIconBar.iconSize
    }

    function setIconSrc(index, iconSrc)
    {
        lsmIconBar.get(index).icon = iconSrc
    }

    function getIconSrc(index)
    {
        return lsmIconBar.get(index).icon
    }

    gradient: Gradient
    {
        GradientStop
        {
            position: 0
            color: Qt.rgba(0.25, 0.25, 0.25, 1)
        }

        GradientStop
        {
            position: 1
            color: Qt.rgba(0, 0, 0, 1)
        }
    }

    ListView
    {
        id: lsvIconBar
        anchors.fill: parent
        orientation: ListView.Horizontal
        focus: true
        interactive: false

        model: ListModel
        {
            id: lsmIconBar
        }

        Component
        {
            id: cmpIconHighlight

            Rectangle
            {
                width: recIconBar.iconSize
                height: recIconBar.iconSize
                radius: recIconBar.iconSize / 2

                gradient: Gradient
                {
                    GradientStop
                    {
                        position: 0
                        color: recIconBar.highlightUp
                    }

                    GradientStop
                    {
                        position: 1
                        color: recIconBar.highlightDown
                    }
                }
            }
        }

        delegate: Component
        {
           Image
            {
                width: recIconBar.iconSize
                height: recIconBar.iconSize
                source: icon
            }
        }

        MouseArea
        {
            id: msaIconBar
            hoverEnabled: true
            anchors.fill: parent
            onClicked: recIconBar.clicked(lsvIconBar.indexAt(mouseX, mouseY))
            onPressed: lsvIconBar.currentItem.scale = 0.75
            onReleased: lsvIconBar.currentItem.scale = 1
            onEntered: recIconBar.entered()
            onExited: recIconBar.exited()

            onPositionChanged:
            {
                var index = lsvIconBar.indexAt(mouseX, mouseY)
                lsvIconBar.currentIndex = index
                dlbTitle.anchors.horizontalCenterOffset = index * (recIconBar.width - recIconBar.iconSize) / (lsmIconBar.count - 1) + (recIconBar.iconSize - recIconBar.width) / 2
                dlbTitle.setText(lsmIconBar.get(index).title)
            }
        }
    }

    states:
    [
        State
        {
            name: "onHover"
            when: msaIconBar.containsMouse == true

            PropertyChanges
            {
                target: lsvIconBar
                highlight: cmpIconHighlight
            }

            PropertyChanges
            {
                target: dlbTitle
                opacity: 1
            }
        }
    ]

    DialogBox
    {
        id: dlbTitle
        opacity: 0
        anchors.bottomMargin: recIconBar.height + 2
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
    }
}
