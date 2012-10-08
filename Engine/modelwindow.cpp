#include "modelwindow.h"
#include "ui_modelwindow.h"

#include <iostream>

using namespace std;

ModelWindow::ModelWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ModelWindow)
{
    ui->setupUi(this);

    //ui->actionM_odels->setChecked(true);
    //ui->action_Blocks->setChecked(true);
}

ModelWindow::~ModelWindow()
{
    delete ui;
}

void ModelWindow::modelDockMenuToggled(bool state)
{
    if (state)
    {
        this->ui->modelsDockWidget->show();
    }
    else
    {
        this->ui->modelsDockWidget->hide();
    }
}

void ModelWindow::modelDockVisibilityChanged(bool state)
{
    this->ui->actionM_odels->setChecked(state);
}

void ModelWindow::blockDockMenuToggled(bool state)
{
    if (state)
    {
        this->ui->blocksDockWidget->show();
    }
    else
    {
        this->ui->blocksDockWidget->hide();
    }
}

void ModelWindow::blockDockVisibilityChanged(bool state)
{
    this->ui->action_Blocks->setChecked(state);
}
