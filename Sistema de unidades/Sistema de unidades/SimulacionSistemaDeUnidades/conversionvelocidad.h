#ifndef CONVERSIONVELOCIDAD_H
#define CONVERSIONVELOCIDAD_H

#include <QDialog>
#include <qcgaugewidget.h>

namespace Ui {
class ConversionVelocidad;
}

class ConversionVelocidad : public QDialog
{
    Q_OBJECT

public:
    explicit ConversionVelocidad(QWidget *parent = nullptr);
    ~ConversionVelocidad();
    void velocimetro();

private slots:
    void on_cB_conversiones_velocidad_currentIndexChanged(int index);

    void on_vS_control_velocidad_sliderMoved(int position);


    void on_rB_v_km_clicked();

    void on_rB_v_m_clicked();

    void on_rB_v_millas_clicked();

    void on_btn_convertir_velocidad_clicked();

    void on_btn_volver_clicked();

private:
    Ui::ConversionVelocidad *ui;

    QcGaugeWidget * mSpeedGauge;
    QcNeedleItem *mSpeedNeedle;
};

#endif // CONVERSIONVELOCIDAD_H
