#include "modelwindow.h"
#include "ui_modelwindow.h"

#include <iostream>

#include <QLabel>

using namespace std;

ModelWindow::ModelWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ModelWindow)
{
    ui->setupUi(this);

    this->model = NULL;

    this->editorScene = new ModelEditorScene(this->model, this);

    this->ui->graphicsView->setScene(this->editorScene);

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

void ModelWindow::addBlockGroup(QString &name)
{
}
