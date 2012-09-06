// Copyright (C) 2012 Gonzalo Exequiel Pedone
//
// The following license applies only to THIS file.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//
// Email   : hipersayan DOT x AT gmail DOT com
// Web-Site: https://github.com/hipersayanX/Carnival-LiveCam

#ifndef PLUGIN_H
#define PLUGIN_H

#include <QtPlugin>

#include "element.h"

class Plugin
{
    public:
        /// Returns the unique plugin identifier.
        ///
        /// \return The unique plugin identifier.
        virtual QString pluginId() = 0;

        /// Return the plugin name.
        ///
        /// \return Human readable name of the plugin.
        virtual QString name() = 0;

        /// Returns the plugin version.
        ///
        /// \return Version of the plugin.
        virtual QString version() = 0;

        /// Returns a brief description of the plugin.
        ///
        /// \return Description of the plugin.
        virtual QString summary() = 0;

        /// Returns the type of the driver.
        ///
        /// \return Type of the driver.
        virtual QString type() = 0;

        /// Returns the category of the plugin.
        ///
        /// \return Category of the plugin.
        virtual QString category() = 0;

        /// Returns the thumbnail of the plugin.
        ///
        /// \return thumbnail of the plugin.
        virtual QString thumbnail() = 0;

        /// Returns the license of the plugin.
        ///
        /// \return License of the plugin.
        virtual QString license() = 0;

        /// Returns the author of the plugin.
        ///
        /// \return Author of the plugin.
        virtual QString author() = 0;

        /// Returns the website were is hosted the plugin.
        ///
        /// \return Website of the plugin.
        virtual QString website() = 0;

        /// Returns the mail of the author of the plugin.
        ///
        /// \return Mail of the author of the plugin.
        virtual QString mail() = 0;

        /// Returns \b true if the plugin has a configuration dialog, \b else false.
        ///
        /// \retval true if has a configuration.
        /// \retval false if has not a configuration.
        virtual bool isConfigurable() = 0;

        virtual Element *newObject() = 0;

        virtual ~Plugin() = 0;
};

Q_DECLARE_INTERFACE(Plugin, "CarnivalLiveCam.Plugin")

#endif // PLUGIN_H
