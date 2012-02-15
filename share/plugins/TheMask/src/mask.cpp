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
 * OpenCV face recognition plugin
 */

#include <vector>

#include <QPainter>
#include <QtDebug>

#include "../include/mask.h"

Mask::Mask(QObject *parent): QObject(parent)
{
    this->cascadeClassifier.load("share/plugins/TheMask/share/haars/haarcascade_frontalface_alt.xml");
}

Mask::Mask(QString fileName)
{
    this->cascadeClassifier.load("share/plugins/TheMask/share/haars/haarcascade_frontalface_alt.xml");
    this->mask = QImage(fileName);
}

QImage Mask::render(const QImage &frame)
{
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
                                this->mask);

    painter.end();

    return tmpFrame;
}
