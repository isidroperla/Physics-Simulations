#include "myopenglwidget.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <math.h>
#include <QTimer>
#include <QMouseEvent>
#include <QMessageBox>
#include <QInputDialog>
#include <QToolTip>
#include "funcionesextraopengl.h"

using namespace std;

double xM=20; //Posión en x del mouse.
double yM=20; //Posición en y del mouse.

bool m_is_dragging=false; //Variable boleaana que indica si se clickea el mouse.

float dEmbolo1; //Diametro para el embolo1.
float dEmbolo2; //Diametro para el embolo2.

float m1=0; //Masa en el embolo1.
float m2=0; //Masa en el embolo2.

float P1=0; //Presión en el embolo1.
float F1=0; //Fuerza en el embolo1.
float A1=0; //Area del embolo1.

float P2=0; //Presión en el embolo2.
float F2=0; //Fuerza en el embolo2.
float A2=0; //Area en el embolo2.

const float g = 9.8; //Contante de la gravedad.

bool activar1=false; //Variable para activar la animación cuando hay un masa en el embolo1.
bool activar2=false; //Variable para activar la animación cuando hay un masa en el embolo2.

float w=0; //Variable que guarda el ancho del OpenGL widget.
float h=0; //Variable que guarda el alto del OpenGL widget.
int cont=0; //Almacena el mismo valor que el contador.

float m_obj1=0; //Masa en el embolo1.
float m_obj2=0; //Masa en el embolo2.

int dg=0; //Detecta si esta en la zona de drag para los objetos.
int dp=0; //Detecta si esta en la zona de drop para los objetos.

bool ir[5]; //Vector boleano que se activa si se clickeo en el are de drag.
bool ir2[5]; //Vector boleano que se activa si se clickeo en el are de drop.

struct estados{ //Estructura que guarda estados boleanos de los objetos y los embolos.
    bool drag;
    bool drop;
}obj[5], embolo1[5], embolo2[5];

void MyOpenGLWidget::funcionActivacionTimer(){

    cont = contador; //Se le da el valor del contador a cont.

    if(activar1==true || activar2==true){ //Si activa una embolo se procede a hacer la animación. (Se toma en cuenta hasta alcanzar ciertos limites para el dibujado el valor del contador).
        if(P1>P2 && contador>=-1.70){ //Si la presión sobre el embolo1 es mayor la del otro el contador disminuye en 0.1.
            contador-=0.1f;
        }else if(P2>P1 && contador<=1.70){ //Si la presión sobre el embolo2 es mayor la del otro el contador aumenta en 0.1.
            contador+=0.1f;
        }else if(P1==P2){ //Si ambas presiones sobre los embolos son iguales se hace al contador 0.
            contador=0;
        }
    }else if(activar1==false && activar2==false){ //Si no se ha activado ningún embolo se hace al contador 0 y las masas sobre los embolos también.
        contador=0;
        m1=0;
        m2=0;
    }
}

void MyOpenGLWidget::mousePressEvent(QMouseEvent *event){ //Función que detecta si se ha o esta clickeando el mouse (hace a esa variable true).

    bool ok=true;

    if(event->button() == Qt::LeftButton){ //Esta variable boleana se hace true si se mantiene apretado el click izquierdo del mouse.
        m_is_dragging = true;
    }

    if(event->button() == Qt::RightButton && dg==1){ //Si se hace click derecho sobre el primer objetp pide su masa.
        m_obj1=QInputDialog::getDouble(this, tr("Definir masa"), tr("Introduzca la masa:"), 0.00, 0, 10000, 2, &ok);
    }else if(event->button() == Qt::RightButton && dg==2){ //Si se hace click derecho sobre el segundo objetp pide su masa.
        m_obj2=QInputDialog::getDouble(this, tr("Definir masa"), tr("Introduzca el masa:"), 0.00, 0, 10000, 2, &ok);
    }

}

void MyOpenGLWidget::mouseMoveEvent(QMouseEvent *event){ //Se obtine el ancho y el alto del openGL widget (w,h).
    w = MyOpenGLWidget::width();
    h = MyOpenGLWidget::height();
}

void MyOpenGLWidget::mouseReleaseEvent(QMouseEvent *event){ //Función que detecta si se ha dejado clickear el mouse (hace a esa variable false).
    m_is_dragging = false; //Esta variable boleana se hace false si se no esta apretado el click izquierdo del mouse.
}

