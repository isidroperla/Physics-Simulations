#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <GL/glut.h>

#include <QTimer>
#include <QMouseEvent>

#include <mainwindow.h>

class MyOpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions
{
    Q_OBJECT
public:
    MyOpenGLWidget(float diamtro1, float diamtro2, QWidget *parent = nullptr);
    float contador = 0;
    Ui::MainWindow *ui;

public slots:
    void funcionActivacionTimer();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    void toolTip(int dg);
};

#endif // MYOPENGLWIDGET_H
