#include "acelerado.h"
#include "ui_acelerado.h"
#include <mainwindow.h>
#include <iostream>
#include <QDoubleValidator>
#include <string>
#include <sstream>
#include <string.h>
#include <QMessageBox>
#include <math.h>

using namespace std;

double W0=0;
double Alpha;
double Wmax=0;
double Alphamax;
double X_1=0;
double Y_1=0;
double X_2=0;
double Y_2=0;
int Punto2Habilitado=0;

acelerado::acelerado(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::acelerado)
{
    ui->setupUi(this);

    QPixmap bkgnd(":/new/prefix1/pizarra.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    ui->velocidadAngularInicial->setValidator(new QDoubleValidator(-39.5, 99.0, 5, ui->velocidadAngularInicial));
    ui->alpha->setValidator(new QDoubleValidator(-39.5, 99.0, 5, ui->alpha));
    ui->posX1->setValidator(new QDoubleValidator(-39.5, 99.0, 5, ui->posX1));
    ui->posY1->setValidator(new QDoubleValidator(-39.5, 99.0, 5, ui->posY1));
    ui->posX2->setValidator(new QDoubleValidator(-39.5, 99.0, 5, ui->posX2));
    ui->posY2->setValidator(new QDoubleValidator(-39.5, 99.0, 5, ui->posY2));

    ui->posX2->setDisabled(true);
    ui->posY2->setDisabled(true);
}

acelerado::~acelerado()
{
    delete ui;
}

void acelerado::on_pushButton_2_clicked()
{
    hide();
    MainWindow *mainwindow;
    mainwindow = new MainWindow(this);
    mainwindow->show();
}

void acelerado::on_cbHabilitar_clicked()
{
    if(ui->cbHabilitar->isChecked()){
        ui->posX2->setEnabled(true);
        ui->posY2->setEnabled(true);
        Punto2Habilitado=1;
    }else{
        ui->posX2->setDisabled(true);
        ui->posY2->setDisabled(true);
        ui->posX2->clear();
        ui->posY2->clear();
        X_2 = 0;
        Y_2=0;
        Punto2Habilitado=0;
    }
}

void acelerado::on_pushButton_clicked()
{
    string argumento = "";
    stringstream concatenador;

    //Guardamos en las variables los valores capturados en los widget Text Edit.

    W0 = ui->velocidadAngularInicial->text().toDouble();
    Alpha = ui->alpha->text().toDouble();
    X_1 = ui->posX1->text().toDouble();
    Y_1 = ui->posY1->text().toDouble();
    X_2 = ui->posX2->text().toDouble();
    Y_2 = ui->posY2->text().toDouble();

    if(ui->velocidadAngularInicial->text().isEmpty()==false && ui->alpha->text().isEmpty()==false && ui->posX1->text().isEmpty()==false && ui->posY1->text().isEmpty()==false){

        if((sqrt(pow(X_1,2)+pow(Y_1,2))<=2) and (sqrt(pow(X_2,2)+pow(Y_2,2))<=2)){

            if(abs(W0)<=50){

                if(abs(Alpha)<=50){

                    if(abs(W0)<=1){
                        Wmax=W0;
                    }else if(W0>1){
                        Wmax=1;
                        QMessageBox::information(this, tr("¡ATENCIóN!"), tr("Se han reescalado los vestores por ser muy grandes."));
                    }else if(W0<-1){
                        Wmax=-1;
                        QMessageBox::information(this, tr("¡ATENCIóN!"), tr("Se han reescalado los vestores por ser muy grandes."));
                    }

                    if(abs(Alpha)<=2){
                        Alphamax=Alpha;
                    }else if(Alpha>2){
                        Alphamax=2;
                        QMessageBox::information(this, tr("¡ATENCIóN!"), tr("Se han reescalado el vector aceleración tangencial por ser muy grande."));
                    }else if(Alpha<-2){
                        Alphamax=-2;
                        QMessageBox::information(this, tr("¡ATENCIóN!"), tr("Se han reescalado el vector aceleración tangencial por ser muy grande."));
                    }

                    //Concatenamos el nombre del ejectuble de OpenGL y los datos de forma ordenada en una variable llamada concatenador.

                    concatenador << "AMCA.exe " << W0 << " "<< Wmax << " " << Alpha << " " << Alphamax << " " << X_1 << " "<< Y_1 << " "<< X_2 << " "<< Y_2 <<" "<<Punto2Habilitado;
                    argumento = concatenador.str();

                    //Creamos un puntero llamado c que contendra la dirreción de concatenador.

                    const char *c = argumento.c_str();

                    cout << c <<endl;

                    //Mandamos los datos de concatenador y esto abrira el ejecutable de OpenGl.

                    system(c);

                }
                else{
                    QMessageBox::information(this, tr("¡ATENCIóN!"), tr("Este programa no permite un alpha mayor a 50."));
                    ui->alpha->clear(); Alpha=0;
                }

            }else{
                QMessageBox::information(this, tr("¡ATENCIóN!"), tr("Este programa no permite una velocidad angular inicial mayor a 50."));
                ui->velocidadAngularInicial->clear(); W0=0;
            }

        }else{

            QMessageBox::information(this, tr("¡ALERTA!"), tr("Los valores de las posiciones en x,y de los puntos no deben superar el radio de 2m de la circunferencia."));
            ui->posX1->clear(); X_1=0;
            ui->posY1->clear(); Y_1=0;
            ui->posX2->clear(); X_2=0;
            ui->posY2->clear(); Y_2=0;

        }
    }else{
        QMessageBox::information(this, tr("¡ALERTA!"), tr("Rellene todos los campos."));
    }
}
