#include "precisionexactitud.h"
#include "ui_precisionexactitud.h"
#include <mainwindow.h>
#include <QDesktopWidget>
#include <QMessageBox>
#include <random>
#include "QDateTime"
#include <time.h>
#include <math.h>
#include <QPainter>

double o_A;
double o_B;
float m=5;

int random(int min, int max){
    unsigned int ms = static_cast<unsigned>(QDateTime::currentMSecsSinceEpoch());
    std::mt19937 gen(ms);
    std::uniform_int_distribution<> uid(min, max);
    return -min + ( std::rand() % ( max - -(min) + 1 ) );
}

int contarDecimales(double num)
{
    int digits=0;
    double ori=num;//storing original number
    long num2=num;
    while(num2>0)//count no of digits before floating point
    {
        digits++;
        num2=num2/10;
    }
    if(ori==0)
        digits=1;
    num=ori;
    double no_float;
    no_float=ori*(pow(10, (16-digits)));
    long long int total=(long long int)no_float;
    int no_of_digits, extrazeroes=0;
    for(int i=0; i<16; i++)
    {
        int dig;
        dig=total%10;
        total=total/10;
        if(dig!=0)
            break;
        else
            extrazeroes++;
    }
    no_of_digits=16-extrazeroes;
    return no_of_digits;
}

PrecisionExactitud::PrecisionExactitud(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrecisionExactitud)
{
    ui->setupUi(this);

    srand (time(NULL));

    this->move(QApplication::desktop()->availableGeometry().center() - this->rect().center()); //Establecer posición de la ventana en el centro.

    ui->lb_bascula_roja->setStyleSheet("border-image:url(:/new/prefix1/recursos/bascula_roja.png);");
    ui->lb_bascula_azul->setStyleSheet("border-image:url(:/new/prefix1/recursos/bascula_azul.png);");
    ui->lb_notas->setStyleSheet("border-image:url(:/new/prefix1/recursos/notas.png);");

    QPixmap pixmap(":/new/prefix1/recursos/masa_5kg.png");
    ui->lb_masa->setPixmap(pixmap.scaled(ui->lb_masa->width(),ui->lb_masa->height(),Qt::KeepAspectRatioByExpanding));

    REPETIR2:
    REPETIR1:

    m=5;

    double r1 = -3 + ( std::rand() % ( 3 - (-3) + 1 ) );
    o_A = m + (r1/10);
    double r2 = -3 + ( std::rand() % ( 3 - (-3) + 1 ) );
    o_B = m + (r2/10);
    int marcar_indice=0;


    double val_random=0;
    switch((int)(1 + ( std::rand() % ( 4 - (1) + 1 )))){
        case 1:
            marcar_indice=1;
        break;
        case 2:
            do{
                val_random= -99 + ( std::rand() % ( 49 - (-49) + 1 ) );
            }while(val_random==0);
            o_A+=val_random/100;
            marcar_indice=2;
        break;
        case 3:
            do{
                val_random = -999 + ( std::rand() % ( 499 - (-499) + 1 ) );
            }while(val_random==0);
            o_A+=val_random/1000;
            marcar_indice=3;
        break;
        case 4:
            do{
                val_random = -9999 + ( std::rand() % ( 4999 - (-4999) + 1 ) );
            }while(val_random==0);
            o_A+=val_random/10000;
            marcar_indice=4;
        break;
    }

    double val_random2=0;
    int opc;

    do{
        opc= (int)(1 + ( std::rand() % ( 4 - (1) + 1 )));
    }while(opc==marcar_indice);

    switch(opc){
        case 1:
        break;
        case 2:
            do{
                val_random2= -99 + ( std::rand() % ( 49 - (-49) + 1 ) );
            }while(val_random2==0);
            o_B+=val_random2/100;
        break;
        case 3:
            do{
                val_random2 = -999 + ( std::rand() % ( 499 - (-499) + 1 ) );
            }while(val_random2==0);
            o_B+=val_random2/1000;
        break;
        case 4:
            do{
                val_random2 = -9999 + ( std::rand() % ( 4999 - (-4999) + 1 ) );
            }while(val_random2==0);
            o_B+=val_random2/10000;
        break;
    }

    if(abs(o_A-m)==abs(o_B-m)){
        goto REPETIR1;
    }
    if(contarDecimales(o_A)==contarDecimales(o_B)){
        goto REPETIR2;
    }

    ui->lcd_bascula_roja->setDigitCount(6);
    ui->lcd_bascula_azul->setDigitCount(6);
    ui->lcd_bascula_roja->setPalette(Qt::green);
    ui->lcd_bascula_roja->setStyleSheet("border: 0px;");
    ui->lcd_bascula_azul->setPalette(Qt::green);
    ui->lcd_bascula_azul->setStyleSheet("border: 0px;");
}

