#include "modelwindow.h"
#include "ui_modelwindow.h"

#include "blockfactorygrouplistmodel.h"
#include "simulationcore.h"

#include "system/mathgain.h"

#include <iostream>

#include <QLabel>
#include <QPushButton>

using namespace std;

ModelWindow::ModelWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ModelWindow)
{
    ui->setupUi(this);

    this->editorScene = new ModelEditorScene(this->model, this);

    this->ui->graphicsView->setScene(this->editorScene);

    this->blockToolbox = new QToolBox(this);

    boost::shared_ptr<ISimulationCore> core = SimulationCore::getInstance();

    //follow the block factory around with our toolbox
    core->getBlockFactory()->sigBlockAdded.connect(boost::bind(&ModelWindow::addBlock, this, _1, _2));

    //create our initial toolboxes
    for(std::map<std::string, std::list<std::string> >::const_iterator iter = core->getBlockFactory()->getValidBlockNames().begin();
        iter != core->getBlockFactory()->getValidBlockNames().end();
        iter++)
    {
        QListView* view = new QListView(this);
        view->setModel(new BlockFactoryGroupListModel(core, (*iter).first, this));
        this->blockToolbox->addItem(view, QString((*iter).first.c_str()));

        this->toolboxListViews[QString((*iter).first.c_str())] = view;
    }

    this->ui->scrollArea_2->setWidget(this->blockToolbox);
}

ModelWindow::~ModelWindow()
{
    delete ui;
}

boost::shared_ptr<IBlock> g(long id)
{
    return boost::shared_ptr<IBlock>();
}

void ModelWindow::undockBlockDock()
{
    ui->blocksDockWidget->show();
    ui->blocksDockWidget->setFloating(true);

    //test to see if we can dynamically add blocks
    SimulationCore::getInstance()->getBlockFactory()->declareBlock(g, "Math", "Test");
}

void ModelWindow::undockModelDock()
{
    ui->modelsDockWidget->show();
    ui->modelsDockWidget->setFloating(true);

    //test to see if we can dynamically add groups
    SimulationCore::getInstance()->getBlockFactory()->declareBlock(g, "Noms", "Test");
}

void ModelWindow::addBlock(const string &group, const string &)
{
    if (!this->toolboxListViews.count(QString(group.c_str())))
    {
        //we need to create a new group for this block
        QListView* view = new QListView(this);
        view->setModel(new BlockFactoryGroupListModel(SimulationCore::getInstance(), group, this));
        this->blockToolbox->addItem(view, QString(group.c_str()));

        this->toolboxListViews[QString(group.c_str())] = view;
    }
}
