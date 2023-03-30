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
#include <QStyle>
#include <QDesktopWidget>
#include <QDoubleValidator>

using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

  //  ui->setupUi(this);
        this->move(QApplication::desktop()->availableGeometry().center() - this->rect().center());

   ui->txt_m->setValidator(new QDoubleValidator(-39.5, 99.0, 5, ui->txt_m));

   ui->txt_q->setValidator(new QDoubleValidator(-39.5, 99.0, 5, ui->txt_q));
   ui->txt_Q->setValidator(new QDoubleValidator(-39.5, 99.0, 5, ui->txt_Q));
   ui->txt_vox->setValidator(new QDoubleValidator(-39.5, 99.0, 5, ui->txt_vox));
   ui->txt_voy->setValidator(new QDoubleValidator(-39.5, 99.0, 5, ui->txt_voy));
   ui->txt_xo->setValidator(new QDoubleValidator(-39.5, 99.0, 5, ui->txt_xo));
   ui->txt_yo->setValidator(new QDoubleValidator(-39.5, 99.0, 5, ui->txt_yo));
   ui->txt_intervalo_tiempo->setValidator(new QDoubleValidator(-39.5, 99.0, 5, ui->txt_intervalo_tiempo));

    for(int i=1; i<=50; i++){
        ui->cb_m->addItem(QString::number(-i));
    }
    for(int i=1; i<=50; i++){
        ui->cb_q->addItem(QString::number(-i));
    }
    for(int i=1; i<=50; i++){
        ui->cb_Q->addItem(QString::number(-i));
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

//Este es el botón para mandar datos y abrir el ejecutable de OpenGl

void MainWindow::on_pushButton_clicked()
{ QMessageBox msgBox;
    if(        ui->txt_m->text().isEmpty()
            || ui->txt_Q->text().isEmpty()
            || ui->txt_q->text().isEmpty()
            || ui->txt_xo->text().isEmpty()
            || ui->txt_yo->text().isEmpty()
            || ui->txt_vox->text().isEmpty()
            || ui->txt_voy->text().isEmpty()
        )
    {
        msgBox.setText("Rellene todos los campos");
        msgBox.exec();
    }else{
    double m; //Variable masa
    double q; //Carga que se mueve
    double Q; //Carga fija
    double xo; //Posición inicial de la carga en movimiento en x
    double yo; //Posición inicial de la carga en movimiento en y
    double vox; //Velocidad inicial de la carga en movimiento en x
    double voy; //Velocidad inicial de la carga en movimiento en y
    double intervalo_tiempo; //Intervalo de tasa de actualización del programa
    int exponente_m; //Exponenente de la masa
    int exponente_q; //Exponenete de la carga q
    int exponente_Q; //Exponente de la carga Q

    string argumento = "";
    stringstream concatenador;

    //Guardamos en las variables los valores escritos en los  QTextEdit y se convertidos a datos del tipo double.

    m = ui->txt_m->text().toDouble();
    q = ui->txt_q->text().toDouble();
    Q = ui->txt_Q->text().toDouble();

    xo = ui->txt_xo->text().toDouble();
    yo = ui->txt_yo->text().toDouble();
    vox = ui->txt_vox->text().toDouble();
    voy = ui->txt_voy->text().toDouble();
    intervalo_tiempo = ui->txt_intervalo_tiempo->text().toDouble();

    exponente_m = ui->cb_m->currentText().toInt();
    exponente_q = ui->cb_q->currentText().toInt();
    exponente_Q = ui->cb_Q->currentText().toInt();

    //Concatenamos el nombre del ejectuble de OpenGL y los datos de forma ordenada en una variable llamada concatenador.

    concatenador << "Animacion.exe " << m << " "<< q << " "<< Q << " "<< xo << " "<< yo << " "<< vox << " "<< voy << " "<< exponente_m << " "<< exponente_q << " "<< exponente_Q << " "<< intervalo_tiempo;
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

    ui->txt_m->clear(); ui->txt_m->setText("2");
    ui->txt_q->clear(); ui->txt_q->setText("2");
    ui->txt_Q->clear(); ui->txt_Q->setText("-2");
    ui->txt_xo->clear(); ui->txt_xo->setText("-2");
    ui->txt_yo->clear(); ui->txt_yo->setText("-2");
    ui->txt_vox->clear(); ui->txt_vox->setText("20");
    ui->txt_voy->clear(); ui->txt_voy->setText("0");
    ui->cb_m->clear(); ui->cb_m->addItem("-31");
    ui->cb_q->clear(); ui->cb_q->addItem("-19");
    ui->cb_Q->clear(); ui->cb_Q->addItem("-19");
    ui->txt_intervalo_tiempo->clear(); ui->txt_intervalo_tiempo->setText("50");

    //Concatenamos el nombre del ejectuble de OpenGL y los datos de forma ordenada en una variable llamada concatenador.

    concatenador << "Animacion.exe " << 2 << " "<< 2 << " "<< -2 << " "<< -2 << " "<< -2 << " "<< 20 << " "<< 0 << " "<< -31 << " "<< -19 << " "<< -19 << " "<< 50;
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
    font.setPointSize( 20 );
    font.setWeight( QFont::Bold);
    font.setItalic(true);
    msgBox.setFont(font);
    msgBox.setText("FORMULAS CAMPOS ELÉCTRICOS\n\n"
                   "    F = qE\n\n"
                   "=> ma = qE => ma = keqQ/r2\n\n"
                   "    a = keqQ/mr2");
    msgBox.exec();

}

void MainWindow::on_txt_m_editingFinished()
{
    if(ui->txt_m->text().toDouble() <= 0 )
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
        msgBox.setText("No se Permiten Negativos o 0");
        msgBox.exec();

        ui->txt_m->clear();
    }
}

void MainWindow::on_txt_xo_editingFinished()
{
    if(ui->txt_xo->text().toDouble() == 0 || ui->txt_xo->text().toDouble() > 10 || ui->txt_xo->text().toDouble() < -10 )
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
        msgBox.setText("Rango Permitido -10,-1 y 1,10");
        msgBox.exec();

        ui->txt_xo->clear();
    }
}

void MainWindow::on_txt_yo_editingFinished()
{
    if(ui->txt_yo->text().toDouble() == 0 || ui->txt_yo->text().toDouble() > 10 || ui->txt_yo->text().toDouble() < -10 )
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
        msgBox.setText("Rango Permitido -10,-1 y 1,10");
        msgBox.exec();

        ui->txt_yo->clear();
    }

}

void MainWindow::on_txt_intervalo_tiempo_editingFinished()
{
    if(ui->txt_intervalo_tiempo->text().toDouble() <= 0 )
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
        msgBox.setText("No se Permiten Negativos o 0");
        msgBox.exec();

        ui->txt_intervalo_tiempo->clear();
    }
}
