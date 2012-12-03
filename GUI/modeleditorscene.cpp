#include "modeleditorscene.h"

#include <QPainter>
#include <QApplication>

#include <iostream>

using namespace std;

ModelEditorScene::ModelEditorScene(Simulation::Model *model, QObject *parent) : QGraphicsScene(parent)
{
    this->model = model;
}
