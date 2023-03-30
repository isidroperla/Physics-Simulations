#include "grafica2.h"
#include "ui_grafica2.h"

double new_h2=0.1;
double new_r2=0.2;
double new_obj2=1;
double x_02;
double y_02;
double A2;
double B2;
double s2;
double tmax2;
const double g2 = 9.8;
double acm2;
double theta2;
double tMod2;
double w2;
double t2=02;

double vecX2[10000];
double vecY2[10000];

int fila2;

Grafica2::Grafica2(double h, double r, int obj, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Grafica2)
{
    ui->setupUi(this);

    QList<QString> titulos;
    titulos << "Tiempo 't'" << "Velocidad 'm/s'";
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setHorizontalHeaderLabels(titulos);

    new_h2 = h;
    new_r2 = r;
    new_obj2 = obj;

    theta2 = asin(abs(new_h2/new_r2));

    if(new_obj2==1){
        acm2 = (0.7143)*g2*sin(theta2);
        w2= (sqrt((2*new_r2)/acm2));
    }else if(new_obj2==2){
        acm2 = (0.6667)*g2*sin(theta2);
        w2= (sqrt((2*new_r2)/acm2));
    }else if(new_obj2==3){
        acm2 = g2*sin(theta2);
        w2= (sqrt((2*new_r2)/acm2));
    }

    tmax2 = w2;

    ui->label->setText("v = ("+QString::number(acm2)+"m/s<sup>2</sup>)t");
    ui->label->setAlignment(Qt::AlignCenter);

    Grafica2::makePlot();

    for(int i=0; i<(int)(tmax2*100 +1); i++){
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        fila2 = ui->tableWidget->rowCount()-1;
        ui->tableWidget->setItem(fila2 , TIEMPO, new QTableWidgetItem(QString::number(vecX2[i])));
        ui->tableWidget->setItem(fila2 , DISTANCIA, new QTableWidgetItem(QString::number(vecY2[i])));
    }

}

Grafica2::~Grafica2()
{
    delete ui;
}

void Grafica2::makePlot()
{

    QVector<double> x(10000), y(10000); // initialize with entries 0..100

        t2=0;

        for (int i=0; i<(tmax2*100 +10); i+=1)
        {

            if(t2>=tmax2){
                break;
            }else{

                s2 = (0.5)*acm2*pow(t2,2);

                x[i] = t2; // x goes from -1 to 1
                y[i] = (acm2*t2); // let's plot a quadratic function

                vecX2[i] = x[i];
                vecY2[i] = y[i];

                // create graph and assign data to it:
                ui->customPlot->addGraph();
                ui->customPlot->graph(0)->setData(x, y);
                // give the axes some labels:
                ui->customPlot->xAxis->setLabel("Tiempo 's'");
                ui->customPlot->yAxis->setLabel("Velocidad centro de masa 'm/s'");
                // set axes ranges, so we see all data:
                ui->customPlot->xAxis->setRange(0, tmax2);
                ui->customPlot->yAxis->setRange(0, (acm2*tmax2));
                ui->customPlot->replot();

                t2 = t2 + 0.01;

                }
        }

}
