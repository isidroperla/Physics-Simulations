//AUTORES:
//José Isidro Perla Rosa
//Melvin Osmel Batres Rodríguez

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <string.h>
#include <QKeyEvent>
#include <math.h>
#include <QMessageBox>
#include <QDoubleValidator>
#include <QDesktopWidget>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->move(QApplication::desktop()->availableGeometry().center() - this->rect().center());

    ui->sB_XF1->setRange(-5.00f, 5.00f); //Se define el rango de valores para el spinBox de la masa.
    ui->sB_XF1->setSingleStep(0.25f); //Se hacen aumentos de 0.25.

    ui->sB_YF1->setRange(-2.50f, 2.50f); //Se define el rango de valores para el spinBox de la masa.
    ui->sB_YF1->setSingleStep(0.25f); //Se hacen aumentos de 0.25.

    ui->sB_XF2->setRange(-5.00f, 5.00f); //Se define el rango de valores para el spinBox de la masa.
    ui->sB_XF2->setSingleStep(0.25f); //Se hacen aumentos de 0.25.

    ui->sB_YF1->setRange(-2.50f, 2.50f); //Se define el rango de valores para el spinBox de la masa.
    ui->sB_YF1->setSingleStep(0.25f); //Se hacen aumentos de 0.25.

    ui->txt_K1->setValidator(new QDoubleValidator(-39.5, 99.0, 5, ui->txt_K1));
    ui->txt_K2->setValidator(new QDoubleValidator(-39.5, 99.0, 5, ui->txt_K2));
    ui->txt_W1->setValidator(new QDoubleValidator(-39.5, 99.0, 5, ui->txt_W1));
    ui->txt_W2->setValidator(new QDoubleValidator(-39.5, 99.0, 5, ui->txt_W2));
    ui->txt_T->setValidator(new QDoubleValidator(-39.5, 99.0, 5, ui->txt_T));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Este es el botón para mandar datos y abrir el ejecutable de OpenGl

void MainWindow::on_pushButton_clicked()
{
    QMessageBox msgBox;
        if(
                   ui->txt_K1->text().isEmpty()
                || ui->txt_K2->text().isEmpty()
                || ui->txt_W1->text().isEmpty()
                || ui->txt_W2->text().isEmpty()
                || ui->txt_T->text().isEmpty()
            )
        {
            msgBox.setText("Rellene todos los campos");
            msgBox.exec();
        }else{
    string argumento = "";
    stringstream concatenador;

    //Se crean las variables que almacenaran los datos de los QTextEdit

    double xf1; //Posicion en x de la fuente 1
    double yf1; //Posicion en y de la fuente 1
    double k1; //Número de ondas de la fuente 1
    double w1; //Velocidad angular de la fuente 1
    double xf2; //Posicion en x de la fuente 2
    double yf2; //Posicion en y de la fuente 2
    double k2; //Número de ondas de la fuente 2
    double w2; //Velocidad angular de la fuente 2
    double t; //tiempo

    //Guardamos en las variables pertenecientes a la Fuente 1 los valores escritos en los  QTextEdit y se convertidos a datos del tipo double.

    xf1 = ui->sB_XF1->text().toDouble();
    yf1 = ui->sB_YF1->text().toDouble();
    k1 = ui->txt_K1->text().toDouble();
    w1 = ui->txt_W1->text().toDouble();

    //Guardamos en las variables pertenecientes a la Fuente 2 los valores escritos en los  QTextEdit y se convertidos a datos del tipo double.

    xf2 = ui->sB_XF2->text().toDouble();
    yf2 = ui->sB_YF2->text().toDouble();
    k2 = ui->txt_K2->text().toDouble();
    w2 = ui->txt_W2->text().toDouble();

    t = ui->txt_T->text().toDouble();

    //Concatenamos el nombre del ejectuble de OpenGL y los datos de forma ordenada en una variable llamada concatenador.

    concatenador << "Animacion.exe " << xf1 << " "<< yf1 << " "<< k1 << " "<< w1 << " "<< xf2 << " "<< yf2 << " "<< k2 << " "<< w2 << " "<< t;
    argumento = concatenador.str();

    //Creamos un puntero llamado c que contendra la dirreción de concatenador.

    const char *c = argumento.c_str();

    cout << c <<endl;

    //Mandamos los datos de concatenador y esto abrira el ejecutable de OpenGl.

    system(c);
}
}

//Este botón manda parametros ya establecido siendo estas datos de una demostración

