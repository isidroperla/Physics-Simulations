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
    void on_cB_Fluidos_activated(int index);
    void on_txt_DensidadFluido_textEdited(const QString &arg1);
    void on_txt_Viscosidad_textEdited(const QString &arg1);
    void on_btn_Calcular_clicked();
    void on_cB_opcDetenerse_clicked();
};

#endif // MAINWINDOW_H
