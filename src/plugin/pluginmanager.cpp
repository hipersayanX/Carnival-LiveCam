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

#include "include/plugin/pluginmanager.h"

/*!
  \class PluginManager

  \brief This class is used for manage plugins.
 */

/*!
  \fn PluginManager::PluginManager(QObject *parent)

  \param parent Parent widget.
 */
PluginManager::PluginManager(QObject *parent): QObject(parent)
{
    this->m_pipelineRoutingMode = NoCheck;

    QDir pluginDir("share/plugins");

    foreach (QString dirext, pluginDir.entryList(QDir::AllDirs | QDir::NoDot | QDir::NoDotDot, QDir::Name))
    {
        pluginDir.cd(dirext);

        foreach (QString pluginPath, pluginDir.entryList(QDir::Files, QDir::Name))
        {
            QString fileName = pluginDir.absoluteFilePath(pluginPath);

            if (!QLibrary::isLibrary(fileName))
                continue;

            qDebug() << "Loading: " << fileName;

            this->m_pluginLoader.setFileName(fileName);

            if (!this->m_pluginLoader.load())
            {
                qDebug() << this->m_pluginLoader.errorString();

                continue;
            }

            QObject *pluginInstance = this->m_pluginLoader.instance();

            if (!pluginInstance)
                continue;

            Plugin *plugin = qobject_cast<Plugin *>(pluginInstance);

            if (!plugin)
                continue;

            this->m_pluginsInfo[plugin->pluginId()] = PluginInfo(fileName,
                                                                 plugin->pluginId(),
                                                                 plugin->name(),
                                                                 plugin->version(),
                                                                 plugin->summary(),
                                                                 plugin->type(),
                                                                 plugin->category(),
                                                                 plugin->thumbnail(),
                                                                 plugin->license(),
                                                                 plugin->author(),
                                                                 plugin->website(),
                                                                 plugin->mail(),
                                                                 plugin->isConfigurable());

            this->m_availableElementTypes << plugin->pluginId();
            this->m_pluginLoader.unload();
        }

        pluginDir.cdUp();
    }
}

/*!
  \fn QList<QVariant> PluginManager::pluginsToQml()

  \return The list of plugins information in standard format.

  \brief Returns the list of plugins information in standard format.
 */
QList<QVariant> PluginManager::pluginList()
{
    QList<QVariant> list;

    foreach (PluginInfo plugin, this->m_pluginsInfo)
        list << plugin.toMap();

    return list;
}

Plugin *PluginManager::plugin(QString pluginId)
{
    return this->isLoaded(pluginId)? this->m_plugins[pluginId]: NULL;
}

bool PluginManager::isLoaded(QString pluginId)
{
    return this->m_plugins.contains(pluginId);
}

bool PluginManager::load(QString pluginId)
{
    if (this->isLoaded(pluginId))
        return true;

    this->m_pluginLoader.setFileName(this->m_pluginsInfo[pluginId].fileName());

    if (!this->m_pluginLoader.load())
        return false;

    QObject *pluginInstance = this->m_pluginLoader.instance();

    if (!pluginInstance)
        return false;

    Plugin *plugin = qobject_cast<Plugin *>(pluginInstance);

    if (!plugin)
        return false;

    this->m_plugins[pluginId] = plugin;

    return true;
}

bool PluginManager::unload(QString pluginId)
{
    if(!this->isLoaded(pluginId))
         return true;

    delete this->m_plugins[pluginId];
    this->m_plugins.remove(pluginId);
    this->m_pluginLoader.setFileName(this->m_pluginsInfo[pluginId].fileName());
    this->m_pluginLoader.unload();

    return true;
}

bool PluginManager::startElement(QString elementId)
{
    if (!this->m_elements.contains(elementId))
        return false;

    return this->m_elements[elementId]->start();
}

bool PluginManager::stopElement(QString elementId)
{
    if (!this->m_elements.contains(elementId))
        return false;

    return this->m_elements[elementId]->stop();
}

