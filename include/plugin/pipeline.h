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

#ifndef PIPELINE_H
#define PIPELINE_H

#include <QtCore>

class Element;

class Pipeline: public QObject
{
    Q_OBJECT
    Q_ENUMS(PipelineRoutingMode)

    Q_PROPERTY(QStringList pluginsPaths
               READ pluginsPaths
               WRITE setPluginsPaths
               RESET resetPluginsPaths)

    Q_PROPERTY(QVariantMap pluginList
               READ pluginList)

    Q_PROPERTY(PipelineRoutingMode pipelineRoutingMode
               READ pipelineRoutingMode
               WRITE setPipelineRoutingMode
               RESET resetPipelineRoutingMode)

    /// Enumerator for pipeline diff operations
    public:
        /// Actions to do if some element doesn't exist
        enum PipelineRoutingMode
        {
            NoCheck, // Build the pipeline as is.
            Fail,    // If an element doesn't exist return a void graph.
            Remove,  // If an element doesn't exist return a graph without the
                     // element and it's connections.
            Force    // If an element doesn't exist try to connect all elements
                     // connected to the lost element.
        };

        Q_INVOKABLE virtual void loadPlugins() = 0;
        Q_INVOKABLE virtual QStringList pluginsPaths() = 0;
        Q_INVOKABLE virtual QVariantMap pluginList() = 0;
        Q_INVOKABLE virtual PipelineRoutingMode pipelineRoutingMode() = 0;

        Q_INVOKABLE virtual Element *elementById(QString elementId) = 0;
        Q_INVOKABLE virtual Element *elementByName(QString elementName) = 0;
        Q_INVOKABLE virtual bool startElement(QString elementId) = 0;
        Q_INVOKABLE virtual bool stopElement(QString elementId) = 0;
        Q_INVOKABLE virtual QString addElement(QString pluginId) = 0;
        Q_INVOKABLE virtual bool removeElement(QString elementId) = 0;
        Q_INVOKABLE virtual bool setElementProperty(QString elementId, QString property, QVariant value) = 0;
        Q_INVOKABLE virtual bool resetElementProperty(QString elementId, QString property) = 0;

        Q_INVOKABLE virtual bool connectElementsSS(QString senderId, QString signal, QString receiverId, QString slot) = 0;
        Q_INVOKABLE virtual bool connectElementsSS(QString senderId, QString signal, const QObject *receiver, const char *slot) = 0;
        Q_INVOKABLE virtual bool connectElementsSS(const QObject *sender, const char *signal, QString receiverId, QString slot) = 0;
        Q_INVOKABLE virtual bool disconnectElementsSS(QString senderId, QString signal, QString receiverId, QString slot) = 0;
        Q_INVOKABLE virtual bool disconnectElementsSS(QString senderId, QString signal, const QObject *receiver, const char *slot) = 0;
        Q_INVOKABLE virtual bool disconnectElementsSS(const QObject *sender, const char *signal, QString receiverId, QString slot) = 0;

        Q_INVOKABLE virtual bool connectElements(QString senderId, QString receiverId) = 0;
        Q_INVOKABLE virtual bool connectElements(QString senderId, const QObject *receiver, const char *slot) = 0;
        Q_INVOKABLE virtual bool connectElements(const QObject *sender, const char *signal, QString receiverId) = 0;
        Q_INVOKABLE virtual bool disconnectElements(QString senderId, QString receiverId) = 0;
        Q_INVOKABLE virtual bool disconnectElements(QString senderId, const QObject *receiver, const char *slot) = 0;
        Q_INVOKABLE virtual bool disconnectElements(const QObject *sender, const char *signal, QString receiverId) = 0;

    public slots:
        virtual void setPipeline(QString pipeline) = 0;
        virtual void setPluginsPaths(QStringList pluginsPaths) = 0;
        virtual void setPipelineRoutingMode(PipelineRoutingMode mode) = 0;
        virtual void resetPluginsPaths() = 0;
        virtual void resetPipelineRoutingMode() = 0;
};

#endif // PIPELINE_H
