#include "conversionlongitud.h"
#include "ui_conversionlongitud.h"
#include <mainwindow.h>
#include <conversion.h>
#include <QDesktopWidget>
#include <QPainter>

float longitudes[] = {14.7,26,110, 160};
QString vals_conv1[5];
QString vals_conv2[5];
int indice_long=0;

bool v[] = {0,0,0,0,0};
int A=-4;
int B=-4;
int cont=0;
bool btn_activados[]={0,0,0,0,0};

ConversionLongitud::ConversionLongitud(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConversionLongitud)
{
    ui->setupUi(this);

    this->move(QApplication::desktop()->availableGeometry().center() - this->rect().center()); //Establecer posición de la ventana en el centro.

    //Imagen para los botones de objetos en longitud
    ui->btn_l_obj1->setStyleSheet("border-image:url(:/new/prefix1/recursos/lapiz.png);");
    ui->btn_l_obj2->setStyleSheet("border-image:url(:/new/prefix1/recursos/zapato.png);");
    ui->btn_l_obj3->setStyleSheet("border-image:url(:/new/prefix1/recursos/bate.png);");
    ui->btn_l_obj4->setStyleSheet("border-image:url(:/new/prefix1/recursos/sofa.png);");

    float ancho = ui->tabWidget->width()/2;
    ui->tabWidget->setStyleSheet("QTabBar::tab { height: 20px; width: " + QString::number(ancho) +"px; }");

    on_btn_l_obj1_clicked();
}

ConversionLongitud::~ConversionLongitud()
{
    delete ui;
}

void ConversionLongitud::dibujarRegla(int x, int y, int w, int h,QString unidad, int opc){

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
        painter.setPen(Qt::black);
            painter.drawRect(0,0,w-2,h-1);

            for(int i=0; i<=420; i+=21){
                painter.drawLine(i, 0, i, 7);
                painter.drawText(390,20,unidad);
            }
            ui->lb_regla_horizontal1->setPixmap(pixmap);
        break;
        case 2:
        painter.setPen(Qt::blue);
            painter.drawRect(0,0,w-2,h-1);

            for(int i=0; i<=421; i+=21){
                painter.drawLine(i, 0, i, 7);
                painter.drawText(390,20,unidad);
            }
            ui->lb_regla_horizontal2->setPixmap(pixmap);
        break;
    }
}

void ConversionLongitud::mostrarObjeto(QString ruta_objeto){
    QPixmap pixmap(ruta_objeto);
    ui->label->setPixmap(pixmap.scaled(ui->label->width(),ui->label->height(),Qt::KeepAspectRatioByExpanding));
}

void ConversionLongitud::on_btn_l_obj1_clicked()
{
    mostrarObjeto(":/new/prefix1/recursos/lapiz.png");
    indice_long=0;
    actualizarBotones();
}

void ConversionLongitud::on_btn_l_obj2_clicked()
{
    mostrarObjeto(":/new/prefix1/recursos/zapato.png");
    indice_long=1;
    actualizarBotones();
}

void ConversionLongitud::on_btn_l_obj3_clicked()
{
    mostrarObjeto(":/new/prefix1/recursos/bate.png");
    indice_long=2;
    actualizarBotones();
}

void ConversionLongitud::on_btn_l_obj4_clicked()
{
    mostrarObjeto(":/new/prefix1/recursos/sofa.png");
    indice_long=3;
    actualizarBotones();
}

void ConversionLongitud::actualizarBotones(){
    for(int i=0; i<=4; i++){
        if(btn_activados[i]==true){
            switch(i){
                case 0:
                    on_btn_regla1_clicked();
                    on_btn_regla1_clicked();
                break;
                case 1:
                    on_btn_regla2_clicked();
                    on_btn_regla2_clicked();
                break;
                case 2:
                    on_btn_regla3_clicked();
                    on_btn_regla3_clicked();
                break;
                case 3:
                    on_btn_regla4_clicked();
                    on_btn_regla4_clicked();
                break;
                case 4:
                    on_btn_regla5_clicked();
                    on_btn_regla5_clicked();
                break;
            }
        }
    }
}

