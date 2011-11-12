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
 */

#include <QDir>
#include <QDebug>

#include "../../include/shell/shellmanager.h"
#include "../../include/shell/shellfactory.h"

ShellManager::ShellManager(QObject *parent): QObject(parent)
{
    QDir shellDir("share/shells");

    foreach (QString dirext, shellDir.entryList(QDir::AllDirs | QDir::NoDot | QDir::NoDotDot, QDir::Name))
    {
        shellDir.cd(dirext);

        foreach (QString shellFile, shellDir.entryList(QDir::Files, QDir::Name))
        {
            QString fileName = shellDir.absoluteFilePath(shellFile);

            if (!QLibrary::isLibrary(fileName))
                continue;

            qDebug() << "Loading: " << fileName;

            this->shellLoader.setFileName(fileName);

            if (!this->shellLoader.load())
            {
                qDebug() << this->shellLoader.errorString();

                continue;
            }

            QObject *shellInstance = this->shellLoader.instance();

            if (!shellInstance)
                continue;

            ShellFactory *shellFactory = qobject_cast<ShellFactory *>(shellInstance);

            if (!shellFactory)
                continue;

            Shell *shell = shellFactory->shell();

            if (!shell)
                continue;

            this->shellsInfo[shell->id()] = ShellInfo(fileName,
                                                      false,
                                                      shell->id(),
                                                      shell->name(),
                                                      shell->version(),
                                                      shell->summary(),
                                                      shell->type(),
                                                      shell->thumbnail(),
                                                      shell->license(),
                                                      shell->author(),
                                                      shell->website(),
                                                      shell->mail(),
                                                      shell->isConfigurable());

            delete shell;
            this->shellLoader.unload();
        }

        shellDir.cdUp();
    }
}

ShellManager::~ShellManager()
{
    if (this->activeShellId != "")
        disableShell(this->activeShellId);
}

QList<QVariant> ShellManager::shellsToQml()
{
    QList<QVariant> shellList;

    foreach (ShellInfo shell, this->shellsInfo)
    {
        QMap<QString, QVariant> shellInfoMap;

        shellInfoMap["shellId"] = QVariant(shell.id);
        shellInfoMap["isEnabled"] = QVariant(shell.isEnabled);
        shellInfoMap["name"] = QVariant(shell.name);
        shellInfoMap["version"] = QVariant(shell.version);
        shellInfoMap["summary"] = QVariant(shell.summary);
        shellInfoMap["type"] = QVariant(shell.type);
        shellInfoMap["thumbnail"] = QVariant(shell.thumbnail);
        shellInfoMap["license"] = QVariant(shell.license);
        shellInfoMap["author"] = QVariant(shell.author);
        shellInfoMap["website"] = QVariant(shell.website);
        shellInfoMap["mail"] = QVariant(shell.mail);
        shellInfoMap["isConfigurable"] = QVariant(shell.isConfigurable);

        shellList << shellInfoMap;
    }

    return shellList;
}

QWidget *ShellManager::widget(QString id)
{
    if (this->activeShellId == id || id == "")
        return this->activeShell->widget();

    return NULL;
}

bool ShellManager::setShell()
{
    return setShell("shell.DefaultShell");
}

bool ShellManager::setShell(QString id)
{
    if (this->activeShellId != "")
        disableShell(this->activeShellId);

    enableShell(id);
    this->activeShellId = id;

    return true;
}

