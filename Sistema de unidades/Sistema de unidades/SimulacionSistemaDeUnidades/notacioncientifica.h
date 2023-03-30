#ifndef NOTACIONCIENTIFICA_H
#define NOTACIONCIENTIFICA_H

#include <QDialog>

namespace Ui {
class NotacionCientifica;
}

class NotacionCientifica : public QDialog
{
    Q_OBJECT

public:
    explicit NotacionCientifica(QWidget *parent = nullptr);
    ~NotacionCientifica();

private slots:

    void on_btn_random_clicked();

    void on_btn_calcular_clicked();

    void on_btn_revisar_clicked();

    void on_btn_volver_clicked();

private:
    Ui::NotacionCientifica *ui;
};

#endif // NOTACIONCIENTIFICA_H