PrecisionExactitud::~PrecisionExactitud()
{
    delete ui;
}

void PrecisionExactitud::mouseMoveEvent(QMouseEvent *event){
    if((event->x()>=55 && event->x()<=906) && (event->y()>=51 && event->y()<=455)){
        ui->lb_masa->move(event->x()-60,event->y()-60);
    }
}

void valorA(){

}

void PrecisionExactitud::mouseReleaseEvent(QMouseEvent *event){

    if((event->x()>=70 && event->x()<=387) && (event->y()>=68 && event->y()<=140)){
        ui->lb_masa->move(170,58);
        ui->lcd_bascula_azul->display(0);
        ui->lcd_bascula_roja->display(o_A);
        ui->lb_medida_A->setText(QString::number(o_A) + " kg");
    }else if(event->x()>=560 && event->x()<=880 && (event->y()>=68 && event->y()<=140)){
        ui->lb_masa->move(660,58);
        ui->lcd_bascula_roja->display(0);
        ui->lcd_bascula_azul->display(o_B);
        ui->lb_medida_B->setText(QString::number(o_B) + " kg");
    }else{
        ui->lb_masa->move(250,350);
        ui->lcd_bascula_roja->display(0);
        ui->lcd_bascula_azul->display(0);
    }

}

void PrecisionExactitud::on_btn_verificar_exactitud_clicked()
{
    char res;
    char res_user;
    if(abs(o_A-m)<abs(o_B-m)){
        res = 'A';
    }else if(abs(o_A-m)>abs(o_B-m)){
        res = 'B';
    }

    if(ui->rB_exactitud_A->isChecked()==false && ui->rB_exactitud_B->isChecked()==false){
        QMessageBox::information(this, tr("Nota"), tr("Marque una opción."));
    }else{
        if(ui->rB_exactitud_A->isChecked()){
            res_user = 'A';
        }else if(ui->rB_exactitud_B->isChecked()){
            res_user = 'B';
        }

        if(res==res_user){
            QMessageBox::information(this, tr("Respuesta"), tr("Correcto, la respuesta es ") + res_user);
        }else{
            QMessageBox::information(this, tr("Respuesta"), tr("Incorrecto, la respuesta no es ") + res_user);
        }
    }
}

void PrecisionExactitud::on_btn_verificar_precision_clicked()
{
    char res;
    char res_user;
    if(contarDecimales(o_A)>contarDecimales(o_B)){
        res = 'A';
    }else if(contarDecimales(o_A)<contarDecimales(o_B)){
        res = 'B';
    }

    if(ui->rB_Precision_A->isChecked()==false && ui->rB_Precision_B->isChecked()==false){
        QMessageBox::information(this, tr("Nota"), tr("Marque una opción."));
    }else{
        if(ui->rB_Precision_A->isChecked()){
            res_user = 'A';
        }else if(ui->rB_Precision_B->isChecked()){
            res_user = 'B';
        }else{
            QMessageBox::information(this, tr("Nota"), tr("Marque una opción."));
        }

        if(res==res_user){
            QMessageBox::information(this, tr("Respuesta"), tr("Correcto, la respuesta es " ) + res_user);
        }else{
            QMessageBox::information(this, tr("Respuesta"), tr("Incorrecto, la respuesta no es ") + res_user);
        }
    }
}

void PrecisionExactitud::on_btn_volver_clicked()
{
    this->close(); //Se cierra esta ventana.
    MainWindow *MW;
    MW = new MainWindow();
    MW->show();
}
