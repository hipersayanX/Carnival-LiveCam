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

#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include "plugin.h"
#include "plugininfo.h"

class PluginManager: public QObject
{
    Q_OBJECT

    Q_PROPERTY(PipelineRoutingMode pipelineRoutingMode
               READ pipelineRoutingMode
               WRITE setPipelineRoutingMode
               RESET resetPipelineRoutingMode)

    /// Enumerator for pipeline diff operations
    public:
        /// Actions to do if some element doesn't exist
        typedef enum _PipelineRoutingMode
        {
            NoCheck, // Build the pipeline as is.
            Fail,    // If an element doesn't exist return a void graph.
            Remove,  // If an element doesn't exist return a graph without the
                     // element and it's connections.
            Force    // If an element doesn't exist try to connect all elements
                     // connected to the lost element.
        } PipelineRoutingMode;

        explicit PluginManager(QObject *parent = 0);
        Q_INVOKABLE QList<QVariant> pluginList();
        PipelineRoutingMode pipelineRoutingMode();

    private:
        QPluginLoader m_pluginLoader;
        QMap<QString, Plugin *> m_plugins;
        QMap<QString, Element *> m_elements;
        QMap<QString, PluginInfo> m_pluginsInfo;
        QList<int> m_usedIds;
        int m_curId;

        // Previous pipeline graph.
        QMap<QString, QVariant> m_instances1; // Nodes
        QList<QStringList> m_connections1;    // Edges
        QList<QStringList> m_ss1;             // Signals & Slots

        QStringList m_availableElementTypes;
        PipelineRoutingMode m_pipelineRoutingMode;

        QMap<QString, QString> m_regexpDict;

        Plugin *plugin(QString pluginId);
        bool isLoaded(QString pluginId);
        bool load(QString pluginId);
        bool unload(QString pluginId);

        void resetRegexpDict();
        int requestId();
        void removeId(int id);

        bool startElement(QString elementId);
        bool stopElement(QString elementId);
        bool addElement(QString elementId, QString pluginId);
        bool removeElement(QString elementId);
        bool changeElementId(QString oldElementId, QString newElementId);
        bool setElementProperty(QString elementId, QString property, QVariant value);
        bool resetElementProperty(QString elementId, QString property);
        bool connectElementsSS(QString senderId, QString signal, QString receiverId, QString slot);
        bool disconnectElementsSS(QString senderId, QString signal, QString receiverId, QString slot);
        bool connectElements(QString senderId, QString receiverId);
        bool disconnectElements(QString senderId, QString receiverId);

        QStringList regexpFindAll(QString regexp, QString text);

        QVariant parseValue(QString value);
        QStringList parseSignalSlotLt(QString id, QString element);
        QStringList parseSignalSlotGt(QString id, QString element);
        QStringList parseSignalSlot(QString id, QString element);

        bool parsePipeline(QString pipeline,
                           QMap<QString, QVariant> *instances,
                           QList<QStringList> *connections,
                           QList<QStringList> *ss);

    public slots:
        void setPipeline(QString pipeline2);
        void setPipelineRoutingMode(QString mode);
        void setPipelineRoutingMode(PipelineRoutingMode mode);
        void resetPipelineRoutingMode();
};

#endif // PLUGINMANAGER_H
