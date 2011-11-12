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
    id: recCandyBar
    width: 192
    height: 512
    property variant candys: []
    property variant candysStack: []

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

    function updateCandys(candys)
    {
        recCandyBar.candys = candys
        cdvCandys.updateCandys(recCandyBar.candys)
        cbxCategory.updateOptions(recCandyBar.listCategories())
    }

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

        for (var candy in recCandyBar.candys)
            if (categories.indexOf(recCandyBar.candys[candy].category) < 0)
                categories.push(recCandyBar.candys[candy].category)

        categories.sort(recCandyBar.sortAlphaNoCase)

        return ["All"].concat(categories)
    }

    CandyView
    {
        id: cdvCandys
        objectName: "CandyView"
        showCategory: "All"
        anchors.top: recCandyBarControls.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left

        onPluginMoved:
        {
            var newCandyStack = []

            if (from < to)
            {
                if (from > 0)
                    newCandyStack = newCandyStack.concat(recCandyBar.candysStack.slice(0, from))

                newCandyStack = newCandyStack.concat(recCandyBar.candysStack.slice(from + 1, to + 1))
                newCandyStack = newCandyStack.concat(recCandyBar.candysStack.slice(from, from + 1))

                if (to + 1 < recCandyBar.candysStack.length)
                    newCandyStack = newCandyStack.concat(recCandyBar.candysStack.slice(to + 1, recCandyBar.candysStack.length))
            }
            else
            {
                if (to > 0)
                    newCandyStack = newCandyStack.concat(recCandyBar.candysStack.slice(0, to))

                newCandyStack = newCandyStack.concat(recCandyBar.candysStack.slice(from, from + 1))
                newCandyStack = newCandyStack.concat(recCandyBar.candysStack.slice(to, from))

                if (from + 1 < recCandyBar.candysStack.length)
                    newCandyStack = newCandyStack.concat(recCandyBar.candysStack.slice(from + 1, recCandyBar.candysStack.length))
            }

            recCandyBar.candysStack = newCandyStack
        }

        onPluginActivated:
        {
            var candys = []

            for (var candy in recCandyBar.candys)
                if (recCandyBar.candys[candy].pluginId == pluginId)
                {
                    var cand = {}

                    for (var prop in recCandyBar.candys[candy])
                        if (prop == "isActivated")
                            cand["isActivated"] = true
                        else
                            cand[prop] = recCandyBar.candys[candy][prop]

                    candys = candys.concat([cand])
                    recCandyBar.candysStack = recCandyBar.candysStack.concat([candys[candy]])
                }
                else
                    candys = candys.concat([recCandyBar.candys[candy]])

            recCandyBar.candys = candys
        }

        onPluginDeactivated:
        {
            var candys = []
            var candysStack = []

            for (var candy in recCandyBar.candys)
                if (recCandyBar.candys[candy].pluginId == pluginId)
                {
                    var cand = {}

                    for (var prop in recCandyBar.candys[candy])
                        if (prop == "isActivated")
                            cand["isActivated"] = false
                        else
                            cand[prop] = recCandyBar.candys[candy][prop]

                    candys = candys.concat([cand])
                }
                else
                {
                    candys = candys.concat([recCandyBar.candys[candy]])

                    if (recCandyBar.candys[candy].isActivated)
                        candysStack = candysStack.concat([candys[candy]])
                }

            recCandyBar.candys = candys
            recCandyBar.candysStack = candysStack

            if (cdvCandys.isStackView)
                cdvCandys.updateCandys(recCandyBar.candysStack)
        }
    }

    Rectangle
    {
        id: recCandyBarControls
        height: 100
        color: "#00000000"
        anchors.left: parent.left
        anchors.right: parent.right

        Rectangle
        {
            id: recCandyBarControlsBackGround
            width: recCandyBarControls.height
            height: recCandyBarControls.width
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            rotation: 90

            gradient: Gradient
            {
                GradientStop
                {
                    position: 0
                    color: "#000000"
                }

                GradientStop
                {
                    position: 0.5
                    color: "#1f1f1f"
                }

                GradientStop
                {
                    position: 1
                    color: "#000000"
                }
            }
        }

        Spaces
        {
            id: spcCandys
            anchors.bottom: cbxCategory.top
            anchors.bottomMargin: 8
            anchors.horizontalCenter: parent.horizontalCenter

            Component.onCompleted: spcCandys.updateSpaces(["Candys", "Candy Stack"])

            onSpaceSelected:
            {
                cdvCandys.isStackView = index == 0? false: true
                cdvCandys.updateCandys(index == 0? recCandyBar.candys: recCandyBar.candysStack)
            }
        }

        ComboBox
        {
            id: cbxCategory
            width: 256
            height: 24
            anchors.rightMargin: 8
            anchors.leftMargin: 8
            anchors.bottomMargin: 8
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.left: parent.left

            Component.onCompleted: cbxCategory.updateOptions(recCandyBar.listCategories())
            onItemSelected: cdvCandys.showCategory = value
        }
    }
}
