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

#include "plugin/pluginmanager.h"

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
    this->m_curId = 0;
    this->resetRegexpDict();

    QDir pluginDir("../share/plugins");

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

            Plugin *plugin = qobject_cast<Plugin *>(this->m_pluginLoader.instance());

            if (!plugin)
                continue;

            QJsonObject metaData = this->m_pluginLoader.metaData();

            this->m_pluginsInfo[metaData["pluginId"].toString()] = PluginInfo(fileName,
                                                                              metaData.toVariantMap());

            this->m_availableElementTypes << metaData["pluginId"].toString();
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

    Plugin *plugin = qobject_cast<Plugin *>(this->m_pluginLoader.instance());

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

void PluginManager::resetRegexpDict()
{
    this->m_regexpDict["bool"] = "true|false";
    this->m_regexpDict["int"] = "[0-9]+";
    this->m_regexpDict["float"] = "[0-9]+\\.[0-9]+|\\.[0-9]+|[0-9]+\\.";
    this->m_regexpDict["pipeSep"] = "!";

    this->m_regexpDict["number"] = this->m_regexpDict["float"] +
                                   "|" +
                                   this->m_regexpDict["int"];

    this->m_regexpDict["string"] = "'(?:\\\\'|[^'])*'|\"(?:\\\\\"|[^\"])*\"";

    this->m_regexpDict["colorConst"] = "white|" \
                                       "black|" \
                                       "red|" \
                                       "darkRed|" \
                                       "green|" \
                                       "darkGreen|" \
                                       "blue|" \
                                       "darkBlue|" \
                                       "cyan|" \
                                       "darkCyan|" \
                                       "magenta|" \
                                       "darkMagenta|" \
                                       "yellow|" \
                                       "darkYellow|" \
                                       "gray|" \
                                       "darkGray|" \
                                       "lightGray|" \
                                       "transparent|" \
                                       "color0|" \
                                       "color1";

    this->m_regexpDict["qColor"] = "qColor\\s*\\(\\s*(?:" +
                                   this->m_regexpDict["colorConst"] +
                                   ")?\\s*\\)";

    this->m_regexpDict["size"] = "(?:size|sizeF)\\s*\\(\\s*(?:(?:" +
                                 this->m_regexpDict["number"] +
                                 ")\\s*,\\s*(?:" +
                                 this->m_regexpDict["number"] +
                                 "))?\\s*\\)";

    this->m_regexpDict["point"] = "(?:point|pointF)\\s*\\(\\s*(?:(?:" +
                                  this->m_regexpDict["number"] +
                                  ")\\s*,\\s*(?:" +
                                  this->m_regexpDict["number"] +
                                  "))?\\s*\\)";

    this->m_regexpDict["rect"] = "(?:rect|rectF)\\s*\\(\\s*(?:(?:" +
                                 this->m_regexpDict["number"] +
                                 ")(?:\\s*,\\s*(?:" +
                                 this->m_regexpDict["number"] +
                                 ")){3})?\\s*\\)";

    this->m_regexpDict["line"] = "(?:line|lineF)\\s*\\(\\s*(?:(?:" +
                                 this->m_regexpDict["number"] +
                                 ")(?:\\s*,\\s*(?:" +
                                 this->m_regexpDict["number"] +
                                 ")){3})?\\s*\\)";

    this->m_regexpDict["date"] = "date\\s*\\(\\s*(?:(?:" +
                                 this->m_regexpDict["number"] +
                                 ")(?:\\s*,\\s*(?:" +
                                 this->m_regexpDict["number"] +
                                 ")){2})?\\s*\\)";

    this->m_regexpDict["time"] = "time\\s*\\(\\s*(?:(?:" +
                                 this->m_regexpDict["number"] +
                                 ")(?:\\s*,\\s*(?:" +
                                 this->m_regexpDict["number"] +
                                 ")){3})?\\s*\\)";

    this->m_regexpDict["bitsValues"] = "0|1";

    this->m_regexpDict["bits"] = "bits\\s*\\(\\s*(?:" +
                                 this->m_regexpDict["bitsValues"] +
                                 "|\\s)*\\s*\\)";

    this->m_regexpDict["bytes"] = "b(?:" + this->m_regexpDict["string"] + ")";

    // Bad repetition
    this->m_regexpDict["urlString"] = "(?:[a-zA-Z]+\\://)*" \
                                      "(?:[0-9a-zA-Z._]+(?:\\:[0-9a-zA-Z%.]+)?@)?" \
                                      "[0-9a-zA-Z]+(?:-[0-9a-zA-Z]+)*" \
                                      "(?:\\.[0-9a-zA-Z]+(?:-[0-9a-zA-Z]+)*)*" \
                                      "\\.[a-zA-Z]+(?:\\:\\d+)?(?:/[0-9a-zA-Z%.-]+)*" \
                                      "(?:/|\\?[a-zA-Z_]\\w*=[0-9a-zA-Z_%.+-]+" \
                                      "(?:(?:&|;)[a-zA-Z_]\\w*=[0-9a-zA-Z_%.+-]+)*)?" \
                                      "(?:#[0-9a-zA-Z%.]+)?";

    this->m_regexpDict["url"] = "url\\s*\\(\\s*(?:" +
                                this->m_regexpDict["urlString"] +
                                ")?\\s*\\)";

    this->m_regexpDict["stringList"] = "\\[\\s*(?:(?:" +
                                       this->m_regexpDict["string"] +
                                       ")\\s*(?:,\\s*(?:" +
                                       this->m_regexpDict["string"] +
                                       ")\\s*)*)?\\]";

    this->m_regexpDict["commonValues"] = "(?:" +
                                         this->m_regexpDict["bool"] +
                                         ")|(?:" +
                                         this->m_regexpDict["number"] +
                                         ")|(?:" +
                                         this->m_regexpDict["string"] +
                                         ")|(?:" +
                                         this->m_regexpDict["qColor"] +
                                         ")|(?:" +
                                         this->m_regexpDict["size"] +
                                         ")|(?:" +
                                         this->m_regexpDict["point"] +
                                         ")|(?:" +
                                         this->m_regexpDict["rect"] +
                                         ")|(?:" +
                                         this->m_regexpDict["line"] +
                                         ")|(?:" +
                                         this->m_regexpDict["date"] +
                                         ")|(?:" +
                                         this->m_regexpDict["time"] +
                                         ")|(?:" +
                                         this->m_regexpDict["bits"] +
                                         ")|(?:" +
                                         this->m_regexpDict["bytes"] +
                                         ")|(?:" +
                                         this->m_regexpDict["url"] +
                                         ")|(?:" +
                                         this->m_regexpDict["stringList"] +
                                         ")";

    this->m_regexpDict["list"] = "\\[\\s*(?:(?:" +
                                 this->m_regexpDict["commonValues"] +
                                 ")\\s*(?:,\\s*(?:" +
                                 this->m_regexpDict["commonValues"] +
                                 ")\\s*)*)?\\]";

    this->m_regexpDict["dictKeyValue"] = "(?:" +
                                         this->m_regexpDict["string"] +
                                         ")\\s*:\\s*(?:" +
                                         this->m_regexpDict["commonVals"] +
                                         "|(?:" +
                                         this->m_regexpDict["list"] +
                                         "))";

    this->m_regexpDict["dict"] = "\\{\\s*(?:(?:" +
                                 this->m_regexpDict["dictKeyValue"] +
                                 ")\\s*(?:,\\s*(?:" +
                                 this->m_regexpDict["dictKeyValue"] +
                                 ")\\s*)*)?\\}";

    this->m_regexpDict["anyString"] = "[^ \\t\\r\\n" +
                                      this->m_regexpDict["pipeSep"] +
                                      "]+";

    this->m_regexpDict["extendedValues"] = "(?:" +
                                           this->m_regexpDict["commonValues"] +
                                           ")|(?:" +
                                           this->m_regexpDict["list"] +
                                           ")|(?:" +
                                           this->m_regexpDict["dict"] +
                                           ")|(?:" +
                                           this->m_regexpDict["anyString"] +
                                           ")";

    this->m_regexpDict["var"] = "[a-zA-Z_]\\w*";


    this->m_regexpDict["property"] = "(?:" +
                                     this->m_regexpDict["var"] +
                                     ")\\s*=\\s*(?:" +
                                     this->m_regexpDict["extendedValues"] +
                                     ")";

    this->m_regexpDict["methodArgs"] = "(?:" +
                                       this->m_regexpDict["var"] +
                                       ")(?:\\s+(?:" +
                                       this->m_regexpDict["var"] +
                                       "))*(?:\\s*<\\s*(?:" +
                                       this->m_regexpDict["var"] +
                                       ")\\s*(,\\s*(?:" +
                                       this->m_regexpDict["var"] +
                                       ")\\s*)*>)?(?:\\s*(?:\\*|&)(?:\\s*(?:" +
                                       this->m_regexpDict["var"] +
                                       "))?)?";

    this->m_regexpDict["method"] = "(?:" +
                                   this->m_regexpDict["var"] +
                                   ")\\s*\\(\\s*(?:" +
                                   this->m_regexpDict["methodArgs"] +
                                   ")?\\s*\\)";

    this->m_regexpDict["objectMethod"] = "(?:" +
                                         this->m_regexpDict["var"] +
                                         ")\\s*\\.\\s*(?:" +
                                         this->m_regexpDict["method"] +
                                         ")";

    this->m_regexpDict["signalSlotLt"] = "(?:(?:" +
                                         this->m_regexpDict["objectMethod"] +
                                         ")\\s*<\\s*(?:" +
                                         this->m_regexpDict["method"] +
                                         "))|(?:(?:" +
                                         this->m_regexpDict["method"] +
                                         ")\\s*<\\s*(?:" +
                                         this->m_regexpDict["objectMethod"] +
                                         "))";

    this->m_regexpDict["signalSlotGt"] = "(?:(?:" +
                                         this->m_regexpDict["objectMethod"] +
                                         ")\\s*>\\s*(?:" +
                                         this->m_regexpDict["method"] +
                                         "))|(?:(?:" +
                                         this->m_regexpDict["method"] +
                                         ")\\s*>\\s*(?:" +
                                         this->m_regexpDict["objectMethod"] +
                                         "))";

    this->m_regexpDict["signalSlot"] = "(?:" +
                                       this->m_regexpDict["signalSlotLt"] +
                                       ")|(?:" +
                                       this->m_regexpDict["signalSlotGt"] +
                                       ")";

    this->m_regexpDict["elementRef"] = this->m_regexpDict["var"] + "\\.";

    this->m_regexpDict["element"] = "(?:" +
                                    this->m_regexpDict["elementRef"] +
                                    ")|(?:" +
                                    this->m_regexpDict["var"] +
                                    ")(?:\\s+(?:(?:" +
                                    this->m_regexpDict["property"] +
                                    ")|(?:" +
                                    this->m_regexpDict["signalSlot"] +
                                    ")))*";

    this->m_regexpDict["pipeline"] = "(?:" +
                                     this->m_regexpDict["element"] +
                                     ")(?:\\s+(?:" +
                                     this->m_regexpDict["element"] +
                                     "))*(?:\\s*(?:" +
                                     this->m_regexpDict["pipeSep"] +
                                     ")\\s*(?:" +
                                     this->m_regexpDict["element"] +
                                     ")(?:\\s+(?:" +
                                     this->m_regexpDict["element"] +
                                     "))*)*";

    this->m_regexpDict["pipelineElements"] = "(?:" +
                                             this->m_regexpDict["property"] +
                                             ")|(?:" +
                                             this->m_regexpDict["signalSlot"] +
                                             ")|(?:" +
                                             this->m_regexpDict["elementRef"] +
                                             ")|(?:" +
                                             this->m_regexpDict["var"] +
                                             ")|(?:" +
                                             this->m_regexpDict["pipeSep"] +
                                             ")";
}

