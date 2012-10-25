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

#ifndef ELEMENT_H
#define ELEMENT_H

#include <QtGui>

#include "pipeline.h"

/// Plugin template.
class Element: public QObject
{
    Q_OBJECT
    Q_ENUMS(StreamFormats)

    public:
        enum StreamFormats
        {
            ARGB32, // This is a image frame stored in 32-bit ARGB format (0xAARRGGBB).
            S16LE   // This is a PCM audio frame stored in signed 16-bit little-endian format.
        };

        /// This function is called after Plugin::setConfigs().
        /// This method executes the initialization code for the plugin.
        Q_INVOKABLE virtual bool start() = 0;

        /// This function is called after Plugin::configs(), and before unload the plugin.
        /// This method executes the finalization code for the plugin.
        Q_INVOKABLE virtual bool stop() = 0;

    signals:
        // Output Channel
        void oStream(QByteArray *data);
        void requestPipeline();

    public slots:
        // Input Channel
        virtual void iStream(QByteArray *data) = 0;
        virtual void setPipeline(Pipeline *pipeline) = 0;
};

#endif // ELEMENT_H
