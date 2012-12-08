#include <QCoreApplication>

#include "simpleengine.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SimpleEngine* n = new SimpleEngine();
    
    return a.exec();
}
