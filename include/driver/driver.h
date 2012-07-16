// Carnival LiveCam, Augmented reality made easy.
// Copyright (C) 2011-2012  Gonzalo Exequiel Pedone
//
// Carnival LiveCam is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Carnival LiveCam is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Carnival LiveCam.  If not, see <http://www.gnu.org/licenses/>.
//
// Email   : hipersayan DOT x AT gmail DOT com
// Web-Site: https://github.com/hipersayanX/Carnival-LiveCam

#ifndef DRIVER_H
#define DRIVER_H

#include <QImage>
#include <QStringList>

/*!
  \class Driver

  \brief Driver template.
 */
class Driver: public QObject
{
    Q_OBJECT

    public:
        /*!
          \fn QString Driver::id()

          \return The unique driver identifier.

          \brief Returns the unique driver identifier.
         */
        virtual QString id() = 0;

        /*!
          \fn QString Driver::name()

          \return Human readable name of the driver.

          \brief Return the driver name.
         */
        virtual QString name() = 0;

        /*!
          \fn QString Driver::version()

          \return Version of the driver.

          \brief Returns the driver version.
         */
        virtual QString version() = 0;

        /*!
          \fn QString Driver::summary()

          \return Description of the driver.

          \brief Returns a brief description of the driver.
         */
        virtual QString summary() = 0;

        /*!
          \fn QString Driver::type()

          \return Type of the driver.

          \brief Returns the type of the driver.
         */
        virtual QString type() = 0;

        /*!
          \fn QString Driver::icon()

          \return Icon of the driver.

          \brief Returns the file name of a representative driver icon.
         */
        virtual QString icon() = 0;

        /*!
          \fn QString Driver::license()

          \return License of the driver.

          \brief Returns the license of the driver.
         */
        virtual QString license() = 0;

        /*!
          \fn QString Driver::author()

          \return Author of the driver.

          \brief Returns the author of the driver.
         */
        virtual QString author() = 0;

        /*!
          \fn QString Driver::website()

          \return Website of the driver.

          \brief Returns the website were is hosted the driver.
         */
        virtual QString website() = 0;

        /*!
          \fn QString Driver::mail()

          \return Mail of the author of the driver.

          \brief Returns the mail of the author of the driver.
         */
        virtual QString mail() = 0;

        /*!
          \fn bool Driver::isConfigurable()

          \retval true if has a configuration.
          \retval false if has not a configuration.

          \brief Returns \b true if the driver has a configuration dialog, \b else false.
         */
        virtual bool isConfigurable() = 0;

        /*!
          \fn QStringList Driver::captureDevices()

          \return List of devices id.

          \brief Returns a list of available devices id.
         */
        virtual QStringList captureDevices() = 0;

        /*!
          \fn QString Driver::deviceSummary(QString id)

          \param id Unique device identifier.

          \return Device description.

          \brief Returns a brief description for a device.
         */
        virtual QString deviceSummary(QString id) = 0;

        /*!
          \fn QImage Driver::captureFrame(QString id)

          \param id Unique device identifier.

          \return The captured frame.

          \brief Capture a frame from a device.
         */
        virtual QImage captureFrame(QString id) = 0;

        /*!
          \fn QSize Driver::frameSize(QString id)

          \param id Unique device identifier.

          \return The frame size.

          \brief Returns the frame size for the device.
         */
        virtual QSize frameSize(QString id) = 0;

        /*!
          \fn void Driver::begin()

          \brief This function is called after Driver::setConfigs().

          This method executes the initialization code for the driver.
         */
        virtual void begin() = 0;

        /*!
          \fn void Driver::end()

          \brief This function is called after Driver::configs(), and before unload the driver.

          This method executes the finalization code for the driver.
         */
        virtual void end() = 0;

        /*!
          \fn bool Driver::disableDevice(QString id)

          \param id Unique device identifier.

          \retval true if was disabled.
          \retval false if was not disabled.

          \brief Disable a device.
         */
        virtual bool disableDevice(QString id) = 0;

        /*!
          \fn bool Driver::enableDevice(QString id)

          \param id Unique device identifier.

          \retval true if was enabled.
          \retval false if was not enabled.

          \brief Enable a device.
         */
        virtual bool enableDevice(QString id) = 0;

        /*!
          \fn bool Driver::isActive(QString id)

          \param id Unique device identifier.

          \retval true if device is active.
          \retval false if device is not active.

          \brief Indicates if device is active.
         */
        virtual bool isActive(QString id) = 0;

        /*!
          \fn bool Driver::configureDevice(QString id)

          \param id Unique device identifier.

          \brief Calls the configuration dialog of the device.
         */
        virtual void configureDevice(QString id) = 0;

        /*!
          \fn QVariant Driver::configs()

          \return Driver configurations.

          \brief This method is called before Driver::end().

          Must return all significant data that the driver wants to reload again.
         */
        virtual QVariant configs() = 0;

        /*!
          \fn void Driver::setConfigs(QVariant configs)

          \param configs Driver configurations.

          \brief This method is called before Driver::begin().

          Set all configurations presaved with Driver::configs().
         */
        virtual void setConfigs(QVariant configs) = 0;

    signals:
        /*!
          \fn void Driver::devicesModified()

          \brief This signal is emited when a device is added or removed.
         */
        void devicesModified();
};

#endif // DRIVER_H
