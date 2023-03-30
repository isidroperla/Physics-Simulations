#ifndef GRAFICA_H
#define GRAFICA_H
#include <QDialog>
#include <QMessageBox>

namespace Ui {
class Grafica;
}

class Grafica : public QDialog
{
    Q_OBJECT

public:
    explicit Grafica(double h, double r, int obj, QWidget *parent = nullptr);
    ~Grafica();

private slots:
    void makePlot();

private:
    Ui::Grafica *ui;

    enum Columna
    {
      TIEMPO, DISTANCIA
    };

};

#endif // GRAFICA_H