int dragArea(double posX, double posY){ //Funcíón que detecta si ha pasado el mouse por la zona origen de los objetos (recibe posión x, y del mouse) y retorna un número correspondiente a cada objeto.
    if((posX>=-7.5f && posX<=-4.5f) && (posY>=-9.5f && posY<=-6.5f)){
        return 1;
    }else if((posX>=-4.0f && posX<=-1.0f) && (posY>=-9.5f && posY<=-6.5f)){
        return 2;
    }else if((posX>=-0.5f && posX<=2.5f) && (posY>=-9.5f && posY<=-6.5f)){
        return 3;
    }else if((posX>=3 && posX<=6) && (posY>=-9.5f && posY<=-6.5f)){
        return 4;
    }else if((posX>=6.5 && posX<=9.5) && (posY>=-9.5f && posY<=-6.5f)){
        return 5;
    }else{
        return 0; //Retorna cero si no se ha pasado el mouse en una zona de rangos para del drag.
    }
}

int dropArea(double posX, double posY){ //Funcíón que detecta si ha pasado el mouse por la zona para soltar los objetos (recibe posión x, y del mouse) y retorna y retorna un número correspondiente a cada zona de drop.
    if((posX>=-7.5f && posX<=-4.5f) && (posY>=1.75+cont && posY<=4.75+cont)){
        return 1;
    }else if((posX>=4.5f && posX<=7.5f) && (posY>=1.75-cont && posY<=4.75-cont)){
        return 2;
    }else{
        return 0; //Retorna cero si no se ha pasado el mouse en una zona de rangos para del drop.
    }
}

void MyOpenGLWidget::toolTip(int dg){ //Función que muestra un tooltip con el dato de la masa dependiendo en que figura se pase el mouse.
    QPoint point;
    switch (dg) { //Se pasa dg a un swicth para saber en que figura se ha pasado el mouse, dependiendo de la figura se mostrara un mensaje determinado.
        case 0: //Este caso sirve para limpiar el tooltip.
        point = mapToGlobal(QPoint(0,0));
        QToolTip::showText(point, "");
        break;
        case 1:
        point = mapToGlobal(QPoint(50,570));
        QToolTip::showText(point, "Click derecho insertar masa");
        break;
        case 2:
        point = mapToGlobal(QPoint(160,570));
        QToolTip::showText(point, "Click derecho insertar masa");
        break;
        case 3:
        point = mapToGlobal(QPoint(355,570));
        QToolTip::showText(point, "67.9 kg");
        break;
        case 4:
        point = mapToGlobal(QPoint(475,570));
        QToolTip::showText(point, "1200 kg");
        break;
        case 5:
        point = mapToGlobal(QPoint(595,570));
        QToolTip::showText(point, "6000 kg");
        break;
    }
}

void arrastrarObjeto(double posX, double posY){ //Función que activa diversos flags para determinar si las figuras se pueden arrastrar, soltar, se quedan en un determinado puesto o vuelven a su porsición original.

    dg = dragArea(xM, -yM-8); //Se obntiene el número que indica si esta en el area de drag para un figura (obtiene el valor retornado de una función para ello).
    dp = dropArea(xM, -yM-8); //Se obntiene el número que indica si esta en el area de drop para un figura (obtiene el valor retornado de una función para ello).

    if(m_is_dragging==true){

        for(int i=0; i<5; i++){
            if(dg==(i+1)){
                ir[i]=true;
            }
            if(dp==1){
                ir2[i]=true;
            }
            if(dp==2){
                ir2[i]=true;
            }

            if(dg==(i+1) || (dp==1 && ir[i]==true) || (dp==2 && ir[i]==true)){
                obj[i].drag=true;
            }

            if(dp==1 && ir[i]==true){
                embolo1[i].drop=true;
            }else if(dp==2 && ir[i]==true){
                embolo2[i].drop=true;
            }

        }

    }else if(m_is_dragging==false){

        for(int i=0; i<5; i++){

            if(ir2[i]==true && dp==0){
                activar1=false;
                activar2=false;
                embolo1[i].drop=false;
                embolo2[i].drop=false;
            }

            ir[i]=false;
            ir2[i]=false;
            obj[i].drag=false;
        }

    }

}


