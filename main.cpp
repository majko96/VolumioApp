#include "mainwindow.h"
#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    a.setWindowIcon( QIcon(":/res/images/logo.png") );
    w.hide();
    return a.exec();
    return 0;

}
