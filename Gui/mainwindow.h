#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "pluginsdialog.h"
#include "plugintracker.h"

#include <QMainWindow>

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
    
private:
    Ui::MainWindow *ui;
    PluginsDialog* pluginsDialog;
    PluginTracker* pluginTracker;
};

#endif // MAINWINDOW_H
