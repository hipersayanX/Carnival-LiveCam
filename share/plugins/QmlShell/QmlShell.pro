# Carnival LiveCam, Augmented reality made easy.
# Copyright (C) 2011-2012  Gonzalo Exequiel Pedone
#
# Carnival LiveCam is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Carnival LiveCam is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Carnival LiveCam.  If not, see <http://www.gnu.org/licenses/>.
#
# Email   : hipersayan DOT x AT gmail DOT com
# Web-Site: https://github.com/hipersayanX/Carnival-LiveCam

exists(commons.pri) {
    include(commons.pri)
} else {
    exists(../../../commons.pri) {
        include(../../../commons.pri)
    } else {
        error("commons.pri file not found.")
    }
}

CONFIG += plugin

HEADERS += \
    include/element.h \
    include/pipeline.h \
    include/plugin.h \
    include/qmlshellelement.h \
    include/qmlshell.h \
    include/qmlshellgui.h \
    include/imageprovider.h


INCLUDEPATH += include

OTHER_FILES = \
    QmlShell.json \
    share/qml/main.qml \
    share/qml/About.qml \
    share/qml/Button.qml \
    share/qml/ComboBox.qml \
    share/qml/Device.qml \
    share/qml/Devices.qml \
    share/qml/DialogBox.qml \
    share/qml/Effects.qml \
    share/qml/IconBar.qml \
    share/qml/ListWidget.qml \
    share/qml/Slider.qml \
    share/qml/Spaces.qml \
    share/qml/Window.qml \
    share/qml/WindowControls.qml

QT += core gui widgets quick

RESOURCES += \
    QmlShell.qrc

SOURCES += \
    src/qmlshellelement.cpp \
    src/qmlshell.cpp \
    src/qmlshellgui.cpp \
    src/imageprovider.cpp

TEMPLATE = lib

# Install rules

INSTALLS += target \
            data

target.files = $$TARGET
target.path = $${COMMONS_PLUGINS_INSTALL_PATH}/$$TARGET

data.files = share/*
data.path = $${COMMONS_PLUGINS_INSTALL_PATH}/$$TARGET/share