void ConversionLongitud::seleccionador(int posVectorial){

    if(v[posVectorial]==false){
        if(cont<=1){
            v[posVectorial]=true;
            cont++;
        }

    }else if(v[posVectorial]==true){
        v[posVectorial]=false;
        cont--;
    }

    for(int i=0; i<5; i++){
        if(v[i]==true){
            A=i;
            break;
        }
    }

    for(int i=0; i<5; i++){
        if(v[i]==true){
            if(i==A){
            }else{
                B=i;
            }
        }
    }

    ui->lb_regla_horizontal1->clear();
    ui->lb_regla_horizontal2->clear();
    ui->lb_unidades_regla1->setText("");
    ui->lb_unidades_regla2->setText("");
    ui->btn_convertir_long1->setText("");
    ui->btn_convertir_long2->setText("");

    if(A==0){
        dibujarRegla(1,0,ui->lb_regla_horizontal1->width(), ui->lb_regla_horizontal1->height(),"cm",1);
        ui->lb_unidades_regla1->setText(QString::number(longitudes[indice_long]) + " cm");
    }else if(A==1){
        dibujarRegla(1,0,ui->lb_regla_horizontal1->width(), ui->lb_regla_horizontal1->height(),"pulg",1);
        ui->lb_unidades_regla1->setText(QString::number(longitudes[indice_long]/ 2.540) + " pulg");
    }else if(A==2){
        dibujarRegla(1,0,ui->lb_regla_horizontal1->width(), ui->lb_regla_horizontal1->height(),"pies",1);
        ui->lb_unidades_regla1->setText(QString::number(longitudes[indice_long]/ 30.48) + " pies");
    }else if(A==3){
        dibujarRegla(1,0,ui->lb_regla_horizontal1->width(), ui->lb_regla_horizontal1->height(),"yd",1);
        ui->lb_unidades_regla1->setText(QString::number(longitudes[indice_long]/ 91.44) + " yd");
    }else if(A==4){
        dibujarRegla(1,0,ui->lb_regla_horizontal1->width(), ui->lb_regla_horizontal1->height(),"m",1);
        ui->lb_unidades_regla1->setText(QString::number(longitudes[indice_long]/ 100) + " m");
    }

    if(B==0){
        dibujarRegla(1,0,ui->lb_regla_horizontal2->width(), ui->lb_regla_horizontal2->height(),"cm",2);
        ui->lb_unidades_regla2->setText(QString::number(longitudes[indice_long]) + " cm");
    }else if(B==1){
        dibujarRegla(1,0,ui->lb_regla_horizontal2->width(), ui->lb_regla_horizontal2->height(),"pulg",2);
        ui->lb_unidades_regla2->setText(QString::number(longitudes[indice_long]/ 2.540) + " pulg");
    }else if(B==2){
        dibujarRegla(1,0,ui->lb_regla_horizontal2->width(), ui->lb_regla_horizontal2->height(),"pies",2);
        ui->lb_unidades_regla2->setText(QString::number(longitudes[indice_long]/ 30.48) + " pies");
    }else if(B==3){
        dibujarRegla(1,0,ui->lb_regla_horizontal1->width(), ui->lb_unidades_regla2->height(),"yd",2);
        ui->lb_unidades_regla2->setText(QString::number(longitudes[indice_long]/ 91.44) + " yd");
    }else if(B==4){
        dibujarRegla(1,0,ui->lb_regla_horizontal1->width(), ui->lb_unidades_regla2->height(),"m",2);
        ui->lb_unidades_regla2->setText(QString::number(longitudes[indice_long]/ 100) + " m");
    }

    if(A==0 and B==1){
        ui->btn_convertir_long1->setText("cm a pulg");
        ui->btn_convertir_long2->setText("pulg a cm");
        vals_conv1[0]= QString::number(longitudes[indice_long]); vals_conv1[1] = "1"; vals_conv1[2] = "pulg"; vals_conv1[3] = "2.540"; vals_conv1[4] = "cm";
        vals_conv2[0]= QString::number(longitudes[indice_long]/2.540); vals_conv2[1] = "2.540"; vals_conv2[2] = "cm"; vals_conv2[3] = "1"; vals_conv2[4] = "pulg";
    }else if(A==0 and B==2){
        ui->btn_convertir_long1->setText("cm a pies");
        ui->btn_convertir_long2->setText("pies a cm");
        vals_conv1[0]= QString::number(longitudes[indice_long]); vals_conv1[1] = "1"; vals_conv1[2] = "pies"; vals_conv1[3] = "30.84"; vals_conv1[4] = "cm";
        vals_conv2[0]= QString::number(longitudes[indice_long]/30.84); vals_conv2[1] = "30.84"; vals_conv2[2] = "cm"; vals_conv2[3] = "1"; vals_conv2[4] = "pies";
    }else if(A==0 and B==3){
        ui->btn_convertir_long1->setText("cm a yd");
        ui->btn_convertir_long2->setText("yd a cm");
        vals_conv1[0]= QString::number(longitudes[indice_long]); vals_conv1[1] = "1"; vals_conv1[2] = "yd"; vals_conv1[3] = "91.44"; vals_conv1[4] = "cm";
        vals_conv2[0]= QString::number(longitudes[indice_long]/91.44); vals_conv2[1] = "91.44"; vals_conv2[2] = "cm"; vals_conv2[3] = "1"; vals_conv2[4] = "yd";
    }else if(A==0 and B==4){
        ui->btn_convertir_long1->setText("cm a m");
        ui->btn_convertir_long2->setText("m a cm");
        vals_conv1[0]= QString::number(longitudes[indice_long]); vals_conv1[1] = "1"; vals_conv1[2] = "m"; vals_conv1[3] = "100"; vals_conv1[4] = "cm";
        vals_conv2[0]= QString::number(longitudes[indice_long]/100); vals_conv2[1] = "100"; vals_conv2[2] = "cm"; vals_conv2[3] = "1"; vals_conv2[4] = "m";
    }else if(A==1 and B==2){
        ui->btn_convertir_long1->setText("pulg a pies");
        ui->btn_convertir_long2->setText("pies a pulg");
        vals_conv1[0]= QString::number(longitudes[indice_long]/ 2.540); vals_conv1[1] = "1"; vals_conv1[2] = "pies"; vals_conv1[3] = "39.37"; vals_conv1[4] = "pulg";
        vals_conv2[0]= QString::number(longitudes[indice_long]/30.48); vals_conv2[1] = "39.37"; vals_conv2[2] = "pulg"; vals_conv2[3] = "1"; vals_conv2[4] = "pies";
    }else if(A==1 and B==3){
        ui->btn_convertir_long1->setText("pulg a yd");
        ui->btn_convertir_long2->setText("yd a pulg");
        vals_conv1[0]= QString::number(longitudes[indice_long]/ 2.540); vals_conv1[1] = "1"; vals_conv1[2] = "yd"; vals_conv1[3] = "36"; vals_conv1[4] = "pulg";
        vals_conv2[0]= QString::number(longitudes[indice_long]/91.44); vals_conv2[1] = "36"; vals_conv2[2] = "pulg"; vals_conv2[3] = "1"; vals_conv2[4] = "yd";
    }else if(A==1 and B==4){
        ui->btn_convertir_long1->setText("pulg a m");
        ui->btn_convertir_long2->setText("m a pulg");
        vals_conv1[0]= QString::number(longitudes[indice_long]/ 2.540); vals_conv1[1] = "1"; vals_conv1[2] = "m"; vals_conv1[3] = "39.37"; vals_conv1[4] = "pulg";
        vals_conv2[0]= QString::number(longitudes[indice_long]/100); vals_conv2[1] = "39.37"; vals_conv2[2] = "pulg"; vals_conv2[3] = "1"; vals_conv2[4] = "m";
    }else if(A==2 and B==3){
        ui->btn_convertir_long1->setText("pies a yd");
        ui->btn_convertir_long2->setText("yd a pies");
        vals_conv1[0]= QString::number(longitudes[indice_long]/ 30.48); vals_conv1[1] = "1"; vals_conv1[2] = "yd"; vals_conv1[3] = "3"; vals_conv1[4] = "pies";
        vals_conv2[0]= QString::number(longitudes[indice_long]/91.44); vals_conv2[1] = "3"; vals_conv2[2] = "pies"; vals_conv2[3] = "1"; vals_conv2[4] = "yd";
    }else if(A==2 and B==4){
        ui->btn_convertir_long1->setText("pies a m");
        ui->btn_convertir_long2->setText("m a pies");
        vals_conv1[0]= QString::number(longitudes[indice_long]/ 30.48); vals_conv1[1] = "1"; vals_conv1[2] = "m"; vals_conv1[3] = "3.281"; vals_conv1[4] = "pies";
        vals_conv2[0]= QString::number(longitudes[indice_long]/100); vals_conv2[1] = "3.281"; vals_conv2[2] = "pies"; vals_conv2[3] = "1"; vals_conv2[4] = "m";
    }else if(A==3 and B==4){
        ui->btn_convertir_long1->setText("yd a m");
        ui->btn_convertir_long2->setText("m a yd");
        vals_conv1[0]= QString::number(longitudes[indice_long]/ 91.44); vals_conv1[1] = "1"; vals_conv1[2] = "m"; vals_conv1[3] = "0.9144"; vals_conv1[4] = "yd";
        vals_conv2[0]= QString::number(longitudes[indice_long]/100); vals_conv2[1] = "0.9144"; vals_conv2[2] = "yd"; vals_conv2[3] = "1"; vals_conv2[4] = "m";
    }

    A=-4;
    B=-4;
}

