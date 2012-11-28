#include "modelwindow.h"
#include "ui_modelwindow.h"

#include <iostream>

#include <QLabel>
#include <QPushButton>

using namespace std;

ModelWindow::ModelWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ModelWindow)
{
    ui->setupUi(this);

    this->model = NULL;

    this->editorScene = new ModelEditorScene(this->model, this);

    this->ui->graphicsView->setScene(this->editorScene);

    /*QPushButton* btn = new QPushButton("Button 1", this);
    QPushButton* btn1 = new QPushButton("Button 2", this);
    QPushButton* btn2 = new QPushButton("Button 3", this);
    QPushButton* btn3 = new QPushButton("Button 4", this);
    QPushButton* btn4 = new QPushButton("Button 5", this);
    QPushButton* btn5 = new QPushButton("Button 6", this);
    QPushButton* btn6 = new QPushButton("Button 7", this);
    QPushButton* btn7 = new QPushButton("Button 8", this);
    QPushButton* btn8 = new QPushButton("Button 9", this);
    QPushButton* btn9 = new QPushButton("Button 10", this);
    QPushButton* btn10 = new QPushButton("Button 11", this);
    QPushButton* btn11 = new QPushButton("Button 12", this);
    QPushButton* btn12 = new QPushButton("Button 13", this);*/

    this->blockToolbox = new QToolBox(this);

    this->ui->scrollArea_2->setWidget(this->blockToolbox);

    connect(Simulation::BlockFactory::getInstance(), SIGNAL(test(QString)), SLOT(test2(QString)));
    connect(Simulation::BlockFactory::getInstance(), SIGNAL(blockAdded(QSharedPointer<Simulation::BlockFactory::BlockInfo>)), SLOT(addBlock(QSharedPointer<Simulation::BlockFactory::BlockInfo>)));

    /*this->blockToolbox->addItem(btn, "1");
    this->blockToolbox->addItem(btn1, "2");
    this->blockToolbox->addItem(btn2, "3");
    this->blockToolbox->addItem(btn3, "4");
    this->blockToolbox->addItem(btn4, "5");
    this->blockToolbox->addItem(btn5, "6");
    this->blockToolbox->addItem(btn6, "7");
    this->blockToolbox->addItem(btn7, "8");
    this->blockToolbox->addItem(btn8, "9");
    this->blockToolbox->addItem(btn9, "10");
    this->blockToolbox->addItem(btn10, "11");
    this->blockToolbox->addItem(btn11, "12");
    this->blockToolbox->addItem(btn12, "13");*/

    //ui->actionM_odels->setChecked(true);
    //ui->action_Blocks->setChecked(true);
}

ModelWindow::~ModelWindow()
{
    delete ui;
}

void ModelWindow::undockBlockDock()
{
    ui->blocksDockWidget->show();
    ui->blocksDockWidget->setFloating(true);
}

void ModelWindow::undockModelDock()
{
    ui->modelsDockWidget->show();
    ui->modelsDockWidget->setFloating(true);
}

void ModelWindow::addBlock(QSharedPointer<Simulation::BlockFactory::BlockInfo> info)
{
    cout << info->getName().toLocal8Bit().data() << endl;
    cout.flush();
}

void ModelWindow::test2(QString recv)
{
    cout << recv.toLocal8Bit().data() << endl;
    cout.flush();
}
