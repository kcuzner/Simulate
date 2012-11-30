#ifndef MODELWINDOW_H
#define MODELWINDOW_H

#include <QMainWindow>
#include <QToolBox>

#include "simulation/blockfactory.h"
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
    void addBlock(QSharedPointer<Simulation::BlockFactory::BlockInfo> info);
    void test2(QString recv);
    
private:
    Ui::ModelWindow *ui;
    ModelEditorScene* editorScene;
    QToolBox* blockToolbox;
};

#endif // MODELWINDOW_H
