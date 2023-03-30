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

private:
    Ui::MainWindow *ui;

protected:
    virtual void resizeEvent(QResizeEvent *evt);
private slots:
    void on_sliderRadio_valueChanged(int value);
    void on_pushButton_clicked();
    void on_cb_objetos_currentTextChanged(const QString &arg1);
};

#endif // MAINWINDOW_H
