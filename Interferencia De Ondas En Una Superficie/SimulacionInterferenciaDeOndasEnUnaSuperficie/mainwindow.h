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
    void on_pushButton_clicked();

    void on_pB_demo_clicked();

    void on_pB_demo_2_clicked();

    void on_pB_demo_3_clicked();

    void on_pushButton_2_clicked();

    void on_txt_K1_editingFinished();

    void on_txt_K2_editingFinished();

    void on_txt_W1_editingFinished();

    void on_txt_W2_editingFinished();

    void on_txt_T_editingFinished();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
