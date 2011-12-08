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
    this->snow = new Snow(640, // width
                          480, // height
                          this->config.spbNFlakes->value(),
                          this->config.spbAcceleration->value(),
                          this->config.spbDirection->value(),
                          this->config.spbRandFactor->value(),
                          this->config.spbBorder->value(),
                          this->config.spbMinZ->value(),
                          this->config.spbMaxZ->value(),
                          this->config.spbMinScale->value(),
                          this->config.spbMaxScale->value());

    this->config.setSnow(this->snow);
}

void SnowFall::resize(int width, int height)
{
    this->snow->resize(width, height);
}

QImage SnowFall::render(const QImage &image)
{
    QImage frame = this->snow->render(image);

    this->snow->next();

    return frame;
}

void SnowFall::end()
{
    delete this->snow;
}

void SnowFall::configure()
{
    this->config.exec();
}

QVariant SnowFall::configs()
{
    QList<QVariant> snowConfigs;

    snowConfigs << QVariant(this->snow->nFlakes())
                << QVariant(this->snow->acceleration())
                << QVariant(this->snow->direction())
                << QVariant(this->snow->randFactor())
                << QVariant(this->snow->border())
                << QVariant(this->snow->minZ())
                << QVariant(this->snow->maxZ())
                << QVariant(this->snow->minScale())
                << QVariant(this->snow->maxScale());

    return QVariant(snowConfigs);
}

void SnowFall::setConfigs(QVariant configs)
{
    QList<QVariant> snowConfigs = configs.toList();

    this->config.spbNFlakes->setValue(snowConfigs[0].toInt());
    this->config.spbAcceleration->setValue(snowConfigs[1].toFloat());
    this->config.spbDirection->setValue(snowConfigs[2].toInt());
    this->config.spbRandFactor->setValue(snowConfigs[3].toFloat());
    this->config.spbBorder->setValue(snowConfigs[4].toInt());
    this->config.spbMinZ->setValue(snowConfigs[5].toFloat());
    this->config.spbMaxZ->setValue(snowConfigs[6].toFloat());
    this->config.spbMinScale->setValue(snowConfigs[7].toFloat());
    this->config.spbMaxScale->setValue(snowConfigs[8].toFloat());
}

Q_EXPORT_PLUGIN2(SnowFall, SnowFall)
