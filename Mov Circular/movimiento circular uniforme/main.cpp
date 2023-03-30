#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <string.h>
#include <stdio.h>
#include <cmath>
#include <iostream>
#include <ctime>
#define TIME_INTERVAL 1000
#define M_PI 3.14159265358979323846

using namespace std;

bool animacion = true;
int activarOpausa=-1;
int punto2Habilitado=0;

double theta;
double w=0.5;
double wmax;
double t=1;
double giro=0;
double auxtheta;

int signOmega;

double x_1=0;
double y_1=0;

double x_2=0;
double y_2=0;

double x_v1;
double y_v1;

double x_v2;
double y_v2;

double timeTest;

double r1;
double v1;
double ac1;
double angulo_Phi;
double angulo_Alpha;
double angulo_Alpha2;
double vector_v1[2];
double vector_ac1[2];

double r2;
double v2;
double ac2;
double vector_v2[2];
double vector_ac2[2];

int iterations = 360;

void toggleGlutWindowMaximizeBox(char *szWindowTitle)
{
    long dwStyle;
    HWND hwndGlut;

    hwndGlut = FindWindow(NULL, szWindowTitle);

    dwStyle = GetWindowLong(hwndGlut, GWL_STYLE);
    dwStyle ^= WS_MAXIMIZEBOX;
    SetWindowLong(hwndGlut, GWL_STYLE, dwStyle);
}

