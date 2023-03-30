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

    void on_btn_Opc1_clicked();

    void on_btn_Opc2_clicked();

private:
    Ui::MainWindow *ui;

    enum Columna
    {
      MASA, CALOR, TEMPERATURA
    };

protected:
    virtual void resizeEvent(QResizeEvent *evt);

};

#endif // MAINWINDOW_H