void MainWindow::on_pB_demo_clicked()
{
    string argumento = "";
    stringstream concatenador;

    //Se limpian los campos y se establecen los que se presionaron en el boton de la demo.

    ui->sB_XF1->clear(); ui->sB_XF1->setValue(5);
    ui->sB_YF1->clear(); ui->sB_YF1->setValue(0);
    ui->txt_K1->clear(); ui->txt_K1->setText("4");
    ui->txt_W1->clear(); ui->txt_W1->setText("0.1");
    ui->sB_XF2->clear(); ui->sB_XF2->setValue(0.4978);
    ui->sB_YF2->clear(); ui->sB_YF2->setValue(0);
    ui->txt_K2->clear(); ui->txt_K2->setText("4");
    ui->txt_W2->clear(); ui->txt_W2->setText("0.1");
    ui->txt_T->clear(); ui->txt_T->setText("2");

    //Concatenamos el nombre del ejectuble de OpenGL y los datos de forma ordenada en una variable llamada concatenador.

    concatenador << "Animacion.exe " << 5 << " "<< 0 << " "<< 4 << " "<< 0.1 << " "<< 0.4978 << " "<< 0 << " "<< 4 << " "<< 0.1 << " "<< 2;
    argumento = concatenador.str();

    //Creamos un puntero llamado c que contendra la dirreción de concatenador.

    const char *c = argumento.c_str();

    cout << c <<endl;

    //Mandamos los datos de concatenador y esto abrira el ejecutable de OpenGl.

    system(c);
}

void MainWindow::on_pB_demo_2_clicked()
{
    string argumento = "";
    stringstream concatenador;

    //Se limpian los campos y se establecen los que se presionaron en el boton de la demo.

    ui->sB_XF1->clear(); ui->sB_XF1->setValue(5);
    ui->sB_YF1->clear(); ui->sB_YF1->setValue(3);
    ui->txt_K1->clear(); ui->txt_K1->setText("4");
    ui->txt_W1->clear(); ui->txt_W1->setText("0.1");
    ui->sB_XF2->clear(); ui->sB_XF2->setValue(0.4978);
    ui->sB_YF2->clear(); ui->sB_YF2->setValue(-1);
    ui->txt_K2->clear(); ui->txt_K2->setText("4");
    ui->txt_W2->clear(); ui->txt_W2->setText("2.1");
    ui->txt_T->clear(); ui->txt_T->setText("2");

    //Concatenamos el nombre del ejectuble de OpenGL y los datos de forma ordenada en una variable llamada concatenador.

    concatenador << "Animacion.exe " << 5 << " "<< 3 << " "<< 4 << " "<< 2.1 << " "<< 0.4978 << " "<< -1 << " "<< 4 << " "<< 0.1 << " "<< 2;
    argumento = concatenador.str();

    //Creamos un puntero llamado c que contendra la dirreción de concatenador.

    const char *c = argumento.c_str();

    cout << c <<endl;

    //Mandamos los datos de concatenador y esto abrira el ejecutable de OpenGl.

    system(c);

}

void MainWindow::on_pB_demo_3_clicked()
{
    string argumento = "";
    stringstream concatenador;

    //Se limpian los campos y se establecen los que se presionaron en el boton de la demo.

    ui->sB_XF1->clear(); ui->sB_XF1->setValue(3);
    ui->sB_YF1->clear(); ui->sB_YF1->setValue(0);
    ui->txt_K1->clear(); ui->txt_K1->setText("4");
    ui->txt_W1->clear(); ui->txt_W1->setText("1.3");
    ui->sB_XF2->clear(); ui->sB_XF2->setValue(-2);
    ui->sB_YF2->clear(); ui->sB_YF2->setValue(3);
    ui->txt_K2->clear(); ui->txt_K2->setText("4");
    ui->txt_W2->clear(); ui->txt_W2->setText("1.3");
    ui->txt_T->clear(); ui->txt_T->setText("2");

    //Concatenamos el nombre del ejectuble de OpenGL y los datos de forma ordenada en una variable llamada concatenador.

    concatenador << "Animacion.exe " << 3 << " "<< 0 << " "<< 4 << " "<< 1.3 << " "<< -2 << " "<< 3 << " "<< 4 << " "<< 1.3 << " "<< 2;
    argumento = concatenador.str();

    //Creamos un puntero llamado c que contendra la dirreción de concatenador.

    const char *c = argumento.c_str();

    cout << c <<endl;

    //Mandamos los datos de concatenador y esto abrira el ejecutable de OpenGl.

    system(c);

}

