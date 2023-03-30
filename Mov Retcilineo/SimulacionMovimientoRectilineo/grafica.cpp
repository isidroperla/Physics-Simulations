#include "grafica.h"
#include "ui_grafica.h"
#include <math.h>

double new_h=0.1;
double new_r=0.2;
double new_obj=1;
double x_0;
double y_0;
double A;
double B;
double s;
double tmax;
const double g = 9.8;
double acm;
double theta;
double tMod;
double w;
double t=0;

double vecX[10000];
double vecY[10000];

int fila;

Grafica::Grafica(double h, double r, int obj, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Grafica)
{
    ui->setupUi(this);


    QList<QString> titulos;
    titulos << "Tiempo 't'" << "Desplazamiento 'm'";
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setHorizontalHeaderLabels(titulos);

    new_h = h;
    new_r = r;
    new_obj = obj;

    theta = asin(abs(new_h/new_r));

    if(new_obj==1){
        acm = (0.7143)*g*sin(theta);
        w= (sqrt((2*new_r)/acm));
    }else if(new_obj==2){
        acm = (0.6667)*g*sin(theta);
        w= (sqrt((2*new_r)/acm));
    }else if(new_obj==3){
        acm = g*sin(theta);
        w= (sqrt((2*new_r)/acm));
    }

    tmax = w;

    ui->label->setText("x = (1/2)("+QString::number(acm)+"m/s<sup>2</sup>)t<sup>2</sup>");
    ui->label->setAlignment(Qt::AlignCenter);

    Grafica::makePlot();

    for(int i=0; i<(int)(tmax*100 +1); i++){
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        fila = ui->tableWidget->rowCount()-1;
        ui->tableWidget->setItem(fila , TIEMPO, new QTableWidgetItem(QString::number(vecX[i])));
        ui->tableWidget->setItem(fila , DISTANCIA, new QTableWidgetItem(QString::number(vecY[i])));
    }

}

Grafica::~Grafica()
{
    delete ui;
}

void Grafica::makePlot()
{

    QVector<double> x(10000), y(10000); // initialize with entries 0..100

        t=0;

        for (int i=0; i<(tmax*100 +10); i+=1)
        {

            if(t>=tmax){
                break;
            }else{

                s = (0.5)*acm*pow(t,2);

                x[i] = t; // x goes from -1 to 1
                y[i] = s; // let's plot a quadratic function

                vecX[i] = x[i];
                vecY[i] = y[i];

                // create graph and assign data to it:
                ui->customPlot->addGraph();
                ui->customPlot->graph(0)->setData(x, y);
                // give the axes some labels:
                ui->customPlot->xAxis->setLabel("Tiempo 's'");
                ui->customPlot->yAxis->setLabel("Desplazamiento 'm'");
                // set axes ranges, so we see all data:
                ui->customPlot->xAxis->setRange(0, tmax);
                ui->customPlot->yAxis->setRange(0, new_r);
                ui->customPlot->replot();

                t = t + 0.01;

                }
        }

}
