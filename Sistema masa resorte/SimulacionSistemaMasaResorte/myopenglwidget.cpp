#include "myopenglwidget.h"
#include <GL/gl.h>
#include <QDebug>
#include <math.h>
#include <QMouseEvent>
#include <mainwindow.h>
#include <QTimer>

float xM=0; //Posición en x del puntero del mouse.
float yM=0; //Posición en y del puntero del mouse.
float w=0; //Variable que guarda el ancho del OpenGL widget.
float h=0; //Variable que guarda el alto del OpenGL widget.

float m=20; //Masa.
float k=20; //Constante del resorte.
float vx=0; //Velocidad en x.
float ax=0; //Aceleración en x.
float phi=0; //Angulo phi.

float A=0; //Amplitud.
float b=0; //Fuerza restauradora.

float xP=0; //Posición de la masa
float xT=0; //Velocidad conque transcure el tiempo de la animación.

bool m_is_dragging=false; //Variable boleaana que indica si se clickea el mouse.
bool act=false; //Flag si la animación fue activada o no.
bool drag=true; //Flag que si es true se permite mover la masa, de ser false ya no se detectara el drag con el mouse.
bool pausar_animacion=false; //Flag que en el caso de ser true pausa la animación, de ser false se reanudará.
bool reiniciarSimulacion=false; //Flag que en el caso de ser true se reiniciara la simulación en una codición, de ser false no hará nada.
QString tipo_de_movimiento; //Almacena el nombre del tipo de movimiento de la simulación determinado con unas condiciones.
bool animacion_activada=false; //Flag que es true si la animación esta en cuso y false si no se esta realizando la animación.
int opcion=1; //Variable que guarda un entero para definir dos casos: 1 si no se toma en cuenta el valor de b, 2 si se toma en cuenta el valor de b.

MyOpenGLWidget::MyOpenGLWidget(float m_sB, float k_sB, float b_sB, float t_cB, bool pausar, bool reiniciar, int opc, QWidget *parent)
    : QOpenGLWidget {parent}
{
    //Se almacenan en las variables globales los correspondientes valores recibidos por el contructor desde la clase MainWindow.
    m=m_sB;
    k=k_sB;
    b=b_sB;
    xT=t_cB;
    pausar_animacion=pausar;
    opcion = opc;
    reiniciarSimulacion=reiniciar;

    if(pausar_animacion==false){ //Si no se ha pausado la animación, todos los timers trabajaran normalmente.
        QTimer *actualizarPantalla = new QTimer(this); //Timer que actualiza la escena.
        connect(actualizarPantalla, SIGNAL(timeout()), this, SLOT(update()));
        actualizarPantalla->start(50); //Se actualiza cada 50 milisegundos.

        QTimer *cronometro=new QTimer(this); //Timer para incrementar el valor de t (la variable del tiempo utilizada en los calculos).
        connect(cronometro, SIGNAL(timeout()), this, SLOT(funcionActivacionTimer()));
        cronometro->start(50); //Se actualiza cada 50 milisegundos.

        QTimer *enviar; //Timer para actualizar las variables que se envian a la clase MainWindow para imprimirlas en los label.
        enviar = new QTimer;
        enviar->start(50);
        connect(enviar, SIGNAL(timeout()), this, SLOT(enviarVariables())); //Se actualiza cada 50 milisegundos.

    }
}

void MyOpenGLWidget::enviarVariables() //Esta función es la que se encarga de mandar el valor de posición, velocidad en x, aceleración en x, tiempo y un flag si la animación esta en curso a la clase MainWindow, para posteriormente imprimirlos con los labels.
{
    emit varCustomSignal(xP, vx, ax,t, tipo_de_movimiento, animacion_activada);
}

void MyOpenGLWidget::reiniciarAnimacion(void){ //Esta función se encaega de reiniciar las variables, para así reiniciar completamente la simulación.
    xM=0;
    yM=0;
    vx=0;
    ax=0;
    phi=0;
    t=0;
    A=0;
    xP=0;
    m_is_dragging=false;
    act=false;
    drag=true;
    pausar_animacion=false;
    animacion_activada=false;
}

