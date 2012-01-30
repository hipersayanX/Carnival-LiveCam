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

/*!
  \class ShellManager

  \brief This class is used for manage shells.
 */

/*!
  \fn ShellManager::ShellManager(QObject *parent)

  \param parent Parent widget.
 */
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

            if (this->shellConfigs.contains(shell->id()))
                shell->setConfigs(this->shellConfigs[shell->id()]);

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

/*!
  \fn ShellManager::~ShellManager()
 */
ShellManager::~ShellManager()
{
    if (this->activeShellId != "")
        disableShell(this->activeShellId);
}

/*!
  \fn QList<QVariant> ShellManager::shellsToQml()

  \return The list of shells information in standard format.

  \brief Returns the list of shells information in standard format.
 */
QList<QVariant> ShellManager::shellsInfoList()
{
    QList<QVariant> shellList;

    foreach (ShellInfo shell, this->shellsInfo)
    {
        QMap<QString, QVariant> shellInfoMap;

        shellInfoMap["shellId"] = QVariant(shell.shellId());
        shellInfoMap["isEnabled"] = QVariant(shell.isEnabled());
        shellInfoMap["name"] = QVariant(shell.name());
        shellInfoMap["version"] = QVariant(shell.version());
        shellInfoMap["summary"] = QVariant(shell.summary());
        shellInfoMap["type"] = QVariant(shell.type());
        shellInfoMap["thumbnail"] = QVariant(shell.thumbnail());
        shellInfoMap["license"] = QVariant(shell.license());
        shellInfoMap["author"] = QVariant(shell.author());
        shellInfoMap["website"] = QVariant(shell.website());
        shellInfoMap["mail"] = QVariant(shell.mail());
        shellInfoMap["isConfigurable"] = QVariant(shell.isConfigurable());

        shellList << shellInfoMap;
    }

    return shellList;
}

/*!
  \fn QWidget *ShellManager::widget(QString id)

  \param id Unique shell identifier.

  \return A pointer to the widget object.

  \brief Returns a pointer to the shell widget object if active else returns NULL.
 */
QWidget *ShellManager::widget(QString shellId)
{
    if (this->activeShellId == shellId || shellId == "")
        return this->activeShell->widget();

    return NULL;
}

QSize ShellManager::viewPortSize(QString shellId)
{
    if (this->activeShellId == shellId || shellId == "")
        return this->activeShell->viewPortSize();

    return QSize();
}

/*!
  \fn bool ShellManager::setShell(QString id)

  \param id Unique shell identifier.

  \retval true if the shell is active.
  \retval false if the shell is inactive.

  \brief Try to activate the shell id.
 */
bool ShellManager::setShell(QString shellId)
{
    if (this->activeShellId != "")
        disableShell(this->activeShellId);

    enableShell(shellId);
    this->activeShellId = shellId;

    return true;
}

/*!
  \fn bool ShellManager::enableShell(QString id)

  \param id Unique shell identifier.

  \retval true if the shell is active.
  \retval false if the shell is inactive.

  \brief Try to activate the shell id.
 */
bool ShellManager::enableShell(QString shellId)
{
    if (!this->shellsInfo.contains(shellId))
        return false;

    this->shellLoader.setFileName(this->shellsInfo[shellId].fileName());

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

    if (this->shellConfigs.contains(shellId))
        shell->setConfigs(this->shellConfigs[shellId]);

    this->shellsInfo[shellId].setIsEnabled(true);
    this->activeShell = shell;
    this->activeShell->begin();

    connect(this->activeShell, SIGNAL(toggleEditMode()), this, SLOT(onToggleEditMode()));
    connect(this->activeShell, SIGNAL(viewPortSizeChanged(QSize)), this, SLOT(onViewPortSizeChanged(QSize)));
    connect(this->activeShell, SIGNAL(mouseDoubleClicked(QMouseEvent *)), this, SLOT(onMouseDoubleClicked(QMouseEvent *)));
    connect(this->activeShell, SIGNAL(mousePositionChanged(QMouseEvent *)), this, SLOT(onMousePositionChanged(QMouseEvent *)));
    connect(this->activeShell, SIGNAL(mousePressed(QMouseEvent *)), this, SLOT(onMousePressed(QMouseEvent *)));
    connect(this->activeShell, SIGNAL(mouseReleased(QMouseEvent *)), this, SLOT(onMouseReleased(QMouseEvent *)));
    connect(this->activeShell, SIGNAL(takePicture()), this, SLOT(onTakePicture()));
    connect(this->activeShell, SIGNAL(startStopRecord()), this, SLOT(onStartStopRecord()));
    connect(this->activeShell, SIGNAL(deviceEnable(QString)), this, SLOT(onDeviceEnable(QString)));
    connect(this->activeShell, SIGNAL(deviceDisable(QString)), this, SLOT(onDeviceDisable(QString)));
    connect(this->activeShell, SIGNAL(pluginActivated(QString)), this, SLOT(onPluginActivated(QString)));
    connect(this->activeShell, SIGNAL(pluginDeactivated(QString)), this, SLOT(onPluginDeactivated(QString)));
    connect(this->activeShell, SIGNAL(pluginMoved(int, int)), this, SLOT(onPluginMoved(int, int)));
    connect(this->activeShell, SIGNAL(pluginConfigureClicked(QString)), this, SLOT(onPluginConfigureClicked(QString)));
    connect(this->activeShell, SIGNAL(deviceConfigureClicked(QString)), this, SLOT(onDeviceConfigureClicked(QString)));
    connect(this->activeShell, SIGNAL(closed()), this, SLOT(onClosed()));

    return true;
}

