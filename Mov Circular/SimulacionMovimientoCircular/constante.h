#ifndef CONSTANTE_H
#define CONSTANTE_H

#include <QDialog>

namespace Ui {
class constante;
}

class constante : public QDialog
{
    Q_OBJECT

public:
    explicit constante(QWidget *parent = nullptr);
    ~constante();

private:
    Ui::constante *ui;
};

#endif // CONSTANTE_H