void calculos(){ //Función que realiza los calculos de la simulación. Calcula radio, fuerza, area, presión; para ambos embolos.
    float r1=(dEmbolo1+0.25)/2; //Calculo del radio del embolo1.
    float r2=(dEmbolo2+0.25)/2; //Calculo del radio del embolo2.

    F1= (m1*g); //Calculo de la fuerza sobre el embolo1.
    F2= (m2*g); //Calculo de la fuerza sobre el embolo2.
    A1= (M_PI*pow((r1),2)); //Calculo del area del embolo1.
    A2= (M_PI*pow((r2),2)); //Calculo del area del embolo2.
    P1 = (F1)/(A1); //Calculo de la presión sobre el embolo1.
    P2 = (F2)/(A2); //Calculo de la presión sobre el embolo2.
}

MyOpenGLWidget::MyOpenGLWidget(float diametro1, float diametro2, QWidget *parent) //Aquí se define la conección del timer.
    : QOpenGLWidget { parent }
{
        QTimer *cronometro=new QTimer(this);
        connect(cronometro, SIGNAL(timeout()), this, SLOT(funcionActivacionTimer()));
        cronometro->start(50); //Se actualiza cada 50 milisegundos.

        //Se reciben los diametros desde la clase de mainwindow y se guardan en nuevas variables, también se hace un ajuste conveniente para el dibujado restandole 0.25.
        dEmbolo1 = diametro1;
        dEmbolo1-=0.25f;

        dEmbolo2 = diametro2;
        dEmbolo2-=0.25;
}