void MyOpenGLWidget::funcionActivacionTimer(){ //Está es la función que se encarga de incrementar la variable que control el tiempo (t), y también controlar la velocidad en que este transcurre.
    if(pausar_animacion==false){
        if(t<=60 && m_is_dragging==false && act==true){ //El timer terminara llegado a los 60 s.
            animacion_activada=true;
            t+=(0.05f/xT); //Controla la velocidad del timer con la variable xT que divide el valor de 0.05f. (Si es entre 1 es tiempo real, sino se divide entre 10 o entre 100 dependiendo del valor de xT).
        }if(t==60){
            t=0;
            act=false;
        }
    }

    if(reiniciarSimulacion==true){ //Si el flag reiniciarSimulacion es true, se procede a llamar a la función reiniciarAnimacion() que reinicia todas las varibles.
        reiniciarAnimacion(); //Se colocó en esta función este llamado para manipular el valor de t que esta definido en MyOpenGLWidget.
    }
}

void MyOpenGLWidget::mousePressEvent(QMouseEvent *event){ //Función que detecta si se ha o esta clickeando el mouse (hace a esa variable true).

    if(animacion_activada==false){
        if(event->button() == Qt::LeftButton){ //Esta variable boleana se hace true si se mantiene apretado el click izquierdo del mouse.
            m_is_dragging = true; //Esta flag se hace true si se esta haciendo drag sobre el objeto.
            act=true;
        }
    }

}

void MyOpenGLWidget::mouseMoveEvent(QMouseEvent *event){ //Captura con la posición del mouse el valor de la amplitud.
    if(m_is_dragging==true){
        if(pausar_animacion==false){
            A=(event->pos().rx())*(1/w)-0.5f;
            if(A<=-0.3f){ //Limite izquierdo para la amplitud, (0.3f en la vista ortogonal sobre el eje x positivo).
                A=-0.3f;
            }else if(A>=0.3f){ //Limite derecho para la amplitud hasta 0.3f. (0.7f en la vista ortogonal sobre el eje x positivo).
                A=0.3f;
            }
        }
    }
}

void MyOpenGLWidget::mouseReleaseEvent(QMouseEvent *event){ //Función que detecta si se ha dejado clickear el mouse (hace a esa variable false).
    m_is_dragging = false; //Esta flag se hace false si se no se esta haciendo drag sobre el objeto.
}

void MyOpenGLWidget::initializeGL(){ //Función que incializa ciertas funciones, color de fondo, ancho de la ventana y altura de la ventana.
    initializeOpenGLFunctions();
    glClearColor(1,1,1,1);
    w = MyOpenGLWidget::width();
    h = MyOpenGLWidget::height();
}

void dibujoSuperficie(void){ //Función que dibuja la superficie donde esta conectado el resorte y también donde se desplaza la caja.

    glColor3f(0,0,0); //Color negro
    glBegin(GL_LINE_STRIP); //Aquí se conectan lineas para dibujar la superficie donde esta el sistema masa resorte.
    glVertex2f(0.001f,0.5f);
    glVertex2f(0.001f,0.3f);
    glVertex2f(1.0f,0.3f);
    glEnd();

}

void posicionDeEquilibrio(void){ //Función que dibuja la línea que indica cual es la posición de equilibrio del sistema.

    glColor3f(0,0,0); //Color negro.
    glBegin(GL_LINES);
    for(float i=0.025f; i<=1; i+=0.05f) //Aquí se dibuja las linea punteada vertical en el centro de la ventana.
    {
        glVertex2f(0.5f,i-0.025f);
        glVertex2f(0.5f,i);
    }
    glEnd();

}

void resorte(void){ //Función que dibuja y anima el resorte reescalandolo.
    glPushMatrix();
    if(m_is_dragging==true){ //Si se hace drag sobre el objeto, dependiendo donde lo mueva, así se resacalara el resorte.
        glScalef((xM-0.1f)/0.4f,1,0);
    }else if(m_is_dragging==false and act==true){ //Aquí se indica que si la animación ya empezo y no esta activado el dragm que dependa de los calculos de xP para su movimiento.
        glScalef((xP+0.4f)/0.4f,1,0);
    }

    glBegin(GL_LINE_STRIP); //Aquí se dibuja el resorte con un ciclo que aumenta una variable siguendo una ecuación senoidal.
    for(float i=0; i<0.4f; i+=0.005f){
        glVertex2f(i,(0.1f*sin(120*i))+0.4f);
    }
    glEnd();
    glPopMatrix();
}

