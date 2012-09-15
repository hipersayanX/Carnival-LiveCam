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
#
# Snow fall plugin

CONFIG += plugin

DESTDIR += $$PWD

HEADERS += \
    include/plugin.h \
    include/element.h \
    include/particle.h \
    include/particlefall.h \
    include/particlefallelement.h

MOC_DIR += $$PWD/build

OBJECTS_DIR += $$PWD/build

OTHER_FILES += \
    share/thumbnail-128x96.png \
    share/sprites/flake0.png \
    share/sprites/flake1.png \
    share/sprites/flake2.png \
    share/sprites/flake3.png

QT += core gui

RCC_DIR += $$PWD/build

SOURCES += \
    src/particle.cpp \
    src/particlefall.cpp \
    src/particlefallelement.cpp

TEMPLATE = lib

UI_DIR += $$PWD/build

FORMS +=
