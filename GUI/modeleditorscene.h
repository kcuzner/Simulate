#ifndef MODELEDITORWIDGET_H
#define MODELEDITORWIDGET_H

#include "simulation/model.h"
#include "simulation/block.h"

#include <QGraphicsScene>

class ModelEditorScene : public QGraphicsScene
{
    Q_OBJECT

public:
    ModelEditorScene(Simulation::Model* model, QObject *parent = 0);

private:
    Simulation::Model* model;
    
};

#endif // MODELEDITORWIDGET_H
