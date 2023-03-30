#include "mainwindow.h"
#include <QApplication>
#include <QStyle>
#include <QDesktopWidget>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowIcon(QIcon(":/new/prefix1/icono.png"));

    w.show();

    return a.exec();
}
