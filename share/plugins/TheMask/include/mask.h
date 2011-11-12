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

#ifndef MASK_H
#define MASK_H

#include <QImage>
#include <opencv2/opencv.hpp>

using namespace cv;

class Mask: public QObject
{
    Q_OBJECT
    public:
        explicit Mask(QObject *parent = 0);
        Mask(QString fileName);
        QImage render(const QImage &frame);

    private:
        QImage mask;
        CascadeClassifier cascadeClassifier;
};

#endif // MASK_H
