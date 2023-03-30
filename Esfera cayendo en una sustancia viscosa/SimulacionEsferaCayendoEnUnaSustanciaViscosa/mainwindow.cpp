//Autor: José Isidro Perla Rosa

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>
#include <iostream>
#include <sstream>
#include <string.h>
#include <QDoubleValidator>
#include <QMessageBox>
#include <QInputDialog>
#include <QDebug>

using namespace std;

float R=0; //Radio de la esfera.
float De=0; //Densidad de la esfera.
float Df=0; //Densidad del fluido.
float n=0; //Valor de la viscosidad.
int opc=1; //Valor para definir el tipo de fluido seleccionado.

int res =0; //Variable de respuesta boleena para validaciones.
float tiempoMax=90; //Valor para definir el tiempo maximo de la animación (opcional).
float distanciamax=0; //Valor para definir la distancia maxima de la animación (opcional).

QString densidadesFluidos[] = {"1030", "1050", "791", "1260", "13600", "1000"}; //Valores de las densidades de los fluidos en kg/m3.
QString viscosidadesFluidos[] = {"0.015", "0.004", "0.00120", "1.49", "0.00155", "0.001"}; //Valores de las viscosidades en kg/m·s.

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowState(Qt::WindowMaximized); //Establecer tamaño de la ventana de forma maximizada.
    this->move(QApplication::desktop()->availableGeometry().center() - this->rect().center()); //Establecer posición de la ventana en el centro.

    ui->cB_Fluidos->addItems({"Plasma sanguíneo", "Sangre", "Etanol", "Glicerina", "Mercurio", "Agua pura", "Otro"});

    ui->txt_RadioEsfera->setValidator(new QDoubleValidator(-39.5, 99.0, 5, ui->txt_RadioEsfera)); //Validación para que el usuario solo pueda ingresar números en el lineEdit.
    ui->txt_DensidadEsfera->setValidator(new QDoubleValidator(-39.5, 99.0, 5, ui->txt_DensidadEsfera)); //Validación para que el usuario solo pueda ingresar números en el lineEdit.
    ui->txt_DensidadFluido->setValidator(new QDoubleValidator(-39.5, 99.0, 5, ui->txt_DensidadFluido)); //Validación para que el usuario solo pueda ingresar números en el lineEdit.
    ui->txt_Viscosidad->setValidator(new QDoubleValidator(-39.5, 99.0, 5, ui->txt_Viscosidad)); //Validación para que el usuario solo pueda ingresar números en el lineEdit.

    QPalette* color = new QPalette();
    color->setColor(QPalette::Foreground,Qt::white);
    ui->cB_opcDetenerse->setPalette(*color); //Se añade por defecto el color blanco al texto del checkBox

    ui->cB_opcDetenerse->setLayoutDirection(Qt::RightToLeft);
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

void MainWindow::on_cB_Fluidos_activated(int index) //Función que coloca automaticamnte el valor de la densidad y viscosidad del fluido seleccionado.
{
    switch (ui->cB_Fluidos->currentIndex()) {

    case 0:
        ui->txt_DensidadFluido->setText(densidadesFluidos[0]);
        ui->txt_Viscosidad->setText(viscosidadesFluidos[0]);
        opc=1;
        break;
    case 1:
        ui->txt_DensidadFluido->setText(densidadesFluidos[1]);
        ui->txt_Viscosidad->setText(viscosidadesFluidos[1]);
        opc=2;
        break;
    case 2:
        ui->txt_DensidadFluido->setText(densidadesFluidos[2]);
        ui->txt_Viscosidad->setText(viscosidadesFluidos[2]);
        opc=3;
        break;
    case 3:
        ui->txt_DensidadFluido->setText(densidadesFluidos[3]);
        ui->txt_Viscosidad->setText(viscosidadesFluidos[3]);
        opc=4;
        break;
    case 4:
        ui->txt_DensidadFluido->setText(densidadesFluidos[4]);
        ui->txt_Viscosidad->setText(viscosidadesFluidos[4]);
        opc=5;;
        break;
    case 5:
        ui->txt_DensidadFluido->setText(densidadesFluidos[5]);
        ui->txt_Viscosidad->setText(viscosidadesFluidos[5]);
        opc=6;
        break;
    case 6:
        opc=7;
        break;
    }
}

