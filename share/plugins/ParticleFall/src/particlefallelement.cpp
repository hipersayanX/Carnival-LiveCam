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

#include <cstdlib>

#include "particlefallelement.h"

ParticleFallElement::ParticleFallElement()
{
    this->resetNParticles();
    this->resetPadding();
    this->resetMinSpeed();
    this->resetMaxSpeed();
    this->resetMinDirection();
    this->resetMaxDirection();
    this->resetMinSize();
    this->resetMaxSize();
    this->resetSprites();
    this->resetInc();
}

int ParticleFallElement::nParticles()
{
    return this->m_nParticles;
}

int ParticleFallElement::padding()
{
    return this->m_padding;
}

float ParticleFallElement::minSpeed()
{
    return this->m_minSpeed;
}

float ParticleFallElement::maxSpeed()
{
    return this->m_maxSpeed;
}

float ParticleFallElement::minDirection()
{
    return this->m_minDirection;
}

float ParticleFallElement::maxDirection()
{
    return this->m_maxDirection;
}

QSize ParticleFallElement::minSize()
{
    return this->m_minSize;
}

QSize ParticleFallElement::maxSize()
{
    return this->m_maxSize;
}

QStringList ParticleFallElement::sprites()
{
    return this->m_sprites;
}

float ParticleFallElement::inc()
{
    return this->m_inc;
}

bool ParticleFallElement::start()
{
    return true;
}

bool ParticleFallElement::stop()
{
    return false;
}

void ParticleFallElement::setNParticles(int nParticles)
{
    this->m_nParticles = nParticles;

    QRect rect(-this->m_padding,
               -this->m_padding,
               this->m_curFrameSize.width() + 2 * this->m_padding,
               this->m_curFrameSize.height() + 2 * this->m_padding);

    while (this->m_particles.length() < this->m_nParticles)
        this->m_particles << Particle(rect,
                                      this->m_minSpeed,
                                      this->m_maxSpeed,
                                      this->m_minDirection,
                                      this->m_maxDirection,
                                      this->m_minSize,
                                      this->m_maxSize,
                                      &this->m_pixmaps,
                                      this->m_inc);

    while (this->m_particles.length() > this->m_nParticles)
        this->m_particles.removeLast();
}

void ParticleFallElement::setPadding(int padding)
{
    this->m_padding = padding;

    QRect rect(-this->m_padding,
               -this->m_padding,
               this->m_curFrameSize.width() + 2 * this->m_padding,
               this->m_curFrameSize.height() + 2 * this->m_padding);

    for (int i = 0; i < this->m_particles.length(); i++)
        this->m_particles[i].setRect(rect);
}

void ParticleFallElement::setMinSpeed(float minSpeed)
{
    this->m_minSpeed = minSpeed;

    for (int i = 0; i < this->m_particles.length(); i++)
        this->m_particles[i].setMinSpeed(this->m_minSpeed);
}

void ParticleFallElement::setMaxSpeed(float maxSpeed)
{
    this->m_maxSpeed = maxSpeed;

    for (int i = 0; i < this->m_particles.length(); i++)
        this->m_particles[i].setMaxSpeed(this->m_maxSpeed);
}

void ParticleFallElement::setMinDirection(float minDirection)
{
    this->m_minDirection = minDirection;

    for (int i = 0; i < this->m_particles.length(); i++)
        this->m_particles[i].setMinDirection(this->m_minDirection);
}

void ParticleFallElement::setMaxDirection(float maxDirection)
{
    this->m_maxDirection = maxDirection;

    for (int i = 0; i < this->m_particles.length(); i++)
        this->m_particles[i].setMaxDirection(this->m_maxDirection);
}

void ParticleFallElement::setMinSize(QSize minSize)
{
    this->m_minSize = minSize;

    for (int i = 0; i < this->m_particles.length(); i++)
        this->m_particles[i].setMinSize(this->m_minSize);
}

