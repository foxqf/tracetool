/**********************************************************************
** Copyright (C) 2010 froglogic GmbH.
** All rights reserved.
**********************************************************************/

#ifndef SETTINGS_H
#define SETTINGS_H

#include "restorableobject.h"

#include <QList>
#include <QStringList>

class EntryFilter;
class ColumnsInfo;

class Settings
{
public:
    Settings();
    ~Settings();

    bool save() const;

    void registerRestorable(const QString &name, RestorableObject *r);
    bool saveSession();
    bool restoreSession() const;

    // [Database]
    void setDatabaseFile(const QString &file) {
	m_databaseFile = file;
    }
    QString databaseFile() const { return m_databaseFile; }

    // [Server]
    void setServerPort(int port) { m_serverPort = port; }
    int serverPort() const { return m_serverPort; }
    
    void setSoftLimit(int bytes);
    int softLimit() const { return m_softLimit; }

    void setHardLimit(int bytes);
    int hardLimit() const { return m_hardLimit; }

    // [Filter]
    EntryFilter* entryFilter() { return m_entryFilter; }

    // [ColumnsInfo]
    ColumnsInfo* columnsInfo() { return m_columnsInfo; }

    // [Configuration]
    void addConfigurationFile(const QString &fileName);
    bool hasConfigurationFiles() const { return m_configFiles.isEmpty(); }
    QStringList configurationFiles() const { return m_configFiles; }

private:
    bool load();

    QMap<QString, RestorableObject*> m_restorables;

    QString m_databaseFile;
    int m_serverPort;
    EntryFilter* m_entryFilter;
    ColumnsInfo *m_columnsInfo;
    int m_softLimit, m_hardLimit;
    QStringList m_configFiles;
};

#endif
