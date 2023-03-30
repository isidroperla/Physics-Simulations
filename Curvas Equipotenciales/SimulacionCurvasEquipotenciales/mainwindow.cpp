//Autor: José Isidro Perla Rosa

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>
#include <iostream>
#include <math.h>
#include <QString>
#include <sstream>
#include <string.h>
#include <QDoubleValidator>
#include <QMessageBox>

float x_1=0; //Posición en x carga 1
float y_1=0; //Posición en y carga 2
float q1=0; //Carga 1
float x_2=0; //Posición en x carga 2
float y_2=0; //Posición en x carga 2
float q2=0; //Carga 2
float exponente1=0; //Eponente de la carga 1 x10^.
float exponente2=0; //Eponente de la carga 2 x10^.
bool activarLineasDeCampo=false; //Variable booleana para activar/desactivar las lineas de campo eléctrico.

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowState(Qt::WindowMaximized); //Establecer tamaño de la ventana de forma maximizada.
    this->move(QApplication::desktop()->availableGeometry().center() - this->rect().center()); //Establecer posición de la ventana en el centro.

    ui->txt_x1->setValidator(new QDoubleValidator(-39.5, 99.0, 5, ui->txt_x1)); //Validación para que el usuario solo pueda ingresar números en el lineEdit.
    ui->txt_y1->setValidator(new QDoubleValidator(-39.5, 99.0, 5, ui->txt_y1)); //Validación para que el usuario solo pueda ingresar números en el lineEdit.
    ui->txt_x2->setValidator(new QDoubleValidator(-39.5, 99.0, 5, ui->txt_x2)); //Validación para que el usuario solo pueda ingresar números en el lineEdit.
    ui->txt_y2->setValidator(new QDoubleValidator(-39.5, 99.0, 5, ui->txt_y2)); //Validación para que el usuario solo pueda ingresar números en el lineEdit.
    ui->txt_q1->setValidator(new QDoubleValidator(-39.5, 99.0, 5, ui->txt_q1)); //Validación para que el usuario solo pueda ingresar números en el lineEdit.
    ui->txt_q2->setValidator(new QDoubleValidator(-39.5, 99.0, 5, ui->txt_q2)); //Validación para que el usuario solo pueda ingresar números en el lineEdit.

    ui->sB_q1->setRange(-15,0); //Rango del spinBox
    ui->sB_q1->setSingleStep(3); //Se define el salto del spinBox
    ui->sB_q1->findChild<QLineEdit*>()->setReadOnly(true); //SpinBox validación para no escribir manualmente los valores.

    ui->sB_q2->setRange(-15,0); //Rango del spinBox
    ui->sB_q2->setSingleStep(3); //Se define el salto del spinBox
    ui->sB_q2->findChild<QLineEdit*>()->setReadOnly(true); //SpinBox validación para no escribir manualmente los valores.

    QPalette* color = new QPalette();
    color->setColor(QPalette::Foreground,Qt::white);
    ui->cB_lineasDeCampo->setPalette(*color); //Se añade por defecto el color blanco al texto del checkBox.
}

void MainWindow::resizeEvent(QResizeEvent *evt) //Función para establecer la imagen de fondo y que sea responsiba
{
    QPixmap bkgnd(":/new/prefix1/pizarra.png");//Cargar imagen.
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);//Establecer escala de imagen para que coincida con la ventana.
    QPalette p = palette(); //Copiar actual, no crear nuevo.
    p.setBrush(QPalette::Background, bkgnd);//Poner la imagen de fondo.
    setPalette(p);//Mostrar la imagen de fondo.
    QMainWindow::resizeEvent(evt); //Implementación de base de llamadas.
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_calcular_clicked()
{
    string argumento = "";
    stringstream concatenador;

    bool res=true; //Variable de respuesta booleana para las validaciones.

    //Se guardan los datos de los campos en las variables.
    x_1 = ui->txt_x1->text().toDouble();
    y_1 = ui->txt_y1->text().toDouble();
    q1 = ui->txt_q1->text().toDouble();
    exponente1 = ui->sB_q1->value();
    q1*=pow(10,exponente1);

    x_2 = ui->txt_x2->text().toDouble();
    y_2 = ui->txt_y2->text().toDouble();
    q2 = ui->txt_q2->text().toDouble();
    exponente2 = ui->sB_q2->value();
    q2*=pow(10,exponente2);

    if((x_1<0 || y_1<0 || y_1<0 || y_2<0) || (x_1>10 || y_1>10 || y_1>10 || y_2>10)){ //Valicación de posiciones.
        QMessageBox::information(this, tr("¡ALERTA!"), tr("Las posiciones x1, y1, x2, y2 solo puden aceptar valores en el rango de (0-10)."));
        res=false;
    }
    if(x_1==x_2 && y_1==y_2){ //Validación de que no se puedan poner las dos cargas en la misma posición.
        QMessageBox::information(this, tr("¡ALERTA!"), tr("No se pueden colocar las dos cargas en la misma posición."));
        res=false;
    }
    if(q1==0 || q2==0){ //Validación de que las cargas no sean cero.
        QMessageBox::information(this, tr("¡ALERTA!"), tr("Los valores de las cargas q1 y q2 no pueden tomar el valor de 0."));
        res=false;
    }
    if(ui->txt_x1->text().isEmpty() || ui->txt_y1->text().isEmpty() || ui->txt_x2->text().isEmpty() || ui->txt_y2->text().isEmpty() || ui->txt_q1->text().isEmpty() || ui->txt_q2->text().isEmpty()){ //Validación de que no hayan campos vacios.
        QMessageBox::information(this, tr("¡ALERTA!"), tr("Debe llenar todos los campos."));
        res=false;
    }

    if(ui->cB_lineasDeCampo->isChecked()){ //Condición para activar o desactivar las lineas de campos eléctrico.
        activarLineasDeCampo=true;
    }else{
        activarLineasDeCampo=false;
    }

    if(res!=false){

        //Concatenamos el nombre del ejectuble de OpenGL y los datos de forma ordenada en una variable llamada concatenador.

        concatenador << "Animacion.exe " << x_1 << " " << y_1 << " " << q1 << " " << x_2 << " " << y_2 << " " << q2 << " " << activarLineasDeCampo;
        argumento = concatenador.str();

        //Creamos un puntero llamado c que contendra la dirreción de concatenador.

        const char *c = argumento.c_str();

        //Se imprimen los datos en el Application Output para verificar que todo este en orden.

        cout << c <<endl;

        //Mandamos los datos de concatenador y esto abrira el ejecutable de OpenGl.

        system(c);

    }

}
