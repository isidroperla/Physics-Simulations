//Autor: José Isidro Perla Rosa

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <string>
#include <sstream>
#include <string.h>
#include <QMessageBox>
#include <QDoubleValidator>
#include <QDesktopWidget>
#include <grafica.h>
#include <grafica2.h>

using namespace std;

double r=0;
double h=0;
int obj=0;
int p=0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowState(Qt::WindowMaximized);

    this->move(QApplication::desktop()->availableGeometry().center() - this->rect().center());

    ui->cb_objetos->addItem("Esfera");
    ui->cb_objetos->addItem("Cilindro");
    ui->cb_objetos->addItem("Cubo");

    ui->txt_h->setValidator(new QDoubleValidator(-39.5, 99.0, 5, ui->txt_h));
    ui->txt_r->setValidator(new QDoubleValidator(-39.5, 99.0, 5, ui->txt_r));

    QPalette* color = new QPalette();
    color->setColor(QPalette::Foreground,Qt::white);
    ui->radioButton->setPalette(*color);
    ui->radioButton_2->setPalette(*color);
}

void MainWindow::resizeEvent(QResizeEvent *evt)
{

    QPixmap bkgnd(":/new/prefix1/pizarra.png");//Load pic
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

void MainWindow::on_btn_calcular_clicked()
{

    string argumento = "";
    stringstream concatenador;

    h = ui->txt_h->text().toDouble();
    r = ui->txt_r->text().toDouble();

    if(ui->cb_objetos->currentText() == "Esfera"){
        obj = 1;
    }
    else if(ui->cb_objetos->currentText() == "Cilindro"){
        obj = 2;
    }
    else if(ui->cb_objetos->currentText() == "Cubo"){
        obj = 3;
    }

    if(ui->radioButton->isChecked()){
        p=25;
        QMessageBox::information(this, tr("¡PRECISIÓN DE LA ANIMACIÓN BAJA!"), tr("El programa intenta simular en tiempo real, pero la animación no es precisa."));
    }
    if(ui->radioButton_2->isChecked()){
        p=1;
        QMessageBox::information(this, tr("¡PRECISIÓN DE LA ANIMACIÓN ALTA!"), tr("El tiempo podría pasar lento en comparación al real pero la animación es precisa."));
    }

    //Guardamos en las variables los valores capturados en los widget Text Edit.

    if((h>=0 && r>=0)){

        if(h<r){

            //Concatenamos el nombre del ejectuble de OpenGL y los datos de forma ordenada en una variable llamada concatenador.

            concatenador << "Animacion " << h << " " << r << " "<<obj << " "<<p;
            argumento = concatenador.str();

            //Creamos un puntero llamado c que contendra la dirreción de concatenador.

            const char *c = argumento.c_str();

            cout << c <<endl;

            //Mandamos los datos de concatenador y esto abrira el ejecutable de OpenGl.

            system(c);

        }else{
            QMessageBox::information(this, tr("¡ALERTA!"), tr("r debe ser mayor que h."));

            ui->txt_h->clear(); h=0;
            ui->txt_r->clear(); r=0;
        }

    }else{
        QMessageBox::information(this, tr("¡ALERTA!"), tr("Los valores de h y r deben ser positivos."));

        ui->txt_h->clear(); h=0;
        ui->txt_r->clear(); r=0;
    }

}

void MainWindow::on_pushButton_clicked()
{

    h = ui->txt_h->text().toDouble();
    r = ui->txt_r->text().toDouble();

    if(ui->cb_objetos->currentText() == "Esfera"){
        obj = 1;
    }
    else if(ui->cb_objetos->currentText() == "Cilindro"){
        obj = 2;     
    }
    else if(ui->cb_objetos->currentText() == "Cubo"){
        obj = 3;
    }


    if((h>=0 && r>=0)){

        if(h<r){

            //hide();
            Grafica *grafica;
            grafica = new Grafica(h, r, obj, this);
            grafica->show();

        }else{
            QMessageBox::information(this, tr("¡ALERTA!"), tr("r debe ser mayor que h."));

            ui->txt_h->clear(); h=0;
            ui->txt_r->clear(); r=0;
        }

    }else{
        QMessageBox::information(this, tr("¡ALERTA!"), tr("Los valores de h y r deben ser positivos."));

        ui->txt_h->clear(); h=0;
        ui->txt_r->clear(); r=0;
    }

}

void MainWindow::on_pushButton_2_clicked()
{

    h = ui->txt_h->text().toDouble();
    r = ui->txt_r->text().toDouble();

    if(ui->cb_objetos->currentText() == "Esfera"){
        obj = 1;
    }
    else if(ui->cb_objetos->currentText() == "Cilindro"){
        obj = 2;
    }
    else if(ui->cb_objetos->currentText() == "Cubo"){
        obj = 3;
    }


    if((h>=0 && r>=0)){

        if(h<r){

            //hide();
            Grafica2 *grafica2;
            grafica2 = new Grafica2(h, r, obj, this);
            grafica2->show();

        }else{
            QMessageBox::information(this, tr("¡ALERTA!"), tr("r debe ser mayor que h."));

            ui->txt_h->clear(); h=0;
            ui->txt_r->clear(); r=0;
        }

    }else{
        QMessageBox::information(this, tr("¡ALERTA!"), tr("Los valores de h y r deben ser positivos."));

        ui->txt_h->clear(); h=0;
        ui->txt_r->clear(); r=0;
    }


}
