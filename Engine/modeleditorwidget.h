#ifndef MODELEDITORWIDGET_H
#define MODELEDITORWIDGET_H

#include <QWidget>
#include <QPaintEvent>

class ModelEditorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ModelEditorWidget(QWidget *parent = 0);
    
signals:
    
public slots:

protected:
    virtual void paintEvent(QPaintEvent *e);

private:
    QPixmap getABlock();
    
};

#endif // MODELEDITORWIDGET_H
