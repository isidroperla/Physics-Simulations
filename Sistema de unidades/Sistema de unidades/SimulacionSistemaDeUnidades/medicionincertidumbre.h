#ifndef MEDICIONINCERTIDUMBRE_H
#define MEDICIONINCERTIDUMBRE_H

#include <QDialog>
#include <QMouseEvent>

namespace Ui {
class MedicionIncertidumbre;
}

class MedicionIncertidumbre : public QDialog
{
    Q_OBJECT

public:
    explicit MedicionIncertidumbre(QWidget *parent = nullptr);
    ~MedicionIncertidumbre();
    void dibujarRegla(int x, int y, int w, int h, int opc);
    void mostrarObjeto(float posY, float w, float h, QString ruta_objeto);

private slots:
    void on_rB_md_1cm_clicked();

    void on_rB_md_01cm_clicked();

    void on_btn_medir_clicked();

    void on_btn_i_obj1_clicked();

    void on_btn_i_obj2_clicked();

    void on_btn_i_obj3_clicked();

    void on_btn_volver_clicked();

protected:
    //virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

private:
    Ui::MedicionIncertidumbre *ui;
};

#endif // MEDICIONINCERTIDUMBRE_H
