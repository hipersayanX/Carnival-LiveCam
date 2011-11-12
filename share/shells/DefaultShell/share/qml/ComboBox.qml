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

Button
{
    id: recComboBox
    width: 100
    height: 24
    radius: 8
    borderColorNormal: "#7f7f7f"
    property bool isExpanded: false
    property real currentOption: 0

    signal itemSelected(int index, string value)

    onEntered: recExpand.border.color = recComboBox.borderColorHover
    onExited: recExpand.border.color = recComboBox.borderColorNormal
    onPressed: recExpand.border.color = recComboBox.borderColorPressed
    onReleased: recExpand.border.color = recComboBox.borderColorHover
    onClicked: recComboBox.isExpanded = !recComboBox.isExpanded

    function updateOptions(options)
    {
        txtOption.text = options[recComboBox.currentOption]
        lswOptions.updateOptions(options)
    }

    Text
    {
        id: txtOption
        y: 24
        color: "#ffffff"
        anchors.right: recExpand.left
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    Rectangle
    {
        id: recExpand
        width: 8
        height: 8
        color: "#00000000"
        radius: 3
        smooth: true
        anchors.rightMargin: 4
        border.width: 1
        border.color: "#7f7f7f"
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
    }

    ListWidget
    {
        id: lswOptions
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
        radius: recComboBox.radius
        opacity: 0

        onItemSelected:
        {
            recComboBox.currentOption = index
            txtOption.text = value
            recComboBox.isExpanded = false
            recComboBox.itemSelected(index, value)
        }

        onEscapePressed:
        {
            if (recComboBox.isExpanded)
                recComboBox.isExpanded = false

            setIndex(recComboBox.currentOption)
        }
    }

    states:
    [
        State
        {
            name: "State1"
            when: recComboBox.isExpanded == true

            PropertyChanges
            {
                target: lswOptions
                opacity: 1
            }
        }
    ]
}
