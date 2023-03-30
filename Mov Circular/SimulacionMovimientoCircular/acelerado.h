#ifndef ACELERADO_H
#define ACELERADO_H

#include <QDialog>

namespace Ui {
class acelerado;
}

class acelerado : public QDialog
{
    Q_OBJECT

public:
    explicit acelerado(QWidget *parent = nullptr);
    ~acelerado();

private slots:
    void on_pushButton_2_clicked();

    void on_cbHabilitar_clicked();

    void on_pushButton_clicked();

private:
    Ui::acelerado *ui;
};

#endif // ACELERADO_H