int PluginManager::requestId()
{
    while (this->m_usedIds.contains(this->m_curId))
        this->m_curId++;

    this->m_usedIds << this->m_curId;

    return this->m_curId++;
}

void PluginManager::removeId(int id)
{
    if (!this->m_usedIds.contains(id))
        return;

    this->m_usedIds.removeAll(id);

    if (id < this->m_curId)
        this->m_curId = id;
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

QString PluginManager::addElement(QString pluginId)
{
    if (!this->load(pluginId))
        return "";

    Element *element = this->m_plugins[pluginId]->newElement();

    if (!element)
        return "";

    QString elementId = QString("%1").arg(this->requestId());

    this->m_elements[elementId] = element;
    this->m_elements[elementId]->setManager(this);

    return elementId;
}

bool PluginManager::removeElement(QString elementId)
{
    if (!this->m_elements.contains(elementId))
        return true;

    QString pluginId = this->m_instances1[elementId].toList()[0].toString();

    delete this->m_elements[elementId];
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

    this->removeId(elementId.toInt());

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

QStringList PluginManager::regexpFindAll(QString regexp, QString text)
{
    QRegExp rx(regexp);
    QString txt(text);
    QStringList match;

    while (true)
    {
        int pos = rx.indexIn(txt);
        int matchedLength = rx.matchedLength();

        if (matchedLength < 1)
            break;

        match << txt.mid(pos, matchedLength);
        txt = txt.mid(pos + matchedLength);
    }

    return match;
}

/// Parse a string and returns the native value.
QVariant PluginManager::parseValue(QString value)
{
    // QVariant(Qt::GlobalColor color)

    // Bool
    if (QRegExp(this->m_regexpDict["bool"]).exactMatch(value))
        return (value == "true")? true: false;
    // Qt::GlobalColor
    else if (QRegExp(this->m_regexpDict["qColor"]).exactMatch(value))
    {
        QStringList r = this->regexpFindAll(this->m_regexpDict["colorConst"],
                                            value);

        if (r[0] == "white")
            return Qt::white;
        else if (r[0] == "black")
            return Qt::black;
        else if (r[0] == "red")
            return Qt::red;
        else if (r[0] == "darkRed")
            return Qt::darkRed;
        else if (r[0] == "green")
            return Qt::green;
        else if (r[0] == "darkGreen")
            return Qt::darkGreen;
        else if (r[0] == "blue")
            return Qt::blue;
        else if (r[0] == "darkBlue")
            return Qt::darkBlue;
        else if (r[0] == "cyan")
            return Qt::cyan;
        else if (r[0] == "darkCyan")
            return Qt::darkCyan;
        else if (r[0] == "magenta")
            return Qt::magenta;
        else if (r[0] == "darkMagenta")
            return Qt::darkMagenta;
        else if (r[0] == "yellow")
            return Qt::yellow;
        else if (r[0] == "darkYellow")
            return Qt::darkYellow;
        else if (r[0] == "gray")
            return Qt::gray;
        else if (r[0] == "darkGray")
            return Qt::darkGray;
        else if (r[0] == "lightGray")
            return Qt::lightGray;
        else if (r[0] == "transparent")
            return Qt::transparent;
        else if (r[0] == "color0")
            return Qt::color0;
        else if (r[0] == "color1")
            return Qt::color1;
        else
            return Qt::color0;
    }
    // Size
    else if (QRegExp(this->m_regexpDict["size"]).exactMatch(value))
    {
        QStringList r = this->regexpFindAll(this->m_regexpDict["number"],
                                            value);

        if (value.startsWith("sizeF"))
        {
            if (r.length() == 2)
                return QSizeF(r[0].toFloat(), r[1].toFloat());
            else
                return QSizeF();
        }
        else
        {
            if (r.length() == 2)
                return QSize(r[0].toFloat(), r[1].toFloat());
            else
                return QSize();
        }
    }
    // Point
    else if (QRegExp(this->m_regexpDict["point"]).exactMatch(value))
    {
        QStringList r = this->regexpFindAll(this->m_regexpDict["number"],
                                            value);

        if (value.startsWith("pointF"))
        {
            if (r.length() == 2)
                return QPointF(r[0].toFloat(), r[1].toFloat());
            else
                return QPointF();
        }
        else
        {
            if (r.length() == 2)
                return QPoint(r[0].toFloat(), r[1].toFloat());
            else
                return QPoint();
        }
    }
    // Rect
    else if (QRegExp(this->m_regexpDict["rect"]).exactMatch(value))
    {
        QStringList r = this->regexpFindAll(this->m_regexpDict["number"],
                                            value);

        if (value.startsWith("rectF"))
        {
            if (r.length() == 4)
                return QRectF(r[0].toFloat(), r[1].toFloat(), r[2].toFloat(), r[3].toFloat());
            else
                return QRectF();
        }
        else
        {
            if (r.length() == 4)
                return QRect(r[0].toFloat(), r[1].toFloat(), r[2].toFloat(), r[3].toFloat());
            else
                return QRect();
        }
    }
    // Line
    else if (QRegExp(this->m_regexpDict["line"]).exactMatch(value))
    {
        QStringList r = this->regexpFindAll(this->m_regexpDict["number"],
                                            value);

        if (value.startsWith("lineF"))
        {
            if (r.length() == 4)
                return QLineF(r[0].toFloat(), r[1].toFloat(), r[2].toFloat(), r[3].toFloat());
            else
                return QLineF();
        }
        else
        {
            if (r.length() == 4)
                return QLine(r[0].toFloat(), r[1].toFloat(), r[2].toFloat(), r[3].toFloat());
            else
                return QLine();
        }
    }
    // Date
    else if (QRegExp(this->m_regexpDict["date"]).exactMatch(value))
    {
        QStringList r = this->regexpFindAll(this->m_regexpDict["number"],
                                            value);

        if (r.length() == 3)
            return QDate(r[0].toFloat(), r[1].toFloat(), r[2].toFloat());
        else
            return QDate();
    }
    // Time
    else if (QRegExp(this->m_regexpDict["time"]).exactMatch(value))
    {
        QStringList r = this->regexpFindAll(this->m_regexpDict["number"],
                                            value);

        if (r.length() == 4)
            return QTime(r[0].toFloat(), r[1].toFloat(), r[2].toFloat(), r[3].toFloat());
        else
            return QTime();
    }
    // Bits
    else if (QRegExp(this->m_regexpDict["bits"]).exactMatch(value))
    {
        QStringList r = this->regexpFindAll(this->m_regexpDict["bitsValues"],
                                            value);
        QBitArray bits(r.length());

        for (int i = 0; i < r.length(); i++)
            if (r[i] == "0")
                bits.setBit(i, false);
            else
                bits.setBit(i, true);

        return bits;
    }
    // Url
    else if (QRegExp(this->m_regexpDict["url"]).exactMatch(value))
    {
        QStringList r = this->regexpFindAll(this->m_regexpDict["urlString"],
                                            value);

        return QUrl(r[0]);
    }
    // Bytes
    else if (QRegExp(this->m_regexpDict["bytes"]).exactMatch(value))
        return value.mid(2, value.length() - 3).toUtf8();
    // String
    else if (QRegExp(this->m_regexpDict["string"]).exactMatch(value))
        return value.mid(1, value.length() - 2);
    // String List
    else if (QRegExp(this->m_regexpDict["stringList"]).exactMatch(value))
    {
        QStringList r = this->regexpFindAll(this->m_regexpDict["string"],
                                            value);

        QStringList strList;

        foreach (QString str, r)
            strList << str.mid(1, str.length() - 2);

        return strList;
    }
    // Variant List
    else if (QRegExp(this->m_regexpDict["list"]).exactMatch(value))
    {
        QStringList r = this->regexpFindAll(this->m_regexpDict["commonValues"],
                                            value.mid(1, value.length() - 2));

        QList<QVariant> l;

        foreach (QString item, r)
            l << this->parseValue(item);

        return l;
    }
    // Dictionary
    else if (QRegExp(this->m_regexpDict["dict"]).exactMatch(value))
    {
        QStringList r = this->regexpFindAll(this->m_regexpDict["dictKeyValue"],
                                            value.mid(1, value.length() - 2));

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
    // Float
    else if (QRegExp(this->m_regexpDict["float"]).exactMatch(value))
        return value.toFloat();
    // Int
    else if (QRegExp(this->m_regexpDict["int"]).exactMatch(value))
        return value.toInt();
    // Any String
    else
        return value;
}

QStringList PluginManager::parseSignalSlotLt(QString id, QString element)
{
    int eq = element.indexOf("<");
    QString s1 = element.left(eq).trimmed();
    QString s2 = element.right(element.length() - eq - 1).trimmed();

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
        receiver = id;
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
        sender = id;
        signal = s2;
    }

    signal = signal.split(QRegExp("\\s+"), QString::SkipEmptyParts).join("");
    slot = slot.split(QRegExp("\\s+"), QString::SkipEmptyParts).join("");

    return (QStringList() << sender << signal << receiver << slot);
}

QStringList PluginManager::parseSignalSlotGt(QString id, QString element)
{
    int eq = element.indexOf(">");
    QString s1 = element.left(eq).trimmed();
    QString s2 = element.right(element.length() - eq - 1).trimmed();

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
        sender = id;
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
        receiver = id;
        slot = s2;
    }

    signal = signal.split(QRegExp("\\s+"), QString::SkipEmptyParts).join("");
    slot = slot.split(QRegExp("\\s+"), QString::SkipEmptyParts).join("");

    return (QStringList() << sender << signal << receiver << slot);
}

QStringList PluginManager::parseSignalSlot(QString id, QString element)
{
    if (QRegExp(this->m_regexpDict["signalSlotLt"]).exactMatch(element))
        return this->parseSignalSlotLt(id, element);
    else
        return this->parseSignalSlotGt(id, element);
}

bool PluginManager::parsePipeline(QString pipeline,
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

    if (!QRegExp(this->m_regexpDict["pipeline"]).exactMatch(pipeline))
    {
        qDebug() << QRegExp(this->m_regexpDict["pipeline"]).errorString();

        return false;
    }

    QStringList r = this->regexpFindAll(this->m_regexpDict["pipelineElements"],
                                        pipeline);

    QStringList pipe;
    QList<QStringList> pipes;
    QString curId;
    int curIntId = 0;
    QMap<QString, QString> references; // reference. -> id

    foreach (QString p, r)
    {
        // Parse property
        if (QRegExp(this->m_regexpDict["property"]).exactMatch(p))
        {
            int eq = p.indexOf("=");

            QString key = p.left(eq).trimmed();
            QString value = p.right(p.length() - eq - 1).trimmed();

            QList<QVariant> list = (*instances)[curId].toList();
            QMap<QString, QVariant> map = list[1].toMap();
            map[key] = this->parseValue(value);
            list[1] = map;
            (*instances)[curId] = list;

            if (key == "objectName")
                references[QString("%1.").arg(value)] = curId;
        }
        // Parse Signals & Slots
        else if (QRegExp(this->m_regexpDict["signalSlot"]).exactMatch(p))
        {
            if (ss)
                *ss << this->parseSignalSlot(curId, p);
        }
        // Parse element reference.
        else if (QRegExp(this->m_regexpDict["elementRef"]).exactMatch(p))
            pipe << p;
        // Parse element.
        else if (QRegExp(this->m_regexpDict["var"]).exactMatch(p))
        {
            if (this->m_pipelineRoutingMode == Fail &&
                !this->m_availableElementTypes.contains(p))
            {
                if (instances)
                    *instances = QMap<QString, QVariant>();

                if (connections)
                    *connections = QList<QStringList>();

                if (ss)
                    *ss = QList<QStringList>();

                return false;
            }

            curId = QString("%1").arg(curIntId++);
            (*instances)[curId] = QList<QVariant>() << p << QMap<QString, QVariant>();
            pipe << curId;
        }
        // Parse pipe.
        else if (QRegExp(this->m_regexpDict["pipeSep"]).exactMatch(p))
        {
            pipes << pipe;
            pipe.clear();
        }
    }

    pipes << pipe;
    pipe.clear();

    // Solve connections between elements.
    foreach (QStringList pipe, pipes)
        for (int i = 0; i < pipe.length() - 1; i++)
        {
            QString cur;

            if (pipe.at(i).endsWith("."))
                cur = references[pipe.at(i)];
            else
                cur = pipe.at(i);

            QString nxt;

            if (pipe.at(i + 1).endsWith("."))
                nxt = references[pipe.at(i + 1)];
            else
                nxt = pipe.at(i + 1);

            if (connections)
                *connections << (QStringList() << cur << nxt);
        }

    // Solve signals & slots.
    if (ss)
        for (int i = 0; i < ss->length(); i++)
        {
            if (ss[i][0].endsWith("."))
                (*ss)[i][0] = references[(*ss)[i][0]];

            if (ss[i][2].endsWith("."))
                (*ss)[i][2] = references[(*ss)[i][2]];
        }

    // Fix Pipeline
    if (this->m_pipelineRoutingMode == Remove ||
        this->m_pipelineRoutingMode == Force)
    {
        QStringList removeId;

        foreach (QString id, instances->keys())
            if (!this->m_availableElementTypes.contains((*instances)[id].toList()[0].toString()))
                removeId << id;

        foreach (QString id, removeId)
        {
            instances->remove(id);

            QStringList iConns;
            QStringList oConns;

            for (int i = 0; i < connections->length(); i++)
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

            for (int i = 0; i < ss->length(); i++)
                if ((*ss)[i][0] == id || (*ss)[i][2] == id)
                {
                    ss->removeAt(i);
                    i--;
                }
        }
    }

    return true;
}

QString PluginManager::bestMatchId(QMap<QString, QVariant> instances1, QMap<QString, QVariant> instances2, QString id2)
{
    QString type2 = instances2[id2].toList().at(0).toString();
    QMap<QString, QVariant> properties2 = instances2[id2].toList().at(1).toMap();
    QString bestId = "";
    int bestScore = 0;

    foreach (QString id1, instances1.keys())
    {
        QString type1 = instances1[id1].toList().at(0).toString();
        QMap<QString, QVariant> properties1 = instances1[id1].toList().at(1).toMap();

        if (type1 != type2)
            continue;

        if (properties1.contains("objectName") &&
            properties2.contains("objectName") &&
            properties1["objectName"].toString() == properties2["objectName"].toString())
            return id1;

        QSet<QString> propertiesSet1 = QSet<QString>::fromList(properties1.keys());
        QSet<QString> propertiesSet2 = QSet<QString>::fromList(properties2.keys());

        QSet<QString> commonProperties = propertiesSet1.intersect(propertiesSet2);
        QSet<QString> diffProperties = propertiesSet1.subtract(propertiesSet2) +
                                       propertiesSet2.subtract(propertiesSet1);

        int score = commonProperties.count() - 2 * diffProperties.count();

        foreach (QString property, commonProperties)
            if (properties1[property].toString() == properties2[property].toString())
                score++;
            else
                score--;

        if (bestId == "" || score > bestScore)
        {
            bestId = id1;
            bestScore = score;
        }
    }

    return bestId;
}

QString PluginManager::changeId(QString srcId,
                                QString dstId,
                                QMap<QString, QVariant> *instances,
                                QList<QStringList> *connections,
                                QList<QStringList> *ss)
{
    QString ghostId = "";

    if (instances && instances->contains(srcId))
    {
        if (instances->contains(dstId))
        {
            ghostId = QString(".%1").arg(dstId);
            (*instances)[ghostId] = (*instances)[dstId];
        }

        (*instances)[dstId] = (*instances)[srcId];
        instances->remove(srcId);
    }

    if (connections)
        for (int i = 0; i < connections->length(); i++)
        {
            QStringList connection = connections->at(i);

            if (connection[0] == dstId)
            {
                ghostId = QString(".%1").arg(dstId);
                connection[0] = ghostId;
            }
            else if (connection[0] == srcId)
                connection[0] = dstId;

            if (connection[1] == dstId)
            {
                ghostId = QString(".%1").arg(dstId);
                connection[1] = ghostId;
            }
            else if (connection[1] == srcId)
                connection[1] = dstId;

            (*connections)[i] = connection;
        }

    if (ss)
        for (int i = 0; i < ss->length(); i++)
        {
            QStringList s = ss->at(i);

            if (s[0] == dstId)
            {
                ghostId = QString(".%1").arg(dstId);
                s[0] = ghostId;
            }
            else if (s[0] == srcId)
                s[0] = dstId;

            if (s[2] == dstId)
            {
                ghostId = QString(".%1").arg(dstId);
                s[2] = ghostId;
            }
            else if (s[2] == srcId)
                s[2] = dstId;

            (*ss)[i] = s;
        }

    return ghostId;
}

void PluginManager::alignPipelines(QMap<QString, QVariant> instances1,
                                   QMap<QString, QVariant> *instances2,
                                   QList<QStringList> *connections2,
                                   QList<QStringList> *ss2)
{
    while (true)
    {
        bool cont = false;

        foreach (QString id2, instances2->keys())
        {
            QString id1 = this->bestMatchId(instances1, *instances2, id2);

            if (id1 != "" && id1 != id2)
            {
                this->changeId(id2, id1, instances2, connections2, ss2);
                cont = true;

                break;
            }
        }

        if (!cont)
            break;
    }
}

template <typename T> QList<T> PluginManager::subtractLists(QList<T> list1, QList<T> list2)
{
    QList<T> list;

    foreach (T element, list1)
        if (!list2.contains(element))
            list << element;

    return list;
}

QStringList PluginManager::subtractMapKeys(QMap<QString, QVariant> instances1,
                                      QMap<QString, QVariant> instances2)
{
    return this->subtractLists(instances1.keys(), instances2.keys());
}

void PluginManager::setPipeline(QString pipeline2)
{
    QMap<QString, QVariant> instances2;
    QList<QStringList> connections2;
    QList<QStringList> ss2;

    this->parsePipeline(pipeline2, &instances2, &connections2, &ss2);
    this->alignPipelines(this->m_instances1, &instances2, &connections2, &ss2);

    QStringList removeElements = this->subtractMapKeys(this->m_instances1, instances2);

    QList<QStringList> disconnectElementsSS = this->subtractLists(this->m_ss1, ss2);
    QList<QStringList> disconnectElements = this->subtractLists(this->m_connections1, connections2);

    QStringList addElements = this->subtractMapKeys(instances2, this->m_instances1);

    QList<QStringList> connectElements = this->subtractLists(connections2, this->m_connections1);
    QList<QStringList> connectElementsSS = this->subtractLists(ss2, this->m_ss1);





/*
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

//    foreach (QStringList change, changeId)
//        this->changeElementId(change[0], change[1]);

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
        */
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
