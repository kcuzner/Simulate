#ifndef MODELWINDOW_H
#define MODELWINDOW_H

#include <QMainWindow>

namespace Ui {
class ModelWindow;
}

class ModelWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ModelWindow(QWidget *parent = 0);
    ~ModelWindow();

public slots:
    void modelDockMenuToggled(bool state);
    void modelDockVisibilityChanged(bool state);
    void blockDockMenuToggled(bool state);
    void blockDockVisibilityChanged(bool state);
    
private:
    Ui::ModelWindow *ui;
};

#endif // MODELWINDOW_H
