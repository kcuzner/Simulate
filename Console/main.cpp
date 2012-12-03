#include <QCoreApplication>

#include "engine.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Engine* n = new Engine();
    
    return a.exec();
}
