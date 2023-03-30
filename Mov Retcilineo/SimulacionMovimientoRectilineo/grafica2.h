#ifndef GRAFICA2_H
#define GRAFICA2_H

#include <QDialog>

namespace Ui {
class Grafica2;
}

class Grafica2 : public QDialog
{
    Q_OBJECT

public:
    explicit Grafica2(double h, double r, int obj, QWidget *parent = nullptr);
    ~Grafica2();

private slots:
    void makePlot();
private:
    Ui::Grafica2 *ui;

    enum Columna
    {
      TIEMPO, DISTANCIA
    };

};

#endif // GRAFICA2_H
