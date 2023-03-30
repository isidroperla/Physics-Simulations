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

private slots:

    void on_btn_opc_longitud_clicked();

    void on_btn_opc_incertidumbre_clicked();

    void on_btn_opc_notacion_clicked();

    void on_btn_opc_masa_clicked();

    void on_btn_opc_velocidad_clicked();

    void on_btn_opc_precision_clicked();

    void on_btn_cerrar_clicked();

protected:
    virtual void resizeEvent(QResizeEvent *evt);

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
