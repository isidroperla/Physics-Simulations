#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    Ui::MainWindow *ui;
private slots:
    void on_sB_diametro1_valueChanged(const QString &arg1);
    void on_sB_diametro2_valueChanged(const QString &arg1);
};

#endif // MAINWINDOW_H
