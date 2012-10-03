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

    COMMONS_PRI_EXISTS = 1
}

isEmpty(COMMONS_PRI_EXISTS) {
    exists(../commons.pri) {
        include(../commons.pri)

        COMMONS_PRI_EXISTS = 1
    }
}

CONFIG += qt

HEADERS += \
    ../include/core/core.h \
    ../include/plugin/plugin.h \
    ../include/plugin/element.h \
    ../include/plugin/plugininfo.h \
    ../include/plugin/pluginmanager.h \
    ../include/shell/shell.h \
    ../include/shell/shellfactory.h \
    ../include/shell/shellmanager.h \
    ../include/shell/shellinfo.h

INCLUDEPATH += ../include

QT += core gui

SOURCES += \
    main.cpp \
    core/core.cpp \
    plugin/plugininfo.cpp \
    plugin/pluginmanager.cpp \
    shell/shellmanager.cpp \
    shell/shellinfo.cpp

TARGET = $${COMMONS_TARGET}

TEMPLATE += app

# Install rules

INSTALLS += target

target.files = $$TARGET
target.path = $${COMMONS_TARGET_INSTALL_PATH}
