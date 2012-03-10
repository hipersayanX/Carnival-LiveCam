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
 */

#ifndef SHELL_H
#define SHELL_H

#include <QImage>
#include <QMouseEvent>
#include <QPushButton>

/*!
  \class Shell

  \brief Shell template.
 */
class Shell: public QObject
{
    Q_OBJECT

    public:
        /*!
          \fn QString Shell::id()

          \return The unique shell identifier.

          \brief Returns the unique shell identifier.
         */
        virtual QString id() = 0;

        /*!
          \fn QString Shell::name()

          \return Human readable name of the shell.

          \brief Return the shell name.
         */
        virtual QString name() = 0;

        /*!
          \fn QString Shell::version()

          \return Version of the shell.

          \brief Returns the shell version.
         */
        virtual QString version() = 0;

        /*!
          \fn QString Shell::summary()

          \return Description of the shell.

          \brief Returns a brief description of the shell.
         */
        virtual QString summary() = 0;

        /*!
          \fn QString Shell::type()

          \return Type of the shell.

          \brief Returns the type of the shell.
         */
        virtual QString type() = 0;

        /*!
          \fn QString Shell::thumbnail()

          \return thumbnail of the shell.

          \brief Returns the thumbnail of the shell.
         */
        virtual QString thumbnail() = 0;

        /*!
          \fn QString Shell::license()

          \return License of the shell.

          \brief Returns the license of the shell.
         */
        virtual QString license() = 0;

        /*!
          \fn QString Shell::author()

          \return Author of the shell.

          \brief Returns the author of the shell.
         */
        virtual QString author() = 0;

        /*!
          \fn QString Shell::website()

          \return Website of the shell.

          \brief Returns the website were is hosted the shell.
         */
        virtual QString website() = 0;

        /*!
          \fn QString Shell::mail()

          \return Mail of the author of the shell.

          \brief Returns the mail of the author of the shell.
         */
        virtual QString mail() = 0;

        /*!
          \fn bool Shell::isConfigurable()

          \retval true if has a configuration.
          \retval false if has not a configuration.

          \brief Returns \b true if the shell has a configuration dialog, \b else false.
         */
        virtual bool isConfigurable() = 0;

        /*!
          \fn void Shell::begin()

          \brief This function is called after Shell::setConfigs().

          This method executes the initialization code for the shell.
         */
        virtual void begin() = 0;

        /*!
          \fn void Shell::end()

          \brief This function is called after Shell::configs(), and before unload the shell.

          This method executes the finalization code for the shell.
         */
        virtual void end() = 0;

        /*!
          \fn bool Shell::configure()

          \brief Calls the configuration dialog of the shell.
         */
        virtual void configure() = 0;

        /*!
          \fn QVariant Shell::configs()

          \return Shell configurations.

          \brief This method is called before Shell::end().

          Must return all significant data that the shell wants to reload again.
         */
        virtual QVariant configs() = 0;

        /*!
          \fn void Shell::setConfigs(QVariant configs)

          \param configs Shell configurations.

          \brief This method is called before Shell::begin().

          Set all configurations presaved with Shell::configs().
         */
        virtual void setConfigs(QVariant configs) = 0;

        /*!
          \fn QWidget *Shell::widget()

          \return Pointer to the GUI Widget.

          \brief Returns a pointer to the GUI Widget.
         */
        virtual QWidget *widget() = 0;

        virtual QSize viewPortSize() = 0;

        virtual QString showPreview() = 0;

    public slots:
        /*!
          \fn void Shell::setFrame(const QImage &frame)

          \param frame The frame to show.

          \brief Set the frame to be showed in the GUI.
         */
        virtual void setFrame(const QImage &frame) = 0;

        virtual void setPreview(const QImage &frame) = 0;

        /*!
          \fn void Shell::updateDevices(const QList<QVariant> &devices, const QStringList &activeSpaces)

          \param devices Devices info list.

          \brief Set the devices to be selected by the user in the GUI.
         */
        virtual void updateDevices(const QList<QVariant> &devices, const QStringList &activeSpaces) = 0;

        /*!
          \fn void Shell::updatePlugins(const QList<QVariant> &plugins)

          \param plugins Plugins info list.

          \brief Set the plugins to be selected by the user in the GUI.
         */
        virtual void updatePlugins(const QList<QVariant> &plugins) = 0;

        virtual void setControlButtons(QPushButton *toggleMaximizedButton, QPushButton *scaleAndRotateButton) = 0;
        virtual void moveDevice(qint32 from, qint32 to) = 0;

    signals:
        void viewPortSizeChanged(QSize size);
        void mouseDoubleClicked(QMouseEvent *event);
        void mousePositionChanged(QMouseEvent *event);
        void mousePressed(QMouseEvent *event);
        void mouseReleased(QMouseEvent *event);
        void toggleEditMode();
        void enabledDeviceMoved(qint32 from, qint32 to);

        /*!
          \fn void Shell::takePicture()

          \brief This signal is emited when the user wants to save the current frame to a file.
         */
        void takePicture();

        /*!
          \fn void Shell::startStopRecord()

          \brief This signal is emited when the user wants to start video recording, if already recording stop it.
         */
        void startStopRecord();

        void deviceEnable(QString deviceId);
        void deviceDisable(QString deviceId);

        /*!
          \fn void Shell::pluginActivated(QString pluginId)

          \param pluginId The plugin to activate.

          \brief This signal is emited when the user activate a plugin.
         */
        void setEffect(QString pluginId, QString spaceId);

        /*!
          \fn void Shell::pluginDeactivated(QString pluginId)

          \param pluginId The plugin to deactivate.

          \brief This signal is emited when the user deactivate a plugin.
         */
        void unsetEffect(QString pluginId, QString spaceId);

        /*!
          \fn void Shell::pluginMoved(qint32 from, qint32 to)

          \param from The old index position of the plugin.
          \param to The new index position of the plugin.

          \brief This signal is emited when the user changes the index of a plugin.
         */
        void pluginMoved(QString spaceId, qint32 from, qint32 to);

        /*!
          \fn void Shell::pluginConfigureClicked(QString pluginId)

          \param pluginId The plugin to configure.

          \brief This signal is emited when the user wants to configure a plugin.
         */
        void pluginConfigureClicked(QString pluginId);

        /*!
          \fn void Shell::deviceConfigureClicked(QString deviceId)

          \param deviceId The device to configure.

          \brief This signal is emited when the user wants to configure a device.
         */
        void deviceConfigureClicked(QString deviceId);

        /*!
          \fn void Shell::closed()

          \brief This signal is emited when the GUI is closed.
         */
        void closed();
};

#endif // SHELL_H
