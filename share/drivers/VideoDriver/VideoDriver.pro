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
# Image driver for linux

CONFIG += plugin

DESTDIR += $$PWD

HEADERS += \
    include/driver.h \
    include/driverfactory.h \
    include/config.h \
    include/videodriver.h \
    include/videodriverfactory.h

LIBS += \
    -lopencv_calib3d \
    -lopencv_contrib \
    -lopencv_core \
    -lopencv_features2d \
    -lopencv_flann \
    -lopencv_gpu \
    -lopencv_highgui \
    -lopencv_imgproc \
    -lopencv_legacy \
    -lopencv_ml \
    -lopencv_objdetect \
    -lopencv_video

MOC_DIR += $$PWD/build

OBJECTS_DIR += $$PWD/build

QT += core gui

RCC_DIR += $$PWD/build

SOURCES += \
    src/config.cpp \
    src/videodriver.cpp \
    src/videodriverfactory.cpp

TEMPLATE = lib

UI_DIR += $$PWD/build

FORMS += \
    share/ui/config.ui

RESOURCES += \
    share/icons.qrc
