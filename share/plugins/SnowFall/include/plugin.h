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
 * Snow fall plugin
 */

#ifndef PLUGIN_H
#define PLUGIN_H

#include <QImage>
#include <QtPlugin>

class Plugin
{
    public:
        virtual QString author() = 0;
        virtual QString mail() = 0;
        virtual QString website() = 0;
        virtual QString category() = 0;
        virtual QString id() = 0;
        virtual QString license() = 0;
        virtual QString name() = 0;
        virtual QString summary() = 0;
        virtual QString  thumbnail() = 0;
        virtual bool is3D() = 0;
        virtual QString version() = 0;
        virtual bool isConfigurable() = 0;

        virtual void begin() = 0;
        virtual void resize(int width, int height) = 0;
        virtual QImage render(const QImage &image) = 0;
        virtual void end() = 0;
        virtual void configure() = 0;
};

Q_DECLARE_INTERFACE(Plugin, "plugins.PluginInterface")

#endif // PLUGIN_H
