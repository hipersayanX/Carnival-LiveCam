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

#include <QtGui>

#include "../include/core/core.h"
/*!
  \mainpage About Carnival LiveCam

  \image html snowexample.png This is an example of the snowplugin.

  \section intro Introduction

  <b>Carnival LiveCam</b> is a project that bring augmented reality experience
  to end users in the simplest way possible.
  <b>Carnival LiveCam</b> can apply various 2D and 3D effects, face recognition,
  take pictures and record video, and much more.
  Its main technologies are <i>Qt</i> which is the heart of the software,
  <i>OpenCV</i> which offers functionality for face recognition, shapes, colors
  and movement among other things, <i>OpenSceneGraph</i> an advanced and popular
  OpenGL-based graphic engine that allows complex 3D scenes rendering with
  relative ease, and  <i>FFmpeg</i>, the most advanced transcoding framework of
  the world allows record video and audio in several possible formats.

  \section requirements Requirements

  - <a target="_bank" href="https://qt.nokia.com/">Qt</a> >= 4.7.x
  - <a target="_bank" href="http://www.openscenegraph.org/projects/osg">OpenSceneGraph</a> >= 3.0.x
  - <a target="_bank" href="http://opencv.willowgarage.com/wiki/">OpenCV</a> >= 2.3.x
  - <a target="_bank" href="http://ffmpeg.org/">FFmpeg</a>
  - <a target="_bank" href="http://code.google.com/p/ffmpegthumbnailer/">ffmpegthumbnailer</a> >= 2.x.x
  - <a target="_bank" href="http://www.stack.nl/~dimitri/doxygen/">Doxygen</a> >= 1.7.5.x
  - <a target="_bank" href="http://www.graphviz.org/">Graphviz</a> >= 2.28.x
  - <a target="_bank" href="http://www.tug.org/texlive/">Texlive-bin</a> >= 2011.x

  \section buildinstall Build and Install

  <b>Carnival LiveCam</b> is in a very early stage of development and is not recommended for installation, and it works only in <i>GNU/Linux</i>.
  To build <b>Carnival LiveCam</b> and their plugins, follow the instructions below:

<pre>
  ./build_all.sh
</pre>

  \section license License

  \verbatim
Carnival LiveCam, Augmented reality made easy.
Copyright (C) 2011  Gonzalo Exequiel Pedone

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with This program.  If not, see <http://www.gnu.org/licenses/>.
  \endverbatim
*/

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Core core;

    return app.exec();
}
