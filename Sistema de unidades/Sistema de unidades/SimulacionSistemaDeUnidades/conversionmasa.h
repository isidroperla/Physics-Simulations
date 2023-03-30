#ifndef CONVERSIONMASA_H
#define CONVERSIONMASA_H

#include <QDialog>

namespace Ui {
class ConversionMasa;
}

class ConversionMasa : public QDialog
{
    Q_OBJECT

public:
    explicit ConversionMasa(QWidget *parent = nullptr);
    ~ConversionMasa();
    void mostrarMasa(QString ruta_masa);
    void actualizar();

private slots:
    void on_btn_m_obj1_clicked();

    void on_btn_m_obj2_clicked();

    void on_btn_m_obj3_clicked();

    void on_btn_m_obj4_clicked();

    void on_btn_m_obj5_clicked();

    void on_rB_g_clicked();

    void on_rB_kg_clicked();

    void on_rB_oz_clicked();

    void on_cB_conversiones_masa_currentIndexChanged(int index);

    void on_btn_convertir_masa_clicked();

    void on_btn_volver_clicked();

private:
    Ui::ConversionMasa *ui;
};

#endif // CONVERSIONMASA_H
