#include "pluginsdialog.h"
#include "ui_pluginsdialog.h"


PluginsDialog::PluginsDialog(PluginTracker *tracker, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PluginsDialog)
{
    ui->setupUi(this);
    this->tracker = tracker;
}

PluginsDialog::~PluginsDialog()
{
    delete ui;
}
