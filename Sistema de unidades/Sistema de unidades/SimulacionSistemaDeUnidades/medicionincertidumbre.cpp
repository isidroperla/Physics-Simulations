#include "medicionincertidumbre.h"
#include "ui_medicionincertidumbre.h"
#include <mainwindow.h>
#include <QDesktopWidget>
#include <QPainter>
#include <QInputDialog>
#include <QMessageBox>

double respuestas[] = {2.65, 4.85, 7.38};
float posX = 862;
float wVentana=962;
int indice_res=0;
int rango_drop[3];

double truncar(double valueToTrunc){
    return (double)((int)(valueToTrunc*10))/(double)10;
}

void MedicionIncertidumbre::dibujarRegla(int x, int y, int w, int h, int opc){

    QPixmap pixmap(w,h);
    pixmap.fill(QColor("transparent"));

    QPainter painter(&pixmap);

    QFont font = painter.font() ;
    /* twice the size than the current font size */
    font.setPointSize(font.pointSize() * 1);
    /* set the modified font to the painter */
    painter.setFont(font);

    switch(opc){
        case 1:
            painter.setPen(QPen(Qt::black, 0.5));
            painter.drawRect(0,0,w-2,h-1);

            for(float i=20; i<=860; i+=8.4f){
                painter.drawLine(i, 0, i, 10);
                //painter.drawText(i,14,QString::number(i));
            }
            ui->lb_regla->setPixmap(pixmap);

        case 0:
            painter.setPen(QPen(Qt::black, 1.5));
            painter.drawRect(0,0,w-2,h-1);

            for(int i=20; i<=860; i+=84){
                painter.drawLine(i, 0, i, 15);
                painter.drawText(i-2.5,27,QString::number((i-10)/84));
            }

            painter.drawText(820.5,30,"cm");

            ui->lb_regla->setPixmap(pixmap);
            break;
    }

}

void MedicionIncertidumbre::mouseMoveEvent(QMouseEvent *event){
    if((event->x()>=0 && event->x()<=962) && (event->y()>=280 && event->y()<=321)){
        ui->lb_regla->move((event->x()-405),280);
    }
}

void MedicionIncertidumbre::mouseReleaseEvent(QMouseEvent *event){
    if(event->x()>=rango_drop[1] and event->x()<=rango_drop[2]){
        ui->lb_regla->move((rango_drop[0]-405),280);
        QMessageBox::information(this, tr("Medición"), tr("La regla ya está en su sitio."));
        ui->btn_medir->setStyleSheet("border-radius: 10px; border: 2px solid  rgb(0, 211, 211);");
        ui->btn_medir->setEnabled(true);
    }else{
        QMessageBox::information(this, tr("Medición"), tr("Coloca bien la regla"));
        ui->btn_medir->setStyleSheet("border-radius: 10px; border: 2px solid  rgb(159, 159, 159);");
        ui->btn_medir->setEnabled(false);
    }
}

MedicionIncertidumbre::MedicionIncertidumbre(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MedicionIncertidumbre)
{
    ui->setupUi(this);

    this->move(QApplication::desktop()->availableGeometry().center() - this->rect().center()); //Establecer posición de la ventana en el centro.

    ui->btn_medir->setEnabled(false);

    ui->btn_i_obj1->setStyleSheet("border-image:url(:/new/prefix1/recursos/sacapunta.png);");
    ui->btn_i_obj2->setStyleSheet("border-image:url(:/new/prefix1/recursos/bateria.png);");
    ui->btn_i_obj3->setStyleSheet("border-image:url(:/new/prefix1/recursos/memoria.png);");

    dibujarRegla(1,0,ui->lb_regla->width(), ui->lb_regla->height(),0);
    on_btn_i_obj1_clicked();
}


MedicionIncertidumbre::~MedicionIncertidumbre()
{
    delete ui;
}

void MedicionIncertidumbre::on_rB_md_1cm_clicked()
{
    dibujarRegla(1,0,ui->lb_regla->width(), ui->lb_regla->height(),0);
}

void MedicionIncertidumbre::on_rB_md_01cm_clicked()
{
    dibujarRegla(1,0,ui->lb_regla->width(), ui->lb_regla->height(),1);
}

void MedicionIncertidumbre::on_btn_medir_clicked()
{
    bool ok=true;
    double medicion;
    float valor_incerteza;
    float incerteza;
    unsigned int num_decimales;
    double respuesta;
    double incerteza_condicion=0.01;

    respuesta = respuestas[indice_res];
    if(ui->rB_md_1cm->isChecked()){
        num_decimales=1;
        incerteza=0.1f;
        incerteza_condicion=0.1;
        respuesta=truncar(respuestas[indice_res]);
    }else if(ui->rB_md_01cm->isChecked()){
        num_decimales=2;
        incerteza=0.01f;
        incerteza_condicion=0.02f;
        respuesta=respuestas[indice_res];
    }

    medicion = QInputDialog::getDouble(this, tr("Medición"), tr("¿Cuál valor lee?"), 0.00, 0, 500, num_decimales, &ok);

    if(medicion>=(respuesta-incerteza_condicion) && medicion<=(respuesta+incerteza_condicion)){
        valor_incerteza = QInputDialog::getDouble(this, tr("Medición"), tr("¿Cuál es la incertidumbre?"), 0.00, 0, 0.9, num_decimales, &ok);
        if(valor_incerteza==incerteza){
            QMessageBox::information(this, tr("Medición"), tr("CORRECTO\n(Respuesta: ") + QString::number(medicion) + " ± " + QString::number(incerteza) + ") cm");
        }else{
            QMessageBox::information(this, tr("Medición"), tr("La incertidumbre no es la correcta."));
        }
    }else{
        QMessageBox::information(this, tr("Medición"), tr("No es el valor, inténtelo de nuevo."));
    }

    //ui->lb_respuesta->setText("Respuesta: ("+QString::number(respuestas[indice_res]) + "± 0.1) cm");
}

void MedicionIncertidumbre::mostrarObjeto(float posY, float w, float h, QString ruta_objeto){
    QPixmap pixmap(ruta_objeto);
    ui->lb_mostrar_objeto->setPixmap(pixmap.scaled(w,h,Qt::KeepAspectRatioByExpanding));

    ui->lb_mostrar_objeto->setGeometry(481-(w/2),posY,w,h);
    ui->lb_mostrar_objeto->setPixmap(pixmap.scaled(w,h,Qt::KeepAspectRatioByExpanding));

    ui->line->move((481-(w/2)-10),0);
    ui->line_2->move((481+(w/2)-10),0);
}

void MedicionIncertidumbre::on_btn_i_obj1_clicked()
{
    mostrarObjeto(70, 222, 180, ":/new/prefix1/recursos/sacapunta.png");
    indice_res=0;
    rango_drop[0]=755; rango_drop[1]=745; rango_drop[2]=765;
}

void MedicionIncertidumbre::on_btn_i_obj2_clicked()
{
    mostrarObjeto(130, 408, 91, ":/new/prefix1/recursos/bateria.png");
    indice_res=1;
    rango_drop[0]=662; rango_drop[1]=652; rango_drop[2]=672;
}

void MedicionIncertidumbre::on_btn_i_obj3_clicked()
{
    mostrarObjeto(80, 620, 150, ":/new/prefix1/recursos/memoria.png");
    indice_res=2;
    rango_drop[0]=556; rango_drop[1]=546; rango_drop[2]=566;
}

void MedicionIncertidumbre::on_btn_volver_clicked()
{
    this->close(); //Se cierra esta ventana.
    MainWindow *MW;
    MW = new MainWindow();
    MW->show();
}
