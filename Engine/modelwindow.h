#ifndef MODELWINDOW_H
#define MODELWINDOW_H

#include <QMainWindow>

#include "modeleditorwidget.h"

namespace Ui {
class ModelWindow;
}

class ModelWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ModelWindow(QWidget *parent = 0);
    ~ModelWindow();

public slots:
    void undockBlockDock(void);
    void undockModelDock(void);
    
private:
    Ui::ModelWindow *ui;
    ModelEditorWidget* editor;
};

#endif // MODELWINDOW_H
