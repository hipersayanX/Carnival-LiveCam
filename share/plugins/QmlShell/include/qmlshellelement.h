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

#ifndef QMLSHELLELEMENT_H
#define QMLSHELLELEMENT_H

#include "element.h"
#include "qmlshellgui.h"

class QmlShellElement: public Element
{
    Q_OBJECT

    Q_PROPERTY(QString spacesBoard READ spacesBoard WRITE setSpacesBoard RESET resetSpacesBoard)
    Q_PROPERTY(QString spacePreview READ spacePreview WRITE setSpacePreview RESET resetSpacePreview)

    public:
        explicit QmlShellElement();

        QString spacesBoard();
        QString spacePreview();

        Q_INVOKABLE bool start();
        Q_INVOKABLE bool stop();

    private:
        QString m_spacesBoard;
        QString m_spacePreview;

        QmlShellGui m_qmlShellGui;
        QList<Element *> m_srcs;
        QList<Element *> m_sinks;

    signals:
        // Simple actions signals.
        void closed();
        void streamStateChanged(ElementState state);
        void takePicture(QString fileName);
        void startVideoRecord(QString fileName);
        void stopVideoRecord();
        void editModeChanged(bool enabled);

        // Spaces related signals.
        void addSpace(QString spaceTypeId);
        void removeSpace(QString spaceId);
        void spaceZIndexChanged(QString spaceId, int index);
        void requestSpaceControls(QString spaceId);
        void setupSpaceControls(QString spaceId, QVariantList controls);

        // Effects related signals.
        void addFx(QString fxTypeId);
        void removeFx(QString fxId);
        void fxIndexChanged(QString fxId, int index);
        void requestFxInfo(QString fxId);
        void openURL(QUrl url);
        void mailTo(QUrl mail);
        void requestFxUpdate(QString fxId);
        void fxPreviewStateChanged(QString fxId, ElementState state);
        void requestFxControls(QString fxId);
        void setupFxControls(QString fxId, QVariantList controls);

    public slots:
        void setSpacesBoard(QString spacesBoard);
        void setSpacePreview(QString spacePreview);
        void resetSpacesBoard();
        void resetSpacePreview();

        // Simple actions slots.
        void showError(QString message);
        void setStreamState(ElementState state);
        void setEditMode(bool enabled);
        void setRecordingState(bool recording);

        // Spaces related slots.
        void setAvailableSpaceTypes(QStringList spaceTypes);
        void setSpaces(QStringList spaces);
        void setSpaceIndex(QString spaceId, int index);
        void setSpaceControls(QString spaceId, QVariantList controls);

        // Effects related slots.
        void setAvailableFxCategories(QStringList categories);
        void setAvailableFx(QStringList fxs);
        void setFxs(QStringList fxs);
        void setFxIndex(QString fxId, int index);
        void setFxInfo(QString fxId, QVariantList controls);
        void setFxControls(QString fxId, QVariantList controls);

        void iStream(const void *data, int datalen, QString dataType);
        void setPipeline(Pipeline *pipeline);
        void setPeers(QList<Element *> srcs, QList<Element *> sinks);
};

#endif // QMLSHELLELEMENT_H
