#include "conversionvelocidad.h"
#include "ui_conversionvelocidad.h"
#include <mainwindow.h>
#include <conversion.h>
#include <QDesktopWidget>
#include <QMovie>

QMovie *movie;
float velocidad=20;
QString vals_conv_v[5];
int indice_actual=0;

void ConversionVelocidad::velocimetro(){

    mSpeedGauge = new QcGaugeWidget;
    mSpeedGauge->addBackground(79);
    QcBackgroundItem *bkg1 = mSpeedGauge->addBackground(72);
    bkg1->clearrColors();
    bkg1->addColor(0.1,Qt::black);
    bkg1->addColor(1.0,Qt::white);

    QcBackgroundItem *bkg2 = mSpeedGauge->addBackground(68);
    bkg2->clearrColors();
    bkg2->addColor(0.1,Qt::gray);
    bkg2->addColor(1.0,Qt::darkGray);

    mSpeedGauge->addArc(35);
    //mSpeedGauge->addDegrees(45)->setValueRange(0,200);
    mSpeedGauge->addColorBand(30);

    //mSpeedGauge->addValues(60)->setValueRange(0,200);

    QcLabelItem *lab = mSpeedGauge->addLabel(20);
    //mSpeedGauge->addLabel(50)->setText("Km/h");
    lab->setText("0");
    mSpeedNeedle = mSpeedGauge->addNeedle(50);
    mSpeedNeedle->setLabel(lab);
    mSpeedNeedle->setColor(Qt::white);
    mSpeedGauge->addBackground(7);
    mSpeedGauge->addGlass(68);
    ui->vL_velocimetro->addWidget(mSpeedGauge);

    mSpeedGauge->addLabel(50)->setText("Km/h");
    mSpeedGauge->addDegrees(45)->setValueRange(0,200);
    mSpeedGauge->addValues(60)->setValueRange(0,200);
    mSpeedNeedle->setValueRange(0,200);
    mSpeedNeedle->setCurrentValue(20);
}

ConversionVelocidad::ConversionVelocidad(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConversionVelocidad)
{
    ui->setupUi(this);

    this->move(QApplication::desktop()->availableGeometry().center() - this->rect().center()); //Establecer posición de la ventana en el centro.

    movie = new QMovie(":/new/prefix1/recursos/carro.gif");
    movie->setSpeed(40);
    ui->lb_animacion_velocidad->setMovie(movie);
    movie->start();

    ui->vS_control_velocidad->setRange(20,200);
    ui->vS_control_velocidad->setTickInterval(1);

    velocimetro();

    on_cB_conversiones_velocidad_currentIndexChanged(0);
}

ConversionVelocidad::~ConversionVelocidad()
{
    delete ui;
}

void ConversionVelocidad::on_cB_conversiones_velocidad_currentIndexChanged(int index)
{
    indice_actual=index;
    switch(index){
        case 0:
            vals_conv_v[0]= QString::number(velocidad); vals_conv_v[1] = "1"; vals_conv_v[2] = "m/s"; vals_conv_v[3] = "3.6"; vals_conv_v[4] = "km/h";
        break;
        case 1:
            vals_conv_v[0]= QString::number(velocidad); vals_conv_v[1] = "1"; vals_conv_v[2] = "mi/h"; vals_conv_v[3] = "1.609"; vals_conv_v[4] = "km/h";
        break;
        case 2:
            vals_conv_v[0]= QString::number(velocidad/3.6); vals_conv_v[1] = "3.6"; vals_conv_v[2] = "km/h"; vals_conv_v[3] = "1"; vals_conv_v[4] = "m/s";
        break;
        case 3:
            vals_conv_v[0]= QString::number(velocidad/1.609f); vals_conv_v[1] = "2.237"; vals_conv_v[2] = "mi/h"; vals_conv_v[3] = "1"; vals_conv_v[4] = "m/s";
        break;
        case 4:
            vals_conv_v[0]= QString::number(velocidad/1.609f); vals_conv_v[1] = "1.609"; vals_conv_v[2] = "km/h"; vals_conv_v[3] = "1"; vals_conv_v[4] = "mi/h";
        break;
        case 5:
            vals_conv_v[0]= QString::number(velocidad/1.609f); vals_conv_v[1] = "1"; vals_conv_v[2] = "km/h"; vals_conv_v[3] = "2.237"; vals_conv_v[4] = "mi/h";
        break;
    }
}

void ConversionVelocidad::on_vS_control_velocidad_sliderMoved(int position)
{
    velocidad=position;
    movie->setSpeed(position*2);
    on_cB_conversiones_velocidad_currentIndexChanged(indice_actual);
    if(ui->rB_v_km->isChecked()){
        mSpeedNeedle->setCurrentValue(position);
    }else if(ui->rB_v_m->isChecked()){
        mSpeedNeedle->setCurrentValue((position/3.6));
    }else if(ui->rB_v_millas->isChecked()){
        mSpeedNeedle->setCurrentValue((position/1.609f));
    }
}

void ConversionVelocidad::on_rB_v_km_clicked()
{
    mSpeedGauge->removeDegrees(45);
    mSpeedGauge->removeValues(60);
    mSpeedGauge->removeLabel(1);
    mSpeedGauge->addLabel(50)->setText("Km/h");
    mSpeedGauge->addDegrees(45)->setValueRange(0,200);
    mSpeedGauge->addValues(60)->setValueRange(0,200);
    mSpeedNeedle->setValueRange(0,200);
    on_cB_conversiones_velocidad_currentIndexChanged(indice_actual);
    on_vS_control_velocidad_sliderMoved(velocidad);
}

void ConversionVelocidad::on_rB_v_m_clicked()
{
    mSpeedGauge->removeDegrees(45);
    mSpeedGauge->removeValues(60);
    mSpeedGauge->removeLabel(1);
    mSpeedGauge->addLabel(50)->setText("m/s");
    mSpeedGauge->addDegrees(45)->setValueRange(0,60);
    mSpeedGauge->addValues(60)->setValueRange(0,60);
    mSpeedNeedle->setValueRange(0,60);
    on_cB_conversiones_velocidad_currentIndexChanged(indice_actual);
    on_vS_control_velocidad_sliderMoved(velocidad);
}

void ConversionVelocidad::on_rB_v_millas_clicked()
{
    mSpeedGauge->removeDegrees(45);
    mSpeedGauge->removeValues(60);
    mSpeedGauge->removeLabel(1);
    mSpeedGauge->addLabel(50)->setText("mi/h");
    mSpeedGauge->addDegrees(45)->setValueRange(0,120);
    mSpeedGauge->addValues(60)->setValueRange(0,120);
    mSpeedNeedle->setValueRange(0,120);
    on_cB_conversiones_velocidad_currentIndexChanged(indice_actual);
    on_vS_control_velocidad_sliderMoved(velocidad);
}

void ConversionVelocidad::on_btn_convertir_velocidad_clicked()
{
    Conversion *conv;
    conv = new Conversion(vals_conv_v[0], vals_conv_v[1], vals_conv_v[2], vals_conv_v[3], vals_conv_v[4]);
    conv->show();
}

void ConversionVelocidad::on_btn_volver_clicked()
{
    this->close(); //Se cierra esta ventana.
    MainWindow *MW;
    MW = new MainWindow();
    MW->show();
}
