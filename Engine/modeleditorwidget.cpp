#include "modeleditorwidget.h"

#include <QPainter>

#include <iostream>

using namespace std;

ModelEditorWidget::ModelEditorWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setAcceptDrops(true);

    this->resize(1000, 1000);

    cout << this->rect().x() << " " << this->rect().width() << endl;

    this->update();
}

void ModelEditorWidget::paintEvent(QPaintEvent *e)
{
    cout << "painting";
    cout.flush();

    QWidget::paintEvent(e);

    QPainter painter(this);

    painter.setBrush(QBrush(Qt::green));
    painter.setPen(QPen(Qt::red));
    painter.drawRect(400, 400, 50, 50);
    painter.fillRect(e->rect(), Qt::SolidPattern);
}
