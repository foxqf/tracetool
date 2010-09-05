/**********************************************************************
** Copyright (C) 2010 froglogic GmbH.
** All rights reserved.
**********************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "settings.h"

class EntryItemModel;
class Server;
class WatchTree;
class FilterForm;

class MainWindow : public QMainWindow, private Ui::MainWindow,
                   public RestorableObject
{
    Q_OBJECT
public:
    explicit MainWindow(Settings *settings,
                        QWidget *parent = 0, Qt::WindowFlags flags = 0);
    virtual ~MainWindow();

    bool setDatabase(const QString &databaseFileName, QString *errMsg);

    void postRestore();
    
protected:
    // from RestorableObject interface
    QVariant sessionState() const;
    bool restoreSessionState(const QVariant &state);

private slots:
    void fileOpenTrace();
    void fileOpenConfiguration();
    void configFilesAboutToShow();
    void openRecentConfigFile();
    void helpAbout();
    void toggleFreezeState();
    void editColumns();
    void editStorage();
    void updateColumns();
    void filterChange();

private:
    bool openConfigurationFile(const QString &fileName);
    void showError(const QString &title, const QString &message);

    Settings* const m_settings;
    EntryItemModel* m_entryItemModel;
    WatchTree* m_watchTree;
    FilterForm *m_filterForm;
    Server *m_server;
    QMenu *m_configFilesMenu;
};

#endif

