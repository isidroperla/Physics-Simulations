#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "uniforme.h"
#include <acelerado.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_opcion1_clicked();

    void on_opcion2_clicked();

private:
    Ui::MainWindow *ui;
    Uniforme *uniforme;
    acelerado *ac;
};

#endif // MAINWINDOW_H