/*!
  \fn bool ShellManager::disableShell(QString id)

  \param id Unique shell identifier.

  \retval true if the shell is inactive.
  \retval false if the shell is active.

  \brief Try to desactivate the shell id.
 */
bool ShellManager::disableShell(QString shellId)
{
    if (!this->shellsInfo.contains(shellId) || this->activeShellId != shellId)
        return false;

    this->shellConfigs[shellId] = this->activeShell->configs();

    disconnect(this->activeShell, SIGNAL(toggleEditMode()), this, SLOT(onToggleEditMode()));
    disconnect(this->activeShell, SIGNAL(viewPortSizeChanged(QSize)), this, SLOT(onViewPortSizeChanged(QSize)));
    disconnect(this->activeShell, SIGNAL(mouseDoubleClicked(QMouseEvent *)), this, SLOT(onMouseDoubleClicked(QMouseEvent *)));
    disconnect(this->activeShell, SIGNAL(mousePositionChanged(QMouseEvent *)), this, SLOT(onMousePositionChanged(QMouseEvent *)));
    disconnect(this->activeShell, SIGNAL(mousePressed(QMouseEvent *)), this, SLOT(onMousePressed(QMouseEvent *)));
    disconnect(this->activeShell, SIGNAL(mouseReleased(QMouseEvent *)), this, SLOT(onMouseReleased(QMouseEvent *)));
    disconnect(this->activeShell, SIGNAL(takePicture()), this, SLOT(onTakePicture()));
    disconnect(this->activeShell, SIGNAL(startStopRecord()), this, SLOT(onStartStopRecord()));
    disconnect(this->activeShell, SIGNAL(deviceEnable(QString)), this, SLOT(onDeviceEnable(QString)));
    disconnect(this->activeShell, SIGNAL(deviceDisable(QString)), this, SLOT(onDeviceDisable(QString)));
    disconnect(this->activeShell, SIGNAL(pluginActivated(QString)), this, SLOT(onPluginActivated(QString)));
    disconnect(this->activeShell, SIGNAL(pluginDeactivated(QString)), this, SLOT(onPluginDeactivated(QString)));
    disconnect(this->activeShell, SIGNAL(pluginMoved(int, int)), this, SLOT(onPluginMoved(int, int)));
    disconnect(this->activeShell, SIGNAL(pluginConfigureClicked(QString)), this, SLOT(onPluginConfigureClicked(QString)));
    disconnect(this->activeShell, SIGNAL(deviceConfigureClicked(QString)), this, SLOT(onDeviceConfigureClicked(QString)));
    disconnect(this->activeShell, SIGNAL(closed()), this, SLOT(onClosed()));

    this->activeShell->end();
    delete this->activeShell;
    this->activeShell = NULL;
    this->shellLoader.setFileName(this->shellsInfo[shellId].fileName());
    this->shellLoader.unload();
    this->shellsInfo[shellId].setIsEnabled(false);
    this->activeShellId = "";

    return true;
}

/*!
  \fn void ShellManager::configureShell(QString id)

  \param id Unique shell identifier.

  \brief Calls the configuration dialog of the shell id.
 */
