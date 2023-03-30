#ifndef UNIFORME_H
#define UNIFORME_H

#include <QDialog>

namespace Ui {
class Uniforme;
}

class Uniforme : public QDialog
{
    Q_OBJECT

public:
    explicit Uniforme(QWidget *parent = nullptr);
    ~Uniforme();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_cbHabilitar_clicked();

private:
    Ui::Uniforme *ui;
};

#endif // UNIFORME_H
