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

    connect(this->tracker, SIGNAL(errorsWhileLoading()), SLOT(onPluginError()));

    this->tracker->scan();
}

PluginsDialog::~PluginsDialog()
{
    delete ui;
}

void PluginsDialog::onPluginError()
{
    cout << "hi" << endl;
    cout.flush();
    if (!this->tracker->hasErrors())
        return; //nothing to do if there are no errors

    QMessageBox msgBox;
    msgBox.setText("There were errors while loading plugins.");
    msgBox.setInformativeText("Not all plugins may have loaded");
    QString errors;

    while(this->tracker->hasErrors())
    {
        errors.append(this->tracker->getError());
        errors.append("\n");
    }

    msgBox.setDetailedText(errors);
    msgBox.exec();
}
