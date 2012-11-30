#ifndef PLUGINSDIALOG_H
#define PLUGINSDIALOG_H

#include <QDialog>
#include "plugintracker.h"

namespace Ui {
class PluginsDialog;
}

class PluginsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit PluginsDialog(PluginTracker* tracker, QWidget *parent = 0);
    ~PluginsDialog();
    
private:
    Ui::PluginsDialog *ui;
    PluginTracker* tracker;
};

#endif // PLUGINSDIALOG_H
