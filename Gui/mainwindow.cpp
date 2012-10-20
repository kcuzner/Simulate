#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->pluginsDialog = NULL;
    this->pluginTracker = new PluginTracker(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::viewPlugins()
{
    if (this->pluginsDialog)
    {
        this->pluginsDialog->show();
    }
    else
    {
        this->pluginsDialog = new PluginsDialog(this->pluginTracker, this);
        this->pluginsDialog->show();
    }

}
