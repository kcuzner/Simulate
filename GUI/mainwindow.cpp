#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>

#include "simulationcore.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    this->pluginTracker = new PluginTracker(this);
    connect(this->pluginTracker, SIGNAL(errorsWhileLoading()), SLOT(onPluginError()));
    this->pluginTracker->scan();

    this->pluginsDialog = NULL;

    this->lastOpenDirectory = QDir(this->settings.value("gui/lastOpenDirectory", QVariant(QString())).toString());

    QMessageBox::information(this, "Info", this->settings.value("gui/lastOpenDirectory", QVariant(QString())).toString());
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

void MainWindow::newSimulation()
{
}

void MainWindow::openSimulation()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Simulation", this->lastOpenDirectory.absolutePath(), QString(SimulationCore::getInstance()->getFileFilterString().c_str()));
    if (fileName != "")
    {
        this->lastOpenDirectory = QFileInfo(fileName).absoluteDir();

        this->settings.setValue("gui/lastOpenDirectory", this->lastOpenDirectory.absolutePath());
    }

    QMessageBox::information(this, "Info", this->settings.value("gui/lastOpenDirectory", QVariant(QString())).toString());
}

void MainWindow::saveSimulation()
{
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
