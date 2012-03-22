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
 *
 * Snow fall plugin
 */

#include <QtDebug>

#include "../include/snowfall.h"

QString SnowFall::author()
{
    return "Gonzalo Exequiel Pedone";
}

QString SnowFall::mail()
{
    return "hipersayan.x@gmail.com";
}

QString SnowFall::website()
{
    return "hipersayanx.blogspot.com";
}

QString SnowFall::category()
{
    return "Snow";
}

QString SnowFall::id()
{
    return "plugin.SnowFall";
}

QString SnowFall::license()
{
    return "GPLv3";
}

QString SnowFall::name()
{
    return "Snow Fall";
}

QString SnowFall::summary()
{
    return "Falling snow flakes";
}

QString SnowFall::thumbnail()
{
    return "../../../../../share/plugins/SnowFall/share/thumbnail-128x96.png";
}

bool SnowFall::is3D()
{
    return false;
}

QString SnowFall::version()
{
    return "1.0.0";
}

bool SnowFall::isConfigurable()
{
    return true;
}

void SnowFall::begin()
{
    this->config.setSnow(&this->snow);
}

void SnowFall::addSpace(QString spaceId, QSize frameSize)
{
    if (this->snow.contains(spaceId))
        return;

    this->snow[spaceId] = Snow(frameSize.width(),
                               frameSize.height(),
                               75,   // Number of Flakes
                               0.12, // Acceleration
                               10,   // Direction
                               0.1,  // Rand Factor
                               100,  // Border
                               0.2,  // Min Z
                               1,    // Max Z
                               0.1,  // Min Scale
                               0.2); // MaxScale
}

void SnowFall::removeSpace(QString spaceId)
{
    this->snow.remove(spaceId);
}

QImage SnowFall::render(QString spaceId, const QImage &image)
{
    if (this->snow.contains(spaceId))
    {
        QImage frame = this->snow[spaceId].render(image);

        this->snow[spaceId].next();

        return frame;
    }

    return image;
}

void SnowFall::end()
{
}

void SnowFall::configure()
{
    this->config.exec();
}

QVariant SnowFall::configs()
{
    QHash<QString, QVariant> snowConfigs;

    foreach (QString spaceId, this->snow.keys())
    {
        QList<QVariant> snowConfig;

        snowConfig << QVariant(this->snow[spaceId].width())
                   << QVariant(this->snow[spaceId].height())
                   << QVariant(this->snow[spaceId].nFlakes())
                   << QVariant(this->snow[spaceId].acceleration())
                   << QVariant(this->snow[spaceId].direction())
                   << QVariant(this->snow[spaceId].randFactor())
                   << QVariant(this->snow[spaceId].border())
                   << QVariant(this->snow[spaceId].minZ())
                   << QVariant(this->snow[spaceId].maxZ())
                   << QVariant(this->snow[spaceId].minScale())
                   << QVariant(this->snow[spaceId].maxScale());

        snowConfigs[spaceId] = QVariant(snowConfig);
    }

    return QVariant(snowConfigs);
}

void SnowFall::setConfigs(QVariant configs)
{
    QHash<QString, QVariant> snowConfigs = configs.toHash();

    this->snow.clear();

    foreach (QString spaceId, snowConfigs.keys())
    {
        QList<QVariant> config = snowConfigs[spaceId].toList();

        this->snow[spaceId] = Snow(config[0].toInt(),     // Width
                                   config[1].toInt(),     // Height
                                   config[2].toInt(),     // Number of Flakes
                                   config[3].toFloat(),   // Acceleration
                                   config[4].toInt(),     // Direction
                                   config[5].toFloat(),   // Rand Factor
                                   config[6].toInt(),     // Border
                                   config[7].toFloat(),   // Min Z
                                   config[8].toFloat(),   // Max Z
                                   config[9].toFloat(),   // Min Scale
                                   config[10].toFloat()); // MaxScale
    }
}

void SnowFall::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
}

void SnowFall::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
}

void SnowFall::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
}

void SnowFall::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
}

Q_EXPORT_PLUGIN2(SnowFall, SnowFall)
