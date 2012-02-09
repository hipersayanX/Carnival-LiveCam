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
    id: recEffectBar
    width: 192
    height: 512
    property variant effects: []
    property variant effectsStack: []

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

    function updateEffects(effects)
    {
        recEffectBar.effects = effects
        cdvEffects.updateEffects(recEffectBar.effects)
        cbxCategory.updateOptions(recEffectBar.listCategories())
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

        for (var effect in recEffectBar.effects)
            if (categories.indexOf(recEffectBar.effects[effect].category) < 0)
                categories.push(recEffectBar.effects[effect].category)

        categories.sort(recEffectBar.sortAlphaNoCase)

        return ["All"].concat(categories)
    }

    EffectView
    {
        id: cdvEffects
        objectName: "EffectView"
        showCategory: "All"
        anchors.top: recEffectBarControls.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left

        onPluginMoved:
        {
            var newEffectStack = []

            if (from < to)
            {
                if (from > 0)
                    newEffectStack = newEffectStack.concat(recEffectBar.effectsStack.slice(0, from))

                newEffectStack = newEffectStack.concat(recEffectBar.effectsStack.slice(from + 1, to + 1))
                newEffectStack = newEffectStack.concat(recEffectBar.effectsStack.slice(from, from + 1))

                if (to + 1 < recEffectBar.effectsStack.length)
                    newEffectStack = newEffectStack.concat(recEffectBar.effectsStack.slice(to + 1, recEffectBar.effectsStack.length))
            }
            else
            {
                if (to > 0)
                    newEffectStack = newEffectStack.concat(recEffectBar.effectsStack.slice(0, to))

                newEffectStack = newEffectStack.concat(recEffectBar.effectsStack.slice(from, from + 1))
                newEffectStack = newEffectStack.concat(recEffectBar.effectsStack.slice(to, from))

                if (from + 1 < recEffectBar.effectsStack.length)
                    newEffectStack = newEffectStack.concat(recEffectBar.effectsStack.slice(from + 1, recEffectBar.effectsStack.length))
            }

            recEffectBar.effectsStack = newEffectStack
        }

        onPluginActivated:
        {
            var effects = []

            for (var effect in recEffectBar.effects)
                if (recEffectBar.effects[effect].pluginId == pluginId)
                {
                    var cand = {}

                    for (var prop in recEffectBar.effects[effect])
                        if (prop == "isActivated")
                            cand["isActivated"] = true
                        else
                            cand[prop] = recEffectBar.effects[effect][prop]

                    effects = effects.concat([cand])
                    recEffectBar.effectsStack = recEffectBar.effectsStack.concat([effects[effect]])
                }
                else
                    effects = effects.concat([recEffectBar.effects[effect]])

            recEffectBar.effects = effects
        }

        onPluginDeactivated:
        {
            var effects = []
            var effectsStack = []

            for (var effect in recEffectBar.effects)
                if (recEffectBar.effects[effect].pluginId == pluginId)
                {
                    var cand = {}

                    for (var prop in recEffectBar.effects[effect])
                        if (prop == "isActivated")
                            cand["isActivated"] = false
                        else
                            cand[prop] = recEffectBar.effects[effect][prop]

                    effects = effects.concat([cand])
                }
                else
                {
                    effects = effects.concat([recEffectBar.effects[effect]])

                    if (recEffectBar.effects[effect].isActivated)
                        effectsStack = effectsStack.concat([effects[effect]])
                }

            recEffectBar.effects = effects
            recEffectBar.effectsStack = effectsStack

            if (cdvEffects.isStackView)
                cdvEffects.updateEffects(recEffectBar.effectsStack)
        }
    }

    Rectangle
    {
        id: recEffectBarControls
        height: 100
        color: "#00000000"
        anchors.left: parent.left
        anchors.right: parent.right

        Rectangle
        {
            id: recEffectBarControlsBackGround
            width: recEffectBarControls.height
            height: recEffectBarControls.width
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
            id: spcEffects
            anchors.bottom: cbxCategory.top
            anchors.bottomMargin: 8
            anchors.horizontalCenter: parent.horizontalCenter

            Component.onCompleted: spcEffects.updateSpaces(["Effects", "Effect Stack"])

            onSpaceSelected:
            {
                cdvEffects.isStackView = index == 0? false: true
                cdvEffects.updateEffects(index == 0? recEffectBar.effects: recEffectBar.effectsStack)
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

            Component.onCompleted: cbxCategory.updateOptions(recEffectBar.listCategories())
            onItemSelected: cdvEffects.showCategory = value
        }
    }
}
