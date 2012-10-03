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

#include "include/fxbin.h"

QString FxBin::pluginId()
{
    return "FxBin";
}

QString FxBin::name()
{
    return "Fx Bin";
}

QString FxBin::version()
{
    return "1.0.0";
}

QString FxBin::summary()
{
    return "Effects container and manager.";
}

QString FxBin::type()
{
    return "video";
}

QString FxBin::category()
{
    return "plugin";
}

QString FxBin::thumbnail()
{
    return "";
}

QString FxBin::license()
{
    return "GPLv3";
}

QString FxBin::author()
{
    return "Gonzalo Exequiel Pedone";
}

QString FxBin::website()
{
    return "https://github.com/hipersayanX/Carnival-LiveCam";
}

QString FxBin::mail()
{
    return "hipersayan DOT x AT gmail DOT com";
}

bool FxBin::isConfigurable()
{
    return false;
}

Element *FxBin::newElement()
{
    return new FxBinElement();
}

Q_EXPORT_PLUGIN2(FxBin, FxBin)
