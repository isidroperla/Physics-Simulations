#include "objetossumergidosenliquidos.h"
#include "ui_objetossumergidosenliquidos.h"
#include <mainwindow.h>
#include <QDesktopWidget>
#include <sstream>
#include <string.h>
#include <qmessagebox.h>
#include <iostream>

using namespace std;

float m_Obj=0; //Masa del objeto.
float c_Obj=0; //Calor especifico del objeto.
float t_Obj=0; //Temperatura inicial del objeto.
float m_Fl=0; //Masa del líquido.
float c_Fl=0; //Calor especifico del líquido.
float t_Fl=0; //Temperatura inicial del líquido.

QString nombres_Materiales[] = {"Hierro", "Aluminio", "Plomo", "Cobre", "Plata", "Oro", "Otro", "----"}; //Vector que almacena el nombre de los materiales.
float caloresEspecificos_Materiales[] = {448, 900, 128, 387, 234, 129}; //Vector que almacena los calores específicos de los materiales.
float puntoDeFusion_Materiales[] = {1808, 660, 327.3f, 1083, 960.80f, 1063.00f}; //Vector que almacena los puntos de fusión de los materiales.

QString nombres_Fluidos[] = {"Agua", "Alcohol etilico", "Otro", "----"}; //Vector que almacena el nombre de los fluidos.
float caloresEspecificos_Fluidos[] = {4186, 2400}; //Vector que almacena los calores específicos de los fluidos.
float puntoDeFusion_Fluidos[] = {0.00f, -114}; //Vector que almacena los puntos de fusión de los fluidos.
float puntoDeFision_Fluidos[] = {100.0f, 78}; //Vector que almacena los puntos de fusión de los fluidos.

int numeroDeMateriales = sizeof(nombres_Materiales) / sizeof(nombres_Materiales[0]); //Obtiene el númerode materiales del vector.
int numeroDeFluidos = sizeof(nombres_Fluidos) / sizeof(nombres_Fluidos[0]); //Obtiene el número de fluidos del vector.

string nombreObjeto[2]; //Almacena el nombre del objeto, también el del fluido para concatenarlo después para madar al exe de OpenGl.

objetosSumergidosEnLiquidos::objetosSumergidosEnLiquidos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::objetosSumergidosEnLiquidos)
{
    ui->setupUi(this);

    this->move(QApplication::desktop()->availableGeometry().center() - this->rect().center()); //Establecer posición de la ventana en el centro.

    for(int i=0; i<numeroDeMateriales; i++){ //Este ciclo recorre el vector de lista de materiales y los añade al combobox para estos.
        ui->cB_Materiales->addItem(nombres_Materiales[i]);
    }

    for(int i=0; i<numeroDeFluidos; i++){ //Este ciclo recorre el vector de lista de fluidos y los añade al combobox para estos.
        ui->cB_Fluidos->addItem(nombres_Fluidos[i]);
    }

    ui->cB_Materiales->setCurrentIndex(numeroDeMateriales-1); //Se inicializa como "----" (ningún objeto seleccionado) siendo el indice de este el ultimo elemento.
    ui->cB_Fluidos->setCurrentIndex(numeroDeFluidos-1); //Se inicializa como "----" (ningún fluido seleccionado) siendo el indice de este el ultimo elemento.

    ui->txt_m_Obj->setValidator(new QDoubleValidator(-39.5, 99.0, 5, ui->txt_m_Obj)); //Validación para que el usuario solo pueda ingresar números en el lineEdit.
    ui->txt_c_Obj->setValidator(new QDoubleValidator(-39.5, 99.0, 5, ui->txt_c_Obj)); //Validación para que el usuario solo pueda ingresar números en el lineEdit.
    ui->txt_t_Obj->setValidator(new QDoubleValidator(-39.5, 99.0, 5, ui->txt_t_Obj)); //Validación para que el usuario solo pueda ingresar números en el lineEdit.

    ui->txt_m_Fl->setValidator(new QDoubleValidator(-39.5, 99.0, 5, ui->txt_m_Fl)); //Validación para que el usuario solo pueda ingresar números en el lineEdit.
    ui->txt_c_Fl->setValidator(new QDoubleValidator(-39.5, 99.0, 5, ui->txt_c_Fl)); //Validación para que el usuario solo pueda ingresar números en el lineEdit.
    ui->txt_t_Fl->setValidator(new QDoubleValidator(-39.5, 99.0, 5, ui->txt_t_Fl)); //Validación para que el usuario solo pueda ingresar números en el lineEdit  

    ui->txt_c_Obj->setText("0"); //Se inicializa el cuadro de texto del calor especifico del objeto como cero.
    ui->txt_c_Fl->setText("0"); //Se inicializa el cuadro de texto del calor especifico del fluido como cero.
}

objetosSumergidosEnLiquidos::~objetosSumergidosEnLiquidos()
{
    delete ui;
}

