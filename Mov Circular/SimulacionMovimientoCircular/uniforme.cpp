#include "uniforme.h"
#include "ui_uniforme.h"
#include "mainwindow.h"
#include <iostream>
#include <QDoubleValidator>
#include <string>
#include <sstream>
#include <string.h>
#include <QMessageBox>
#include <math.h>

using namespace std;

double w=0;
double wmax=0;
double x_1=0;
double y_1=0;
double x_2=0;
double y_2=0;
int punto2Habilitado=0;

Uniforme::Uniforme(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Uniforme)
{
    ui->setupUi(this);

    QPixmap bkgnd(":/new/prefix1/pizarra.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    ui->velocidadAngular->setValidator(new QDoubleValidator(-39.5, 99.0, 5, ui->velocidadAngular));
    ui->posX1->setValidator(new QDoubleValidator(-39.5, 99.0, 5, ui->posX1));
    ui->posY1->setValidator(new QDoubleValidator(-39.5, 99.0, 5, ui->posY1));
    ui->posX2->setValidator(new QDoubleValidator(-39.5, 99.0, 5, ui->posX2));
    ui->posY2->setValidator(new QDoubleValidator(-39.5, 99.0, 5, ui->posY2));

    ui->posX2->setDisabled(true);
    ui->posY2->setDisabled(true);

}

Uniforme::~Uniforme()
{
    delete ui;
}

void Uniforme::on_pushButton_2_clicked()
{
    hide();
    MainWindow *mainwindow;
    mainwindow = new MainWindow(this);
    mainwindow->show();
}

void Uniforme::on_pushButton_clicked()
{
    string argumento = "";
    stringstream concatenador;

    //Guardamos en las variables los valores capturados en los widget Text Edit.

    w = ui->velocidadAngular->text().toDouble();
    x_1 = ui->posX1->text().toDouble();
    y_1 = ui->posY1->text().toDouble();
    x_2 = ui->posX2->text().toDouble();
    y_2 = ui->posY2->text().toDouble();

    if(ui->velocidadAngular->text().isEmpty()==false && ui->posX1->text().isEmpty()==false && ui->posY1->text().isEmpty()==false){

        if((sqrt(pow(x_1,2)+pow(y_1,2))<=2) and (sqrt(pow(x_2,2)+pow(y_2,2))<=2)){

            if(abs(w)<=1){
                wmax=w;
            }else if(w>1){
                wmax=1;
                QMessageBox::information(this, tr("¡ATENCIóN!"), tr("Se han reescalado los vestores por ser muy grandes."));
            }else if(w<-1){
                wmax=-1;
                QMessageBox::information(this, tr("¡ATENCIóN!"), tr("Se han reescalado los vestores por ser muy grandes."));
            }

            //Concatenamos el nombre del ejectuble de OpenGL y los datos de forma ordenada en una variable llamada concatenador.

            concatenador << "AMCU.exe " << w << " "<< wmax << " "<< x_1 << " "<< y_1 << " "<< x_2 << " "<< y_2 <<" "<<punto2Habilitado;
            argumento = concatenador.str();

            //Creamos un puntero llamado c que contendra la dirreción de concatenador.

            const char *c = argumento.c_str();

            cout << c <<endl;

            //Mandamos los datos de concatenador y esto abrira el ejecutable de OpenGl.

            system(c);

        }else{

            QMessageBox::information(this, tr("¡ALERTA!"), tr("Los valores de las posiciones en x,y de los puntos no deben superar el radio de 2m de la circunferencia."));
            ui->posX1->clear(); x_1=0;
            ui->posY1->clear(); y_1=0;
            ui->posX2->clear(); x_2=0;
            ui->posY2->clear(); y_2=0;

        }

    }else{
        QMessageBox::information(this, tr("¡ALERTA!"), tr("Rellene todos los campos."));
    }

}

void Uniforme::on_cbHabilitar_clicked()
{
    if(ui->cbHabilitar->isChecked()){
        ui->posX2->setEnabled(true);
        ui->posY2->setEnabled(true);
        punto2Habilitado=1;
    }else{
        ui->posX2->setDisabled(true);
        ui->posY2->setDisabled(true);
        ui->posX2->clear();
        ui->posY2->clear();
        x_2 = 0;
        y_2=0;
        punto2Habilitado=0;
    }
}