void caja(float l, float x, float y){ //Función que dibuja el objeto (masa en forma de caja) que se va a desplazar.
    glPushMatrix();
    glTranslatef(x,y,0);
    if(m_is_dragging==true){ //Si se hace drag sobre el objeto seguira el mouse (hay limites establecidos para esto).
        glTranslatef(xM-0.5,0,0);
    }else if(m_is_dragging==false){ //Si se suelta el objeto ahora dependera del valor de xP porque la animación ya se ha activado.
        glTranslatef(xP,0,0);
    }
    glColor3f(1,0,0); //Color rojo.
    glBegin(GL_POLYGON); //Aquí se dibuja el resorte.
    glVertex2f((-l/2),(l/2));
    glVertex2f((-l/2),(-l/2));
    glVertex2f((l/2),(-l/2));
    glVertex2f((l/2),(l/2));
    glEnd();
    glPopMatrix();
}

void vectores(float xPos, float y, char opc, float r, float g, float b){ //Función que diubuja y reescala los vectores de posición de la velocidad y aceleración en x.

    float lon=0; //Variable que almacena los calculos de la longitud para dibujar el vector.
    float sign=0; //Variable que almacena (vx o ax) dependiendo de la que se le pase como parametro, lo que interesa más que todo el simbolo.

    switch(opc){
        case 'v': //Si se recibe como 'v' en los parametros se indica que se dibujara el vector de la velocidad.
        lon= (((0.1f*vx)/(sqrt(k/m)*abs(A)))+0.50f); //Calculo de la longitud (se reescala).
        sign = vx; //La variable sign almacena el valor de vx (lo que interesa de esto es el simbolo).
        break;
        case 'a': //Si se recibe como 'a' en los parametros se indica que se dibujara el vector de la aceleración.
        lon= (((0.1f*ax)/((k/m)*abs(A)))+0.50f); //Calculo de la longitud (se reescala).
        sign = ax;  //La variable sign almacena el valor de ax (lo que interesa de esto es el simbolo).
        break;
    }

    if(m_is_dragging==false && act==true){ //Condición que decta si no hace drag y la animación está activada para que se puedan realizar las siguientes instrucciones.

        glPushMatrix();
        glTranslatef(xPos,0,0); //Se traslada el vector con xP
        glColor3f(r,g,b); //Se establece un color según los parametros recibidos (r,g,b).
        glBegin(GL_LINES);
        glVertex2f(0.50,y); //Se define un valor inicial para el vector (la altura se recibe en la función).
        glVertex2f(lon,y); //La variable lon reescala el vector.
        glEnd();

        if(sign<0){ //Si el valor de sign es negativo, la fleha apunta hacia la izquierda.
            glBegin(GL_TRIANGLES); //Aquí se dibuja el triangulo para la flecha y también se mueve dependiendo de la variable lon.
            glVertex2f(lon-0.02f,y);
            glVertex2f(lon,(y+0.02f));
            glVertex2f(lon,(y-0.02f));
            glEnd();
        }else if(sign>0){ //Si el valor de sign es positivo se apunta hacia la derecha.
            glBegin(GL_TRIANGLES); //Aquí se dibuja el triangulo para la flecha y también se mueve dependiendo de la variable lon.
            glVertex2f((lon+0.02f),y);
            glVertex2f(lon,(y+0.02f));
            glVertex2f(lon,(y-0.02f));
            glEnd();
        }
        glPopMatrix();

    }
}

