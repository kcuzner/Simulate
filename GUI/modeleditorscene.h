#ifndef MODELEDITORWIDGET_H
#define MODELEDITORWIDGET_H

#include <QGraphicsScene>

#include "interfaces/imodel.h"

class ModelEditorScene : public QGraphicsScene
{
    Q_OBJECT

public:
    ModelEditorScene(boost::shared_ptr<IModel> model, QObject *parent = 0);

private:
    boost::shared_ptr<IModel> model;
};

#endif // MODELEDITORWIDGET_H
