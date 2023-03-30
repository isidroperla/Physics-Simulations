#include "conversionmasa.h"
#include "ui_conversionmasa.h"
#include <mainwindow.h>
#include <conversion.h>
#include <QDesktopWidget>

float masas[] = {200,5000,6600,7200,12400};
int indice_masa=0;
int indice_cB_masas=0;
QString vals_conv_m[5];

ConversionMasa::ConversionMasa(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConversionMasa)
{
    ui->setupUi(this);

    this->move(QApplication::desktop()->availableGeometry().center() - this->rect().center()); //Establecer posición de la ventana en el centro.

    //Parte de la opcion masa
    ui->lb_bascula->setStyleSheet("border-image:url(:/new/prefix1/recursos/bascula_roja.png);");
    ui->lcdNumber->setPalette(Qt::green);
    ui->lcdNumber->setStyleSheet("border: 0px;");

    ui->btn_m_obj1->setStyleSheet("border-image:url(:/new/prefix1/recursos/manzana.png);");
    ui->btn_m_obj2->setStyleSheet("border-image:url(:/new/prefix1/recursos/sandia.png);");
    ui->btn_m_obj3->setStyleSheet("border-image:url(:/new/prefix1/recursos/pescado.png);");
    ui->btn_m_obj4->setStyleSheet("border-image:url(:/new/prefix1/recursos/bola.png);");
    ui->btn_m_obj5->setStyleSheet("border-image:url(:/new/prefix1/recursos/lingote.png);");

    ui->lb_unidades_masa->setText("<p align='right'>g</p>");
    on_cB_conversiones_masa_currentIndexChanged(0);
}

ConversionMasa::~ConversionMasa()
{
    delete ui;
}

void ConversionMasa::mostrarMasa(QString ruta_masa){
    QPixmap pixmap(ruta_masa);
    ui->lb_mostrar_masas->setPixmap(pixmap.scaled(ui->lb_mostrar_masas->width(),ui->lb_mostrar_masas->height(),Qt::KeepAspectRatio));
}

void ConversionMasa::actualizar(){
    if(ui->rB_g->isChecked()){
        ui->lcdNumber->display(masas[indice_masa]);
        ui->lb_unidades_masa->setText("<p align='right'>g</p>");
    }else if(ui->rB_kg->isChecked()){
        ui->lcdNumber->display(masas[indice_masa]/1000);
        ui->lb_unidades_masa->setText("<p align='right'>kg</p>");
    }else if(ui->rB_oz->isChecked()){
        ui->lcdNumber->display(masas[indice_masa]/28.35);
        ui->lb_unidades_masa->setText("<p align='right'>oz</p>");
    }
    on_cB_conversiones_masa_currentIndexChanged(indice_cB_masas);
}

void ConversionMasa::on_btn_m_obj1_clicked()
{
    mostrarMasa(":/new/prefix1/recursos/manzana.png");
    indice_masa=0;
    actualizar();
}

void ConversionMasa::on_btn_m_obj2_clicked()
{
    mostrarMasa(":/new/prefix1/recursos/sandia.png");
    indice_masa=1;
    actualizar();
}

void ConversionMasa::on_btn_m_obj3_clicked()
{
    mostrarMasa(":/new/prefix1/recursos/pescado.png");
    indice_masa=2;
    actualizar();
}

void ConversionMasa::on_btn_m_obj4_clicked()
{
    mostrarMasa(":/new/prefix1/recursos/bola.png");
    indice_masa=3;
    actualizar();
}

void ConversionMasa::on_btn_m_obj5_clicked()
{
    mostrarMasa(":/new/prefix1/recursos/lingote.png");
    indice_masa=4;
    actualizar();
}

void ConversionMasa::on_rB_g_clicked()
{
    actualizar();
}

void ConversionMasa::on_rB_kg_clicked()
{
    actualizar();
}

void ConversionMasa::on_rB_oz_clicked()
{
    actualizar();
}

void ConversionMasa::on_cB_conversiones_masa_currentIndexChanged(int index)
{
    indice_cB_masas=index;
    switch(index){
        case 0:
        vals_conv_m[0]= QString::number(masas[indice_masa]); vals_conv_m[1] = "1"; vals_conv_m[2] = "kg"; vals_conv_m[3] = "1000"; vals_conv_m[4] = "g";
        break;
        case 1:
        vals_conv_m[0]= QString::number(masas[indice_masa]); vals_conv_m[1] = "1"; vals_conv_m[2] = "oz"; vals_conv_m[3] = "28.35"; vals_conv_m[4] = "g";
        break;
        case 2:
        vals_conv_m[0]= QString::number(masas[indice_masa]/1000); vals_conv_m[1] = "1000"; vals_conv_m[2] = "g"; vals_conv_m[3] = "1"; vals_conv_m[4] = "kg";
        break;
        case 3:
        vals_conv_m[0]= QString::number(masas[indice_masa]/1000); vals_conv_m[1] = "35.274"; vals_conv_m[2] = "oz"; vals_conv_m[3] = "1"; vals_conv_m[4] = "kg";
        break;
        case 4:
        vals_conv_m[0]= QString::number(masas[indice_masa]/28.35); vals_conv_m[1] = "28.35"; vals_conv_m[2] = "g"; vals_conv_m[3] = "1"; vals_conv_m[4] = "oz";
        break;
        case 5:
        vals_conv_m[0]= QString::number(masas[indice_masa]/28.35); vals_conv_m[1] = "0.02835"; vals_conv_m[2] = "kg"; vals_conv_m[3] = "1"; vals_conv_m[4] = "oz";
        break;
    }

}

void ConversionMasa::on_btn_convertir_masa_clicked()
{
    Conversion *conv;
    conv = new Conversion(vals_conv_m[0], vals_conv_m[1], vals_conv_m[2], vals_conv_m[3], vals_conv_m[4]);
    conv->show();
}

void ConversionMasa::on_btn_volver_clicked()
{
    this->close(); //Se cierra esta ventana.
    MainWindow *MW;
    MW = new MainWindow();
    MW->show();
}