void MyOpenGLWidget::initializeGL(){ //Aquí se hacen algunas iniciaciones para OpenGL y se cargan las texturas.
    initializeOpenGLFunctions();
    glClearColor(1,1,1,1);

    texture[0] = SOIL_load_OGL_texture //Carga un archivo de imagen directamente como una nueva textura OpenGL (Pesa#1).
    (
        "Img1.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    texture[1] = SOIL_load_OGL_texture //Carga un archivo de imagen directamente como una nueva textura OpenGL (Pesa#2).
    (
        "Img2.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    texture[2] = SOIL_load_OGL_texture //Carga un archivo de imagen directamente como una nueva textura OpenGL (Persona de palos).
    (
        "Img3.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    texture[3] = SOIL_load_OGL_texture //Carga un archivo de imagen directamente como una nueva textura OpenGL (Dibujo de un carro).
    (
        "Img4.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    texture[4] = SOIL_load_OGL_texture //Carga un archivo de imagen directamente como una nueva textura OpenGL (Dibujo de un elefante).
    (
        "Img5.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

}

void MyOpenGLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QPoint p = mapFromGlobal(QCursor::pos());
    xM = (p.rx())*(20/w) -10; //Se ontiene la posiciób en X del cursor y se convierte a coordenadas ortogonales.
    yM = ((p.ry())*(20/h) -10)-8; //Se ontiene la posiciób en Y del cursor y se convierte a coordenadas ortogonales.

    toolTip(dg); //Se llama a la función que miestra los tooltip de las figuras.

    glColor3f(0.1176f,0.7569f,0.9608);
    glBegin(GL_POLYGON); //Dibujado del fluido del embolo1 (izquierdo) se anima dependiendo de la presión.
    glVertex2f(-6.25-dEmbolo1 ,-1.75+contador);
    glVertex2f(-6.25-dEmbolo1,-6);
    glVertex2f(-5.75+dEmbolo1,-6);
    glVertex2f(-5.75+dEmbolo1,-1.75+contador);
    glEnd();

    glBegin(GL_POLYGON); //Dibujado del fluido del embolo2 (derecho) y se anima dependiendo de la presión.
    glVertex2f(6.25+dEmbolo2 ,-1.75-contador);
    glVertex2f(6.25+dEmbolo2 ,-6);
    glVertex2f(5.75-dEmbolo2,-6);
    glVertex2f(5.75-dEmbolo2,-1.75-contador);
    glEnd();

    glBegin(GL_POLYGON); //Dibujo del contenido del agua del sistema (menos la parte de los embolos).
    glVertex2f(-6.25 ,-3.5);
    glVertex2f(-6.25 ,-6);
    glVertex2f(6.25,-6);
    glVertex2f(6.25,-3.5);
    glEnd();

    glColor3f(0,0,0);
    glPushMatrix();
    glTranslatef(0,contador,0);
    glLineWidth(5);
    glBegin(GL_LINES);
    glVertex2f(-6.25-dEmbolo1,-1.75); //Embolo1, area circular inferior.
    glVertex2f(-5.75+dEmbolo1,-1.75);

    glVertex2f(-6,-1.75); //Embolo1, palo que conecta el circulo inferior con el superior.
    glVertex2f(-6,1.75);

    glVertex2f(-6.25-dEmbolo1,1.75); //Embolo1, area circular superior.
    glVertex2f(-5.75+dEmbolo1,1.75);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-contador,0);
    glBegin(GL_LINES);
    glVertex2f(5.75-dEmbolo2,-1.75); //Embolo2 area circular inferior.
    glVertex2f(6.25+dEmbolo2,-1.75);

    glVertex2f(6,-1.75); //Embolo2, palo que conecta el circulo inferior con el superior.
    glVertex2f(6,1.75);

    glVertex2f(5.75-dEmbolo2,1.75); //Embolo2, area circular superior.
    glVertex2f(6.25+dEmbolo2,1.75);
    glEnd();
    glPopMatrix();

    glColor3f(0,0,0);
    glLineWidth(1);
    glBegin(GL_LINE_LOOP); //Dibujado del contorno del sistema de embolos.
    glVertex2f(-5.75+dEmbolo1,-3.5);
    glVertex2f(-5.75+dEmbolo1,0);
    glVertex2f(-6.25-dEmbolo1 ,0);
    glVertex2f(-6.25-dEmbolo1 ,-6);
    glVertex2f(6.25+dEmbolo2,-6);
    glVertex2f(6.25+dEmbolo2,0);
    glVertex2f(5.75-dEmbolo2,0);
    glVertex2f(5.75-dEmbolo2,-3.5);
    glEnd();

    arrastrarObjeto(xM, -yM-8); //Se llama a la función donde se establece los flags de drag y drop, y se le para la posición en X y Y del cursor.

    glPushMatrix();
    if(obj[0].drag==false && embolo1[0].drop==false && embolo2[0].drop==false){ //Si el drag esta desactivado y el drop para el embolo1 y embolo2 también, el objeto se quedará/volverá en su posición original.
        glTranslatef(-6,-8,0);
    }else if(obj[0].drag==true){ //Si el drag está activado, el objeto seguirá el cursor.
        glTranslatef(xM, -yM-8, 0);
    }else if(embolo1[0].drop==true){ //Si el drop del embolo1 está activo, este se quedará fijo encima del embolo1.
        glTranslatef(0,contador,0);
        glTranslatef(-6, 3.25, 0);
        activar1=true;
        m1=m_obj1;
    }else if(embolo2[0].drop==true){ //Si el drop del embolo2 está activo, este se quedará fijo encima del embolo2.
        glTranslatef(0,-contador,0);
        glTranslatef(6, 3.25, 0);
        activar2=true;
        m2=m_obj1;
    }else{ //Si no se presenta ninguno de los anteriores casos las variables boleanas que activan la animación se hacen false.
        activar1=false;
        activar2=false;
    }
    cubo(3,0); //Se dibuja un cuadro cuyos lados miden 3 y se mapea (1: pesa plateada).
    text("%.2f kg", m_obj1,-0.80,-0.50);
    glPopMatrix();

    glPushMatrix();
    if(obj[1].drag==false && embolo1[1].drop==false && embolo2[1].drop==false){ //Si el drag esta desactivado y el drop para el embolo1 y embolo2 también, el objeto se quedará/volverá en su posición original.
        glTranslatef(-2.50,-8,0);
    }else if(obj[1].drag==true){ //Si el drag está activado, el objeto seguirá el cursor.
        glTranslatef(xM, -yM-8, 0);
    }else if(embolo1[1].drop==true){ //Si el drop del embolo1 está activo, este se quedará fijo encima del embolo1.
        glTranslatef(0,contador,0);
        glTranslatef(-6, 3.25, 0);
        activar1=true;
        m1=m_obj2;
    }else if(embolo2[1].drop==true){ //Si el drop del embolo2 está activo, este se quedará fijo encima del embolo2.
        glTranslatef(0,-contador,0);
        glTranslatef(6, 3.25, 0);
        activar2=true;
        m2=m_obj2;
    }else{ //Si no se presenta ninguno de los anteriores casos las variables boleanas que activan la animación se hacen false.
        activar1=false;
        activar2=false;
    }
    cubo(3,1); //Se dibuja un cuadro cuyos lados miden 3 y se mapea (2: pesa bronce).
    text("%.2f kg", m_obj2,-0.80f,-0.50);
    glPopMatrix();


    glPushMatrix();

    if(obj[2].drag==false && embolo1[2].drop==false && embolo2[2].drop==false){ //Si el drag esta desactivado y el drop para el embolo1 y embolo2 también, el objeto se quedará/volverá en su posición original.
        glTranslatef(1.0,-8,0);
    }else if(obj[2].drag==true){ //Si el drag está activado, el objeto seguirá el cursor.
        glTranslatef(xM, -yM-8, 0);
    }else if(embolo1[2].drop==true){ //Si el drop del embolo1 está activo, este se quedará fijo encima del embolo1.
        glTranslatef(0,contador,0);
        glTranslatef(-6, 3.25, 0);
        activar1=true;
        m1=67.9f;
    }else if(embolo2[2].drop==true){ //Si el drop del embolo2 está activo, este se quedará fijo encima del embolo2.
        glTranslatef(0,-contador,0);
        glTranslatef(6, 3.25, 0);
        activar2=true;
        m2=67.9f;
    }else{ //Si no se presenta ninguno de los anteriores casos las variables boleanas que activan la animación se hacen false.
        activar1=false;
        activar2=false;
    }
    cubo(3,2); //Se dibuja un cuadro cuyos lados miden 3 y se mapea (3: persona de palos).
    glPopMatrix();

    glPushMatrix();

    if(obj[3].drag==false && embolo1[3].drop==false && embolo2[3].drop==false){ //Si el drag esta desactivado y el drop para el embolo1 y embolo2 también, el objeto se quedará/volverá en su posición original.
        glTranslatef(4.5,-8,0);
    }else if(obj[3].drag==true){ //Si el drag está activado, el objeto seguirá el cursor.
        glTranslatef(xM, -yM-8, 0);
    }else if(embolo1[3].drop==true){ //Si el drop del embolo1 está activo, este se quedará fijo encima del embolo1.
        glTranslatef(0,contador,0);
        glTranslatef(-6, 3.25, 0);
        activar1=true;
        m1=1200;
    }else if(embolo2[3].drop==true){ //Si el drop del embolo2 está activo, este se quedará fijo encima del embolo2.
        glTranslatef(0,-contador,0);
        glTranslatef(6, 3.25, 0);
        activar2=true;
        m2=1200;
    }else{ //Si no se presenta ninguno de los anteriores casos las variables boleanas que activan la animación se hacen false.
        activar1=false;
        activar2=false;
    }
    cubo(3,3); //Se dibuja un cuadro cuyos lados miden 3 y se mapea (4: carro).
    glPopMatrix();

    glPushMatrix();

    if(obj[4].drag==false && embolo1[4].drop==false && embolo2[4].drop==false){ //Si el drag esta desactivado y el drop para el embolo1 y embolo2 también, el objeto se quedará/volverá en su posición original.
        glTranslatef(8,-8,0);
    }else if(obj[4].drag==true){ //Si el drag está activado, el objeto seguirá el cursor.
        glTranslatef(xM, -yM-8, 0);
    }else if(embolo1[4].drop==true){ //Si el drop del embolo1 está activo, este se quedará fijo encima del embolo1.
        glTranslatef(0,contador,0);
        glTranslatef(-6, 3.25, 0);
        activar1=true;
        m1=6000;
    }else if(embolo2[4].drop==true){ //Si el drop del embolo2 está activo, este se quedará fijo encima del embolo2.
        glTranslatef(0,-contador,0);
        glTranslatef(6, 3.25, 0);
        activar2=true;
        m2=6000;
    }else{ //Si no se presenta ninguno de los anteriores casos las variables boleanas que activan la animación se hacen false.
        activar1=false;
        activar2=false;
    }
    cubo(3,4); //Se dibuja un cuadro cuyos lados miden 3 y se mapea (5: elefante).
    glPopMatrix();

    calculos(); //Se invoca a la función que realiza los calculos de las variables del sistema.

    //Impresión de datos para el objeto sobre el émbolo#1.
    text("P1: %.2f Pa", P1,-8,9);
    text("F1: %.2f N", F1,-8,8);
    text("A1: %.2f m^2", A1,-8,7);

    //Impresión de datos para el objeto sobre el émbolo#2.
    text("P2: %.2f Pa", P2,4,9);
    text("F2: %.2f N", F2,4,8);
    text("A2: %.2f m^2", A2,4,7);

    update();

}

void MyOpenGLWidget::resizeGL(int w, int h){ //Se define los modos de vista, se uso la vista ortogonal aquí.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10, 10, -10, 10, -10, 10);
}