void MainWindow::on_pushButton_2_clicked()
{
    QMessageBox msgBox;

    //Change background color
    QPalette palette;
    palette.setColor(QPalette::Background, Qt::blue);
    msgBox.setPalette(palette);
    msgBox.setWindowTitle("Información");
    msgBox.setIcon(QMessageBox::Question);
    //Change font
    QFont font( "Comic Sans MS" );
    font.setPointSize( 15 );
    font.setWeight( QFont::Bold);
    font.setItalic(true);
    msgBox.setFont(font);
    msgBox.setText("FORMULAS ONDAS:\n\n"
                   "y = y1 + y2\n\n"
                   "= A1sen(k1x-w1t)+A2sen(k2x+w2t)");
    msgBox.exec();
}

void MainWindow::on_txt_K1_editingFinished()
{
    if(ui->txt_K1->text().toDouble() <= 0 )
    {
        QMessageBox msgBox;

        //Change background color
        QPalette palette;
        palette.setColor(QPalette::Background, Qt::blue);
        msgBox.setPalette(palette);
        msgBox.setWindowTitle("Información");
        msgBox.setIcon(QMessageBox::Warning);
        //Change font
        QFont font( "Comic Sans MS" );
        font.setPointSize( 11 );
        font.setWeight( QFont::Bold);
        font.setItalic(true);
        msgBox.setFont(font);
        msgBox.setText("No se Permiten Negativos ni Valor 0");
        msgBox.exec();

        ui->txt_K1->clear();
    }
}

void MainWindow::on_txt_K2_editingFinished()
{
    if(ui->txt_K2->text().toDouble() <= 0 )
    {
        QMessageBox msgBox;

        //Change background color
        QPalette palette;
        palette.setColor(QPalette::Background, Qt::blue);
        msgBox.setPalette(palette);
        msgBox.setWindowTitle("Información");
        msgBox.setIcon(QMessageBox::Warning);
        //Change font
        QFont font( "Comic Sans MS" );
        font.setPointSize( 11 );
        font.setWeight( QFont::Bold);
        font.setItalic(true);
        msgBox.setFont(font);
        msgBox.setText("No se Permiten Negativos ni Valor 0");
        msgBox.exec();

        ui->txt_K2->clear();
    }
}

void MainWindow::on_txt_W1_editingFinished()
{
    if(ui->txt_W1->text().toDouble() <= 0 )
    {
        QMessageBox msgBox;
        //Change background color
        QPalette palette;
        palette.setColor(QPalette::Background, Qt::blue);
        msgBox.setPalette(palette);
        msgBox.setWindowTitle("Información");
        msgBox.setIcon(QMessageBox::Warning);
        //Change font
        QFont font( "Comic Sans MS" );
        font.setPointSize( 11 );
        font.setWeight( QFont::Bold);
        font.setItalic(true);
        msgBox.setFont(font);
        msgBox.setText("No se Permiten Negativos ni Valor 0");
        msgBox.exec();
        ui->txt_W1->clear();
    }
}

void MainWindow::on_txt_W2_editingFinished()
{
    if(ui->txt_W2->text().toDouble() <= 0 )
    {
        QMessageBox msgBox;
        //Change background color
        QPalette palette;
        palette.setColor(QPalette::Background, Qt::blue);
        msgBox.setPalette(palette);
        msgBox.setWindowTitle("Información");
        msgBox.setIcon(QMessageBox::Warning);
        //Change font
        QFont font( "Comic Sans MS" );
        font.setPointSize( 11 );
        font.setWeight( QFont::Bold);
        font.setItalic(true);
        msgBox.setFont(font);
        msgBox.setText("No se Permiten Negativos ni Valor 0");
        msgBox.exec();
        ui->txt_W2->clear();
    }
}

void MainWindow::on_txt_T_editingFinished()
{
    if(ui->txt_T->text().toDouble() <= 0 )
    {
        QMessageBox msgBox;
        //Change background color
        QPalette palette;
        palette.setColor(QPalette::Background, Qt::blue);
        msgBox.setPalette(palette);
        msgBox.setWindowTitle("Información");
        msgBox.setIcon(QMessageBox::Warning);
        //Change font
        QFont font( "Comic Sans MS" );
        font.setPointSize( 11 );
        font.setWeight( QFont::Bold);
        font.setItalic(true);
        msgBox.setFont(font);
        msgBox.setText("No se Permiten Negativos ni Valor 0");
        msgBox.exec();
        ui->txt_T->clear();
    }
}