void text(string valor, double dato, double espaciadoX, double espaciadoY)
{
	std::string const s(valor);
    char text[32];
    sprintf(text, s.c_str(), dato);
    glColor3f(0, 0, 0);
    glRasterPos3f(espaciadoX,espaciadoY,0);

    for(int i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
}

void onlytext(string cadena, double espaciadoX, double espaciadoY, double r, double g, double b, bool letraNormal)
{
	std::string const s(cadena);
    char onlytext[32];
    sprintf(onlytext, s.c_str());
    glColor3f(r, g, b);
    glRasterPos3f(espaciadoX,espaciadoY,0);

    if(letraNormal==true){
		for(int i = 0; onlytext[i] != '\0'; i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, onlytext[i]);
	}else{
		for(int i = 0; onlytext[i] != '\0'; i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, onlytext[i]);
		}
}

void TimerRutina(int value) //Este timer sirve para animar la rutina
{
   // Do something here.
   if (animacion){

		giro += w*0.025*(180/M_PI);

		timeTest += 0.025;

		//---------------------->

		if(x_1>=0 && y_1>=0){
			angulo_Alpha = atan(abs((y_1/x_1)));
		}
		else if(x_1<0 && y_1>=0){
			angulo_Alpha = M_PI-atan(abs((y_1/x_1)));
		}
		else if(x_1<0 && y_1<0){
			angulo_Alpha = M_PI+atan(abs((y_1/x_1)));
		}
		else if(x_1>=0 && y_1<0){
			angulo_Alpha = (2*M_PI)-atan(abs((y_1/x_1)));
		}


		if(x_2>=0 && y_2>=0){
			angulo_Alpha2 = atan(abs((y_2/x_2)));
		}
		else if(x_2<0 && y_2>=0){
			angulo_Alpha2 = M_PI-atan(abs((y_2/x_2)));
		}
		else if(x_2<0 && y_2<0){
			angulo_Alpha2 = M_PI+atan(abs((y_2/x_2)));
		}
		else if(x_2>=0 && y_2<0){
			angulo_Alpha2 = (2*M_PI)-atan(abs((y_2/x_2)));
		}

		//---------------------->

		//-------------------------->Datos punto 1

		x_v1 = r1*cos(giro*(M_PI/180)+angulo_Alpha);
		y_v1 = r1*sin(giro*(M_PI/180)+angulo_Alpha);

		r1 = sqrt(pow(x_1,2) + pow(y_1,2));

		v1 = sqrt(pow((-w*y_1),2) + pow((w*x_1),2));

		ac1 = sqrt(pow(pow(-w,2)*x_1,2) + pow(pow(-w,2)*y_1,2));

		vector_v1[0] = -w*y_v1;
		vector_v1[1] = w*x_v1;

		vector_ac1[0] = -pow(w,2)*x_v1;
		vector_ac1[1] = -pow(w,2)*y_v1;

		//-------------------------->Datos punto 2

		x_v2 = r2*cos(giro*(M_PI/180)+angulo_Alpha2);
		y_v2 = r2*sin(giro*(M_PI/180)+angulo_Alpha2);

		r2 = sqrt(pow(x_2,2) + pow(y_2,2));

		v2 = sqrt(pow((-w*y_2),2) + pow((w*x_2),2));

		ac2 = sqrt(pow(pow(-w,2)*x_2,2) + pow(pow(-w,2)*y_2,2));

		vector_v2[0] = -w*y_v2;
		vector_v2[1] = w*x_v2;

		vector_ac2[0] = -pow(w,2)*x_v2;
		vector_ac2[1] = -pow(w,2)*y_v2;

		glutPostRedisplay();
		glutTimerFunc(25, TimerRutina, iterations);
		--iterations;
		}
}

double anguloPhi(double valX, double valY){

	if(valX>=0 && valY>=0){
		angulo_Phi = atan(abs(valY/valX));
		}
	else if(valX<0 && valY>=0){
		angulo_Phi = M_PI-atan(abs(valY/valX));
		}
	else if(valX<0 && valY<0){
		angulo_Phi = M_PI+atan(abs(valY/valX));
		}
	else if(valX>=0 && valY<0){
		angulo_Phi = (2*M_PI)-atan(abs(valY/valX));
		}

	return angulo_Phi;
	}

int signo(){

	if(w>=0){

		signOmega=1;

		}
		else{
			signOmega=-1;
		}

	return signOmega;
	}

void figura(void){

    double x, y;

    glColor3f(0.235, 0.113, 0.003); //Color Rueda borde
    glutSolidSphere(2,100,100); //Rueda Borde

    glColor3f(0.380, 0.176, 0); //Color rueda fondo

    glutSolidSphere(1.8,100,100); //Rueda fondo

    glLineWidth(2.5); //Tamaño de los rayos

    glColor3f(0.588, 0.588, 0.588); //Rueda rayos

    x=0,y=0;
    glBegin(GL_LINES);
	for(double i=0; i<360; i+=10){
		x = cos(i*(2*3.1416)/360);
		y = sin(i*(2*3.1416)/360);
		glVertex2f (0, 0);
		glVertex2f (x*1.8, y*1.8);

	}
    glEnd();

	glColor3f(0.235, 0.113, 0.003); //Color ruida centro
    glutSolidSphere(0.25,20,10); //Rueda centro

    glPointSize(3);
    glColor3f(0, 0, 0); //Color punto del centro
    glBegin(GL_POINTS);
		glVertex2f(0,0); //Punto del centro
	glEnd();

	//----->Vector velocidad tagencial punto#1

	glColor3f(0,1,0);
	glBegin(GL_LINES);
	glVertex2f(x_1,y_1); //Linea que conecta punto#1 con flecha del vector v1
	glVertex2f((x_1-wmax*y_1), (y_1+wmax*x_1));
	glEnd();

	glPushMatrix();
	glTranslatef((x_1-wmax*y_1),(y_1+wmax*x_1),0);
	glRotated((anguloPhi(x_1, y_1)*(180/M_PI))-90*signo(),0,0,1);
	glBegin(GL_TRIANGLES); //Triaungulo de la flecha vector verde
	glVertex2f(0,0);
	glVertex2f(0.1,0.1);
	glVertex2f(0.1,-0.1);
	glEnd();
	glPopMatrix();

	//Vector aceleracion centripeta

	glColor3f(1,0,0);
	glBegin(GL_LINES);
	glVertex2f(x_1,y_1); //Linea que conecta punto#1 con la flecha roja
	glVertex2f((x_1-pow(wmax,2)*x_1), (y_1-pow(wmax,2)*y_1));
	glEnd();

	glPushMatrix();
	glTranslatef((x_1-pow(wmax,2)*x_1),(y_1-pow(wmax,2)*y_1),0);
	glRotated(anguloPhi(x_1, y_1)*(180/M_PI),0,0,1);
	glBegin(GL_TRIANGLES); //>Triaungulo de la flecha vector rojo
	glVertex2f(0,0);
	glVertex2f(0.1,0.1);
	glVertex2f(0.1,-0.1);
	glEnd();
	glPopMatrix();

	glPointSize(10);
	glColor3f(0,0,1);
	glBegin(GL_POINTS);
	glVertex2f(x_1,y_1); //Punto#1(azul)
	glEnd();

//------------------------------------------------------------------------------->

	if(punto2Habilitado==1){

	//----->Vector velocidad tagencial punto#2

	glColor3f(0,1,0);
	glBegin(GL_LINES);
	glVertex2f(x_2,y_2); //Linea que conecta punto#2 con flecha del vector v2
	glVertex2f((x_2-wmax*y_2), (y_2+wmax*x_2));
	glEnd();

	glPushMatrix();
	glTranslatef((x_2-wmax*y_2),(y_2+wmax*x_2),0);
	glRotated((anguloPhi(x_2, y_2)*(180/M_PI))-90*signo(),0,0,1);
	glBegin(GL_TRIANGLES); //Triaungulo de la flecha vector verde
	glVertex2f(0,0);
	glVertex2f(0.1,0.1);
	glVertex2f(0.1,-0.1);
	glEnd();
	glPopMatrix();

	//Vector aceleracion centripeta

	glColor3f(1,0,0);
	glBegin(GL_LINES);
	glVertex2f(x_2,y_2); //Linea que conecta punto#2 con la flecha roja
	glVertex2f((x_2-pow(wmax,2)*x_2), (y_2-pow(wmax,2)*y_2));
	glEnd();

	glPushMatrix();
	glTranslatef((x_2-pow(wmax,2)*x_2),(y_2-pow(wmax,2)*y_2),0);
	glRotated(anguloPhi(x_2, y_2)*(180/M_PI),0,0,1);
	glBegin(GL_TRIANGLES); //Triaungulo de la flecha vector rojo
	glVertex2f(0,0);
	glVertex2f(0.1,0.1);
	glVertex2f(0.1,-0.1);
	glEnd();
	glPopMatrix();

	glPointSize(10);
	glColor3f(1,0,1);
	glBegin(GL_POINTS);
	glVertex2f(x_2,y_2); //Punto#2(rosa)
	glEnd();

	onlytext("2", x_2, y_2 ,0.874, 0.368, 0.047, true);
	}

	onlytext("1", x_1, y_1, 0.874, 0.368, 0.047, true);

	glColor3f(0,0,0);

	glBegin(GL_LINES);
	//Letra U
	glVertex2f(-0.6,0.5);
	glVertex2f(-0.6,1.0);
	glVertex2f(-0.6,0.5);
	glVertex2f(-0.3,0.5);
	glVertex2f(-0.3,0.5);
	glVertex2f(-0.3,1.0);
	//Letra E
	glVertex2f(-0.1,0.5);
	glVertex2f(0.2,0.5);
	glVertex2f(-0.1,0.5);
	glVertex2f(-0.1,1.0);
	glVertex2f(-0.1,0.75);
	glVertex2f(0.2,0.75);
	glVertex2f(-0.1,1.0);
	glVertex2f(0.2,1.0);
	//Letra S
	glVertex2f(0.4,0.5);
	glVertex2f(0.7,0.5);
	glVertex2f(0.7,0.5);
	glVertex2f(0.7,0.75);
	glVertex2f(0.7,0.75);
	glVertex2f(0.4,0.75);
	glVertex2f(0.4,0.75);
	glVertex2f(0.4,1.0);
	glVertex2f(0.4,1.0);
	glVertex2f(0.7,1.0);
	glEnd();

	}


void display(void)
{
	glClearColor(1, 1, 1, 1);
    glClear (GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    glRotatef(giro,0,0,1);
    figura();
    glPopMatrix();

    //Texto complementario
    onlytext("Punto 1", -4.0, 4.7, 0, 0, 0, true);
    onlytext("Activar/pausar animacion:", -4.5, -4.12, 0,0,0, true);
    onlytext("Tecla 'x' o 'X'", -4.0, -4.42, 0,0,0, true);

    onlytext("->", -4.9, 2.66, 0,0,0, false);
    onlytext("->", -4.9, 2.15, 0,0,0, false);

	//Datos del punto tiempo y angulo
    text("t: %.3f s", (timeTest), -0.8, 4.7);
    text("angulo: %.3f deg", (giro), -0.8, 4.3);
    text("w: %.3f rad/s", (w), -0.8, 3.9);

    //Datos del punto 1
    text("r : %.3f m", r1, -4.9, 4.5); onlytext("1", -4.83, 4.42, 0,0,0, false);
    text("w : %.3f rad/s", w, -4.9, 4.0); onlytext("1", -4.76, 3.93, 0,0,0, false);
    text("v : %.3f m/s", v1, -4.9, 3.5); onlytext("1", -4.83, 3.42, 0,0,0, false);
    text("a  : %.3f m/s^2", ac1, -4.9, 3.0); onlytext("c1", -4.83, 2.92, 0,0,0, false);
    text("v : [(%.2f i) +", vector_v1[0], -4.9, 2.5); text(" (%.2f j)] m/s", vector_v1[1], -3.6, 2.5); onlytext("1", -4.83, 2.42, 0,0,0, false);
    text("a  : [(%.2f i) +", vector_ac1[0], -4.9, 2.0); text("(%.2f j)] m/s^2", vector_ac1[1], -3.5, 2.0); onlytext("c1", -4.83, 1.92, 0,0,0, false);

    if(punto2Habilitado==1){

	onlytext("->", 2.1, 2.66, 0,0,0, false);
    onlytext("->", 2.1, 2.15, 0,0,0, false);

    //Datos del punto 2
    onlytext("Punto 2", 3.0, 4.7, 0,0,0,true);
    text("r : %.3f m", r2, 2.1, 4.5); onlytext("2", 2.17, 4.42, 0,0,0, false);
    text("w : %.3f rad/s", w, 2.1, 4.0); onlytext("2", 2.24, 3.92, 0,0,0, false);
    text("v : %.3f m/s", v2, 2.1, 3.5); onlytext("2", 2.17, 3.42, 0,0,0, false);
    text("a  : %.3f m/s^2", ac2, 2.1, 3.0); onlytext("c2", 2.17, 2.92, 0,0,0, false);
    text("v : [(%.2f i) +", vector_v2[0], 2.1, 2.5); text(" (%.2f j)] m/s", vector_v2[1], 3.4, 2.5); onlytext("2", 2.17, 2.42, 0,0,0, false);
    text("a  : [(%.2f i) +", vector_ac2[0], 2.1, 2.0); text("(%.2f j)] m/s^2", vector_ac2[1], 3.5, 2.0); onlytext("c2", 2.17, 1.92, 0,0,0, false);

	}
    //Cuadro de los datos del punto 1
    glBegin(GL_LINE_LOOP);
	glVertex2f(-2,1.8);
	glVertex2f(-2,5);
	glVertex2f(-5,5);
	glVertex2f(-5,1.8);
	glEnd();

    if(punto2Habilitado==1){
    //Cuadro de los datos del punto 2
    glBegin(GL_LINE_LOOP);
	glVertex2f(2,1.8);
	glVertex2f(2,5);
	glVertex2f(5,5);
	glVertex2f(5,1.8);
	glEnd();
	}

	//Cuadro de los datos generales
	glBegin(GL_LINE_LOOP);
	glVertex2f(-2,3.7);
	glVertex2f(-2,5);
	glVertex2f(2,5);
	glVertex2f(2,3.7);
	glEnd();

    //Leyenda

    onlytext("Aceleracion centripeta \242", 2.7, -4.05, 0,0,0, true);
    onlytext("Velocidad tangencial", 2.7, -4.55, 0,0,0, true);

    glBegin(GL_LINES);
    glColor3f(1,0,0);
    glVertex2f(1.5, -4.0);
    glVertex2f(2.5, -4.0);
    glColor3f(0,1,0);
    glVertex2f(1.5, -4.5);
    glVertex2f(2.5, -4.5);
    glEnd();

    glutSwapBuffers();

}
void init (void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5, 5, -5, 5, -5, 5);

}

	void keyboard (unsigned char key, int x, int y)
{
switch (key) {
    case 'x':

    case 'X':

    theta = w*t;

    activarOpausa*=-1;

	if(activarOpausa>0){
		animacion = true;
		TimerRutina(0);
		}else{
			animacion = false;
			}
    break;

}
    glutPostRedisplay(); // Redraw the scene
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    if(argc < 7)
    {
        cout << "Faltan " << 7 - argc << " argumentos. ¿Abrió la interfaz grafica primero?";
		return 1;
	}

    w = atof(argv[1]);
    wmax = atof(argv[2]);
    x_1 = atof(argv[3]);
    y_1= atof(argv[4]);
    x_2 = atof(argv[5]);
    y_2 = atof(argv[6]);
    punto2Habilitado = atoi(argv[7]);

    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(((glutGet(GLUT_SCREEN_WIDTH)-700)/2), ((glutGet(GLUT_SCREEN_HEIGHT)-700)/2));
    char *szWindowTitle = "SIMULACION ANIMADA MOVIMIENTO CIRCULAR UNIFORME";
    glutCreateWindow(szWindowTitle);
    toggleGlutWindowMaximizeBox(szWindowTitle);
    init();
    //glutIdleFunc(escena);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard); //
    glutMainLoop();
    return 0;
}