void ConversionLongitud::on_btn_regla1_clicked()
{
    seleccionador(0);

    if(v[0]==true and cont<=2){
        ui->btn_regla1->setStyleSheet("border-radius: 10px; border: 2px solid rgb(51,184,255);");
        btn_activados[0]=1;
    }else if(v[0]==false){
        ui->btn_regla1->setStyleSheet("border-radius: 10px; border: 1px solid rgb(0,0,0);");
        btn_activados[0]=0;
    }

    if(cont>=2){
        ui->btn_convertir_long1->setStyleSheet("background-color: rgb(255, 255, 255); border-radius: 10px; border: 2px solid  rgb(0, 211, 211); font-weight: bold;");
        ui->btn_convertir_long2->setStyleSheet("background-color: rgb(255, 255, 255); border-radius: 10px; border: 2px solid  rgb(0, 211, 211); font-weight: bold;");
    }else{
        ui->btn_convertir_long1->setStyleSheet("background-color: rgb(255, 255, 255); border-radius: 10px; border: 2px solid  rgb(159, 159, 159); font-weight: bold;");
        ui->btn_convertir_long2->setStyleSheet("background-color: rgb(255, 255, 255); border-radius: 10px; border: 2px solid  rgb(159, 159, 159); font-weight: bold;");
    }
}

