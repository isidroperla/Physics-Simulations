#include "conversion.h"
#include "ui_conversion.h"
#include <QDesktopWidget>
#include <QPainter>

QString valor_conv, valor_numerador, unidades_numerador, valor_denominador, unidades_denominador, resultado;

QLabel *pasos;

void mostrar(int index){
    QPixmap pixmap(450,71);
    pixmap.fill(QColor("transparent"));
    QPainter painter(&pixmap);
    QFont font = painter.font() ;
    /* twice the size than the current font size */
    font.setPointSize(font.pointSize() * 2);
    /* set the modified font to the painter */
    painter.setFont(font);
    painter.setPen(QPen(Qt::black, 2));

    int alto = painter.fontMetrics().height();
    int ancho1 = painter.fontMetrics().width(valor_conv + " " + unidades_denominador + " X ");
    int ancho2, ancho_numerador, ancho_denominador;
    if(valor_numerador=="1"){
        ancho2 = painter.fontMetrics().width(valor_denominador + " " + unidades_denominador);
        ancho_denominador=ancho2;
        ancho_numerador=0;
    }else if(valor_denominador=="1"){
        ancho2 = painter.fontMetrics().width(valor_numerador + " " + unidades_numerador);
        ancho_numerador=ancho2;
        ancho_denominador=0;
    }
    int anchow = painter.fontMetrics().width(valor_conv + " ");
    int anchow2 = painter.fontMetrics().width(unidades_denominador);
    int anchow3 = painter.fontMetrics().width(valor_denominador + " ");

    switch(index){

        case 6:
        painter.drawText((ancho1+ancho2),1.5*alto," = " + resultado + " " + unidades_numerador);
        pasos->setPixmap(pixmap);
        case 5:
        painter.drawLine(anchow, alto*1.5, (anchow+anchow2), alto);
        painter.drawLine(ancho1+anchow3, 2*alto, (ancho1+anchow3+anchow2), 1.5*alto);
        pasos->setPixmap(pixmap);
        case 4:
        painter.drawText(ancho1,alto,valor_numerador + " " + unidades_numerador);
        pasos->setPixmap(pixmap);
        case 3:
        painter.drawText(ancho1,2*alto, valor_denominador + " " + unidades_denominador);
        pasos->setPixmap(pixmap);
        case 2:
        painter.drawLine(ancho1, alto*1.15f, (ancho1+ancho2), alto*1.15f);
        pasos->setPixmap(pixmap);
        case 1:
        painter.drawText(1,1.5*alto,(valor_conv + " " + unidades_denominador + " X "));
        pasos->setPixmap(pixmap);
        case 0:
        painter.drawText(1,1.5*alto,(valor_conv + " " + unidades_denominador));
        pasos->setPixmap(pixmap);
        break;

    }
}

Conversion::Conversion(QString val_conv, QString val_numerador, QString unid_numerador, QString val_denominador, QString unid_denominador, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Conversion)
{
    ui->setupUi(this);

    this->move(QApplication::desktop()->availableGeometry().center() - this->rect().center()); //Establecer posición de la ventana en el centro.

    valor_conv = val_conv;
    valor_numerador = val_numerador;
    unidades_numerador = unid_numerador;
    valor_denominador = val_denominador;
    unidades_denominador = unid_denominador;

    resultado = QString::number(valor_conv.toFloat()*(valor_numerador.toFloat()/valor_denominador.toFloat()));

    pasos = new QLabel(this);
    pasos->setGeometry(20,140,450,71);

    mostrar(0);
}

Conversion::~Conversion()
{
    delete ui;
}

void Conversion::on_tabWidget_currentChanged(int index)
{
    mostrar(index);
}
