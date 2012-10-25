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

#ifndef MAINPIPELINE_H
#define MAINPIPELINE_H

#include "plugin.h"

class MainPipeline: public Pipeline
{
    Q_OBJECT
    Q_ENUMS(PipelineRoutingMode)

        Q_PROPERTY(QStringList pluginsPaths
                   READ pluginsPaths
                   WRITE setPluginsPaths
                   RESET resetPluginsPaths)

        Q_PROPERTY(QVariantMap pluginList
                   READ pluginList)

        Q_PROPERTY(PipelineRoutingMode pipelineRoutingMode
                   READ pipelineRoutingMode
                   WRITE setPipelineRoutingMode
                   RESET resetPipelineRoutingMode)

    /// Enumerator for pipeline diff operations
    public:
        explicit MainPipeline(QObject *parent = 0);
        MainPipeline(const MainPipeline &object);
        MainPipeline& operator =(const MainPipeline &other);

        Q_INVOKABLE void loadPlugins();
        Q_INVOKABLE QStringList pluginsPaths();
        Q_INVOKABLE QVariantMap pluginList();
        Q_INVOKABLE PipelineRoutingMode pipelineRoutingMode();

        Q_INVOKABLE bool startElement(QString elementId);
        Q_INVOKABLE bool stopElement(QString elementId);
        Q_INVOKABLE QString addElement(QString pluginId);
        Q_INVOKABLE bool removeElement(QString elementId);
        Q_INVOKABLE bool setElementProperty(QString elementId, QString property, QVariant value);
        Q_INVOKABLE bool resetElementProperty(QString elementId, QString property);

        Q_INVOKABLE bool connectElementsSS(QString senderId, QString signal, QString receiverId, QString slot);
        Q_INVOKABLE bool connectElementsSS(QString senderId, QString signal, const QObject *receiver, const char *slot);
        Q_INVOKABLE bool connectElementsSS(const QObject *sender, const char *signal, QString receiverId, QString slot);
        Q_INVOKABLE bool disconnectElementsSS(QString senderId, QString signal, QString receiverId, QString slot);
        Q_INVOKABLE bool disconnectElementsSS(QString senderId, QString signal, const QObject *receiver, const char *slot);
        Q_INVOKABLE bool disconnectElementsSS(const QObject *sender, const char *signal, QString receiverId, QString slot);

        Q_INVOKABLE bool connectElements(QString senderId, QString receiverId);
        Q_INVOKABLE bool connectElements(QString senderId, const QObject *receiver, const char *slot);
        Q_INVOKABLE bool connectElements(const QObject *sender, const char *signal, QString receiverId);
        Q_INVOKABLE bool disconnectElements(QString senderId, QString receiverId);
        Q_INVOKABLE bool disconnectElements(QString senderId, const QObject *receiver, const char *slot);
        Q_INVOKABLE bool disconnectElements(const QObject *sender, const char *signal, QString receiverId);

    private:
        QStringList m_pluginsPaths;
        QVariantMap m_pluginList;
        PipelineRoutingMode m_pipelineRoutingMode;

        QPluginLoader m_pluginLoader;
        QMap<QString, Plugin *> m_plugins;
        QMap<QString, Element *> m_elements;
        QList<int> m_usedIds;
        int m_curId;

        // Previous pipeline graph.
        QMap<QString, QVariantList> m_instances1; // Nodes
        QList<QStringList> m_connections1;        // Edges
        QList<QStringList> m_ss1;                 // Signals & Slots

        QMap<QString, QString> m_regexpDict;

        Plugin *plugin(QString pluginId);
        bool isLoaded(QString pluginId);
        bool load(QString pluginId);
        bool unload(QString pluginId);

        void resetRegexpDict();
        int requestId();
        void removeId(int id);

        QStringList regexpFindAll(QString regexp, QString text);
        QString bestMatchId(QMap<QString, QVariantList> instances1, QMap<QString, QVariantList> instances2, QString id2);

        QString changeId(QString srcId,
                         QString dstId,
                         QMap<QString, QVariantList> *instances,
                         QList<QStringList> *connections,
                         QList<QStringList> *ss);

        void alignPipelines(QMap<QString, QVariantList> instances1,
                            QMap<QString, QVariantList> *instances2,
                            QList<QStringList> *connections2,
                            QList<QStringList> *ss2);

        template <typename T> QList<T> subtractLists(QList<T> list1, QList<T> list2);

        QStringList subtractMapKeys(QMap<QString, QVariantList> instances1,
                                    QMap<QString, QVariantList> instances2);

        QList<QMap<QString, QStringList> > propertiesDiff(const QMap<QString, QVariantList> &instances1,
                                                          const QMap<QString, QVariantList> &instances2);

        QVariant parseValue(QString value);
        QStringList parseSignalSlotLt(QString id, QString element);
        QStringList parseSignalSlotGt(QString id, QString element);
        QStringList parseSignalSlot(QString id, QString element);

        bool parsePipeline(QString pipeline,
                           QMap<QString, QVariantList> *instances,
                           QList<QStringList> *connections,
                           QList<QStringList> *ss);

    public slots:
        void setPipeline(QString pipeline);
        void setPluginsPaths(QStringList pluginsPaths);
        void setPipelineRoutingMode(PipelineRoutingMode mode);
        void resetPluginsPaths();
        void resetPipelineRoutingMode();

    private slots:
        void assignPipeline();
};

#endif // MAINPIPELINE_H