void objetosSumergidosEnLiquidos::on_cB_Materiales_currentIndexChanged(int index) //Función que reconoce elementos del campo de texto para calor específico (objeto) y lo señala en el combobox de lista de materiales.
{
    if(index<numeroDeMateriales-2){ //Si el indice esta entre los valores de la lista de materiales, se coloca el valor del calor específico que le corresponde en ese vector con el index obtenido.
        ui->txt_c_Obj->setText(QString::number(caloresEspecificos_Materiales[index]));
        nombreObjeto[0] = nombres_Materiales[index].toStdString();
    }else if(index==numeroDeMateriales-1){ //Sino se marcara con el penultimo valor del vector de nombres de materiales poniendo "Desconocido".
        nombreObjeto[0] = "Desconocido";
    }
}

void objetosSumergidosEnLiquidos::on_cB_Fluidos_currentIndexChanged(int index) //Función que reconoce elementos del campo de texto para calor específico  (liquído )y lo señala en el combobox de lista de fluidos.
{
    if(index<numeroDeFluidos-2){ //Si el indice esta entre los valores de la lista de fluidos, se coloca el valor del calor específico que le corresponde en ese vector con el index obtenido.
        ui->txt_c_Fl->setText(QString::number(caloresEspecificos_Fluidos[index]));
        nombreObjeto[1] = nombres_Fluidos[index].toStdString();
    }else if(index==numeroDeFluidos-1){
        nombreObjeto[1] = "Desconocido"; //Sino se marcara con el penultimo valor del vector de nombres de fluidos poniendo "Desconocido".
    }
}

void objetosSumergidosEnLiquidos::on_txt_c_Obj_textEdited(const QString &arg1)
{
    for(int i=0; i<(numeroDeMateriales-2); i++){ //For que aumenta en uno el iterador dependiendo del numero de materiales del vector (no se toman en cuenta el ultimo ni penultimo elemento de ese).
        if(ui->txt_c_Obj->text().toFloat() != caloresEspecificos_Materiales[i]){ //Primero identfica si es un elemento de la lista de materaiales comparando el dato de calor específico.
            ui->cB_Materiales->setCurrentIndex(numeroDeMateriales-2); //Si no lo es se marca con al antepenultimo elemento elemento de la lista de nombres como "Otro".
            nombreObjeto[0] = "Desconocido";
        }
    }

    for(int i=0; i<(numeroDeMateriales-2); i++){ //For que aumenta en uno el iterador dependiendo del numero de materiales del vector (no se toman en cuenta el ultimo ni penultimo elemento de ese).
        if(ui->txt_c_Obj->text().toFloat() == caloresEspecificos_Materiales[i]){ //Primero identfica si es un elemento de la lista de meteriales comparando el dato de calor específico.
            ui->cB_Materiales->setCurrentIndex(i); //Si lo es, marca ese indice para identificar el elemento en el combobox para los materiales.
        }else if(ui->txt_c_Obj->text().toFloat()==0){ //Si es cero
            ui->cB_Materiales->setCurrentIndex(numeroDeMateriales-1); //Marca el penultimo elemento como "----".
        }
    }
}

void objetosSumergidosEnLiquidos::on_txt_c_Fl_textEdited(const QString &arg1)
{
    for(int i=0; i<(numeroDeFluidos-2); i++){ //For que aumenta en uno el iterador dependiendo del numero de fluidos del vector (no se toman en cuenta el ultimo ni penultimo elemento de ese).
        if(ui->txt_c_Fl->text().toFloat() != caloresEspecificos_Fluidos[i]){ //Primero identfica si es un elemento de la lista de fluidos comparando el dato de calor específico.
            ui->cB_Fluidos->setCurrentIndex(numeroDeFluidos-2); //Si no lo es se marca con al antepenultimo elemento elemento de la lista de nombres como "Otro".
            nombreObjeto[1] = "Desconocido";
        }
    }

    for(int i=0; i<(numeroDeFluidos-2); i++){ //For que aumenta en uno el iterador dependiendo del numero de fluidos del vector (no se toman en cuenta el ultimo ni penultimo elemento de ese).
        if(ui->txt_c_Fl->text().toFloat() == caloresEspecificos_Fluidos[i]){ //Primero identfica si es un elemento de la lista de fluidos comparando el dato de calor específico.
            ui->cB_Fluidos->setCurrentIndex(i); //Si lo es, marca ese indice para identificar el elemento en el combobox para los fluidos.
        }else if(ui->txt_c_Fl->text().toFloat()==0){
            ui->cB_Fluidos->setCurrentIndex(numeroDeFluidos-1); //Marca el penultimo elemento como "----".
        }
    }
}

