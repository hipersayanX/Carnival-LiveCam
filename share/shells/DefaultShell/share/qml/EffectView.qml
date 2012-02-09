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
    id: recEffectView
    width: 152
    height: 384
    color: "#00000000"
    property bool isStackView: false
    property string showCategory: "All"

    signal pluginConfigureClicked(string pluginId)
    signal pluginActivated(string pluginId)
    signal pluginDeactivated(string pluginId)
    signal pluginMoved(int from, int to)

    function updateEffects(effects)
    {
        lsmEffects.clear()

        for (var effect in effects)
        {
            var newEffect = {}

            for (var prop in effects[effect])
                newEffect["prop" + prop.charAt(0).toUpperCase() + prop.slice(1)] = effects[effect][prop]

            lsmEffects.append(newEffect)
        }

        lsvEffects.currentIndex = 0
        recEffectView.updateHeight()
    }

    function updateHeight()
    {
        if (lsvEffects.currentItem && lsvEffects.contentHeight < 0)
            lsvEffects.contentHeight = lsvEffects.currentItem.children[0].height * lsvEffects.count

        recEffectView.height = lsvEffects.contentHeight
    }

    function collapseAll()
    {
        var prevIndex = lsvEffects.currentIndex

        for (var effect = 0; effect < lsmEffects.count; effect++)
        {
            lsvEffects.currentIndex = effect
            lsvEffects.currentItem.children[0].isExpanded = false
            lsvEffects.currentItem.children[0].anchors.horizontalCenterOffset = 0
        }

        lsvEffects.currentIndex = prevIndex
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
            var tmpNewMaxValue = Math.ceil(lsvEffects.contentHeight / lsvEffects.height - 1)

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

        onBeginMove: recEffectView.collapseAll()

        onHeightChanged: updateValue()

        Component.onCompleted: updateValue()

        onValueChanged:
        {
            var index = Math.ceil((value - sldScroll.minValue) * (lsvEffects.count - 1) / (sldScroll.maxValue - sldScroll.minValue))
            lsvEffects.positionViewAtIndex(index, ListView.Beginning)
        }
    }

    ListView
    {
        id: lsvEffects
        interactive: false
        snapMode: ListView.SnapToItem
        anchors.right: sldScroll.left
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.top: parent.top

        function pluginIndex(pluginId)
        {
            var prevIndex = lsvEffects.currentIndex

            for (var effect = 0; effect < lsmEffects.count; effect++)
            {
                lsvEffects.currentIndex = effect

                if (lsvEffects.currentItem.children[0].pluginId == pluginId)
                {
                    lsvEffects.currentIndex = prevIndex

                    return effect
                }
            }

            lsvEffects.currentIndex = prevIndex

            return -1
        }

        model: ListModel
        {
            id: lsmEffects
        }

        delegate: Component
        {
            Rectangle
            {
                width: recEffectView.width - sldScroll.width
                height: cndEffect.height
                color: "#00000000"

                Effect
                {
                    id: cndEffect
                    visible: recEffectView.showCategory == "All" || recEffectView.showCategory == cndEffect.category? true: false
                    height: cndEffect.visible? 104: 0
                    isStacked: recEffectView.isStackView
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
                        oldIndex = lsvEffects.pluginIndex(cndEffect.pluginId)
                        cndEffect.oldPositionY = mouseY
                    }

                    onMove:
                    {
                        cndEffect.newIndex = Math.round((mouseY - cndEffect.oldPositionY) * (lsvEffects.count / lsvEffects.contentHeight) + cndEffect.oldIndex)

                        if (cndEffect.newIndex < 0)
                            cndEffect.newIndex = 0

                        if (cndEffect.newIndex >= lsvEffects.count)
                            cndEffect.newIndex = lsvEffects.count - 1

                        if (cndEffect.newIndex != cndEffect.oldIndex)
                        {
                            lsmEffects.move(cndEffect.oldIndex, cndEffect.newIndex, 1)
                            recEffectView.pluginMoved(cndEffect.oldIndex, cndEffect.newIndex)
                            cndEffect.oldIndex = cndEffect.newIndex
                        }
                    }

                    onExpandedClicked:
                    {
                        var expanded = cndEffect.isExpanded
                        recEffectView.collapseAll()
                        cndEffect.isExpanded = expanded

                        if (cndEffect.isExpanded)
                            cndEffect.anchors.horizontalCenterOffset = - (cndEffect.width - cndEffect.originalContentWidth) / 2
                        else
                            cndEffect.anchors.horizontalCenterOffset = 0
                    }

                    onConfigureClicked: recEffectView.pluginConfigureClicked(cndEffect.pluginId)
                    onActivated: recEffectView.pluginActivated(cndEffect.pluginId)
                    onDeactivated: recEffectView.pluginDeactivated(cndEffect.pluginId)
                    Component.onCompleted: cndEffect.originalContentWidth = cndEffect.width
                }
            }
        }
    }
}
