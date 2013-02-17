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

    this->simulationTreeModel = NULL;

    //simulation loading events
    connect(this, SIGNAL(simulationLoaded(boost::shared_ptr<ISimulation>)), SLOT(onSimulationLoaded(boost::shared_ptr<ISimulation>)));
    this->simulationLoaded(boost::shared_ptr<ISimulation>());

    //plugin loading events
    this->pluginTracker = new PluginTracker(this);
    connect(this->pluginTracker, SIGNAL(errorsWhileLoading()), SLOT(onPluginError()));
    this->pluginTracker->scan();

    this->pluginsDialog = NULL;

    //settings
    this->lastOpenDirectory = QDir(this->settings.value("gui/lastOpenDirectory", QVariant(QString())).toString());

    //QMessageBox::information(this, "Info", this->settings.value("gui/lastOpenDirectory", QVariant(QString())).toString());
}

MainWindow::~MainWindow()
{
    delete ui;

    if (this->simulationTreeModel)
        delete simulationTreeModel;
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

        //load the simulation
        boost::shared_ptr<ISimulation> simulation = SimulationCore::getInstance()->loadSimulation(fileName.toLocal8Bit().data());
        if (!simulation)
        {
            //unable to load the file
            QMessageBox::critical(this, "Error", "Unable to load " + fileName, QMessageBox::Ok, QMessageBox::Ok);
        }
        else
        {
            //simulation loaded!
            this->simulationLoaded(simulation);
        }
    }

    //QMessageBox::information(this, "Info", this->settings.value("gui/lastOpenDirectory", QVariant(QString())).toString());
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

void MainWindow::onSimulationLoaded(boost::shared_ptr<ISimulation> simulation)
{
    bool enabled = false;
    if (simulation)
    {
        //the simulation exists
        enabled = true;
    }

    if (enabled)
    {
        if (this->simulationTreeModel)
            delete this->simulationTreeModel; //out with the old
        this->simulationTreeModel = new SimulationTreeItemModel(simulation, this);
        this->ui->simulationTreeView->setModel(this->simulationTreeModel);
    }
    else
    {
        if (this->simulationTreeModel)
            delete this->simulationTreeModel;
        this->simulationTreeModel = NULL;
        this->ui->simulationTreeView->setModel(NULL);
    }

    //model actions
    this->ui->actionAdd_Model->setEnabled(enabled);
    this->ui->actionRemove_Model->setEnabled(enabled);
    this->ui->actionExport_Model->setEnabled(enabled);
    this->ui->actionImport_Model->setEnabled(enabled);

    //simulation actions
    this->ui->actionSave->setEnabled(enabled);
    this->ui->actionSave_As->setEnabled(enabled);
}
