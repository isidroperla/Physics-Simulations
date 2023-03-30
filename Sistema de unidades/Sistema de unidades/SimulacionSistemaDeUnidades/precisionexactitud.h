#ifndef PRECISIONEXACTITUD_H
#define PRECISIONEXACTITUD_H

#include <QDialog>
#include <QMouseEvent>

namespace Ui {
class PrecisionExactitud;
}

class PrecisionExactitud : public QDialog
{
    Q_OBJECT

public:
    explicit PrecisionExactitud(QWidget *parent = nullptr);
    ~PrecisionExactitud();

private slots:

    void on_btn_verificar_exactitud_clicked();

    void on_btn_verificar_precision_clicked();

    void on_btn_volver_clicked();

protected:
    //virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

private:
    Ui::PrecisionExactitud *ui;
};

#endif // PRECISIONEXACTITUD_H