bool PluginManager::addElement(QString elementId, QString pluginId)
{
    if (!this->load(pluginId))
        return false;

    Element *element = this->m_plugins[pluginId]->newElement();

    if (!element)
        return false;

    this->m_elements[elementId] = element;
    this->m_elements[elementId]->setManager(qobject_cast<QObject *>(this));

    return true;
}

bool PluginManager::removeElement(QString elementId)
{
    if (!this->m_elements.contains(elementId))
        return true;

    QString pluginId = this->m_instances1[elementId].toList()[0].toString();
    Element *element = this->m_elements[elementId];

    delete element;
    this->m_elements.remove(elementId);

    bool unUsed = true;

    foreach (QVariant value, this->m_instances1)
        if (value.toList()[0].toString() == pluginId)
        {
            unUsed = false;

            break;
        }

    if (unUsed)
        this->unload(pluginId);

    return true;
}

bool PluginManager::changeElementId(QString oldElementId, QString newElementId)
{
    if (!this->m_elements.contains(oldElementId))
        return false;

    this->m_elements[newElementId] = this->m_elements[oldElementId];
    this->m_elements.remove(oldElementId);

    return true;
}

bool PluginManager::setElementProperty(QString elementId, QString property, QVariant value)
{
    if (!this->m_elements.contains(elementId))
        return false;

    this->m_elements[elementId]->setProperty(property.toUtf8().constData(), value);

    return true;
}

bool PluginManager::resetElementProperty(QString elementId, QString property)
{
    if (!this->m_elements.contains(elementId))
        return false;

    QString resetMethod = QString("reset%1%2").arg(property.left(1).toUpper()).arg(property.mid(1));

    if (this->m_elements[elementId]->metaObject()->indexOfMethod(resetMethod.toUtf8().constData()) < 0)
        return false;

    QMetaObject::invokeMethod(this->m_elements[elementId], resetMethod.toUtf8().constData());

    return true;
}

bool PluginManager::connectElementsSS(QString senderId, QString signal, QString receiverId, QString slot)
{
    if (!this->m_elements.contains(senderId) || !this->m_elements.contains(receiverId))
        return false;

    const char *cSignal = QMetaObject::normalizedSignature(signal.toUtf8().constData()).constData();
    const char *cSlot = QMetaObject::normalizedSignature(slot.toUtf8().constData()).constData();

    int s = this->m_elements[senderId]->metaObject()->indexOfSignal(cSignal);
    int r = this->m_elements[receiverId]->metaObject()->indexOfSlot(cSlot);

    if (r < 0 || s < 0)
        return false;

    QObject::connect(this->m_elements[senderId],
                     this->m_elements[senderId]->metaObject()->method(s),
                     this->m_elements[receiverId],
                     this->m_elements[receiverId]->metaObject()->method(r));

    return true;
}

bool PluginManager::disconnectElementsSS(QString senderId, QString signal, QString receiverId, QString slot)
{
    if (!this->m_elements.contains(senderId) || !this->m_elements.contains(receiverId))
        return false;

    const char *cSignal = QMetaObject::normalizedSignature(signal.toUtf8().constData()).constData();
    const char *cSlot = QMetaObject::normalizedSignature(slot.toUtf8().constData()).constData();

    int s = this->m_elements[senderId]->metaObject()->indexOfSignal(cSignal);
    int r = this->m_elements[receiverId]->metaObject()->indexOfSlot(cSlot);

    if (r < 0 || s < 0)
        return false;

    QObject::disconnect(this->m_elements[senderId],
                        this->m_elements[senderId]->metaObject()->method(s),
                        this->m_elements[receiverId],
                        this->m_elements[receiverId]->metaObject()->method(r));

    return true;
}

bool PluginManager::connectElements(QString senderId, QString receiverId)
{
    if (this->connectElementsSS(senderId, "oVideo(QImage *)", receiverId, "iVideo(QImage *)") &&
        this->connectElementsSS(senderId, "oAudio(QByteArray *)", receiverId, "iAudio(QByteArray *)"))
        return true;
    else
        return false;
}

