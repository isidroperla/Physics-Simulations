//Autor: José Isidro Perla Rosa
//Programa: Simulación Sistema de Unidades

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <conversionvelocidad.h>
#include <conversionmasa.h>
#include <conversionlongitud.h>
#include <medicionincertidumbre.h>
#include <notacioncientifica.h>
#include <precisionexactitud.h>
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->move(QApplication::desktop()->availableGeometry().center() - this->rect().center()); //Establecer posición de la ventana en el centro.
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *evt)
{

    QPixmap bkgnd(":/new/prefix1/recursos/fondo.png");//Load picture.
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);//set scale of pic to match the window
    QPalette p = palette(); //copy current, not create new
    p.setBrush(QPalette::Background, bkgnd);//set the pic to the background
    setPalette(p);//show the background pic

    QMainWindow::resizeEvent(evt); //call base implementation

}

void MainWindow::on_btn_opc_longitud_clicked()
{
    this->close(); //Se cierra esta ventana.
    ConversionLongitud *CL;
    CL = new ConversionLongitud();
    CL->show();
}

void MainWindow::on_btn_opc_incertidumbre_clicked()
{
    this->close(); //Se cierra esta ventana.
    MedicionIncertidumbre *MI;
    MI = new MedicionIncertidumbre();
    MI->show();
}

void MainWindow::on_btn_opc_notacion_clicked()
{
    this->close(); //Se cierra esta ventana.
    NotacionCientifica *NC;
    NC = new NotacionCientifica();
    NC->show();
}

void MainWindow::on_btn_opc_masa_clicked()
{
    this->close(); //Se cierra esta ventana.
    ConversionMasa *CM;
    CM = new ConversionMasa();
    CM->show();
}

void MainWindow::on_btn_opc_velocidad_clicked()
{
    this->close(); //Se cierra esta ventana.
    ConversionVelocidad *CV;
    CV = new ConversionVelocidad();
    CV->show();
}

void MainWindow::on_btn_opc_precision_clicked()
{
    this->close(); //Se cierra esta ventana.
    PrecisionExactitud *PE;
    PE = new PrecisionExactitud();
    PE->show();
}

void MainWindow::on_btn_cerrar_clicked()
{
    this->close();
}