void ConversionLongitud::on_btn_regla2_clicked()
{
    seleccionador(1);

    if(v[1]==true and cont<=2){
        ui->btn_regla2->setStyleSheet("border-radius: 10px; border: 2px solid rgb(51,184,255);");
        btn_activados[1]=1;
    }else if(v[1]==false){
        ui->btn_regla2->setStyleSheet("border-radius: 10px; border: 1px solid rgb(0,0,0);");
        btn_activados[1]=0;
    }

    if(cont>=2){
        ui->btn_convertir_long1->setStyleSheet("background-color: rgb(255, 255, 255); border-radius: 10px; border: 2px solid  rgb(0, 211, 211); font-weight: bold;");
        ui->btn_convertir_long2->setStyleSheet("background-color: rgb(255, 255, 255); border-radius: 10px; border: 2px solid  rgb(0, 211, 211); font-weight: bold;");
    }else{
        ui->btn_convertir_long1->setStyleSheet("background-color: rgb(255, 255, 255); border-radius: 10px; border: 2px solid  rgb(159, 159, 159); font-weight: bold;");
        ui->btn_convertir_long2->setStyleSheet("background-color: rgb(255, 255, 255); border-radius: 10px; border: 2px solid  rgb(159, 159, 159); font-weight: bold;");
    }
}

