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

#include <QImage>
#include <QtPlugin>
#include <QStringList>
#include <QMouseEvent>
#include <QPushButton>

/// Plugin template.
class Plugin: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString id READ id)
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

    public:
        typedef enum _PluginType
        {
            PluginUnknown,
            PluginAudioEffect,
            PluginVideoEffect,
            PluginShell,
            PluginStream
        } PluginType;

        // Common methods.

        /// Returns the unique plugin identifier.
        ///
        /// \return The unique plugin identifier.
        virtual QString id() = 0;

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

        /// This function is called after Plugin::setConfigs().
        /// This method executes the initialization code for the plugin.
        virtual void begin() = 0;

        /// This function is called after Plugin::configs(), and before unload the plugin.
        /// This method executes the finalization code for the plugin.
        virtual void end() = 0;

        /// Calls the configuration dialog of the plugin.
        virtual void configure() = 0;

        /// This method is called before Plugin::end().
        /// Must return all significant data that the plugin wants to reload again.
        ///
        /// \return Plugin configurations.
        virtual QVariant configs() = 0;

        /// This method is called before Plugin::begin().
        /// Set all configurations presaved with Plugin::configs().
        ///
        /// \param configs Plugin configurations.
        virtual void setConfigs(QVariant configs) = 0;

        /// Capture a frame from a device.
        ///
        /// \param id Unique device identifier.
        ///
        /// \return The captured frame.
        virtual QImage frame(QString deviceId) = 0;

        /// Returns the frame size for the device.
        ///
        /// \param id Unique device identifier.
        ///
        /// \return The frame size.
        virtual QSize frameSize(QString deviceId) = 0;

        // Effects

        /// Returns \b true if the plugin requires 3D accelerated graphics card, \b else false.
        ///
        /// \retval true if requires 3D accelerated graphics card.
        /// \retval false if has not.
        virtual bool is3D() = 0;

        /// This function receives a frame and applies an effect on it.
        ///
        /// \param image The image to will be applied the effect.
        ///
        /// \return height The image with the applied effect.
        virtual QImage render(QString spaceId, const QImage &image) = 0;

        // Drivers

        /// Returns a list of available devices id.
        ///
        /// \return List of devices id.
        virtual QStringList captureDevices() = 0;

        /// \brief Returns a brief description for a device.
        ///
        /// \param id Unique device identifier.
        ///
        /// \return Device description.
        virtual QString deviceSummary(QString deviceId) = 0;

        /// Enable a device.
        ///
        /// \param id Unique device identifier.
        ///
        /// \retval true if was enabled.
        /// \retval false if was not enabled.
        virtual bool enableDevice(QString deviceId) = 0;

        /// Disable a device.
        ///
        /// \param id Unique device identifier.
        ///
        /// \retval true if was disabled.
        /// \retval false if was not disabled.
        virtual bool disableDevice(QString deviceId) = 0;

        /// Indicates if device is active.
        ///
        /// \param id Unique device identifier.
        ///
        /// \retval true if device is active.
        /// \retval false if device is not active.
        virtual bool isDeviceActive(QString deviceId) = 0;

        // Shells

        /// Returns a pointer to the GUI Widget.
        ///
        /// \return Pointer to the GUI Widget.
        virtual QWidget *widget() = 0;

        virtual QSize viewPortSize() = 0;

        virtual QString showPreview() = 0;

        // Streamming

    signals:
        // Drivers

        /// This signal is emited when a device is added or removed.
        void devicesModified();

        // Shells

        void viewPortSizeChanged(QSize size);
        void mouseDoubleClicked(QMouseEvent *event);
        void mousePositionChanged(QMouseEvent *event);
        void mousePressed(QMouseEvent *event);
        void mouseReleased(QMouseEvent *event);
        void toggleEditMode();
        void deviceMoved(qint32 from, qint32 to);

        /// This signal is emited when the user wants to save the current frame to a file.
        void takePicture();

        /// This signal is emited when the user wants to start video recording, if already recording stop it.
        void startStopRecord();

        void deviceEnabled(QString deviceId);
        void deviceDisabled(QString deviceId);

        /// This signal is emited when the user activate a plugin.
        ///
        /// \param pluginId The plugin to activate.
        void setEffect(QString pluginId, QString spaceId);

        /// This signal is emited when the user deactivate a plugin.
        ///
        /// \param pluginId The plugin to deactivate.
        void unsetEffect(QString pluginId, QString spaceId);

        /// This signal is emited when the user changes the index of a plugin.
        ///
        /// \param from The old index position of the plugin.
        /// \param to The new index position of the plugin.
        void pluginMoved(QString spaceId, qint32 from, qint32 to);

        /// This signal is emited when the user wants to configure a plugin.
        ///
        /// \param pluginId The plugin to configure.
        void pluginConfigureClicked(QString pluginId);

        /// This signal is emited when the user wants to configure a device.
        ///
        /// \param deviceId The device to configure.
        void deviceConfigureClicked(QString deviceId);

        /// This signal is emited when the GUI is closed.
        void closed();

        // Streamming

        void rosterChanged(QVariant roster);
        void stateChanged(int state);

    public slots:
        // Common methods.

        virtual void setFrame(QString deviceId, const QImage &frame) = 0;
        virtual void setFrameSize(QString deviceId, const QSize &size) = 0;

        // Effects

        virtual void addSpace(QString spaceId, QSize frameSize) = 0;
        virtual void removeSpace(QString spaceId) = 0;

        virtual void mouseDoubleClickEvent(QString spaceId, QMouseEvent *event) = 0;
        virtual void mouseMoveEvent(QString spaceId, QMouseEvent *event) = 0;
        virtual void mousePressEvent(QString spaceId, QMouseEvent *event) = 0;
        virtual void mouseReleaseEvent(QString spaceId, QMouseEvent *event) = 0;

        // Shells

        virtual void setPreview(const QImage &frame) = 0;

        /// \brief Set the devices to be selected by the user in the GUI.
        ///
        /// \param devices Devices info list.
        virtual void updateDevices(const QList<QVariant> &devices, const QStringList &activeSpaces) = 0;

        /// \brief Set the plugins to be selected by the user in the GUI.
        ///
        /// \param plugins Plugins info list.
        virtual void updatePlugins(const QList<QVariant> &plugins) = 0;

        virtual void setControlButtons(QPushButton *toggleMaximizedButton, QPushButton *scaleAndRotateButton) = 0;
        virtual void moveDevice(qint32 from, qint32 to) = 0;

        // Streamming
};

#endif // PLUGIN_H
