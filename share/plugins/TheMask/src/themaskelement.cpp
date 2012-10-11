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

#include <vector>

#include "themaskelement.h"

TheMaskElement::TheMaskElement()
{
    this->resetHaarCascadeFile();
    this->resetSprite();
}

QString TheMaskElement::haarCascadeFile()
{
    return this->m_haarCascadeFile;
}

QString TheMaskElement::sprite()
{
    return this->m_sprite;
}

bool TheMaskElement::start()
{
    return true;
}

bool TheMaskElement::stop()
{
    return true;
}

void TheMaskElement::setHaarCascadeFile(QString haarCascadeFile)
{
    this->m_haarCascadeFile = haarCascadeFile;
    this->m_cascadeClassifier.load(this->m_haarCascadeFile.toUtf8().constData());
}

void TheMaskElement::setSprite(QString sprite)
{
    this->m_sprite = sprite;
    this->m_maskImage = QImage(this->m_sprite);
}

void TheMaskElement::resetHaarCascadeFile()
{
    this->setHaarCascadeFile("share/plugins/TheMask/share/haars/haarcascade_frontalface_alt.xml");
}

void TheMaskElement::resetSprite()
{
    this->setSprite(":/share/masks/cow.png");
}

void TheMaskElement::iVideo(QImage *frame)
{
    if (this->m_maskImage.isNull() || this->m_cascadeClassifier.empty())
    {
        emit(oVideo(frame));

        return;
    }

    float scale = 4;

    QImage smallFrame(frame->scaled(frame->size() / scale));

    cv::Mat matFrame(smallFrame.height(),
                     smallFrame.width(),
                     CV_8UC3,
                     (uchar *) smallFrame.bits(),
                     smallFrame.bytesPerLine());

    std::vector<cv::Rect> vecFaces;

    cv::cvtColor(matFrame, matFrame, CV_BGR2GRAY);
    cv::equalizeHist(matFrame, matFrame);
    this->m_cascadeClassifier.detectMultiScale(matFrame, vecFaces);

    if (vecFaces.size() < 1)
    {
        emit(oVideo(frame));

        return;
    }

    this->m_curFrame = *frame;
    QPainter painter;

    painter.begin(&this->m_curFrame);

    for (std::vector<cv::Rect>::const_iterator face = vecFaces.begin(); face != vecFaces.end(); face++)
        painter.drawImage(QRect(face->x * scale,
                                face->y * scale,
                                face->width * scale,
                                face->height * scale),
                                this->m_maskImage);

    painter.end();

    emit(oVideo(&this->m_curFrame));
}

void TheMaskElement::iAudio(QByteArray *frame)
{
    Q_UNUSED(frame)
}

void TheMaskElement::configure()
{
}

void TheMaskElement::setManager(QObject *manager)
{
    Q_UNUSED(manager)
}