void ShellManager::configureShell(QString shellId)
{
    if (this->activeShellId == shellId)
        this->activeShell->configure();
}

/*!
  \fn void ShellManager::setFrame(const QImage &frame)

  \param frame The frame to send.

  \brief Send a frame to the current shell.
 */
void ShellManager::setFrame(const QImage &frame)
{
    this->activeShell->setFrame(frame);
}

/*!
  \fn void ShellManager::updateDevices(const QList<QVariant> &devices)

  \param devices List of devices id.

  \brief Updates the devices list.
 */
void ShellManager::updateDevices(const QList<QVariant> &devices)
{
    this->activeShell->updateDevices(devices);
}

/*!
  \fn void ShellManager::updatePlugins(const QList<QVariant> &plugins)

  \param plugins List of plugins id.

  \brief Updates the plugins list.
 */
void ShellManager::updatePlugins(const QList<QVariant> &plugins)
{
    this->activeShell->updatePlugins(plugins);
}

void ShellManager::setControlButtons(QPushButton *toggleMaximizedButton, QPushButton *scaleAndRotateButton)
{
    this->activeShell->setControlButtons(toggleMaximizedButton, scaleAndRotateButton);
}

void ShellManager::onToggleEditMode()
{
    emit toggleEditMode();
}

void ShellManager::onViewPortSizeChanged(QSize size)
{
    emit viewPortSizeChanged(size);
}

void ShellManager::onMouseDoubleClicked(QMouseEvent *event)
{
    emit mouseDoubleClicked(event);
}

void ShellManager::onMousePositionChanged(QMouseEvent *event)
{
    emit mousePositionChanged(event);
}

void ShellManager::onMousePressed(QMouseEvent *event)
{
    emit mousePressed(event);
}

void ShellManager::onMouseReleased(QMouseEvent *event)
{
    emit mouseReleased(event);
}

/*!
  \internal

  \fn void ShellManager::onTakePicture()

  \brief This slot is called when the user presses the "take picture" button.
 */
void ShellManager::onTakePicture()
{
    emit takePicture();
}

/*!
  \internal

  \fn void ShellManager::onStartStopRecord()

  \brief This slot is called when the user presses the "start/stop video record" button.
 */
void ShellManager::onStartStopRecord()
{
    emit startStopRecord();
}

void ShellManager::onDeviceEnable(QString deviceId)
{
    emit deviceEnable(deviceId);
}

void ShellManager::onDeviceDisable(QString deviceId)
{
    emit deviceDisable(deviceId);
}

/*!
  \internal

  \fn void ShellManager::onPluginActivated(QString pluginId)

  \param pluginId Unique plugin identifier.

  \brief This slot is called when the user activate a plugin.
 */
void ShellManager::onPluginActivated(QString pluginId)
{
    emit pluginActivated(pluginId);
}

/*!
  \internal

  \fn void ShellManager::onPluginDeactivated(QString pluginId)

  \param pluginId Unique plugin identifier.

  \brief This slot is called when the user deactivate a plugin.
 */
void ShellManager::onPluginDeactivated(QString pluginId)
{
    emit pluginDeactivated(pluginId);
}

/*!
  \internal

  \fn void ShellManager::onPluginMoved(int from, int to)

  \param from The old index position of the plugin.
  \param to The new index position of the plugin.

  \brief This slot is called when the user changes the index of a plugin.
 */
void ShellManager::onPluginMoved(int from, int to)
{
    emit pluginMoved(from, to);
}

/*!
  \internal

  \fn void ShellManager::onPluginConfigureClicked(QString pluginId)

  \param pluginId The plugin to configure.

  \brief This slot is called when the user wants to configure a plugin.
 */
void ShellManager::onPluginConfigureClicked(QString pluginId)
{
    emit pluginConfigureClicked(pluginId);
}

/*!
  \internal

  \fn void ShellManager::onDeviceConfigureClicked(QString deviceId)

  \param deviceId The device to configure.

  \brief This slot is called when the user wants to configure a device.
 */
void ShellManager::onDeviceConfigureClicked(QString deviceId)
{
    emit deviceConfigureClicked(deviceId);
}

/*!
  \internal

  \fn void ShellManager::onClosed()

  \brief This slot is called when the shell is closed.
 */
void ShellManager::onClosed()
{
    emit closed();
}
