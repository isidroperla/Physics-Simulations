#include "variosobjetos.h"
#include "ui_variosobjetos.h"
#include <mainwindow.h>
#include <QDesktopWidget>
#include <iostream>
#include <sstream>
#include <string.h>
#include <QMessageBox>
#include <QItemDelegate>
#include <cstring>
#include <math.h>
#include <QString>

using namespace std;

int fila;
float vecM[5]; //Vector que almacena las masas en la tabla.
float vecC[5]; //Vector que almacena los calores específicos en la tabla.
float vecT[5]; //Vector que almacena las temperaturas iniciales en la tabla.
int filas;
int rowe; //Número de filas.
int col; //Número de columnas.

float vMasa[5]; //Vector que almacena las masas de los objetos.
float vCalor[5]; //Vector que almacena los calores específicos de los objetos.
float vTemperatura[5]; //Vector que almacena las temperaturas iniciales de los objetos.

QString nombresMateriales[] = {"Hierro", "Aluminio", "Plomo", "Cobre", "Plata", "Oro", "Otro", "----"}; //Vector que almacena los nombres de los materiales.
float caloresEspecificosMateriales[] = {448, 900, 128, 387, 234, 129}; //Vector que almacena los calores específicos de los materiales.
float puntoDeFusion[] = {1808, 660, 327.3f, 1083, 960.80f, 1063.00f}; //Vector que almacena el punto de fusión de los materiales.

int numeroDeElementos = sizeof(nombresMateriales) / sizeof(nombresMateriales[0]); //Determina el número de elementos del vector nombresMateriales.

string vMaterialesObjetos[5]; //Sirve para indicar que material se utilizo y mandarlo como argumento.

class Delegate : public QItemDelegate //Clase para validar solo la entrada de números en la tablewidget.
{
public:
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem & option,
                      const QModelIndex & index) const
    {
        QLineEdit *lineEdit = new QLineEdit(parent);
        //Set validator
        QDoubleValidator *validator = new QDoubleValidator(-39.5, 2000.0, 5, lineEdit);
        lineEdit->setValidator(validator);
        return lineEdit;
    }
};

variosObjetos::variosObjetos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::variosObjetos)
{
    ui->setupUi(this);

    this->move(QApplication::desktop()->availableGeometry().center() - this->rect().center()); //Establecer posición de la ventana en el centro.

    ui->txt_nObjetos->hide(); //Se esconde este txt (No se va a usar, solo es para validar).

    ui->sB_nObjetos->setRange(0,4); //Rango de valores que admite el qSpinBox del 1-5.

    for(int i=0; i<numeroDeElementos; i++){ //Este ciclo recorre el vector de lista de materiales y los añade al combobox para estos.
        ui->cB_Materiales->addItem(nombresMateriales[i]);
    }

    ui->cB_Materiales->setCurrentIndex(numeroDeElementos-1); //Se inicializa como "----" (ningún objeto seleccionado) siendo el indice de este el ultimo elemento.

    QList<QString> titulos; //Titulos de la tabla.
    titulos << "Masa kg" << "Calor específico J/kg·°C" << "Temperatura inicial °C";
    ui->tableWidget->setItemDelegate(new Delegate); //Validar solo entrada de numeros.
    ui->tableWidget->setColumnCount(3); //Se usaran tres columnas.
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setHorizontalHeaderLabels(titulos);

    ui->cB_Materiales->setEnabled(false); //Se inializa el combobox de la lista de materiales como deshabilitado.
}

variosObjetos::~variosObjetos()
{
    delete ui;
}

void variosObjetos::on_sB_nObjetos_valueChanged(const QString &arg1) //Función para seleccionar el número de objetos a tomar en cuenta para la simulación.
{

    while (ui->tableWidget->rowCount() > 0) //Este while elimina todos las filas de la qTableWidget.
    {
        ui->tableWidget->removeRow(0);
    }

    filas = ui->sB_nObjetos->value(); //Se obtiene numero de filas seleccionadas en el qSpinBox.

    for(int i=0; i<(int)(filas); i++){ //Esto genera las filas necesarias del qTableWidget.
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        fila = ui->tableWidget->rowCount()-1;
        ui->tableWidget->setItem(fila , MASA, new QTableWidgetItem(QString::number(vecM[i]))); //Muestra los items para vectores de masa.
        ui->tableWidget->setItem(fila , CALOR, new QTableWidgetItem(QString::number(vecC[i]))); //Muestra los items para vectores de calor específico.
        ui->tableWidget->setItem(fila , TEMPERATURA, new QTableWidgetItem(QString::number(vecT[i]))); //Muestra los items para vectores de temperatura inicial.
    }

}

