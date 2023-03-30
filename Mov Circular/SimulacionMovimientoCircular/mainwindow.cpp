//Autor: José Isidro Perla Rosa

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "uniforme.h"
#include "acelerado.h"
#include <QStyle>
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->move(QApplication::desktop()->availableGeometry().center() - this->rect().center()); //Con esto se centra la venta de QT.

    QPixmap bkgnd(":/new/prefix1/pizarra.png"); //Esto es para añadir una imagen de fondo.
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_opcion1_clicked()
{
    hide();
    uniforme = new Uniforme(this);
    uniforme->show();
}

void MainWindow::on_opcion2_clicked()
{
    hide();
    ac = new acelerado(this);
    ac->show();
}