void MainWindow::on_txt_DensidadFluido_textEdited(const QString &arg1) //Marca como otro fluido en el comboBox si se ha seleccionado la densidad.
{
    ui->cB_Fluidos->setCurrentIndex(6);
    for(int i=0; i<=5; i++){
        if(ui->txt_DensidadFluido->text()!=densidadesFluidos[i]){
            opc=7;
        }
    }

    for(int i=0; i<=5; i++){
        if((ui->txt_DensidadFluido->text()==densidadesFluidos[i]) &&(ui->txt_Viscosidad->text()==viscosidadesFluidos[i])){
            ui->cB_Fluidos->setCurrentIndex(i);
            opc=i;
        }
    }
}

void MainWindow::on_txt_Viscosidad_textEdited(const QString &arg1) //Marca como otro fluido en el comboBox si se ha seleccionado la viscosidad.
{
    ui->cB_Fluidos->setCurrentIndex(6);
    for(int i=0; i<=5; i++){
        if(ui->txt_Viscosidad->text()!=viscosidadesFluidos[i]){
            opc=7;
        }
    }

    for(int i=0; i<=5; i++){
        if((ui->txt_DensidadFluido->text()==densidadesFluidos[i]) &&(ui->txt_Viscosidad->text()==viscosidadesFluidos[i])){
            ui->cB_Fluidos->setCurrentIndex(i);
            opc=i;
        }
    }
}

void MainWindow::on_btn_Calcular_clicked()
{
    string argumento = "";
    stringstream concatenador;

    bool res=true;

    qDebug() <<opc;

    R = ui->txt_RadioEsfera->text().toDouble();
    De = ui->txt_DensidadEsfera->text().toDouble();
    Df = ui->txt_DensidadFluido->text().toDouble();
    n = ui->txt_Viscosidad->text().toDouble();

    if(Df>=De){
        QMessageBox::information(this, tr("¡ALERTA!"), tr("La densidad de la esfera debe ser mayor que la del fluido."));
        res=false;
    }
    if(ui->txt_RadioEsfera->text().isEmpty() || ui->txt_DensidadEsfera->text().isEmpty() || ui->txt_DensidadFluido->text().isEmpty() || ui->txt_Viscosidad->text().isEmpty()){
        QMessageBox::information(this, tr("¡ALERTA!"), tr("Debe llenar todos los campos."));
        res=false;
    }
    if((R==0 || De==0 || Df==0 || n==0) || (R<0 || De<0 || Df<0 || n<0)){
        QMessageBox::information(this, tr("¡ALERTA!"), tr("Por favor coloque valores diferentes de cero y positivos."));
        res=false;
    }

    if(ui->cB_opcDetenerse->isChecked()==false){
        tiempoMax=90;
        distanciamax=0;
    }

    if(res!=false){

        //Concatenamos el nombre del ejectuble de OpenGL y los datos de forma ordenada en una variable llamada concatenador.

        concatenador << "Animacion.exe " << opc << " " << R << " " << De << " " << Df << " " << n << " " << tiempoMax << " " << distanciamax;
        argumento = concatenador.str();

        //Creamos un puntero llamado c que contendra la dirreción de concatenador.

        const char *c = argumento.c_str();

        //Se imprimen los datos en el Application Output para verificar que todo este en orden.

        cout << c <<endl;

        //Mandamos los datos de concatenador y esto abrira el ejecutable de OpenGl.

        system(c);

    }

}

void MainWindow::on_cB_opcDetenerse_clicked() //Opciones extra para configurar cuando se detendra la animación ya sea seleccionando el tiempo o la distancia.
{

    bool ok=true;
    bool salir=false;
    res=0;

    if(ui->cB_opcDetenerse->isChecked()){
        res = QInputDialog::getText(0, "Detenerse en", "(1)Tiempo\n(2)Distancia\n(3)Salir", QLineEdit::Normal, "", &ok).toDouble();
    }

    switch (res){

        case 1:
            do{
                tiempoMax = QInputDialog::getDouble(this, tr("Detenerse en"), tr("Introduzca el tiempo en segundos:"), 0.00, 0, 10000, 2, &ok);
                if(ok==false){
                    salir=true;
                }
            }while((tiempoMax==0 || tiempoMax<0) && salir==false);
            distanciamax=0;
        break;

        case 2:
            do{
                distanciamax = QInputDialog::getDouble(this, tr("Detenerse en"), tr("Introduzca el tiempo en segundos:"), 0.00, 0, 10000, 2, &ok);
                if(ok==false){
                    salir=true;
                }
            }while((distanciamax==0 || distanciamax<0) && salir==false);
            tiempoMax=90;
        break;

        default:
            ui->cB_opcDetenerse->setChecked(false);
        break;
    }

    if(ok==false){
        ui->cB_opcDetenerse->setChecked(false);
    }

}
