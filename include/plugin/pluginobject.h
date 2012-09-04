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

#ifndef PLUGINOBJECT_H
#define PLUGINOBJECT_H

#include <QtGui>

/// Plugin template.
class PluginObject: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVariant configs READ configs WRITE setConfigs RESET resetConfigs)

    public:
        /// This method is called before Plugin::end().
        /// Must return all significant data that the plugin wants to reload again.
        ///
        /// \return Plugin configurations.
        virtual QVariant configs() = 0;

    signals:
        // Output Channels
        void oVideo(QImage *frame, QStringList receiverObjectName);
        //void oAudio(???, QStringList receiverObjectName);
        void oEvent(QEvent *event, QStringList receiverObjectName);

        void setPipeline(QString pipeline);
        void getPluginList();

    public slots:
        // Input Channels
        virtual void iVideo(QImage *frame, QString senderObjectName) = 0;
        //virtual void iAudio(???, QString senderObjectName) = 0;
        virtual void iEvent(QEvent *event, QString senderObjectName) = 0;

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

        virtual void setPluginList(QList<QVariant> list) = 0;
};

#endif // PLUGINOBJECT_H
