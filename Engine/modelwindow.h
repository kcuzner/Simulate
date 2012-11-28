#ifndef MODELWINDOW_H
#define MODELWINDOW_H

#include <QMainWindow>
#include <QToolBox>

#include "modeleditorscene.h"

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
    void addBlockGroup(QString& name);
    
private:
    Ui::ModelWindow *ui;
    ModelEditorScene* editorScene;
    QToolBox* blockToolbox;
    Simulation::Model* model;
};

#endif // MODELWINDOW_H