void variosObjetos::on_cB_Materiales_activated(int index) //Función que inserta el calor especifico seleccionado en el qComboBox en la qTableWidget (solo segunda columna).
{

    for(int i=0; i<numeroDeElementos; i++){
        if(ui->cB_Materiales->currentIndex()==i){
            ui->tableWidget->setItem(rowe, col, new QTableWidgetItem(QString::number(caloresEspecificosMateriales[i])));
        }
    }

}

void variosObjetos::mostrarTipoDeObjeto(){ //Muestra el tipo de objeto verificando que si el valor del foco de la columna del calor especifico corresponde a un valor de un material del qComboBox.

    QTableWidgetItem* theItem = ui->tableWidget->item(rowe, col);

    for(int i=0; i<numeroDeElementos; i++){ //Iterador que umenta hasta alcanzar el número de elementos.

        if(theItem->text()!=(QString::number(caloresEspecificosMateriales[i]))){ //Si el valor de la casilla de calores específicos no concuerda con los de la lista, se muestra en el combobox el
            ui->cB_Materiales->setCurrentIndex(numeroDeElementos-2);             //tepenultimo elemento siendo este "Otro".
        }

    }

    for(int i=0; i<numeroDeElementos; i++){ //Iterador que umenta hasta alcanzar el número de elementos.

        if(theItem->text()==(QString::number(caloresEspecificosMateriales[i]))){ //Si el valor de la casilla de calores específicos concuerda con los de la lista, se muestra en el combobox el
            ui->cB_Materiales->setCurrentIndex(i);                               //el valor que corresponde al iterdador.
        }else if(theItem->text()=="0"){ //En caso de ser cero
            ui->cB_Materiales->setCurrentIndex(numeroDeElementos-1); //Se marcara el ultimo elemento de la lista que es: "----".
        }

    }

}

void variosObjetos::on_tableWidget_cellClicked(int row, int column) //Función que permite obtener el dato de la fila y columna clickeada en la qTableWidget (Habilita el qComboBox si se ha hecho click en un valor de a segunda columna).
{
    rowe = row;
    col = column;

    mostrarTipoDeObjeto();

    if(column==1){ //Si se ha marcado alguna casilla de la columna 1 se puede habilita el combobox de la lista de materiales para poder asignarle el calor específico de algún material de la lista en la casilla.
        ui->cB_Materiales->setEnabled(true);
    }else{
        ui->cB_Materiales->setEnabled(false); //Si es la casilla de otra fila se deshabilita el combobox de la lista de materiales.
        ui->cB_Materiales->setCurrentIndex(numeroDeElementos-1); //Se vuelve a inicializar como "----" (ningún objeto seleccionado).
    }

}

bool variosObjetos::validarDatos(){ //Función que valida algunos casos especiales.

    bool val=false; //Valor boleano que retorna la función.
    bool activarMensaje1=false; //Flag de validación masas.
    bool activarMensaje2=false; //Flag de validación calores específicos.

    for(int i=0; i<filas; i++){ //Recorre las filas de las tabla columna cero, para asegurarse de que no se coloque una masa con valor cero o negativa y activa un flag.
        if(ui->tableWidget->item(i, 0)->text().toFloat()<=0){
            activarMensaje1=true;
        }
        if(ui->tableWidget->item(i, 1)->text().toFloat()<=0){ //Recorre las filas de las tabla columna cero, para asegurarse de que no se coloque un calor específico con valor cero o negativa y activa un flag.
            activarMensaje2=true;
        }
    }

    if(ui->sB_nObjetos->value()<2){ //No permite seleccionar menos de 2 filas al momento de calcular (botón).
        QMessageBox::information(this, tr("¡ALERTA!"), tr("Debe seleccionar un número de 2 objetos mínimo para comenzar la simulación."));
        val=true;
    }

    if(activarMensaje1==true){ //Mensaje a mostrar si Flag de masa es negativa o cero.
        QMessageBox::information(this, tr("¡ALERTA!"), tr("No se puede colocar el valor de 0 kg o negativos para las masas."));
        val=true;
    }
    if(activarMensaje2==true){ //Mensaje a mostrar si Flag de calor específico es negativa o cero.
        QMessageBox::information(this, tr("¡ALERTA!"), tr("No se puede colocar el valor de 0 J/kg·°C o negativos para los calores especificos."));
        val=true;
    }

    activarMensaje1=false; //Se resetea a false el flag.
    activarMensaje2=false; //Se resetea a false el flag.

    return val; //Retorna un boleano de true si hay una excepción (se activo una validación).

}

