# Carnival LiveCam, Augmented reality made easy.
# Copyright (C) 2011  Gonzalo Exequiel Pedone
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with This program.  If not, see <http://www.gnu.org/licenses/>.
#
# Email   : hipersayan DOT x AT gmail DOT com
# Web-Site: http://hipersayanx.blogspot.com/
#
# QML shell plugin

CONFIG += plugin

DESTDIR += $$PWD

HEADERS += \
    include/shell.h \
    include/shellfactory.h \
    include/defaultshell.h \
    include/defaultshellfactory.h \
    include/webcamimageprovider.h \
    include/gui.h

MOC_DIR += $$PWD/build

OBJECTS_DIR += $$PWD/build

OTHER_FILES += \
    share/images/icons/about.svg \
    share/images/icons/author.svg \
    share/images/icons/category.svg \
    share/images/icons/close.svg \
    share/images/icons/configure.svg \
    share/images/icons/effects.svg \
    share/images/icons/fullscreen.svg \
    share/images/icons/license.svg \
    share/images/icons/mail.svg \
    share/images/icons/maximize.svg \
    share/images/icons/micoff.svg \
    share/images/icons/micon.svg \
    share/images/icons/minimize.svg \
    share/images/icons/move.svg \
    share/images/icons/nostayontop.svg \
    share/images/icons/picture.svg \
    share/images/icons/sound.svg \
    share/images/icons/stayontop.svg \
    share/images/icons/stoprec.svg \
    share/images/icons/video.svg \
    share/images/icons/web.svg \
    share/images/icons/webcam.svg \
    share/images/icons/windowed.svg \
    share/images/pixmaps/thumbnail-128x96.png \
    share/images/pixmaps/windowcontrols.svg \
    share/qml/Button.qml \
    share/qml/Effect.qml \
    share/qml/EffectBar.qml \
    share/qml/EffectView.qml \
    share/qml/ComboBox.qml \
    share/qml/Device.qml \
    share/qml/Devices.qml \
    share/qml/DialogBox.qml \
    share/qml/IconBar.qml \
    share/qml/ListWidget.qml \
    share/qml/Slider.qml \
    share/qml/SoundSlider.qml \
    share/qml/Spaces.qml \
    share/qml/Window.qml \
    share/qml/WindowControls.qml \
    share/qml/main.qml \
    share/qml/About.qml

QT += core gui declarative

RCC_DIR += $$PWD/build

SOURCES += \
    src/defaultshell.cpp \
    src/defaultshellfactory.cpp \
    src/webcamimageprovider.cpp \
    src/gui.cpp

TEMPLATE = lib

UI_DIR += $$PWD/build
