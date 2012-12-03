#include "pluginsdialog.h"
#include "ui_pluginsdialog.h"

#include <QMessageBox>

#include <iostream>

using namespace std;

PluginsDialog::PluginsDialog(PluginTracker *tracker, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PluginsDialog)
{
    ui->setupUi(this);
    this->tracker = tracker;

    this->ui->treeView->setModel(this->tracker);
}

PluginsDialog::~PluginsDialog()
{
    delete ui;
}
