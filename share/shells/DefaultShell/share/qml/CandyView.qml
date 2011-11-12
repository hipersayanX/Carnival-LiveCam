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
    id: recCandyView
    width: 152
    height: 384
    color: "#00000000"
    property bool isStackView: false
    property string showCategory: "All"

    signal pluginConfigureClicked(string pluginId)
    signal pluginActivated(string pluginId)
    signal pluginDeactivated(string pluginId)
    signal pluginMoved(int from, int to)

    function updateCandys(candys)
    {
        lsmCandys.clear()

        for (var candy in candys)
        {
            var newCandy = {}

            for (var prop in candys[candy])
                newCandy["prop" + prop.charAt(0).toUpperCase() + prop.slice(1)] = candys[candy][prop]

            lsmCandys.append(newCandy)
        }

        lsvCandys.currentIndex = 0
        recCandyView.updateHeight()
    }

    function updateHeight()
    {
        if (lsvCandys.currentItem && lsvCandys.contentHeight < 0)
            lsvCandys.contentHeight = lsvCandys.currentItem.children[0].height * lsvCandys.count

        recCandyView.height = lsvCandys.contentHeight
    }

    function collapseAll()
    {
        var prevIndex = lsvCandys.currentIndex

        for (var candy = 0; candy < lsmCandys.count; candy++)
        {
            lsvCandys.currentIndex = candy
            lsvCandys.currentItem.children[0].isExpanded = false
            lsvCandys.currentItem.children[0].anchors.horizontalCenterOffset = 0
        }

        lsvCandys.currentIndex = prevIndex
    }

    Slider
    {
        id: sldScroll
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        showUpDown: true

        function updateValue()
        {
            var tmpNewMaxValue = Math.ceil(lsvCandys.contentHeight / lsvCandys.height - 1)

            if (tmpNewMaxValue < sldScroll.minValue)
                sldScroll.maxValue = sldScroll.minValue
            else
                sldScroll.maxValue = tmpNewMaxValue

            var newValue = sldScroll.minValue

            if (sldScroll.maxValue != sldScroll.minValue)
            {
                var k = (tmpNewMaxValue - sldScroll.minValue) / (sldScroll.maxValue - sldScroll.minValue)
                newValue = Math.ceil(k * (sldScroll.value - sldScroll.minValue) + sldScroll.minValue)
            }

            sldScroll.setValue(newValue)
            sldScroll.visible = sldScroll.maxValue > sldScroll.minValue? true: false
            sldScroll.width = sldScroll.visible? 16: 0
        }

        onBeginMove: recCandyView.collapseAll()

        onHeightChanged: updateValue()

        Component.onCompleted: updateValue()

        onValueChanged:
        {
            var index = Math.ceil((value - sldScroll.minValue) * (lsvCandys.count - 1) / (sldScroll.maxValue - sldScroll.minValue))
            lsvCandys.positionViewAtIndex(index, ListView.Beginning)
        }
    }

    ListView
    {
        id: lsvCandys
        interactive: false
        snapMode: ListView.SnapToItem
        anchors.right: sldScroll.left
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.top: parent.top

        function pluginIndex(pluginId)
        {
            var prevIndex = lsvCandys.currentIndex

            for (var candy = 0; candy < lsmCandys.count; candy++)
            {
                lsvCandys.currentIndex = candy

                if (lsvCandys.currentItem.children[0].pluginId == pluginId)
                {
                    lsvCandys.currentIndex = prevIndex

                    return candy
                }
            }

            lsvCandys.currentIndex = prevIndex

            return -1
        }

        model: ListModel
        {
            id: lsmCandys
        }

        delegate: Component
        {
            Rectangle
            {
                width: recCandyView.width - sldScroll.width
                height: cndCandy.height
                color: "#00000000"

                Candy
                {
                    id: cndCandy
                    visible: recCandyView.showCategory == "All" || recCandyView.showCategory == cndCandy.category? true: false
                    height: cndCandy.visible? 104: 0
                    isStacked: recCandyView.isStackView
                    is3D: propIs3D
                    isActivated: propIsActivated
                    isConfigurable: propIsConfigurable
                    pluginId: propPluginId
                    thumbnail: propThumbnail
                    name: propName
                    version: propVersion
                    summary: propSummary
                    category: propCategory
                    license: propLicense
                    author: propAuthor
                    website: propWebsite
                    mail: propMail
                    anchors.horizontalCenter: parent.horizontalCenter
                    property real originalContentWidth: 0
                    property real oldIndex: 0
                    property real newIndex: 0
                    property real oldPositionY: 0

                    onBeginMove:
                    {
                        oldIndex = lsvCandys.pluginIndex(cndCandy.pluginId)
                        cndCandy.oldPositionY = mouseY
                    }

                    onMove:
                    {
                        cndCandy.newIndex = Math.round((mouseY - cndCandy.oldPositionY) * (lsvCandys.count / lsvCandys.contentHeight) + cndCandy.oldIndex)

                        if (cndCandy.newIndex < 0)
                            cndCandy.newIndex = 0

                        if (cndCandy.newIndex >= lsvCandys.count)
                            cndCandy.newIndex = lsvCandys.count - 1

                        if (cndCandy.newIndex != cndCandy.oldIndex)
                        {
                            lsmCandys.move(cndCandy.oldIndex, cndCandy.newIndex, 1)
                            recCandyView.pluginMoved(cndCandy.oldIndex, cndCandy.newIndex)
                            cndCandy.oldIndex = cndCandy.newIndex
                        }
                    }

                    onExpandedClicked:
                    {
                        var expanded = cndCandy.isExpanded
                        recCandyView.collapseAll()
                        cndCandy.isExpanded = expanded

                        if (cndCandy.isExpanded)
                            cndCandy.anchors.horizontalCenterOffset = - (cndCandy.width - cndCandy.originalContentWidth) / 2
                        else
                            cndCandy.anchors.horizontalCenterOffset = 0
                    }

                    onConfigureClicked: recCandyView.pluginConfigureClicked(cndCandy.pluginId)
                    onActivated: recCandyView.pluginActivated(cndCandy.pluginId)
                    onDeactivated: recCandyView.pluginDeactivated(cndCandy.pluginId)
                    Component.onCompleted: cndCandy.originalContentWidth = cndCandy.width
                }
            }
        }
    }
}
