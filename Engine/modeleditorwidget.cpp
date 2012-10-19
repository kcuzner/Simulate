#include "modeleditorwidget.h"

#include <QPainter>
#include <QApplication>

#include <iostream>

using namespace std;

ModelEditorWidget::ModelEditorWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setAcceptDrops(true);

    this->setFixedSize(1000, 1000);

    cout << this->rect().x() << " " << this->rect().width() << endl;

    this->update();
}

void ModelEditorWidget::paintEvent(QPaintEvent *e)
{
    QWidget::paintEvent(e);

    QPainter painter(this);
    painter.setClipRegion(this->visibleRegion());

    painter.setBrush(QBrush(this->palette().color(QPalette::Highlight)));
    painter.setPen(QPen(Qt::red, 2));

    painter.drawRect(0, 0, 500, 500);

    painter.drawPixmap(250, 250, this->getABlock());
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