bool PluginManager::disconnectElements(QString senderId, QString receiverId)
{
    if (this->disconnectElementsSS(senderId, "oVideo(QImage *)", receiverId, "iVideo(QImage *)") &&
        this->disconnectElementsSS(senderId, "oAudio(QByteArray *)", receiverId, "iAudio(QByteArray *)"))
        return true;
    else
        return false;
}

/// Parse a string and returns the native value.
QVariant PluginManager::parseValue(QString value)
{
    // String
    if (QRegExp("'.*'|\".*\"").exactMatch(value))
        return value.mid(1, value.length() - 2);
    // Dictionary
    else if (QRegExp("\\{.*\\}").exactMatch(value))
    {
        QStringList r = value.mid(1, value.length() - 2).split(QRegExp("(?:[0-9]+\\.[0-9]+|\\.[0-9]+|[0-9]+\\.|[0-9]+|\".*\"|" \
                                                                       "'.*'|\\{.*\\}|\\[.*\\])" \
                                                                       " *: *" \
                                                                       "(?:[0-9]+\\.[0-9]+|\\.[0-9]+|[0-9]+\\.|[0-9]+|\".*\"|" \
                                                                       "'.*'|\\{.*\\}|\\[.*\\])|" \
                                                                       ","), QString::SkipEmptyParts);

        QMap<QString, QVariant> d;

        foreach (QString item, r)
            if (item != ",")
            {
                int kv = item.indexOf(":");
                QString key = item.left(kv);
                QString value = item.right(item.length() - kv - 1);

                d[this->parseValue(key.trimmed()).toString()] = this->parseValue(value.trimmed());
            }

        return d;
    }
    // List
    else if (QRegExp("\\[.*\\]").exactMatch(value))
    {
        QStringList r = value.mid(1, value.length() - 2).split(QRegExp("[0-9]+\\.[0-9]+|" \
                                                                       "\\.[0-9]+|" \
                                                                       "[0-9]+\\.|" \
                                                                       "[0-9]+|" \
                                                                       "\".*\"|" \
                                                                       "'.*'|" \
                                                                       "\\{.*\\}|" \
                                                                       "\\[.*\\]|" \
                                                                       ","), QString::SkipEmptyParts);

        QList<QVariant> l;

        foreach (QString item, r)
            if (item != ",")
                l << this->parseValue(item);

        return l;
    }
    else
    {
        bool ok;

        int valueInt = value.toInt(&ok);

        if (ok)
            return valueInt;

        float valueFloat = value.toFloat(&ok);

        if (ok)
            return valueFloat;

        // String
        return value;
    }
}

