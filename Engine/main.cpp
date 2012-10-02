#include <QApplication>
#include <QLabel>
#include "mainwindow.h"

#include "simulation/model.h"
#include "simulation/block.h"

using namespace Simulation;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
