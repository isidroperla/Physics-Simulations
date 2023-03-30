#include "notacioncientifica.h"
#include "ui_notacioncientifica.h"
#include <mainwindow.h>
#include <QDesktopWidget>
#include <math.h>
#include <random>
#include "QDateTime"
#include <QMessageBox>

double num=0;
QString valor;
int num_digitos=0;
QString res_revisar;

int getRand(int min, int max){
    unsigned int ms = static_cast<unsigned>(QDateTime::currentMSecsSinceEpoch());
    std::mt19937 gen(ms);
    std::uniform_int_distribution<> uid(min, max);
    return uid(gen);
}

NotacionCientifica::NotacionCientifica(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NotacionCientifica)
{
    ui->setupUi(this);

    this->move(QApplication::desktop()->availableGeometry().center() - this->rect().center()); //Establecer posición de la ventana en el centro.

    ui->sB_exponente->setRange(-9,9);
    ui->lE_base->setValidator(new QDoubleValidator(-39.5, 99.0, 6, ui->lE_base));
    ui->lE_base->setAlignment(Qt::AlignRight);

    on_btn_random_clicked();
}

NotacionCientifica::~NotacionCientifica()
{
    delete ui;
}

void numerosAleatorios(){
    switch(getRand(1,4)){
        case 1:
            num = getRand(1,999);
            valor = QString::number(num/1000, 'f', 3);
            num_digitos=3;
        break;
        case 2:
            num = getRand(1,99);
            valor = QString::number(num/100, 'f', 2);
            num_digitos=2;
        break;
        case 3:
            num = getRand(10,999);
            valor = QString::number(num);
            num_digitos=0;
        break;
        case 4:
            num = getRand(10000,999999);
            valor = QString::number(num);
            num_digitos=0;
        break;
    }
}

QString resNotacion(){
    double m=0;
    double n=0;
    int a=0;

    n=valor.toDouble();

    m=n;
    m = truncf(m);

    if(m==0){

        while(m==0){
            m=n;
            m=trunc(m);

            if(m==0){
                n*=10;
                a++;
            }
    }

    return QString::number(n) + "x10" + "<sup>-" + QString::number(a) + "</sup>";

    }else{

        while(m!=0){
            m=n;
            m=trunc(m);

            if(m!=0){
                n/=10;
                a++;
            }
        }
    }

    return QString::number(n*10) + "X10<sup>"+QString::number(a-1) + "</sup>";
}

void NotacionCientifica::on_btn_random_clicked()
{
    ui->lb_mostrar_numero->clear();

    numerosAleatorios();

    //ui->lb_vx->setText("<center>v<sub>x</sub>: " + QString::number(vx, 'f', 2) + " m/s</center>");

    ui->lb_mostrar_numero->setText("<center>" + valor + "</center>");
}

void NotacionCientifica::on_btn_calcular_clicked()
{
    float base=0;
    int exponente=0;

    base = ui->lE_base->text().toFloat();
    exponente = ui->sB_exponente->value();

    if(valor==QString::number(base*pow(10,exponente), 'f', num_digitos)){
        QMessageBox::information(this, tr("Respuesta"), tr("Respuesta correcta."));
    }else{
        QMessageBox::information(this, tr("Respuesta"), tr("Respuesta incorrecta."));
    }
}

void NotacionCientifica::on_btn_revisar_clicked()
{
    QMessageBox::information(this, tr("Respuesta"), tr("La respuesta es: ") + resNotacion());
}

void NotacionCientifica::on_btn_volver_clicked()
{
    this->close(); //Se cierra esta ventana.
    MainWindow *MW;
    MW = new MainWindow();
    MW->show();
}
