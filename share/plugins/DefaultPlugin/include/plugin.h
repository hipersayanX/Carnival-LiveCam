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

#ifndef PLUGIN_H
#define PLUGIN_H

#include <QImage>
#include <QtPlugin>

/*!
  \class Plugin

  \brief Plugin template.
 */
class Plugin
{
    public:
        /*!
          \fn QString Plugin::id()

          \return The unique plugin identifier.

          \brief Returns the unique plugin identifier.
         */
        virtual QString id() = 0;

        /*!
          \fn QString Plugin::name()

          \return Human readable name of the plugin.

          \brief Return the plugin name.
         */
        virtual QString name() = 0;

        /*!
          \fn QString Plugin::version()

          \return Version of the plugin.

          \brief Returns the plugin version.
         */
        virtual QString version() = 0;

        /*!
          \fn QString Plugin::summary()

          \return Description of the plugin.

          \brief Returns a brief description of the plugin.
         */
        virtual QString summary() = 0;

        /*!
          \fn QString Plugin::category()

          \return Category of the plugin.

          \brief Returns the category of the plugin.
         */
        virtual QString category() = 0;

        /*!
          \fn QString Plugin::thumbnail()

          \return thumbnail of the plugin.

          \brief Returns the thumbnail of the plugin.
         */
        virtual QString thumbnail() = 0;

        /*!
          \fn QString Plugin::license()

          \return License of the plugin.

          \brief Returns the license of the plugin.
         */
        virtual QString license() = 0;

        /*!
          \fn QString Plugin::author()

          \return Author of the plugin.

          \brief Returns the author of the plugin.
         */
        virtual QString author() = 0;

        /*!
          \fn QString Plugin::website()

          \return Website of the plugin.

          \brief Returns the website were is hosted the plugin.
         */
        virtual QString website() = 0;

        /*!
          \fn QString Plugin::mail()

          \return Mail of the author of the plugin.

          \brief Returns the mail of the author of the plugin.
         */
        virtual QString mail() = 0;

        /*!
          \fn bool Plugin::is3D()

          \retval true if requires 3D accelerated graphics card.
          \retval false if has not.

          \brief Returns \b true if the plugin requires 3D accelerated graphics card, \b else false.
         */
        virtual bool is3D() = 0;

        /*!
          \fn bool Plugin::isConfigurable()

          \retval true if has a configuration.
          \retval false if has not a configuration.

          \brief Returns \b true if the plugin has a configuration dialog, \b else false.
         */
        virtual bool isConfigurable() = 0;

        /*!
          \fn void Plugin::begin()

          \brief This function is called after Plugin::setConfigs().

          This method executes the initialization code for the plugin.
         */
        virtual void begin() = 0;

        /*!
          \fn void Plugin::resize(qint32 width, qint32 height)

          \param width New width of the frame.
          \param height New height of the frame.

          \brief This function is called on frame size changed.
         */
        virtual void resize(qint32 width, qint32 height) = 0;

        /*!
          \fn QImage Plugin::render(const QImage &image)

          \param image The image to will be applied the effect.

          \return height The image with the applied effect.

          \brief This function receives a frame and applies an effect on it.
         */
        virtual QImage render(const QImage &image) = 0;

        /*!
          \fn void Plugin::end()

          \brief This function is called after Plugin::configs(), and before unload the plugin.

          This method executes the finalization code for the plugin.
         */
        virtual void end() = 0;

        /*!
          \fn bool Plugin::configure()

          \brief Calls the configuration dialog of the plugin.
         */
        virtual void configure() = 0;

        /*!
          \fn QVariant Plugin::configs()

          \return Plugin configurations.

          \brief This method is called before Plugin::end().

          Must return all significant data that the plugin wants to reload again.
         */
        virtual QVariant configs() = 0;

        /*!
          \fn void Plugin::setConfigs(QVariant configs)

          \param configs Plugin configurations.

          \brief This method is called before Plugin::begin().

          Set all configurations presaved with Plugin::configs().
         */
        virtual void setConfigs(QVariant configs) = 0;
};

Q_DECLARE_INTERFACE(Plugin, "plugins.PluginInterface")

#endif // PLUGIN_H
