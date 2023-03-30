#ifndef CONVERSIONLONGITUD_H
#define CONVERSIONLONGITUD_H

#include <QDialog>

namespace Ui {
class ConversionLongitud;
}

class ConversionLongitud : public QDialog
{
    Q_OBJECT

public:
    explicit ConversionLongitud(QWidget *parent = nullptr);
    ~ConversionLongitud();

    void dibujarRegla(int x, int y, int w, int h, QString unidad, int opc);

    void mostrarObjeto(QString ruta_objeto);

    void seleccionador(int posVectorial);

    void actualizarBotones();

private slots:

    void on_btn_l_obj1_clicked();

    void on_btn_l_obj2_clicked();

    void on_btn_l_obj3_clicked();

    void on_btn_l_obj4_clicked();

    void on_btn_regla1_clicked();

    void on_btn_regla2_clicked();

    void on_btn_regla3_clicked();

    void on_btn_regla4_clicked();

    void on_btn_regla5_clicked();

    void on_btn_volver_clicked();

    void on_btn_convertir_long1_clicked();

    void on_btn_convertir_long2_clicked();

private:
    Ui::ConversionLongitud *ui;
};

#endif // CONVERSIONLONGITUD_H