void PluginManager::parsePipeline(QString pipeline,
                                  QMap<QString, QVariant> *instances,
                                  QList<QStringList> *connections,
                                  QList<QStringList> *ss)
{
    if (instances)
        instances->clear();

    if (connections)
        connections->clear();

    if (ss)
        ss->clear();

    QStringList r = pipeline.split(QRegExp("[a-zA-Z_][0-9a-zA-Z_]* *= *(?:'.*'|\".*\"|" \
                                           "\\[.*\\]|\\{.*\\}|[^\r^\n^ ^!]+)|" \
                                           "(?:[a-zA-Z_][0-9a-zA-Z_]*\\.)?" \
                                           "[a-zA-Z_][0-9a-zA-Z_]* *" \
                                           "\\( *(?:[a-zA-Z_][0-9a-zA-Z_]* *" \
                                           "(?:, *[a-zA-Z_][0-9a-zA-Z_]*)*)? *\\)" \
                                           " *(?:<|>) *" \
                                           "(?:[a-zA-Z_][0-9a-zA-Z_]*\\.)?" \
                                           "[a-zA-Z_][0-9a-zA-Z_]* *" \
                                           "\\( *(?:[a-zA-Z_][0-9a-zA-Z_]* *" \
                                           "(?:, *[a-zA-Z_][0-9a-zA-Z_]*)*)? *\\)|" \
                                           "[a-zA-Z_][0-9a-zA-Z_]*\\.?|" \
                                           "!"),
                                           QString::SkipEmptyParts);

    QList<QVariant> pipes;
    QList<QVariant> pipe;
    QString elementName;
    QMap<QString, QVariant> properties;

    int i = 0; // Column
    int j = 0; // Row
    int k = 0;

    foreach (QString p, r)
    {
        // Parse property
        if (QRegExp("[a-zA-Z_][0-9a-zA-Z_]* *= *" \
                    "(?:'.*'|" \
                    "\".*\"|" \
                    "\\[.*\\]|" \
                    "\\{.*\\}|" \
                    "[^\r^\n^ ^!]+)").exactMatch(p))
        {
            int eq = p.indexOf("=");

            QString key = p.left(eq).trimmed();
            QString value = p.right(p.length() - eq - 1).trimmed();

            properties[key] = this->parseValue(value);
        }
        // Parse Signals & Slots
        //
        // sender receiver.slot([type1, tipe2, ...])<signal([type1, tipe2, ...])
        // receiver slot([type1, tipe2, ...])<sender.signal([type1, tipe2, ...])
        else if (QRegExp("(?:[a-zA-Z_][0-9a-zA-Z_]*\\.)?" \
                         "[a-zA-Z_][0-9a-zA-Z_]* *" \
                         "\\( *(?:[a-zA-Z_][0-9a-zA-Z_]* *" \
                         "(?:, *[a-zA-Z_][0-9a-zA-Z_]*)*)? *\\)" \
                         " *< *" \
                         "(?:[a-zA-Z_][0-9a-zA-Z_]*\\.)?" \
                         "[a-zA-Z_][0-9a-zA-Z_]* *" \
                         "\\( *(?:[a-zA-Z_][0-9a-zA-Z_]* *" \
                         "(?:, *[a-zA-Z_][0-9a-zA-Z_]*)*)? *\\)").exactMatch(p))
        {
            int eq = p.indexOf("<");
            QString s1 = p.left(eq).trimmed();
            QString s2 = p.right(p.length() - eq - 1).trimmed();

            QString sender;
            QString signal;
            QString receiver;
            QString slot;

            if (s1.contains("."))
            {
                QStringList receiverSlot = s1.split(".");
                receiver = receiverSlot[0] + ".";
                slot = receiverSlot[1];
            }
            else
            {
                receiver = QString("%1,%2").arg(i).arg(j);
                slot = s1;
            }

            if (s2.contains("."))
            {
                QStringList senderSignal = s2.split(".");
                sender = senderSignal[0] + ".";
                signal = senderSignal[1];
            }
            else
            {
                sender = QString("%1,%2").arg(i).arg(j);
                signal = s2;
            }

            signal = signal.split(QRegExp("\\s+"), QString::SkipEmptyParts).join("");
            slot = slot.split(QRegExp("\\s+"), QString::SkipEmptyParts).join("");

            if (ss)
                *ss << (QStringList() << sender << signal << receiver << slot);
        }
        // Parse Signals & Slots
        //
        // sender signal([type1, tipe2, ...])>receiver.slot([type1, tipe2, ...])
        // receiver sender.signal([type1, tipe2, ...])>slot([type1, tipe2, ...])
        else if (QRegExp("(?:[a-zA-Z_][0-9a-zA-Z_]*\\.)?" \
                         "[a-zA-Z_][0-9a-zA-Z_]* *" \
                         "\( *(?:[a-zA-Z_][0-9a-zA-Z_]* *" \
                         "(?:, *[a-zA-Z_][0-9a-zA-Z_]*)*)? *\\)" \
                         " *> *" \
                         "(?:[a-zA-Z_][0-9a-zA-Z_]*\\.)?" \
                         "[a-zA-Z_][0-9a-zA-Z_]* *" \
                         "\( *(?:[a-zA-Z_][0-9a-zA-Z_]* *" \
                         "(?:, *[a-zA-Z_][0-9a-zA-Z_]*)*)? *\\)").exactMatch(p))
        {
            int eq = p.indexOf(">");
            QString s1 = p.left(eq).trimmed();
            QString s2 = p.right(p.length() - eq - 1).trimmed();

            QString sender;
            QString signal;
            QString receiver;
            QString slot;

            if (s1.contains("."))
            {
                QStringList senderSignal = s1.split(".");
                sender = senderSignal[0] + ".";
                signal = senderSignal[1];
            }
            else
            {
                sender = QString("%1,%2").arg(i).arg(j);
                signal = s1;
            }

            if (s2.contains("."))
            {
                QStringList receiverSlot = s2.split(".");
                receiver = receiverSlot[0] + ".";
                slot = receiverSlot[1];
            }
            else
            {
                receiver = QString("%1,%2").arg(i).arg(j);
                slot = s2;
            }

            signal = signal.split(QRegExp("\\s+"), QString::SkipEmptyParts).join("");
            slot = slot.split(QRegExp("\\s+"), QString::SkipEmptyParts).join("");

            if (ss)
                *ss << (QStringList() << sender << signal << receiver << slot);
        }
        // Parse element
        else
        {
            if (!elementName.isEmpty() && elementName != "!")
            {
                QList<QVariant> ep = QList<QVariant>() << elementName << properties;

                if (!elementName.endsWith(".") && instances)
                {
                    if (this->m_pipelineRoutingMode == Fail &&
                        !this->m_availableElementTypes.contains(elementName))
                    {
                        if (instances)
                            *instances = QMap<QString, QVariant>();

                        if (connections)
                            *connections = QList<QStringList>();

                        if (ss)
                            *ss = QList<QStringList>();

                        return;
                    }

                    (*instances)[QString("%1,%2").arg(i).arg(j)] = ep;
                }

                pipe << ep;
                i++;

                if (p != "!")
                {
                    pipes << pipe;
                    pipe.clear();
                    i = 0;
                    j++;
                }
            }

            elementName = p;
            properties.clear();
        }

        if (k == r.length() - 1)
            if (!elementName.isEmpty() && elementName != "!")
            {
                QList<QVariant> ep = QList<QVariant>() << elementName << properties;

                if (!elementName.endsWith(".") && instances)
                    (*instances)[QString("%1,%2").arg(i).arg(j)] = ep;

                pipe << ep;
                i++;

                if (p != "!")
                {
                    pipes << pipe;
                    pipe.clear();
                    i = 0;
                    j++;
                }
            }

        k++;
    }

    // Solve references.
    //
    // i,j. -> x,y
    QMap<QString, QString> references;

    foreach (QVariant pipe, pipes)
        foreach (QVariant element, pipe.toList())
            if (element.toList()[0].toString().endsWith(".") && instances)
                foreach (QString instance, (*instances).keys())
                {
                    QMap<QString, QVariant> props = (*instances)[instance].toList()[1].toMap();
                    QString name = element.toList()[0].toString();

                    if (props.contains("objectName") &&
                        props["objectName"].toString() == name.left(name.length() - 1))
                        references[name] = instance;
                }

    // Solve connections between elements.
    j = 0;

    foreach (QVariant pipe, pipes)
    {
        i = 0;

        foreach (QVariant element, pipe.toList())
        {
            QString cur;

            if (element.toList()[0].toString().endsWith("."))
                cur = references[element.toList()[0].toString()];
            else
                cur = QString("%1,%2").arg(i).arg(j);

            if (i + 1 < pipe.toList().length())
            {
                QList<QVariant> nextElement = pipe.toList()[i + 1].toList();
                QString nxt;

                if (nextElement[0].toString().endsWith("."))
                    nxt = references[nextElement[0].toString()];
                else
                    nxt = QString("%1,%2").arg(i + 1).arg(j);

                if (connections)
                    *connections << (QStringList() << cur << nxt);
            }

            i++;
        }

        j++;
    }

    // Solve signals & slots.
    if (ss)
        foreach (QStringList s, *ss)
        {
            if (s[0].endsWith("."))
                s[0] = references[s[0]];

            if (s[2].endsWith("."))
                s[2] = references[s[2]];
        }

    if (this->m_pipelineRoutingMode == Remove ||
        this->m_pipelineRoutingMode == Force)
    {
        QStringList removeId;
        QString id;

        foreach (id, instances->keys())
            if (!this->m_availableElementTypes.contains((*instances)[id].toList()[0].toString()))
                removeId << id;

        foreach (id, removeId)
        {
            instances->remove(id);

            QStringList iConns;
            QStringList oConns;

            for (i = 0; i < connections->length(); i++)
                if ((*connections)[i][0] == id || (*connections)[i][1] == id)
                {
                    if ((*connections)[i][0] != id)
                        iConns << (*connections)[i][0];

                    if ((*connections)[i][1] != id)
                        oConns << (*connections)[i][1];

                    connections->removeAt(i);
                    i--;
                }

            if (this->m_pipelineRoutingMode == Force)
                foreach (QString iConn, iConns)
                    foreach (QString oConn, oConns)
                    {
                        QStringList c = QStringList() << iConn << oConn;

                        if (iConn != oConn &&
                            !connections->contains(c))
                            *connections << c;
                    }

            for (i = 0; i < ss->length(); i++)
                if ((*ss)[i][0] == id || (*ss)[i][2] == id)
                {
                    ss->removeAt(i);
                    i--;
                }
        }
    }
}