void objetosSumergidosEnLiquidos::cambiosDeFase(float tObj, float tFl){ //Función que indica su hay cambios de fase en la simulación.
                                                                        //Recibe el valor de la temperatura del objeto y la del fluido.
    bool mostrar_msj=false; //Flag para mostrar un mensaje validación de temperaturas.

    for(int i=0; i<(numeroDeMateriales-2); i++){ //Recorre el iterador hasta alcanzar el número de materiales de la lista.
        if(ui->txt_c_Obj->text().toFloat() == caloresEspecificos_Materiales[i]){ //Primero identfica si es un elemento de la lista de materiales comparando el dato de calor específico.
            if(tObj>=puntoDeFusion_Materiales[i]){ //Revisa si la temperatura del objeto es mayor o igual que la del punto de fusión del vector.
                mostrar_msj=true; //Activa una bandera de mensaje si se cumple la condición.
            }
        }
    }

    for(int i=0; i<(numeroDeFluidos-2); i++){ //Recorre el iterador hasta alcanzar el número de fluidos de la lista.
        if(ui->txt_c_Fl->text().toFloat() == caloresEspecificos_Fluidos[i]){ //Primero identfica si es un elemento de la lista de fluidos comparando el dato de calor específico.
            if(tFl<=puntoDeFusion_Fluidos[i]){ //Revisa si la temperatura del fluido es menor o igual que la del punto de fusión del vector.
                mostrar_msj=true; //Activa una bandera de mensaje si se cumple la condición.
            }
            if(tFl>=puntoDeFision_Fluidos[i]){ //Revisa si la temperatura del fluido es mayor o igual que la del punto de fisión del vector.
                mostrar_msj=true; //Activa una bandera de mensaje si se cumple la condición.
            }
        }
    }

    if(mostrar_msj==true){ //Mensaje que se mostrara si se activo el flag.
        QMessageBox::information(this, tr("¡ALERTA!"), tr("Aquí no se consideran cambios de fase, dados los valores de temperatura introducidos, la simulación no será exacta."));
    }

}

bool objetosSumergidosEnLiquidos::validarDatos(float mObj, float cObj, float mFl, float cFl){ //Esta función valida los datos de las masas, calores especificos del objeto y el líquido.

    bool val=false; //Valor boleano que retorna la funcíon
    bool activarMensaje1=false; //Flag msj1.
    bool activarMensaje2=false; //Flag msj2.

    if(mObj<=0 || mFl<=0){ //Validación para que las masas del objeto y fluido no puedan ser cero o negativas.
        activarMensaje1=true;
    }

    if(cObj<=0 || cFl<=0){ //Validación para que los calores específicos del objeto y fluido no puedan ser cero o negativos.
        activarMensaje2=true;
    }

    if(activarMensaje1==true){
        QMessageBox::information(this, tr("¡ALERTA!"), tr("No se puede colocar el valor de 0 kg o negativos para las masas."));
        val=true;
    }
    if(activarMensaje2==true){
        QMessageBox::information(this, tr("¡ALERTA!"), tr("No se puede colocar el valor de 0 J/kg·°C o negativos para los calores especificos."));
        val=true;
    }

    activarMensaje1=false;
    activarMensaje2=false;
    return val; //Retorna true si hay una validación activa.

}

void objetosSumergidosEnLiquidos::on_btn_Regresar_clicked() //Esta función sirve para regresar a la ventana de inicio cerrando está.
{
    this->close(); //Se cierra esta ventana.

    MainWindow *mW;
    mW = new MainWindow(this);
    mW->show(); //Abre la ventana de inicio.
}

void objetosSumergidosEnLiquidos::on_btn_Calcular_clicked()
{

    string argumento = "";
    stringstream concatenador;

    //Se recibe el valor del lineEdit como texto, y luego se convierte a float.
    m_Obj = ui->txt_m_Obj->text().toFloat();
    c_Obj = ui->txt_c_Obj->text().toFloat();
    t_Obj = ui->txt_t_Obj->text().toFloat();
    m_Fl = ui->txt_m_Fl->text().toFloat();
    c_Fl = ui->txt_c_Fl->text().toFloat();
    t_Fl = ui->txt_t_Fl->text().toFloat();

    cambiosDeFase(t_Obj, t_Fl); //Se manda a llamar la función que indica si hay cambios de fase (Se la manda la temperatura del objeto y la del fluido).

    if(validarDatos(m_Obj, c_Fl, m_Fl, c_Fl)!=true){ //Si la función de validar datos es falsa, se puede procede iniciar y mandar argumentos al ejecutable de OpenGl.

        //Concatenamos el nombre del ejectuble de OpenGL y los datos de forma ordenada en una variable llamada concatenador.

        concatenador << "Animacion.exe " << " " << 2 << " " << 2;

        concatenador << " " << m_Obj << " " << c_Obj << " " << t_Obj << " " << " " << nombreObjeto[0]; //Se concatenan las variables del objeto.
        concatenador << " " << m_Fl << " " << c_Fl << " " << t_Fl << " " << " " << nombreObjeto[1]; //Se concatenan las variables del fluido.

        argumento = concatenador.str();

        //Creamos un puntero llamado c que contendra la dirreción de concatenador.

        const char *c = argumento.c_str();

        //Se imprimen los datos en el Application Output para verificar que todo este en orden.

        cout << c <<endl;

        //Mandamos los datos de concatenador y esto abrira el ejecutable de OpenGl.

        system(c);

    }

}
