#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <GL/gl.h>
#include <mainwindow.h>
#include <QObject>
#include <signal.h>

class MyOpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions
{
    Q_OBJECT
public:
    MyOpenGLWidget(float m_sB, float k_sB, float b_sB, float t_cB, bool pausar, bool reiniciar, int opc, QWidget *parent = nullptr);
    void calculos();
    double t = 0;

private slots:
    void enviarVariables();

signals:
    void varCustomSignal(float, float, float, float, QString, bool);

public slots:
    void funcionActivacionTimer();
    void reiniciarAnimacion();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
};

#endif // MYOPENGLWIDGET_H