void MyOpenGLWidget::calculos(){ //Función que se encarga de realizar los calculos para la simulación (xP,ax,vx).

    if(A<0){
        phi = M_PI; //Se define a phi con el valor de pi si se suelta la masa a la izquierda del punto de equilibrio.
    }else if(A>0){
        phi = 0; //Se define a phi como 0 si se suelta la masa a la derecha del punto de equilibrio.
    }

    switch(opcion){
        case 1: //Caso en que no se toma en cuenta la fuerza restauradora.
            xP = abs(A)*cos(sqrt((k/m))*t+phi); //Posición de la masa.
            vx = -sqrt(k/m)*abs(A)*sin(sqrt(k/m)*t+phi); //Velocidad en x.
            ax = -(k/m)*abs(A)*cos(sqrt(k/m)*t+phi); //Aceleración en x.
        break;

        case 2: //Caso en que se toma en cuenta la fuerza restauradora.
            if(pow((b/2*m),2)>(k/m)){
                xP = (A)*exp(-((b/2*m)-sqrt(pow((b/2*m),2)-(k/m)))*t); //Posición de la masa.
                vx = -((b/2*m)-sqrt(pow((b/2*m),2)-(k/m)))*(A)*exp(-((b/2*m)-sqrt(pow((b/2*m),2)-(k/m)))*t); //Velocidad en x.
                ax = pow(((b/2*m)-sqrt((pow((b/2*m),2)-(k/m)))),2)*(A)*exp(-((b/2*m)-sqrt(pow((b/2*m),2)-(k/m)))*t); //Aceleración en x.
            }else{
                xP = (abs(A)*exp(-(b/2*m)*t))*(cos(sqrt((k/m)-pow((b/2*m),2))*t + phi)); //Posición de la masa.
                vx = ((-sqrt((k/m)-pow((b/2*m),2)))*(abs(A)*exp(-(b/2*m)*t))*sin(sqrt((k/m)-pow((b/2*m),2))*t+phi)) - ((b/2*m)*(abs(A)*exp(-(b/2*m)*t)))*cos(sqrt((k/m)-pow((b/2*m),2))*t + phi); //Velocidad en x.
                ax = (-((k/m)-pow((b/2*m),2))*abs(A)*exp(-(b/2*m)*t)) * (cos(sqrt((k/m)-pow((b/2*m),2))*t+phi) + (b/m)*sqrt((k/m)-pow((b/2*m),2))*abs(A)*exp(-(b/2*m)*t)*sin(sqrt((k/m)-pow((b/2*m),2))*t+phi)) + ((pow(b,2)/4*pow(m,2))*abs(A)*exp(-(b/2*m)*t)*cos(sqrt((k/m)-pow((b/2*m),2))*t+phi)); //Aceleración en x.
            }
        break;
    }

}

void tipoDeMovimiento(){ //Función que describe el tipo de movimiento almacenando en una variable llamada tipo_de_movimiento dependiendo de si se cumplen ciertas condiciones.
    if(b==0){
        tipo_de_movimiento = "Oscilador armónico simple";
    }else if(pow((b/2*m),2)<(k/m)){
        tipo_de_movimiento = "Oscilador amortiguado";
    }
    else if(pow((b/2*m),2)==(k/m)){
        tipo_de_movimiento = "Movimiento críticamente amortiguado";
    }
    else if(pow((b/2*m),2)>(k/m)){
        tipo_de_movimiento = "Movimiento sobreamortiguado";
    }
}

void MyOpenGLWidget::paintGL(){ //Función que dibuja y anima todas las funciones de la animación.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    tipoDeMovimiento(); //Se llama al función que guarda el nombre del tipo de movimiento que presenta en la animación.

    if(pausar_animacion==false){
        QPoint p = mapFromGlobal(QCursor::pos());
        xM = (p.rx())*(1/w); //Se ontiene la posición en X del cursor y se convierte a coordenadas ortogonales.
        yM = ((p.ry())*(20/h) -10)-8; //Se ontiene la posición en Y del cursor y se convierte a coordenadas ortogonales.

        if(xM<=0.2f){ //Limites de lectura para xM en el eje x minimo.
            xM=0.2f;
        }else if(xM>=0.8f){ //Limites de lectura para xM en el eje x maximo.
            xM=0.8f;
        }

        calculos(); //Función que realiza los calculos de la simulación.
    }

    vectores(xP, 0.6f, 'v', 0, 0, 1); //Se llama a la función vectores para que dibuje el vector de velocidad (se le indica 'v' puesto que será de velocidad), (color azul).
    vectores(xP, 0.2f, 'a', 1, 0.33f, 0); //Se llama a la función vectores para que dibuje el vector de velocidad (se le indica 'a' puesto que será de aceleración) (color naranja).

    dibujoSuperficie(); //Se llama a la función que dibuja la superficie donde esta el sistema de masa resorte.

    resorte(); //Se llama a la función que dibuja y anima el resorte.

    caja(0.2f,0.5f,0.4f); //Función que dibuja y desplaza la caja.

    posicionDeEquilibrio(); //Función que dibuja las lineas del punto de equilibrio.

}

void MyOpenGLWidget::resizeGL(int w, int h){ //Función que define los modos de pantalla y la vista ortogonal.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1, 0, 1, 0, 1);
}
