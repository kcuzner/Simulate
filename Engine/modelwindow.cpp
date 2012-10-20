#include "modelwindow.h"
#include "ui_modelwindow.h"

#include <iostream>

using namespace std;

ModelWindow::ModelWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ModelWindow)
{
    ui->setupUi(this);

    editor = new ModelEditorWidget(this);

    ui->scrollArea->setWidget(editor);

    editor->show();
    ui->scrollArea->show();

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
