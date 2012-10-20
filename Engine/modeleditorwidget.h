#ifndef MODELEDITORWIDGET_H
#define MODELEDITORWIDGET_H

#include "simulation/model.h"
#include "simulation/block.h"

#include <QWidget>
#include <QPaintEvent>

class ModelEditorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ModelEditorWidget(QWidget *parent = 0);
    
signals:
    
public slots:
    void setModel(Simulation::Model*);

protected:
    virtual void paintEvent(QPaintEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent *);

private:
    QPixmap getABlock();
    Simulation::Model* model;
    
};

#endif // MODELEDITORWIDGET_H
