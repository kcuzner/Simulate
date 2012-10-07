#include <QApplication>
#include <QLabel>
#include <QPluginLoader>
#include <QSplashScreen>
#include <QDir>
#include <QMessageBox>

#include "mainwindow.h"
#include "modelwindow.h"

#include "simulation/model.h"
#include "simulation/block.h"
#include "simulation/blockplugin.h"
#include "simulation/blockfactory.h"

#include <iostream>

using namespace Simulation;
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //show a splash screen while things are loading
    QDir dataDir(a.applicationDirPath());
    dataDir.cdUp();
    if (!dataDir.cd("data"))
    {
        cout << "ERROR: No data directory. Please ensure the application was installed correctly." << endl;
        return -1;
    }

    QPixmap p(dataDir.absoluteFilePath("splash.png"));

    if (p.isNull())
    {
        cout << "ERROR: Unable to load splash.png in the data directory." << endl;
        return -1;
    }

    QSplashScreen s(p);
    s.show();

    //load all the plugins in the plugins directory

    MainWindow w;
    w.show();
    s.finish(&w);

    ModelWindow w2;
    w2.show();

    return a.exec();
}
