#include <QApplication>
#include <QLabel>
#include <QPluginLoader>
#include <QSplashScreen>
#include <QDir>
#include <QMessageBox>
#include <QIcon>

#include "mainwindow.h"
#include "modelwindow.h"

#include <iostream>

using namespace std;

static const char* GENERIC_TEST_ICON = "document-open";
static const char* FALLBACK_THEME = "silk";

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("Kevincuzner");
    QCoreApplication::setOrganizationDomain("kevincuzner.com");
    QCoreApplication::setApplicationName("Simulate");

    //check for an icon theme
    if (!QIcon::hasThemeIcon(GENERIC_TEST_ICON))
    {
        QIcon::setThemeName(FALLBACK_THEME); //if we don't have a theme, set it to our backup
    }

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

    //ModelWindow mw(&w);
    //mw.show();

    return a.exec();
}
