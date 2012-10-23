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
    connect(this->pluginTracker, SIGNAL(errorsWhileLoading()), SLOT(onPluginError()));
    this->pluginTracker->scan();

    this->pluginsDialog = NULL;
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

void MainWindow::onPluginError()
{
    if (!this->pluginTracker->hasErrors())
        return; //nothing to do if there are no errors

    QMessageBox msgBox;
    msgBox.setText("There were errors while loading plugins.");
    msgBox.setInformativeText("Not all plugins may have loaded");
    QString errors;

    while(this->pluginTracker->hasErrors())
    {
        errors.append(this->pluginTracker->getError());
        errors.append("\n");
    }

    msgBox.setDetailedText(errors);
    msgBox.exec();
}
