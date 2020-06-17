#include "mainwindow.h"

#include <QSystemTrayIcon>

#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    a.setWindowIcon( QIcon("/home/mario/volumio/images/logo.png") );
    w.show();
    return a.exec();

}
