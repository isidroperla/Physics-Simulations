#ifndef CONVERSION_H
#define CONVERSION_H

#include <QDialog>

namespace Ui {
class Conversion;
}

class Conversion : public QDialog
{
    Q_OBJECT

public:
    explicit Conversion(QString val_conv, QString val_numerador, QString unid_numerador, QString val_denominador, QString unid_denominador, QWidget *parent = nullptr);
    ~Conversion();

private slots:
    void on_tabWidget_currentChanged(int index);

private:
    Ui::Conversion *ui;
};

#endif // CONVERSION_H