void ConversionLongitud::on_btn_regla3_clicked()
{
    seleccionador(2);

    if(v[2]==true and cont<=2){
        ui->btn_regla3->setStyleSheet("border-radius: 10px; border: 2px solid rgb(51,184,255);");
        btn_activados[2]=1;
    }else if(v[2]==false){
        ui->btn_regla3->setStyleSheet("border-radius: 10px; border: 1px solid rgb(0,0,0);");
        btn_activados[2]=0;
    }

    if(cont>=2){
        ui->btn_convertir_long1->setStyleSheet("background-color: rgb(255, 255, 255); border-radius: 10px; border: 2px solid  rgb(0, 211, 211); font-weight: bold;");
        ui->btn_convertir_long2->setStyleSheet("background-color: rgb(255, 255, 255); border-radius: 10px; border: 2px solid  rgb(0, 211, 211); font-weight: bold;");
    }else{
        ui->btn_convertir_long1->setStyleSheet("background-color: rgb(255, 255, 255); border-radius: 10px; border: 2px solid  rgb(159, 159, 159); font-weight: bold;");
        ui->btn_convertir_long2->setStyleSheet("background-color: rgb(255, 255, 255); border-radius: 10px; border: 2px solid  rgb(159, 159, 159); font-weight: bold;");
    }
}

void ConversionLongitud::on_btn_regla4_clicked()
{
    seleccionador(3);

    if(v[3]==true and cont<=2){
        ui->btn_regla4->setStyleSheet("border-radius: 10px; border: 2px solid rgb(51,184,255);");
        btn_activados[3]=1;
    }else if(v[3]==false){
        ui->btn_regla4->setStyleSheet("border-radius: 10px; border: 1px solid rgb(0,0,0);");
        btn_activados[3]=0;
    }

    if(cont>=2){
        ui->btn_convertir_long1->setStyleSheet("background-color: rgb(255, 255, 255); border-radius: 10px; border: 2px solid  rgb(0, 211, 211); font-weight: bold;");
        ui->btn_convertir_long2->setStyleSheet("background-color: rgb(255, 255, 255); border-radius: 10px; border: 2px solid  rgb(0, 211, 211); font-weight: bold;");
    }else{
        ui->btn_convertir_long1->setStyleSheet("background-color: rgb(255, 255, 255); border-radius: 10px; border: 2px solid  rgb(159, 159, 159); font-weight: bold;");
        ui->btn_convertir_long2->setStyleSheet("background-color: rgb(255, 255, 255); border-radius: 10px; border: 2px solid  rgb(159, 159, 159); font-weight: bold;");
    }
}

void ConversionLongitud::on_btn_regla5_clicked()
{
    seleccionador(4);

    if(v[4]==true and cont<=2){
        ui->btn_regla5->setStyleSheet("border-radius: 10px; border: 2px solid rgb(51,184,255);");
        btn_activados[4]=1;
    }else if(v[4]==false){
        ui->btn_regla5->setStyleSheet("border-radius: 10px; border: 1px solid rgb(0,0,0);");
        btn_activados[4]=0;
    }

    if(cont>=2){
        ui->btn_convertir_long1->setStyleSheet("background-color: rgb(255, 255, 255); border-radius: 10px; border: 2px solid  rgb(0, 211, 211); font-weight: bold;");
        ui->btn_convertir_long2->setStyleSheet("background-color: rgb(255, 255, 255); border-radius: 10px; border: 2px solid  rgb(0, 211, 211); font-weight: bold;");
    }else{
        ui->btn_convertir_long1->setStyleSheet("background-color: rgb(255, 255, 255); border-radius: 10px; border: 2px solid  rgb(159, 159, 159); font-weight: bold;");
        ui->btn_convertir_long2->setStyleSheet("background-color: rgb(255, 255, 255); border-radius: 10px; border: 2px solid  rgb(159, 159, 159); font-weight: bold;");
    }
}

void ConversionLongitud::on_btn_volver_clicked()
{
    this->close(); //Se cierra esta ventana.
    MainWindow *MW;
    MW = new MainWindow();
    MW->show();
}

void ConversionLongitud::on_btn_convertir_long1_clicked()
{
    if(cont==2){
        Conversion *conv;
        conv = new Conversion(vals_conv1[0], vals_conv1[1], vals_conv1[2], vals_conv1[3], vals_conv1[4]);
        conv->show();
    }
}

void ConversionLongitud::on_btn_convertir_long2_clicked()
{
    if(cont==2){
        Conversion *conv;
        conv = new Conversion(vals_conv2[0], vals_conv2[1], vals_conv2[2], vals_conv2[3], vals_conv2[4]);
        conv->show();
    }
}
