#include "pluginsdialog.h"
#include "ui_pluginsdialog.h"

PluginsDialog::PluginsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PluginsDialog)
{
    ui->setupUi(this);
}

PluginsDialog::~PluginsDialog()
{
    delete ui;
}
