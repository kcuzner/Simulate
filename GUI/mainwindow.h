#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "interfaces/isimulation.h"
#include "pluginsdialog.h"
#include "plugintracker.h"
#include "submodellistmodel.h"
#include "simulationtreeitemmodel.h"

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
    /**
     * @brief Slot called to view the plugins loaded
     */
    void viewPlugins();
    /**
     * @brief Slot called to create a new simulation
     */
    void newSimulation();
    /**
     * @brief Slot called to start opening a simulation
     */
    void openSimulation();
    /**
     * @brief Slot called to save a simulation
     */
    void saveSimulation();
    /**
     * @brief Slot fired when there is a plugin error
     */
    void onPluginError();
    /**
     * @brief Slot to be fired when a simulation has loaded.
     */
    void onSimulationLoaded(boost::shared_ptr<ISimulation> simulation);

signals:
    void simulationLoaded(boost::shared_ptr<ISimulation>);
    
private:
    Ui::MainWindow *ui;
    PluginsDialog* pluginsDialog;
    PluginTracker* pluginTracker;
    SubmodelListModel* submodelListModel;
    SimulationTreeItemModel* simulationTreeModel;

    QDir lastOpenDirectory;
    QSettings settings;
};

#endif // MAINWINDOW_H
