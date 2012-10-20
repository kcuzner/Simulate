#include "modeleditorwidget.h"

#include <QPainter>
#include <QApplication>

#include <iostream>

using namespace std;

ModelEditorWidget::ModelEditorWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setAcceptDrops(true);

    this->setGridDelta(10);


    this->update();
}

int ModelEditorWidget::getGridDelta()
{
    return this->gridDelta;
}

void ModelEditorWidget::setModel(Simulation::Model *)
{
}

void ModelEditorWidget::setGridDelta(int value)
{
    this->gridDelta = value;
}

void ModelEditorWidget::paintEvent(QPaintEvent *e)
{
    QWidget::paintEvent(e);

    QPainter painter(this);
    painter.setClipRegion(this->visibleRegion());

    painter.setBrush(QBrush(this->palette().color(QPalette::Base)));
    painter.setPen(QPen(this->palette().color(QPalette::Base), 1));

    QRect size = this->rect();

    painter.drawRect(size);

    painter.setPen(QPen(this->palette().color(QPalette::Text), 1));

    painter.drawRect(100, 100, 100, 100);

    for(int gy = 0; gy < size.height(); gy += this->gridDelta)
    {
        for(int gx = 0; gx < size.width(); gx += this->gridDelta)
        {
            painter.drawPoint(gx, gy);
        }
    }

}

void ModelEditorWidget::mouseReleaseEvent(QMouseEvent *e)
{
    cout << e->pos().x() << "," << e->pos().y() << endl;
    cout.flush();
}

QPixmap ModelEditorWidget::getABlock()
{
    QPixmap pm(150, 100);
    QPainter painter(&pm);

    painter.setBrush(QBrush(this->palette().color(QPalette::Light)));
    painter.setPen(QPen(this->palette().color(QPalette::Highlight)));
    painter.drawRect(pm.rect());

    return pm;
}
