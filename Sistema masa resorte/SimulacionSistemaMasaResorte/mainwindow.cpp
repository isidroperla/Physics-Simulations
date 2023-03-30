//Autor: José Isidro Perla Rosa

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <myopenglwidget.h>
#include <QMoveEvent>
#include <QTimer>
#include <QDesktopWidget>

MyOpenGLWidget *myOGLW; //Se crea un objeto de la clase MyOpenGLWidget.

float m_sB=0; //Variable que almacena la masa capturada por el spinBox.
float k_sB=0; //Variable que almacena el valor de k capturado por el spinBox.
float b_sB=0; //Variable que almacena el valor de la fuerza restauradora capturada por el spinBox.
float t_cB=0; //Variable que almacena paso del tiempo capturado asignado con una condición para el comboBox.
bool pausar=false;
bool reiniciar=false;
int opc=1; //Variable que guarda un entero que indicara si se considerara la fuerza restauradora o no en la simulación.
int inter=1; //Variable que guarda los valores 1 o -1, si se ha pulsado el botón (pausa = -1) y se vuelve a pausar (reanuda = 1).
bool reiniciarSimul=false; //Flag que indica si se reiniciara la simulación.

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->move(QApplication::desktop()->availableGeometry().center() - this->rect().center()); //Establecer posición de la ventana en el centro.

    ui->cB_tiempo->addItems({"X1 (Tiempo real)", "X 1/10", "X 1/100"});

    ui->sB_masa->setRange(0.01f, 1000.00f); //Se define el rango de valores para el spinBox de la masa.
    ui->sB_masa->setSingleStep(0.25f); //Se hacen aumentos de 0.25.

    ui->sB_k->setRange(0.0f, 1000.00f); //Se define el rango de valores para el spinBox del valor de k.
    ui->sB_k->setSingleStep(0.25f); //Se hacen aumentos de 0.25.

    ui->sB_b->setRange(0.0f, 1000.00f); //Se define el rango de valores para el spinBox de la fuerza restauradora.
    ui->sB_b->setSingleStep(0.10f); //Se hacen aumentos de 0.10.

    ui->sB_b->setEnabled(false); //Se desactiva al principio el spinBox de la fuerza restaudora (se puede activar o desactivar con un checkbox).

    ui->lb_t->setStyleSheet("font-weight: bold;"); //Se define el estilo de fuente negrita para el label que muestra el tiempo.

    myOGLW = new MyOpenGLWidget(m_sB,k_sB,b_sB,t_cB,pausar,reiniciar,opc); //Se hace una instancia del objeto myOGLW con la clase MyOpenGLWidget.
    connect(myOGLW, SIGNAL(varCustomSignal(float, float, float, float, QString, bool)), this, SLOT(varCustomSlot(float, float, float, float, QString, bool)));

    QTimer *rein=new QTimer(this); //Timer que sirve para reactivar la opción de reinicio.
    connect(rein, SIGNAL(timeout()), this, SLOT(activar_reinicio()));
    rein->start(50); //Se actualiza cada 50 milisegundos.

    update();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::varCustomSlot(float x, float vx, float ax, float t, QString tipo_de_movimiento, bool animacion_activada) //Función que recibe desde la clase MyOpenGLWidget ciertos valores que se mostraran con labels.
{
    ui->lb_x->setText("<center>x: " + QString::number(x, 'f', 2) + " m</center>");
    ui->lb_vx->setText("<center>v<sub>x</sub>: " + QString::number(vx, 'f', 2) + " m/s</center>");
    ui->lb_ax->setText("<center>a<sub>x</sub>: " + QString::number(ax, 'f', 2) + " m/s<sup>2</sup></center>");
    ui->lb_t->setText("t: " + QString::number(t, 'f', 2)+ " s");
    ui->lb_tipoDeMovimiento->setText("<center>" + tipo_de_movimiento + "</center>");

    if(animacion_activada==true){ //Si la animación esta activada se ha reactivara todos los controles editables menos el comboBox para el paso del tiempo.
        ui->sB_masa->setEnabled(false);
        ui->sB_k->setEnabled(false);
        ui->sB_b->setEnabled(false);
        ui->check_opc->setEnabled(false);
    }else{ //Si la animación ya no se encuentra en curso se reactivan los controles bloqueados.
        ui->sB_masa->setEnabled(true);
        ui->sB_k->setEnabled(true);
        ui->check_opc->setEnabled(true);
        if(opc==2){ //Si opc esta activo se habilita el spinBox de la fuerza restauradora.
            ui->sB_b->setEnabled(true);
        }
    }

}

void MainWindow::on_sB_masa_valueChanged(const QString &arg1) //Función que detecta si ha cambiado el valor del spinBox de la masa.
{
    m_sB = ui->sB_masa->text().toFloat(); //Se guarda el valor de la masa para mandarlo al constructor de MyOpenGLWidget.
    myOGLW = new MyOpenGLWidget(m_sB,k_sB,b_sB,t_cB,pausar,reiniciar,opc); //Se actualizan los datos mandados al constructor de la clase MyOpenGLWidget.
}