void variosObjetos::asignarMateriales(){

    bool mostrar_msj=false; //Flag para mostrar un mensaje validación de temperaturas.

    for(int i=0; i<filas; i++){ //Este for recorre las filas.

        QTableWidgetItem* theItem = ui->tableWidget->item(i, 1);

        for(int j=0; j<(numeroDeElementos-2); j++){ //Este for analiza todos los elementos (lista de materiales) para chequear el calor especifico, si no esta en ningún elemento del vector se establece como "Desconocido".
            if(theItem->text()!=QString::number(caloresEspecificosMateriales[j])){
                vMaterialesObjetos[i] = "Desconocido";
            }
        }
    }

    for(int i=0; i<filas; i++){ //Este for recorre las filas.

        QTableWidgetItem* theItem = ui->tableWidget->item(i, 1);

        for(int j=0; j<(numeroDeElementos-2); j++){ //Este for analiza todos los elementos (lista de materiales) para chequear el calor especifico, si lo reconoce guarda el nombre del meterial en el vector vMaterialesObjetos.
            if(theItem->text()==QString::number(caloresEspecificosMateriales[j])){
                vMaterialesObjetos[i] = nombresMateriales[j].toStdString();
                if((vTemperatura[i])>=(puntoDeFusion[j])){ //Esta condición activara un flag, que indicara si se ha puesto una temperatura mayor que el punto de fusión de un material.
                    mostrar_msj=true;
                    break;
                }
            }
        }
    }

    if(mostrar_msj==true){ //Mensaje que se mostrara si se activo el flag.
        QMessageBox::information(this, tr("¡ALERTA!"), tr("Aquí no se consideran cambios de fase, dados los valores de temperatura introducidos, la simulación no será exacta."));
    }

}

void variosObjetos::on_btn_Regresar_clicked()
{
    this->close(); //Se cierra esta ventana.

    MainWindow *mW;
    mW = new MainWindow(this);
    mW->show(); //Abre la ventana de inicio.
}

void variosObjetos::on_btn_Calcular_clicked() //Función para mandar los parametros al ejecutable de OpenGL.
{

    string argumento = "";
    stringstream concatenador;

    for(int i=0; i<filas; i++){ //Llena el vector de masa con los valores de la tabla (columna 0, hasta n filas).
        QTableWidgetItem* theItem = ui->tableWidget->item(i, 0);
        float valor = theItem->text().toFloat();
        vMasa[i]= valor;
    }
    for(int i=0; i<filas; i++){ //Llena el vector de calor específico con los valores de la tabla (columna 1, hasta n filas).
        QTableWidgetItem* theItem = ui->tableWidget->item(i, 1);
        float valor = theItem->text().toFloat();
        vCalor[i]= valor;
    }
    for(int i=0; i<filas; i++){ //Llena el vector de temperatura inicial con los valores de la tabla (columna 2, hasta n filas).
        QTableWidgetItem* theItem = ui->tableWidget->item(i, 2);
        float valor = theItem->text().toFloat();
        vTemperatura[i]= valor;
    }

    asignarMateriales();

    if(validarDatos()!=true){

        //Concatenamos el nombre del ejectuble de OpenGL y los datos de forma ordenada en una variable llamada concatenador.

        concatenador << "Animacion.exe " << " " << 1 << " " << filas;

        for (int i=0; i<filas; i++) { //Dependiendo del número de filas, se concateran los valores fundamentales aumentando el iterador para mover posiciones del vector.

            concatenador << " " << vMasa[i] << " " << vCalor[i] << " " << vTemperatura[i] << " " << vMaterialesObjetos[i];
        }

        argumento = concatenador.str();

        //Creamos un puntero llamado c que contendra la dirreción de concatenador.

        const char *c = argumento.c_str();

        //Se imprimen los datos en el Application Output para verificar que todo este en orden.

        cout << c <<endl;

        //Mandamos los datos de concatenador y esto abrira el ejecutable de OpenGl.

        system(c);

    }

}
