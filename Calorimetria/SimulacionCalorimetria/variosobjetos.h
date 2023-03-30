#ifndef VARIOSOBJETOS_H
#define VARIOSOBJETOS_H

#include <QDialog>

namespace Ui {
class variosObjetos;
}

class variosObjetos : public QDialog
{
    Q_OBJECT

public:
    explicit variosObjetos(QWidget *parent = nullptr);
    ~variosObjetos();

private slots:

    void mostrarTipoDeObjeto();

    bool validarDatos();

    void asignarMateriales();

    void on_tableWidget_cellClicked(int row, int column);

    void on_cB_Materiales_activated(int index);

    void on_sB_nObjetos_valueChanged(const QString &arg1);

    void on_btn_Calcular_clicked();

    void on_btn_Regresar_clicked();

private:
    Ui::variosObjetos *ui;

    enum Columna
    {
      MASA, CALOR, TEMPERATURA
    };

};

#endif // VARIOSOBJETOS_H
