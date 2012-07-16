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

#include <QPainter>
#include <QtDebug>

#include "../include/mask.h"

Mask::Mask(QObject *parent): QObject(parent)
{
    this->cascadeClassifier.load("share/plugins/TheMask/share/haars/haarcascade_frontalface_alt.xml");
}

void Mask::setMaskImage(QImage image)
{
    this->m_maskImage = image;
}

QImage Mask::render(const QImage &frame)
{
    if (this->m_maskImage.isNull())
        return frame;

    qreal scale = 4;
    QImage smallFrame(frame.scaled(frame.width() / scale, frame.height() / scale));
    cv::Mat matFrame = cv::Mat(smallFrame.height(), smallFrame.width(), CV_8UC3, (uchar *) smallFrame.bits(), smallFrame.bytesPerLine());
    std::vector<cv::Rect> vecFaces;

    cv::cvtColor(matFrame, matFrame, CV_BGR2GRAY);
    cv::equalizeHist(matFrame, matFrame);
    this->cascadeClassifier.detectMultiScale(matFrame, vecFaces);

    if (vecFaces.size() < 1)
        return frame;

    QImage tmpFrame(frame);
    QPainter painter;

    painter.begin(&tmpFrame);

    for (std::vector<cv::Rect>::const_iterator face = vecFaces.begin(); face != vecFaces.end(); face++)
        painter.drawImage(QRect(face->x * scale,
                                face->y * scale,
                                face->width * scale,
                                face->height * scale),
                                this->m_maskImage);

    painter.end();

    return tmpFrame;
}
