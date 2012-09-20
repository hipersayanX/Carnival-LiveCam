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

include(share/plugins/plugins.pro)

CONFIG += qt

DESTDIR += $$PWD

HEADERS += \
    include/core/core.h \
    include/plugin/plugin.h \
    include/plugin/element.h \
    include/plugin/plugininfo.h \
    include/plugin/pluginmanager.h \
    include/shell/shell.h \
    include/shell/shellfactory.h \
    include/shell/shellmanager.h \
    include/shell/shellinfo.h

INSTALLS += target \
            docs \
            data

MOC_DIR += $$PWD/build

OBJECTS_DIR += $$PWD/build

QT += core gui

RCC_DIR += $$PWD/build

SOURCES += src/main.cpp \
    src/core/core.cpp \
    src/plugin/plugininfo.cpp \
    src/plugin/pluginmanager.cpp \
    src/shell/shellmanager.cpp \
    src/shell/shellinfo.cpp

TEMPLATE += app

UI_DIR += $$PWD/build

# Build rules

docs.commands = qdoc3 $$TARGET.qdocconf
docs.files += share/docs/*
docs.path += /usr/share/docs/$$TARGET

# Install rules

target.files += $$TARGET
target.path += /usr/bin/$$TARGET

data.files = share/*
data.path = /usr/share/$$TARGET