void ParticleFallElement::setMaxSize(QSize maxSize)
{
    this->m_maxSize = maxSize;

    for (int i = 0; i < this->m_particles.length(); i++)
        this->m_particles[i].setMaxSize(this->m_maxSize);
}

void ParticleFallElement::setSprites(QStringList sprites)
{
    this->m_sprites = sprites;

    QList<QImage> pixmaps;

    foreach (QString sprite, this->m_sprites)
        pixmaps << QImage(sprite);

    this->m_pixmaps = pixmaps;
}

void ParticleFallElement::setInc(float inc)
{
    this->m_inc = inc;

    for (int i = 0; i < this->m_particles.length(); i++)
        this->m_particles[i].setInc(this->m_inc);
}

void ParticleFallElement::resetNParticles()
{
    this->setNParticles(250);
}

void ParticleFallElement::resetPadding()
{
    this->setPadding(64);
}

void ParticleFallElement::resetMinSpeed()
{
    this->setMinSpeed(5);
}

void ParticleFallElement::resetMaxSpeed()
{
    this->setMaxSpeed(20);
}

void ParticleFallElement::resetMinDirection()
{
    this->setMinDirection(-80);
}

void ParticleFallElement::resetMaxDirection()
{
    this->setMaxDirection(80);
}

void ParticleFallElement::resetMinSize()
{
    this->setMinSize(QSize(8, 8));
}

void ParticleFallElement::resetMaxSize()
{
    this->setMaxSize(QSize(64, 64));
}

void ParticleFallElement::resetSprites()
{
    QStringList sprites;

    for (int i = 0; i < 4; i++)
        sprites << QString(":/share/sprites/flake%1.png").arg(i);

    this->setSprites(sprites);
}

void ParticleFallElement::resetInc()
{
    this->setInc(0.01);
}

QImage ParticleFallElement::byteArrayToImage(QByteArray *ba)
{
    if (!ba)
        return QImage();

    QDataStream iDataStream(ba, QIODevice::ReadOnly);
    int type;

    iDataStream >> type;

    if (type != ARGB32)
        return QImage();

    int width;
    int height;

    iDataStream >> width >> height;

    QByteArray pixels(4 * width * height, 0);
    iDataStream.readRawData(pixels.data(), pixels.size());

    return QImage((const uchar *) pixels.constData(), width, height, QImage::Format_ARGB32);
}

void ParticleFallElement::imageToByteArray(QImage *image, QByteArray *ba)
{
    if (!image || !ba)
        return;

    QDataStream oDataStream(ba, QIODevice::WriteOnly);

    oDataStream << ARGB32 << image->width() << image->height();
    oDataStream.writeRawData((const char *) image->constBits(), image->byteCount());
}

void ParticleFallElement::iStream(QByteArray *data)
{
    QImage iFrame = this->byteArrayToImage(data);

    if (iFrame.isNull())
        return;

    QSize oldFrameSize = this->m_curFrameSize;
    this->m_curFrameSize = iFrame.size();

    if (this->m_curFrameSize != oldFrameSize)
        this->setPadding(this->padding());

    QPainter painter;

    painter.begin(&iFrame);

    for (int particle = 0; particle < this->m_particles.length(); particle++)
        painter.drawImage(this->m_particles[particle].pos(),
                          this->m_particles[particle].sprite());

    painter.end();

    this->imageToByteArray(&iFrame, &this->m_bCurFrame);

    emit(oStream(&this->m_bCurFrame));

    for (int particle = 0; particle < this->m_particles.length(); particle++)
        this->m_particles[particle]++;
}

void ParticleFallElement::iEvent(QEvent *event)
{
    foreach (Element *element, this->m_srcs)
        element->iEvent(event);
}

void ParticleFallElement::setPipeline(Pipeline *pipeline)
{
    Q_UNUSED(pipeline)
}

void ParticleFallElement::setPeers(QList<Element *> srcs, QList<Element *> sinks)
{
    this->m_srcs = srcs;
    this->m_sinks = sinks;
}
