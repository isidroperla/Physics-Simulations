#ifndef OBJETOSSUMERGIDOSENLIQUIDOS_H
#define OBJETOSSUMERGIDOSENLIQUIDOS_H

#include <QDialog>

namespace Ui {
class objetosSumergidosEnLiquidos;
}

class objetosSumergidosEnLiquidos : public QDialog
{
    Q_OBJECT

public:
    explicit objetosSumergidosEnLiquidos(QWidget *parent = nullptr);
    ~objetosSumergidosEnLiquidos();

private slots:
    void on_btn_Calcular_clicked();

    void cambiosDeFase(float tObj, float tFl);

    bool validarDatos(float mObj, float cObj, float mFl, float cFl);

    void on_txt_c_Obj_textEdited(const QString &arg1);

    void on_txt_c_Fl_textEdited(const QString &arg1);

    void on_cB_Materiales_currentIndexChanged(int index);

    void on_cB_Fluidos_currentIndexChanged(int index);

    void on_btn_Regresar_clicked();

private:
    Ui::objetosSumergidosEnLiquidos *ui;
};

#endif // OBJETOSSUMERGIDOSENLIQUIDOS_H
