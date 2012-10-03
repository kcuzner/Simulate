#include <QApplication>
#include <QLabel>
#include <QPluginLoader>
#include "mainwindow.h"

#include "simulation/model.h"
#include "simulation/block.h"
#include "simulation/blockplugin.h"
#include "simulation/blockfactory.h"

#include <iostream>

using namespace Simulation;
using namespace std;

int main(int argc, char *argv[])
{
    cout << "hi" << endl;

    QCoreApplication::addLibraryPath("../Simulate/Plugins/bin");

    QPluginLoader loader("../Simulate/Plugin/libSystemBlocks.so");

    BlockPlugin* plugin = (BlockPlugin*)loader.instance();

    BlockFactory* factory = new BlockFactory();
    plugin->declareBlocks(factory);

    //for(QHash<QString, Simulation::GenerateBlock>::iterator i = factory->blocks.begin(); i != factory->blocks.end(); i++)
    //{
        //cout << i.key().data() << endl;
    //}

    cout << "hi" << endl;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
