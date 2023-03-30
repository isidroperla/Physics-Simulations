#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <ctime>
#define M_PI 3.14159265358979323846
#define TIME_INTERVAL 50

using namespace std;

bool calculos = false;

double ax=0;
double ay=0;
double vox=0;
double voy=0;
double xo=0;
double yo=0;
double vx=0;
double vy=0;
double x=0;
double y=0;
double q=0;
double Q=0;
double m=0;
double t=0.001;
const double ke=9*pow(10,9);

int exponente_m=0;
int exponente_q=0;
int exponente_Q=0;

double phi=0;
double ghama=0;
double vauxX=0;
double vauxY=0;
double pruebaX=0;
double pruebaY=0;
double R=0.5;
double auxXo=0;
double auxYo=0;
double auxVxo=0;
double auxVyo=0;

int iterations = 5000;
double intervalo = 0;

bool animacion = true; //Condición para activar/desactivar la animación.
int activarOpausa=-1;  //Pausa de la animación.
bool esferaPausa=false; //Dibuja la esfera cuando esta pausada la simulación.

void text()
{
    char text[128];
    sprintf(text, "x:%.2f y:%.2f vx:%.2f vy:%.2f", x, y, vx, vy);
    glColor3f(0, 0, 0);
    glRasterPos3f(0.5f,9.2f,0);
    for(int i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
}

void onlytext(string cadena, float espaciadoX, float espaciadoY) //Funcion que imprime texto.
{
	std::string const s(cadena);
    char onlytext[128];
    sprintf(onlytext, s.c_str());
    glColor3f(0, 0, 0);
    glRasterPos3f(espaciadoX,espaciadoY,0);

    for(int i = 0; onlytext[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, onlytext[i]);
}

void cuadricula(int xmin, int xmax, int ymin, int ymax){

	glColor3f (0, 0, 0);
	glLineWidth(1);

	glBegin(GL_LINES);

    glVertex2f(0,ymin);
    glVertex2f(0,ymax);

    glVertex2f(xmin,0);
    glVertex2f(xmax,0);

    for(int i=xmin; i<=xmax; i++){

		glVertex2f(i,0.1);
		glVertex2f(i,-0.1);

		}

	 for(int i=ymin; i<=ymax; i++){

		glVertex2f(-0.1,i);
		glVertex2f(0.1,i);

		}

    glEnd();

	}

void figura(void){

	glColor3f (0, 0, 0);
    glLineWidth(3);

    glBegin(GL_LINE_LOOP);

    glVertex2f(9.95f,9.95f);
    glVertex2f(-9.95f,9.95f);
    glVertex2f(-9.95f,-9.95f);
    glVertex2f(9.95f,-9.95f);

    glEnd();

    glColor3f(1, 1, 0);
    glutSolidSphere(R,20,20);

	glColor3f(0, 0, 0);
	if(Q>=0){
		glBegin(GL_LINES);
        glVertex2f(-0.3,0);
        glVertex2f(0.3,0);
        glVertex2f(0,-0.3);
        glVertex2f(0,0.3);
		glEnd();
    }else if(Q<0){
        glBegin(GL_LINES);
        glVertex2f(-0.3,0);
        glVertex2f(0.3,0);
        glEnd();
    }

    if(esferaPausa==true){
        glColor3f(1, 0, 0);
        glPushMatrix();
        glTranslatef(x,y,0);
        glutSolidSphere(0.3,20,20);

        glColor3f(0, 0, 0);
        if(q>=0){
            glBegin(GL_LINES);
			glVertex2f(-0.15,0);
			glVertex2f(0.15,0);
			glVertex2f(0,-0.15);
			glVertex2f(0,0.15);
            glEnd();
		}else if(q<0){
			glBegin(GL_LINES);
			glVertex2f(-0.15,0);
			glVertex2f(0.15,0);
			glEnd();
        }
        glPopMatrix();
	}

	if(calculos == true){

	ax= (ke*q*Q*xo)/(m*pow((pow(xo,2)+pow(yo,2)),1.5));
	//ax= roundf(ax * 100)/100;
	ay= (ke*q*Q*yo)/(m*pow((pow(xo,2)+pow(yo,2)),1.5));
	//ay= roundf(ay * 100)/100;

	x = xo+vox*t+0.5*ax*pow(t,2);
	y = yo+voy*t+0.5*ay*pow(t,2);

	vx = vox+ax*t;
	vy = voy+ay*t;

	if(sqrt((pow(x,2)+pow(y,2)))<=R){

		phi = acos(abs((y*vx-x*vy)/(sqrt(pow(vx,2)+pow(vy,2))*sqrt(pow(y,2)+pow(x,2)))));

		ghama = 2*phi;

		vauxX = vx*cos(ghama)-vy*sin(ghama);
		vauxY = vx*sin(ghama)+vy*cos(ghama);
		pruebaX = vx*(0.001);
		pruebaY = vy*(0.001);

		if(sqrt(pow(pruebaX,2)+pow(pruebaY,2))>R){

			vx = vauxX*0.9;
			vy = vauxY*0.9;

			}else{

				ghama = -2*phi;
				vauxX = vx*cos(ghama)-vy*sin(ghama);
				vauxY = vx*sin(ghama)+vy*cos(ghama);
				vx = vauxX*0.9;
				vy = vauxY*0.9;

			}

		}

	glColor3f(1, 0, 0);
	glPushMatrix();
	glTranslatef(x,y,0);
    glutSolidSphere(0.3,20,20);

    glColor3f(0, 0, 0);
	if(q>=0){
		glBegin(GL_LINES);
			glVertex2f(-0.15,0);
			glVertex2f(0.15,0);
			glVertex2f(0,-0.15);
			glVertex2f(0,0.15);
		glEnd();
		}else if(q<0){
			glBegin(GL_LINES);
				glVertex2f(-0.15,0);
				glVertex2f(0.15,0);
			glEnd();
			}

	glPopMatrix();

	xo=x;
    yo=y;
    vox=vx;
    voy=vy;

	}

	if(esferaPausa==true){
        glColor3f(1, 0, 0);
        glPushMatrix();
        glTranslatef(x,y,0);
        glutSolidSphere(0.3,20,20);

        glColor3f(0, 0, 0);
        if(q>=0){
            glBegin(GL_LINES);
			glVertex2f(-0.15,0);
			glVertex2f(0.15,0);
			glVertex2f(0,-0.15);
			glVertex2f(0,0.15);
            glEnd();
		}else if(q<0){
			glBegin(GL_LINES);
			glVertex2f(-0.15,0);
			glVertex2f(0.15,0);
			glEnd();
        }
        glPopMatrix();

        glColor3f(1, 1, 0);
        glutSolidSphere(R,20,20);

        glColor3f(0, 0, 0);
        if(Q>=0){
            glBegin(GL_LINES);
            glVertex2f(-0.3,0);
            glVertex2f(0.3,0);
            glVertex2f(0,-0.3);
            glVertex2f(0,0.3);
            glEnd();
        }else if(Q<0){
            glBegin(GL_LINES);
            glVertex2f(-0.3,0);
            glVertex2f(0.3,0);
            glEnd();
        }
	}

}

void TimerRutina(int value) //Este timer sirve para animar la rutina
{
   if (animacion){

        if (iterations > 0){
            figura();

            glutPostRedisplay();
            glutTimerFunc(intervalo, TimerRutina, iterations);
            --iterations;
		}
   }
}

void display(void)
{
	glClearColor(1,1,1, 1);
    glClear (GL_COLOR_BUFFER_BIT);

    text();

    onlytext("Animar/Pausar: tecla x o X", -9.5f, -8.5f);
    onlytext("Reiniciar: tecla r o R", -9.5f, -9.5f);

    cuadricula(-10, 10, -10, 10);

    figura();

    glFlush ();

}

void reinciar(void){

    calculos = false;
    ax=0;
    ay=0;
    vox=auxVxo;
    voy=auxVyo;
    xo=auxXo;
    yo=auxYo;
    x=0;
    y=0;
    vx=0;
    vy=0;
    t=0.001;
    phi=0;
    ghama=0;
    vauxX=0;
    vauxY=0;
    pruebaX=0;
    pruebaY=0;
    R=0.5;
    iterations = 5000;
}

//-------------------------------------------->

void keyboard (unsigned char key, int x, int y)
{
switch (key) {   // x,X,y,Y,z,Z uses the glRotatef() function
    case 'x': // Rotates screen on x axis

    case 'X': // Rotates screen on x axis
        esferaPausa=false;
        activarOpausa*=-1;

		if(activarOpausa>0){
			animacion = true;
			TimerRutina(0);
			calculos = true;
		}
		else{
			animacion = false;
			calculos = false;
			esferaPausa=true;
		}
    break;

    case 'r': // Rotates screen on x axis

    case 'R': // Rotates screen on x axis
    esferaPausa=false;
    reinciar();
        activarOpausa*=-1;

		if(activarOpausa>0){
			animacion = true;
			TimerRutina(0);
			calculos = true;
		}
		else{
			animacion = false;
			calculos = false;
			esferaPausa=true;
		}
    break;
}
    glutPostRedisplay(); // Redraw the scene
}


void init (void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10, 10, -10, 10, -10, 10);

}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    if(argc < 10)
    {
		return 1;
	}

    m = atof(argv[1]);
    q = atof(argv[2]);
    Q= atof(argv[3]);
    xo = atof(argv[4]);
    yo = atof(argv[5]);
    vox = atof(argv[6]);
    voy = atof(argv[7]);
    exponente_m = atof(argv[8]);
    exponente_q = atof(argv[9]);
    exponente_Q = atof(argv[10]);
    intervalo = atof(argv[11]);

    auxXo=xo;
    auxYo=yo;
    auxVxo = vox;
    auxVyo = voy;

	m*=pow(10,exponente_m);
    q*=pow(10,exponente_q);
    Q*=pow(10,exponente_Q);

    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(((glutGet(GLUT_SCREEN_WIDTH)-700)/2), ((glutGet(GLUT_SCREEN_HEIGHT)-700)/2));
    glutCreateWindow ("SIMULACION ANIMADA MOVIMIENTO DE UNA CARGA EN PRESENCIA DE UN CAMPO ELÉCTRICO");

    init ();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard); // set window's key callback
    glutMainLoop();
    return 0;
}
