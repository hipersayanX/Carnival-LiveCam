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

#include <QtGui>
#include <QtPlugin>

/// Plugin template.
class Plugin: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString pluginId READ pluginId)
    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(QString version READ version)
    Q_PROPERTY(QString summary READ summary)
    Q_PROPERTY(PluginType type READ type)
    Q_PROPERTY(QString category READ category)
    Q_PROPERTY(QString thumbnail READ thumbnail)
    Q_PROPERTY(QString license READ license)
    Q_PROPERTY(QString author READ author)
    Q_PROPERTY(QString website READ website)
    Q_PROPERTY(QString mail READ mail)
    Q_PROPERTY(bool isConfigurable READ isConfigurable)
    Q_PROPERTY(QVariant configs READ configs WRITE setConfigs RESET resetConfigs)

    public:
        typedef enum _PluginType
        {
            PluginUnknown,
            PluginDriver,
            PluginShell,
            PluginAudioEffect,
            PluginVideoEffect,
            PluginStream
        } PluginType;

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
        virtual PluginType type() = 0;

        /// Returns the category of the plugin.
        ///
        /// \return Category of the plugin.
        virtual QString category() = 0;

        /// Returns the thumbnail of the plugin.
        ///
        /// \return thumbnail of the plugin.
        virtual QImage thumbnail() = 0;

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

        /// This method is called before Plugin::end().
        /// Must return all significant data that the plugin wants to reload again.
        ///
        /// \return Plugin configurations.
        virtual QVariant configs() = 0;

    signals:
        void setPipeline(QString pipeline);
        void sendFrame(const QImage &frame);

    public slots:
        /// This function is called after Plugin::setConfigs().
        /// This method executes the initialization code for the plugin.
        virtual void begin() = 0;

        /// This function is called after Plugin::configs(), and before unload the plugin.
        /// This method executes the finalization code for the plugin.
        virtual void end() = 0;

        /// Calls the configuration dialog of the plugin.
        virtual void configure() = 0;

        /// This method is called before Plugin::begin().
        /// Set all configurations presaved with Plugin::configs().
        ///
        /// \param configs Plugin configurations.
        virtual void setConfigs(const QVariant &configs) = 0;

        virtual void resetConfigs() = 0;

        void recvFrame(const QImage &frame);
};

#endif // PLUGIN_H
