#include <QCoreApplication>

#include "simpleengine.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SimpleEngine* n = new SimpleEngine(100, 0.000000001);
    
    return a.exec();
}