void MainWindow::on_sB_k_valueChanged(const QString &arg1) //Función que detecta si ha cambiado el valor del spinBox del valor de k.
{
    k_sB = ui->sB_k->text().toFloat(); //Se guarda el valor de k para mandarlo al constructor de MyOpenGLWidget.
    myOGLW = new MyOpenGLWidget(m_sB,k_sB,b_sB,t_cB,pausar,reiniciar,opc); //Se actualizan los datos mandados al constructor de la clase MyOpenGLWidget.
}

void MainWindow::on_sB_b_valueChanged(const QString &arg1) //Función que detecta si ha cambiado el valor del spinBox de la fuerza restauradora.
{
    b_sB = ui->sB_b->text().toFloat(); //Se guarda el valor de la fuerza restauradora para mandarlo al constructor de MyOpenGLWidget.
    myOGLW = new MyOpenGLWidget(m_sB,k_sB,b_sB,t_cB,pausar,reiniciar,opc); //Se actualizan los datos mandados al constructor de la clase MyOpenGLWidget.
}

void MainWindow::on_cB_tiempo_currentIndexChanged(int index) //Función que detecta el indice del comboBox del paso del tiempo.
{
    switch(index){
        case 0: //Para el caso cero se almacenara el valor de 1 en la variable t_cB para posteriormente mandarlo al constructor de la clase MyOpenGLWidget (Esa variable regulara el tiempo de la simulación).
            t_cB=1;
        break;
        case 1:
            t_cB=10; //Para el caso cero se almacenara el valor de 10 en la variable t_cB para posteriormente mandarlo al constructor de la clase MyOpenGLWidget (Esa variable regulara el tiempo de la simulación).
        break;
        case 2:
            t_cB=100; //Para el caso cero se almacenara el valor de 100 en la variable t_cB para posteriormente mandarlo al constructor de la clase MyOpenGLWidget (Esa variable regulara el tiempo de la simulación).
        break;
    }
    myOGLW = new MyOpenGLWidget(m_sB,k_sB,b_sB,t_cB,pausar,reiniciar,opc); //Se actualizan los datos mandados al constructor de la clase MyOpenGLWidget.
}

void MainWindow::on_btn_pausar_clicked() //Función que detecta si se ha hecho click en el botón pausar.
{
    inter*=-1; //Esta variable se hace negativa si pulsa el botón pausar y se hace positiva si se vuelve a pulsar.
    if(inter==-1){ //Si es negativo se pausa.
        pausar=true;
        ui->btn_pausar->setText("REANUDAR"); //Si esta pausado se imprime "REANUDAR" en el botón.
    }else if(inter==1){ //Si es positivo se reunuda
        ui->btn_pausar->setText("PAUSAR"); //Si se ha reanudado se imprime "PAUSAR" en el botón.
        pausar=false;
    }

    myOGLW = new MyOpenGLWidget(m_sB,k_sB,b_sB,t_cB,pausar,reiniciar,opc); //Se actualizan los datos mandados al constructor de la clase MyOpenGLWidget.
}

void MainWindow::on_check_opc_stateChanged(int arg1) //Función que detecta si se ha marcado la casilla que indica si tomara en cuenta la fuerza restuaradora o no.
{
    if(ui->check_opc->isChecked()==false){ //Si la casilla de la fuerza restauradora no se encuentra marcada, mandara el valor de 1 a opc y el control spinBox del valor de b estará bloqueado y mandando el valor de cero a la variable sB_b.
        opc=1;
        ui->sB_b->setEnabled(false);
        ui->sB_b->setValue(0);
    }else{ //En caso contrario se asignara el valor de 2 a opc y halitara el control spinBox del valor de b.
        opc=2;
        ui->sB_b->setEnabled(true);
    }

    myOGLW = new MyOpenGLWidget(m_sB,k_sB,b_sB,t_cB,pausar,reiniciar,opc); //Se actualizan los datos mandados al constructor de la clase MyOpenGLWidget.
}

void MainWindow::activar_reinicio(){ //Función que ejecuta un timer para reactivar el botón de reinicio.
    if(reiniciarSimul==true){ //Si ha hecho click en el botón reiniciar esta variable guarda true y activa esta condicional que reinicia la simulación con un timer, estableciendo intervalos de tiempo.
        temp+=0.05f;
        if(temp<=0.25f){
            reiniciar=true;
        }else{ //Si ya paso el tiempo de la condicional reinciar y reiniciarSimul se hacen false.
            reiniciar=false;
            reiniciarSimul=false;
            temp=0;
        }
     myOGLW = new MyOpenGLWidget(m_sB,k_sB,b_sB,t_cB,pausar,reiniciar,opc); //Se actualizan los datos mandados al constructor de la clase MyOpenGLWidget.
    }
}

void MainWindow::on_btn_reiniciar_pressed() //Botón que activa el reinicio de la simulación.
{
    reiniciarSimul=true; //Se hace true este flag que hace que la función activar_reinicio reinicie y reactive la opción reincio en un periodo corto de tiempo con un timer.
    if(pausar==true){ //Si activar pausa esta activo, se desactiva con el flag pausar como false y inter multiplicandolo como inter = interx-1.
        inter*=-1;
        pausar=false;
        ui->btn_pausar->setText("PAUSAR"); //Si se ha reanudado se imprime "PAUSAR" en el botón.
    }
}
