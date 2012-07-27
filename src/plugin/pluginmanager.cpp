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

#include "../../include/plugin/pluginmanager.h"

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

            PluginFactory *pluginFactory = qobject_cast<PluginFactory *>(pluginInstance);

            if (!pluginFactory)
                continue;

            Plugin *plugin = pluginFactory->plugin();

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
                                                           plugin->isConfigurable(),
                                                           plugin->configs());

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
QList<QVariant> PluginManager::toList()
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
        return false;

    this->m_pluginLoader.setFileName(this->m_pluginsInfo[pluginId].fileName());

    if (!this->m_pluginLoader.load())
        return false;

    QObject *pluginInstance = this->m_pluginLoader.instance();

    if (!pluginInstance)
        return false;

    PluginFactory *pluginFactory = qobject_cast<PluginFactory *>(pluginInstance);

    if (!pluginFactory)
        return false;

    Plugin *plugin = pluginFactory->plugin();

    if (!plugin)
        return false;

    if (this->m_pluginConfigs.contains(pluginId))
        plugin->setConfigs(this->m_pluginConfigs[pluginId]);

    this->m_plugins[pluginId] = plugin;

    plugin->begin();

    return true;
}

bool PluginManager::unload(QString pluginId)
{
    if(!this->isLoaded(pluginId))
         return false;

    this->m_pluginConfigs[pluginId] = this->m_plugins[pluginId]->configs();
    this->m_plugins[pluginId]->end();
    delete this->m_plugins[pluginId];
    this->m_plugins.remove(pluginId);
    this->m_pluginLoader.setFileName(this->m_pluginsInfo[pluginId].fileName());
    this->m_pluginLoader.unload();

    return true;
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

    QStringList r = pipeline.split(QRegExp("[0-9a-zA-Z.<>=]+=[\"'][^\r^\n]+[\"']|!{1}|[0-9a-zA-Z.<>=]+"),
                                   QString::SkipEmptyParts);

    QList<QVariant> pipes;
    QList<QVariant> pipe;
    QString elementName;
    QMap<QString, QVariant> properties;

    int i = 0;
    int j = 0;
    int k = 0;

    foreach (QString p, r)
    {
        if (p.contains("="))
        {
            int eq = p.indexOf("=");
            QString key = p.left(eq);
            QString value = p.right(p.length() - eq - 1);

            if (value.startsWith("'") || value.startsWith("\""))
                value = value.mid(1, value.length() - 2);

            properties[key] = value;
        }
        else if (p.contains("<"))
        {
            int eq = p.indexOf("<");
            QString s1 = p.left(eq);
            QString s2 = p.right(p.length() - eq - 1);

            QString sender;
            QString signal;
            QString receiver;
            QString slot;

            if (s1.contains("."))
            {
                sender = QString("%1,%2").arg(i).arg(j);
                signal = s2.mid(1);
                QStringList receiverSlot = s1.split(".");
                receiver = receiverSlot[0] + ".";
                slot = receiverSlot[1];
            }
            else
            {
                QStringList senderSignal = s2.split(".");
                sender = senderSignal[0] + ".";
                signal = senderSignal[1];
                receiver = QString("%1,%2").arg(i).arg(j);
                slot = s1;
            }

            if (ss)
                *ss << (QStringList() << sender << signal << receiver << slot);
        }
        else if (p.contains(">"))
        {
            int eq = p.indexOf(">");
            QString s1 = p.left(eq);
            QString s2 = p.right(p.length() - eq - 1);

            QString sender;
            QString signal;
            QString receiver;
            QString slot;

            if (s2.contains("."))
            {
                sender = QString("%1,%2").arg(i).arg(j);
                signal = s1.mid(1);
                QStringList receiverSlot = s2.split(".");
                receiver = receiverSlot[0] + ".";
                slot = receiverSlot[1];
            }
            else
            {
                QStringList senderSignal = s1.split(".");
                sender = senderSignal[0] + ".";
                signal = senderSignal[1];
                receiver = QString("%1,%2").arg(i).arg(j);
                slot = s2;
            }

            if (ss)
                *ss << (QStringList() << sender << signal << receiver << slot);
        }
        else
        {
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

    if (ss)
        foreach (QStringList s, *ss)
        {
            if (s[0].endsWith("."))
                s[0] = references[s[0]];

            if (s[2].endsWith("."))
                s[2] = references[s[2]];
        }
}

int PluginManager::indexOfSubSequence(QStringList l, QStringList sub)
{
    if (sub.length() > l.length())
        return -1;

    for (int i = 0; i < l.length() - sub.length() + 1; i++)
    {
        int j = 0;
        bool eq = true;

        foreach (QString s, sub)
        {
            if (l[i + j] != s)
            {
                eq = false;

                break;
            }

            j++;
        }

        if (eq)
            return i;
    }

    return -1;
}

QList<QStringList> PluginManager::sequences(QList<QStringList> connections)
{
    QList<QStringList> nextConnections;

    while (true)
    {
        nextConnections.clear();
        bool wasChanged = false;

        foreach (QStringList connection, connections)
        {
            bool change = false;

            foreach (QStringList nextConnection, connections)
                if (nextConnection[0] == connection[connection.length() - 1])
                {
                    nextConnections.append(connection + nextConnection.mid(1));
                    wasChanged = true;
                    change = true;
                }

            if (!change)
                nextConnections.append(connection);
        }

        if (wasChanged)
            connections = nextConnections;
        else
            break;
    }

    QList<QStringList> sequences;

    foreach (QStringList sequence, nextConnections)
    {
        bool repeated = false;

        for (int oldSequence = 0; oldSequence < sequences.length(); oldSequence++)
        {
            if (this->indexOfSubSequence(sequences[oldSequence], sequence) >= 0)
            {
                repeated = true;

                break;
            }
            else if (this->indexOfSubSequence(sequence, sequences[oldSequence]) >= 0)
            {
                sequences[oldSequence] = sequence;

                break;
            }
        }

        if (!repeated)
            sequences.append(sequence);
    }

    return sequences;
}

QStringList PluginManager::lcs(QStringList a, QStringList b)
{
    if (a.isEmpty() || b.isEmpty())
        return QStringList();

    int l = a.length() + b.length() - 1;

    QStringList fill;
    int f;

    for (f = 0; f < b.length() - 1; f++)
        fill << "";

    QStringList sa = a + fill;

    fill.clear();

    for (f = 0; f < a.length() - 1; f++)
        fill << "";

    QStringList sb = fill + b;

    QStringList longest;
    QStringList cur;

    for (int k = 0; k < l; k++)
    {
        cur.clear();

        for (int c = 0; c < l; c++)
        {
            if (sa[c] != "" && sb[c] != "" && sa[c] == sb[c])
                cur.append(sa[c]);
            else
            {
                if (cur.length() > longest.length())
                    longest = cur;

                cur.clear();
            }
        }

        if (cur.length() > longest.length())
            longest = cur;

        if (sa[sa.length() - 1] == "")
        {
            sa.prepend("");
            sa.removeLast();
        }
        else
        {
            sb.removeFirst();
            sb.append("");
        }
    }

    return longest;
}

void PluginManager::alignSequences(QStringList sequence1,
                                   QStringList sequence2,
                                   QStringList *aSequence1,
                                   QStringList *aSequence2)
{
    QStringList cs = this->lcs(sequence1, sequence2);

    if (cs.isEmpty())
    {
        QStringList fill;
        int f;

        for (f = 0; f < sequence2.length(); f++)
            fill << "";

        if (aSequence1)
            *aSequence1 = sequence1 + fill;

        fill.clear();

        for (f = 0; f < sequence1.length(); f++)
            fill << "";

        if (aSequence2)
            *aSequence2 = fill + sequence2;
    }
    else
    {
        QStringList left1 = sequence1.mid(0, this->indexOfSubSequence(sequence1, cs));
        QStringList left2 = sequence2.mid(0, this->indexOfSubSequence(sequence2, cs));

        QStringList right1 = sequence1.mid(this->indexOfSubSequence(sequence1, cs) + cs.length());
        QStringList right2 = sequence2.mid(this->indexOfSubSequence(sequence2, cs) + cs.length());

        QStringList als1;
        QStringList als2;
        QStringList ars1;
        QStringList ars2;

        this->alignSequences(left1, left2, &als1, &als2);
        this->alignSequences(right1, right2, &ars1, &ars2);

        if (aSequence1)
            *aSequence1 = als1 + cs + ars1;

        if (aSequence2)
            *aSequence2 = als2 + cs + ars2;
    }
}

void PluginManager::setPipeline(QString pipeline)
{
    pipeline = "element1 objectName=el1 prop1=10 prop2=val2 " \
               "el1. ! element2 .signal1>el5.slot1 " \
               "el1. ! element3 prop3='Hello, world !!!' ! element1 ! element5 ! el5. " \
               "element4 prop1=3.14 slot5<el5.signal5 ! el5. " \
               "element5 objectName=el5 el1.signal2>slot2 ! element6 prop1=val1 el1.slot1<.signal1";

    // Signals & Slots sintax:
    //
    // sender .signal>receiver.slot
    // receiver sender.signal>slot
    // sender receiver.slot<.signal
    // receiver slot<sender.signal

    // http://lists.trolltech.com/qt-interest/2005-12/msg00281.html
}
