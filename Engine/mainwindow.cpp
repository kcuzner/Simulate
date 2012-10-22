#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->blockFactory = new Simulation::BlockFactory();


    this->pluginTracker = new PluginTracker(this->blockFactory, this);
    this->pluginsDialog = new PluginsDialog(this->pluginTracker, this);
}

MainWindow::~MainWindow()
{
    delete blockFactory;
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
