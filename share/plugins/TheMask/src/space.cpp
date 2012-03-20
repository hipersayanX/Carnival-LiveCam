#include "../include/space.h"

Space::Space(QObject *parent): QObject(parent)
{
    this->m_maskImage = QImage();
    this->m_frameSize = QSize();
}

Space::Space(const Space &object):
    QObject(object.parent()),
    m_maskImage(object.m_maskImage),
    m_frameSize(object.m_frameSize)
{
}

Space::Space(QImage maskFileName,
             QSize frameSize):
    m_maskImage(maskFileName),
    m_frameSize(frameSize)
{
}

Space& Space::operator =(const Space &other)
{
    if (this != &other)
    {
        this->m_maskImage = other.m_maskImage;
        this->m_frameSize = other.m_frameSize;
    }

    return *this;
}

QImage Space::maskImage()
{
    return this->m_maskImage;
}

QSize Space::frameSize()
{
    return this->m_frameSize;
}

void Space::setMaskImage(QImage value)
{
    this->m_maskImage = value;
}

void Space::setFrameSize(QSize value)
{
    this->m_frameSize = value;
}

void Space::resetMaskImage()
{
    this->m_maskImage = QImage();
}

void Space::resetFrameSize()
{
    this->m_frameSize = QSize();
}
