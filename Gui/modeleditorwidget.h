#ifndef MODELEDITORWIDGET_H
#define MODELEDITORWIDGET_H

#include "simulation/model.h"
#include "simulation/block.h"

#include <QWidget>
#include <QPaintEvent>

class ModelEditorWidget : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int GridDelta READ getGridDelta WRITE setGridDelta)

public:
    explicit ModelEditorWidget(QWidget *parent = 0);

    int getGridDelta();
    
signals:
    
public slots:
    void setModel(Simulation::Model*);
    void setGridDelta(int);

protected:
    virtual void paintEvent(QPaintEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent *);

private:
    QPixmap getABlock();
    Simulation::Model* model;
    int gridDelta; //delta for the grid
    
};

#endif // MODELEDITORWIDGET_H
