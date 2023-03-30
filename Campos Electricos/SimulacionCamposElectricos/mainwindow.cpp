//Autor: José Isidro Perla Rosa

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QString>
#include <sstream>
#include <string.h>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QProxyStyle>
#include <math.h>

using namespace std;

double obj=1; //Objeto a seleccionar.
float valor=0; //Valor de la variable a pedir.
int exponente=0; //Exponente del valor.
float radioEsfera=0; //Radio del objeto principal.
bool activarLineas = false; //Variable para activar la opción de lineas de campo.

class MyStyle : public QProxyStyle //Clase para establecer el estilo de salto directo del horizontalSlider.
{
public:
    using QProxyStyle::QProxyStyle;

    int styleHint(QStyle::StyleHint hint, const QStyleOption* option = 0, const QWidget* widget = 0, QStyleHintReturn* returnData = 0) const
    {
        if (hint == QStyle::SH_Slider_AbsoluteSetButtons)
            return (Qt::LeftButton | Qt::MidButton | Qt::RightButton);
        return QProxyStyle::styleHint(hint, option, widget, returnData);
    }
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //this->setWindowState(Qt::WindowMaximized); //Establecer tamaño de la ventana de forma maximizada.
    this->move(QApplication::desktop()->availableGeometry().center() - this->rect().center()); //Establecer posición de la ventana en el centro.

    ui->cb_objetos->addItem("Esfera aislante"); //Se añaden los intems al comboBox.
    ui->cb_objetos->addItem("Esfera conductora");
    ui->cb_objetos->addItem("Esfera aislante hueca");
    ui->cb_objetos->addItem("Varilla");
    ui->cb_objetos->addItem("Plano cargado");

    ui->sliderRadio->setStyle(new MyStyle(ui->sliderRadio->style())); //Se aplica el estilo al horizontalSlider para que pueda hacer los saltos directos.

    ui->sliderRadio->setMinimum(1);
    ui->sliderRadio->setMaximum(10);
    ui->sliderRadio->setTickInterval(1);

    ui->sB_valor->setRange(-15,0); //Rango del spinBox
    ui->sB_valor->setSingleStep(3); //Se define el salto del spinBox
    ui->sB_valor->findChild<QLineEdit*>()->setReadOnly(true); //SpinBox validación para no escribir manualmente los valores.

    ui->txt_valorQ->setValidator(new QDoubleValidator(-39.5, 99.0, 5, ui->txt_valorQ)); //Validación para que el usuario solo pueda ingresar números en el lineEdit.

    QPalette* color = new QPalette();
    color->setColor(QPalette::Foreground,Qt::white);
    ui->cB_lineas->setPalette(*color); //Se añade por defecto el color blanco al texto del checkBox
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


void MainWindow::on_sliderRadio_valueChanged(int value) //Metodo a implementar si el horizontalSlider ha cambiado de valor.
{
    radioEsfera = ui->sliderRadio->value()/10.0f;
    ui->lb_valorRadio->setText(QString::number(radioEsfera) + " m");
}

void MainWindow::on_cb_objetos_currentTextChanged(const QString &arg1) //Metodo a implementar si el horizontalSlider ha cambiado de texto índice.
{
    ui->label_dato->setAlignment(Qt::AlignRight);
    ui->lb_radioA->setAlignment(Qt::AlignRight);
    ui->label_dato->setText("Q");
    ui->label_unidadesDato->setText("C");
    ui->sliderRadio->setEnabled(true);
    ui->sliderRadio->show();
    ui->lb_radioA->show();
    ui->lb_valorRadio->show();

    if(ui->cb_objetos->currentText() == "Esfera aislante"){
        ui->lb_radioA->setText("Esfera aislante");
    }
    else if(ui->cb_objetos->currentText() == "Esfera conductora"){
        ui->lb_radioA->setText("Esfera conductora");
    }
    else if(ui->cb_objetos->currentText() == "Esfera aislante hueca"){
        ui->lb_radioA->setText("Esfera aislante hueca");
    }
    else if(ui->cb_objetos->currentText() == "Varilla"){
        ui->label_unidadesDato->setText("C/m");
        ui->label_dato->setText("λ");
        ui->lb_radioA->setText("Varilla");
        ui->sliderRadio->setEnabled(false);
        ui->sliderRadio->setValue(2);
    }
    else if(ui->cb_objetos->currentText() == "Plano cargado"){
        ui->label_unidadesDato->setText("C/m<sup>2</sup>");
        ui->label_dato->setText("σ");
        ui->lb_radioA->setText("Plano cargado");
        ui->sliderRadio->setEnabled(false);
        ui->sliderRadio->setValue(2);
        ui->sliderRadio->hide();
        ui->lb_radioA->hide();
        ui->lb_valorRadio->hide();
    }
}

void MainWindow::on_pushButton_clicked() //Metodo del botón.
{
    string argumento = "";
    stringstream concatenador;

    valor = ui->txt_valorQ->text().toDouble();
    exponente = ui->sB_valor->value();

    valor*=pow(10,exponente);

    if(ui->cb_objetos->currentText() == "Esfera aislante"){
        obj = 1;
    }
    else if(ui->cb_objetos->currentText() == "Esfera conductora"){
        obj = 2;
    }
    else if(ui->cb_objetos->currentText() == "Esfera aislante hueca"){
        obj = 3;
    }
    else if(ui->cb_objetos->currentText() == "Varilla"){
        obj = 4;
    }
    else if(ui->cb_objetos->currentText() == "Plano cargado"){
        obj = 5;
    }

    if(ui->cB_lineas->isChecked()){ //Condición para activar las lineas segun el resultado boleano.
        activarLineas = true;
    }else{
        activarLineas = false;
    }


    if(ui->txt_valorQ->text().isEmpty()){
        QMessageBox::information(this, tr("¡ALERTA!"), tr("Llene todos los campos."));
    }else{
        //Concatenamos el nombre del ejectuble de OpenGL y los datos de forma ordenada en una variable llamada concatenador.

        concatenador << "Animacion.exe " << obj << " " << valor << " "<<radioEsfera  << " " <<activarLineas;
        argumento = concatenador.str();

        //Creamos un puntero llamado c que contendra la dirreción de concatenador.

        const char *c = argumento.c_str();

        //Se imprimen los datos en el Application Output para verificar que todo este en orden.

        cout << c <<endl;

        //Mandamos los datos de concatenador y esto abrira el ejecutable de OpenGl.

        system(c);
    }
}
