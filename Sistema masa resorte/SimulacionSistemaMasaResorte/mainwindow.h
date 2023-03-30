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
    double temp=0;
    ~MainWindow();
    void UpdateLabel(const QString text);

public slots:
    void activar_reinicio();

private slots:
    void varCustomSlot(float, float, float, float, QString, bool);

    void on_sB_masa_valueChanged(const QString &arg1);

    void on_sB_k_valueChanged(const QString &arg1);

    void on_sB_b_valueChanged(const QString &arg1);

    void on_cB_tiempo_currentIndexChanged(int index);

    void on_btn_pausar_clicked();

    void on_check_opc_stateChanged(int arg1);

    void on_btn_reiniciar_pressed();

signals:
    void varCustomSignal(float, float, float, float);

public:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
