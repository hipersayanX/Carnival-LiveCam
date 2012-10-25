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
    error("commons.pri file not found.")
}

CONFIG += qt

HEADERS += \
    include/plugin/plugin.h \
    include/plugin/element.h \
    include/plugin/pipeline.h \
    include/plugin/mainpipeline.h

INCLUDEPATH += include

QT += core gui widgets

SOURCES += \
    src/main.cpp \
    src/plugin/mainpipeline.cpp

TARGET = $${COMMONS_TARGET}

TEMPLATE += app

# Install rules

INSTALLS += target

target.files = $$TARGET
target.path = $${COMMONS_TARGET_INSTALL_PATH}
