 #include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>

MyOpenGLWidget *mOW;

float diametro1=0; //Diametro obtenido del primer spinbox.
float diametro2=0; //Diametro obtenido del segundo spinbox.

//float diametro1=0, diametro2=0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->move(QApplication::desktop()->availableGeometry().center() - this->rect().center()); //Establecer posición de la ventana en el centro.

    ui->sB_diametro1->setRange(0.25f, 3.00f); //Se fime eñ rango de valores para el spinBox del diametro1.
    ui->sB_diametro1->setSingleStep(0.25f); //Se hacen aumentos de 0.25.

    ui->sB_diametro2->setRange(0.25f, 3.00f); //Se fime eñ rango de valores para el spinBox del diametro2.
    ui->sB_diametro2->setSingleStep(0.25f); //Se hacen aumentos de 0.25.
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sB_diametro1_valueChanged(const QString &arg1) //Función que detecta si se ha cambiado el valor del spinBox del diametro1.
{
    diametro1= ui->sB_diametro1->text().toFloat(); //Se ontiene el valor del diametro desde el spinbox, se convierte a float y se guarda en la variable diametro1.
    mOW = new MyOpenGLWidget(diametro1, diametro2); //Se pasa el valor de los diametros al constructor para usarlo en otra clase.
}

void MainWindow::on_sB_diametro2_valueChanged(const QString &arg1) //Función que detecta si se ha cambiado el valor del spinBox del diametro1.
{
    diametro2= ui->sB_diametro2->text().toFloat(); //Se ontiene el valor del diametro desde el spinbox, se convierte a float y se guarda en la variable diametro1.
    mOW = new MyOpenGLWidget(diametro1, diametro2); //Se pasa el valor de los diametros al constructor para usarlo en otra clase.
}