bool ShellManager::enableShell(QString id)
{
    if (!this->shellsInfo.contains(id))
        return false;

    this->shellLoader.setFileName(this->shellsInfo[id].fileName);

    if (!this->shellLoader.load())
        return false;

    QObject *shellInstance = this->shellLoader.instance();

    if (!shellInstance)
        return false;

    ShellFactory *shellFactory = qobject_cast<ShellFactory *>(shellInstance);

    if (!shellFactory)
        return false;

    Shell *shell = shellFactory->shell();

    if (!shell)
        return false;

    this->shellsInfo[id].isEnabled = true;
    this->activeShell = shell;
    this->activeShell->begin();

    connect(this->activeShell, SIGNAL(takePicture()), this, SLOT(onTakePicture()));
    connect(this->activeShell, SIGNAL(startStopRecord()), this, SLOT(onStartStopRecord()));
    connect(this->activeShell, SIGNAL(deviceSelected(QString)), this, SLOT(onDeviceSelected(QString)));
    connect(this->activeShell, SIGNAL(pluginActivated(QString)), this, SLOT(onPluginActivated(QString)));
    connect(this->activeShell, SIGNAL(pluginDeactivated(QString)), this, SLOT(onPluginDeactivated(QString)));
    connect(this->activeShell, SIGNAL(pluginMoved(int, int)), this, SLOT(onPluginMoved(int, int)));
    connect(this->activeShell, SIGNAL(pluginConfigureClicked(QString)), this, SLOT(onPluginConfigureClicked(QString)));
    connect(this->activeShell, SIGNAL(deviceConfigureClicked(QString)), this, SLOT(onDeviceConfigureClicked(QString)));
    connect(this->activeShell, SIGNAL(closed()), this, SLOT(onClosed()));

    return true;
}

bool ShellManager::disableShell(QString id)
{
    if (!this->shellsInfo.contains(id) || this->activeShellId != id)
        return false;

    disconnect(this->activeShell, SIGNAL(takePicture()), this, SLOT(onTakePicture()));
    disconnect(this->activeShell, SIGNAL(startStopRecord()), this, SLOT(onStartStopRecord()));
    disconnect(this->activeShell, SIGNAL(deviceSelected(QString)), this, SLOT(onDeviceSelected(QString)));
    disconnect(this->activeShell, SIGNAL(pluginActivated(QString)), this, SLOT(onPluginActivated(QString)));
    disconnect(this->activeShell, SIGNAL(pluginDeactivated(QString)), this, SLOT(onPluginDeactivated(QString)));
    disconnect(this->activeShell, SIGNAL(pluginMoved(int, int)), this, SLOT(onPluginMoved(int, int)));
    disconnect(this->activeShell, SIGNAL(pluginConfigureClicked(QString)), this, SLOT(onPluginConfigureClicked(QString)));
    disconnect(this->activeShell, SIGNAL(deviceConfigureClicked(QString)), this, SLOT(onDeviceConfigureClicked(QString)));
    disconnect(this->activeShell, SIGNAL(closed()), this, SLOT(onClosed()));

    this->activeShell->end();
    delete this->activeShell;
    this->activeShell = NULL;
    this->shellLoader.setFileName(this->shellsInfo[id].fileName);
    this->shellLoader.unload();
    this->shellsInfo[id].isEnabled = false;
    this->activeShellId = "";

    return true;
}

void ShellManager::configureShell(QString id)
{
    if (this->activeShellId == id)
        this->activeShell->configure();
}

void ShellManager::setFrame(const QImage &frame)
{
    this->activeShell->setFrame(frame);
}

void ShellManager::updateDevices(const QList<QVariant> &devices)
{
    this->activeShell->updateDevices(devices);
}

void ShellManager::updatePlugins(const QList<QVariant> &plugins)
{
    this->activeShell->updatePlugins(plugins);
}

void ShellManager::onTakePicture()
{
    emit takePicture();
}

void ShellManager::onStartStopRecord()
{
    emit startStopRecord();
}

void ShellManager::onDeviceSelected(QString deviceId)
{
    emit deviceSelected(deviceId);
}

void ShellManager::onPluginActivated(QString pluginId)
{
    emit pluginActivated(pluginId);
}

void ShellManager::onPluginDeactivated(QString pluginId)
{
    emit pluginDeactivated(pluginId);
}

void ShellManager::onPluginMoved(int from, int to)
{
    emit pluginMoved(from, to);
}

void ShellManager::onPluginConfigureClicked(QString pluginId)
{
    emit pluginConfigureClicked(pluginId);
}

void ShellManager::onDeviceConfigureClicked(QString deviceId)
{
    emit deviceConfigureClicked(deviceId);
}

void ShellManager::onClosed()
{
    emit closed();
}
