#include "modeleditorscene.h"

#include <QPainter>
#include <QApplication>

#include <iostream>

using namespace std;

ModelEditorScene::ModelEditorScene(boost::shared_ptr<IModel> model, QObject *parent) : QGraphicsScene(parent)
{
    this->model = model;
}
