//Autor: José Isidro Perla Rosa

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>
#include <iostream>
#include <QItemDelegate>
#include <variosobjetos.h>
#include <objetossumergidosenliquidos.h>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->move(QApplication::desktop()->availableGeometry().center() - this->rect().center()); //Establecer posición de la ventana en el centro.
}

void MainWindow::resizeEvent(QResizeEvent *evt)
{

    QPixmap bkgnd(":/new/prefix1/Fondo.png");//Load picture.
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);//set scale of pic to match the window
    QPalette p = palette(); //copy current, not create new
    p.setBrush(QPalette::Background, bkgnd);//set the pic to the background
    setPalette(p);//show the background pic

    QMainWindow::resizeEvent(evt); //call base implementation

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_Opc1_clicked()
{
    this->close(); //Se cierra esta ventana.

    variosObjetos *vO;
    vO = new variosObjetos(this);
    vO->show(); //Se abre la ventana para la simulación con varios objetos.
}

void MainWindow::on_btn_Opc2_clicked()
{
    this->close(); //Se cierra esta ventana.

    objetosSumergidosEnLiquidos *oF;
    oF = new objetosSumergidosEnLiquidos(this); //Se abre la ventana para la simulación con un objeto y fluido.
    oF->show();
}
