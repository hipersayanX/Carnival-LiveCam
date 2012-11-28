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
    include/plugin.h \
    include/element.h \
    include/pipeline.h \
    include/themask.h \
    include/themaskelement.h

INCLUDEPATH += include

unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += opencv
}

OTHER_FILES += \
    TheMask.json \
    share/thumbnail-128x96.png \
    share/masks/cow.png \
    share/haars/aGest.xml \
    share/haars/haarcascade_eye_tree_eyeglasses.xml \
    share/haars/haarcascade_frontalface_alt.xml \
    share/haars/haarcascade_frontalface_alt_tree.xml \
    share/haars/haarcascade_mcs_eyepair_big.xml

QT += core gui

RESOURCES += \
    TheMask.qrc

SOURCES += \
    src/themask.cpp \
    src/themaskelement.cpp

TEMPLATE = lib

# Install rules

INSTALLS += target \
            data

target.files = $$TARGET
target.path = $${COMMONS_PLUGINS_INSTALL_PATH}/$$TARGET

data.files = share/*
data.path = $${COMMONS_PLUGINS_INSTALL_PATH}/$$TARGET/share
