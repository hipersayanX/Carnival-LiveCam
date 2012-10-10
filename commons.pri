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

isEmpty(COMMONS_PRI_INCLUDE) {
    COMMONS_APPNAME = "Carnival-LiveCam"
    COMMONS_TARGET = "Carnival-LiveCam"
    COMMONS_VERSION = 1.0.0

    unix {
        COMMONS_TARGET_INSTALL_PATH = /usr/bin
        COMMONS_DATA_INSTALL_PATH = /usr/share/$${COMMONS_TARGET}
        COMMONS_PLUGINS_INSTALL_PATH = $${COMMONS_DATA_INSTALL_PATH}/plugins
        COMMONS_DOCS_INSTALL_PATH = /usr/share/docs/$${COMMONS_TARGET}
        COMMONS_LICENSE_INSTALL_PATH = /usr/share/licenses/$${COMMONS_TARGET}
    }

    DESTDIR = .
    COMMONS_BUILD_PATH = build
    COMMONS_DEBUG_BUILD_PATH = $${COMMONS_BUILD_PATH}/debug
    COMMONS_RELEASE_BUILD_PATH = $${COMMONS_BUILD_PATH}/release

    CONFIG(debug, debug|release) {
        MOC_DIR = $${COMMONS_DEBUG_BUILD_PATH}
        OBJECTS_DIR = $${COMMONS_DEBUG_BUILD_PATH}
        RCC_DIR = $${COMMONS_DEBUG_BUILD_PATH}
        UI_DIR = $${COMMONS_DEBUG_BUILD_PATH}
    } else {
        MOC_DIR = $${COMMONS_RELEASE_BUILD_PATH}
        OBJECTS_DIR = $${COMMONS_RELEASE_BUILD_PATH}
        RCC_DIR = $${COMMONS_RELEASE_BUILD_PATH}
        UI_DIR = $${COMMONS_RELEASE_BUILD_PATH}
    }

    unix {
        # Enable support for C++11
        CONFIG += c++11
    }

    COMMONS_PRI_INCLUDE = 1
}