void PluginManager::setPipeline(QString pipeline2)
{
    QMap<QString, QVariant> instances2;
    QList<QStringList> connections2;
    QList<QStringList> ss2;

    this->parsePipeline(pipeline2, &instances2, &connections2, &ss2);

    QMap<QString, QVariant> cInstances1(this->m_instances1);
    QMap<QString, QVariant> cInstances2(instances2);

    QList<QStringList> cConnections1(this->m_connections1);
    QList<QStringList> cConnections2(connections2);

    QList<QStringList> cSs1(this->m_ss1);
    QList<QStringList> cSs2(ss2);

    QList<QStringList> disconnectSignalsAndSlots;
    QList<QStringList> disconnectElement;
    QStringList removeElement;
    QList<QStringList> changeId;
    QMap<QString, QMap<QString, QVariant> > setProperties;
    QMap<QString, QStringList> resetProperties;
    QList<QStringList> connectElement;
    QList<QStringList> connectSignalsAndSlots;

    int i;

    while (!cInstances1.isEmpty())
    {
        // Get an item from cInstances1.
        QString key = cInstances1.keys()[0];
        QVariant value = cInstances1.take(key);
        QString bestMatchId = "";

        // Find a similar element.
        foreach (QString instance2, cInstances2.keys())
            if (value.toList()[0].toString() == cInstances2[instance2].toList()[0].toString())
            {
                if (bestMatchId == "")
                    bestMatchId = instance2;
                else if (value.toList()[1].toMap().contains("objectName") &&
                         cInstances2[instance2].toList()[1].toMap().contains("objectName") &&
                         value.toList()[1].toMap()["objectName"].toString() ==
                         cInstances2[instance2].toList()[1].toMap()["objectName"].toString())
                {
                    bestMatchId = instance2;

                    break;
                }
            }

        // There are no similar elements.
        if (bestMatchId == "")
        {
            // Remove it from the previous pipeline.
            removeElement << key;

            // Remove it's connections.
            for (i = 0; i < cConnections1.length(); i++)
                if (cConnections1[i][0] == key ||
                    cConnections1[i][1] == key)
                {
                    disconnectElement << cConnections1[i];
                    cConnections1.removeAt(i);
                    i--;
                }

            // Remove it's signals & slots.
            for (i = 0; i < cSs1.length(); i++)
                if (cSs1[i][0] == key || cSs1[i][2] == key)
                {
                    disconnectSignalsAndSlots << cSs1[i];
                    cSs1.removeAt(i);
                    i--;
                }
        }
        // There are at least one similar element.
        else
        {
            // Change the Id of the element in pipeline1 by the Id of the
            // element in pipeline2.
            if (key != bestMatchId)
            {
                if (cInstances1.contains(bestMatchId))
                    // The new Id is used by other element. Change the Id to
                    // a ghost Id.
                    changeId << (QStringList() << key << QString(".%1").arg(bestMatchId));
                else
                    changeId << (QStringList() << key << bestMatchId);
            }

            // Copy the properties from pipeline2 to the pipeline1.
            QMap<QString, QVariant> setProps;

            foreach (QString prop, cInstances2[bestMatchId].toList()[1].toMap().keys())
                if (!value.toList()[1].toMap().contains(prop) ||
                    (value.toList()[1].toMap().contains(prop) &&
                     cInstances2[bestMatchId].toList()[1].toMap()[prop] != value.toList()[1].toMap()[prop]))
                    setProps[prop] = cInstances2[bestMatchId].toList()[1].toMap()[prop];

            if (!setProps.isEmpty())
                setProperties[bestMatchId] = setProps;

            QStringList resetProps;

            foreach (QString prop, value.toList()[1].toMap().keys())
                if (!cInstances2[bestMatchId].toList()[1].toMap().contains(prop))
                    resetProps << prop;

            if (!resetProps.isEmpty())
                resetProperties[bestMatchId] = resetProps;

            cInstances2.remove(bestMatchId);
        }
    }

    // Converts ghost Id to the final Id.
    for (i = 0; i < changeId.length(); i++)
        if (changeId[i][1].startsWith("."))
        {
            if (removeElement.contains(changeId[i][1].mid(1)))
                changeId[i][1] = changeId[i][1].mid(1);
            else
                changeId << (QStringList() << changeId[i][1] << changeId[i][1].mid(1));
        }

    bool fst;
    bool snd;
    QStringList dstConnection;

    // Solve connections
    for (i = 0; i < cConnections1.length(); i++)
    {
        dstConnection = QStringList(cConnections1[i]);
        fst = false;
        snd = false;

        foreach (QStringList change, changeId)
        {
            QString dst = change[1].startsWith(".")? change[1].mid(1): change[1];

            if (!fst && dstConnection[0] == change[0])
            {
                dstConnection[0] = dst;
                fst = true;
            }

            if (!snd && dstConnection[1] == change[0])
            {
                dstConnection[1] = dst;
                snd = true;
            }

            if (fst && snd)
                break;
        }

        if (!cConnections2.contains(dstConnection))
        {
            disconnectElement << cConnections1[i];
            cConnections1.removeAt(i);
            i--;
        }
    }

    for (i = 0; i < cConnections2.length(); i++)
    {
        dstConnection = QStringList(cConnections2[i]);
        fst = false;
        snd = false;

        foreach (QStringList change, changeId)
        {
            QString src = change[1].startsWith(".")? change[1].mid(1): change[1];

            if (!fst && dstConnection[0] == src)
            {
                dstConnection[0] = change[0];
                fst = true;
            }

            if (!snd && dstConnection[1] == src)
            {
                dstConnection[1] = change[0];
                snd = true;
            }

            if (fst && snd)
                break;
        }

        if (!cConnections1.contains(dstConnection))
        {
            connectElement << cConnections2[i];
            cConnections2.removeAt(i);
            i--;
        }
    }

    QStringList dstSs;

    // Solve signals & slots.
    for (i = 0; i < cSs1.length(); i++)
    {
        dstSs = QStringList(cSs1[i]);
        fst = false;
        snd = false;

        foreach (QStringList change, changeId)
        {
            QString dst = change[1].startsWith(".")? change[1].mid(1): change[1];

            if (!fst && dstSs[0] == change[0])
            {
                dstSs[0] = dst;
                fst = true;
            }

            if (!snd && dstSs[2] == change[0])
            {
                dstSs[2] = dst;
                snd = true;
            }

            if (fst && snd)
                break;
        }

        if (!cSs2.contains(dstSs))
        {
            disconnectSignalsAndSlots << cSs1[i];
            cSs1.removeAt(i);
            i--;
        }
    }

    for (i = 0; i < cSs2.length(); i++)
    {
        dstSs = QStringList(cSs2[i]);
        fst = false;
        snd = false;

        foreach (QStringList change, changeId)
        {
            QString src = change[1].startsWith(".")? change[1].mid(1): change[1];

            if (!fst && dstSs[0] == src)
            {
                dstSs[0] = change[0];
                fst = true;
            }

            if (!snd && dstSs[2] == src)
            {
                dstSs[2] = change[0];
                snd = true;
            }

            if (fst && snd)
                break;
        }

        if (!cSs1.contains(dstSs))
        {
            connectSignalsAndSlots << cSs2[i];
            cSs2.removeAt(i);
            i--;
        }
    }

    // Add elements in pipeline2 to pipeline1.
    QMap<QString, QString> addElement;

    foreach (QString instance, cInstances2.keys())
    {
        addElement[instance] = cInstances2[instance].toList()[0].toString();

        if (!cInstances2[instance].toList()[1].toMap().isEmpty())
            setProperties[instance] = cInstances2[instance].toList()[1].toMap();

        for (i = 0; i < cConnections2.length(); i++)
            if (cConnections2[i][0] == instance ||
                cConnections2[i][1] == instance)
            {
                connectElement << cConnections2[i];
                cConnections2.removeAt(i);
                i--;
            }

        for (i = 0; i < cSs2.length(); i++)
            if (cSs2[i][0] == instance || cSs2[i][2] == instance)
            {
                connectSignalsAndSlots << cSs2[i];
                cSs2.removeAt(i);
                i--;
            }
    }

    // Set pipeline2 as the new pipeline.
    this->m_instances1 = instances2;
    this->m_connections1 = connections2;
    this->m_ss1 = ss2;

    foreach (QString elementId, removeElement)
        this->stopElement(elementId);

    foreach (QStringList ss, disconnectSignalsAndSlots)
        this->disconnectElementsSS(ss[0], ss[1], ss[2], ss[3]);

    foreach (QStringList connection, disconnectElement)
        this->disconnectElements(connection[0], connection[1]);

    foreach (QString elementId, removeElement)
        this->removeElement(elementId);

    foreach (QStringList change, changeId)
        this->changeElementId(change[0], change[1]);

    foreach (QString elementId, addElement.keys())
        this->addElement(elementId, addElement[elementId]);

    foreach (QString elementId, setProperties.keys())
        foreach (QString prop, setProperties[elementId].keys())
            this->setElementProperty(elementId, prop, setProperties[elementId][prop]);

    foreach (QString elementId, resetProperties.keys())
        foreach (QString prop, resetProperties[elementId])
            this->resetElementProperty(elementId, prop);

    foreach (QStringList connection, connectElement)
        this->connectElements(connection[0], connection[1]);

    foreach (QStringList ss, connectSignalsAndSlots)
       this->connectElementsSS(ss[0], ss[1], ss[2], ss[3]);

    foreach (QString elementId, addElement.keys())
        this->startElement(elementId);
}

PluginManager::PipelineRoutingMode PluginManager::pipelineRoutingMode()
{
    return this->m_pipelineRoutingMode;
}

void PluginManager::setPipelineRoutingMode(QString mode)
{
    if (mode == "Fail")
        this->setPipelineRoutingMode(Fail);
    else if (mode == "Remove")
        this->setPipelineRoutingMode(Remove);
    else if (mode == "Force")
        this->setPipelineRoutingMode(Force);
    else if (mode == "NoCheck")
        this->setPipelineRoutingMode(NoCheck);
}

void PluginManager::setPipelineRoutingMode(PipelineRoutingMode mode)
{
    this->m_pipelineRoutingMode = mode;
}

void PluginManager::resetPipelineRoutingMode()
{
    this->m_pipelineRoutingMode = NoCheck;
}
