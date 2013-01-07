#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "pluginsdialog.h"
#include "plugintracker.h"

#include <QMainWindow>
#include <QSettings>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void viewPlugins();
    void newSimulation();
    void openSimulation();
    void saveSimulation();
    void onPluginError();
    
private:
    Ui::MainWindow *ui;
    PluginsDialog* pluginsDialog;
    PluginTracker* pluginTracker;

    QDir lastOpenDirectory;
    QSettings settings;
};

#endif // MAINWINDOW_H
