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

bool animacionCondicion1 = true;
bool animacionCondicion2 = true;
int activarOpausa=-1;
int punto2Habilitado=1;
double alpha_max=0;

double signOmega=0; //Variable complementaria
double signAlpha=0;
double angulo_Phi; //Variable complementaria
double wmax; //Variable complementaria
double theta;
double aux_theta=0;
double w=0;
double wo=0;
double alpha=0;
double t=0; //timetest

double x_1=1.5;
double y_1=-1.0;
double r1;
double v1;
double ac1;
double vector_v1[2];
double vector_ac1[2];
double x_v1;
double y_v1;
double at1;
double vector_at1[2];
double anguloBeta1;

double x_2;
double y_2;
double r2;
double v2;
double ac2;
double vector_v2[2];
double vector_ac2[2];
double x_v2;
double y_v2;
double at2;
double vector_at2[2];
double anguloBeta2;

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
   if (animacionCondicion1==true and animacionCondicion2==true){

		t += 0.025;

		aux_theta = theta;
		theta = (wo*t+(0.5)*alpha*pow(t,2));

        w = wo + alpha*t;

        if(x_1>=0 && y_1>=0){
			anguloBeta1 = atan(abs((y_1/x_1)));
		}
		else if(x_1<0 && y_1>=0){
			anguloBeta1 = M_PI-atan(abs((y_1/x_1)));
		}
		else if(x_1<0 && y_1<0){
			anguloBeta1 = M_PI+atan(abs((y_1/x_1)));
		}
		else if(x_1>=0 && y_1<0){
			anguloBeta1 = (2*M_PI)-atan(abs((y_1/x_1)));
		}

		if(x_2>=0 && y_2>=0){
			anguloBeta2 = atan(abs((y_2/x_2)));
		}
		else if(x_2<0 && y_2>=0){
			anguloBeta2 = M_PI-atan(abs((y_2/x_2)));
		}
		else if(x_2<0 && y_2<0){
			anguloBeta2 = M_PI+atan(abs((y_2/x_2)));
		}
		else if(x_2>=0 && y_2<0){
			anguloBeta2 = (2*M_PI)-atan(abs((y_2/x_2)));
		}

		//-------------------------->Datos punto 1

		x_v1 = r1*cos(theta*(M_PI/180)+anguloBeta1);
		y_v1 = r1*sin(theta*(M_PI/180)+anguloBeta1);

		r1 = sqrt(pow(x_1,2) + pow(y_1,2));

		v1 = sqrt(pow((-w*y_1),2) + pow((w*x_1),2));

		ac1 = sqrt(pow(pow(-w,2)*x_1,2) + pow(pow(-w,2)*y_1,2));

		vector_v1[0] = -w*y_v1;
		vector_v1[1] = w*x_v1;

		vector_ac1[0] = -pow(w,2)*x_v1;
		vector_ac1[1] = -pow(w,2)*y_v1;

		at1 = sqrt(pow((-alpha*y_1),2) + pow((alpha*x_1),2));

		vector_at1[0] = -alpha*y_v1;
		vector_at1[1] = alpha*x_v1;

		//-------------------------->Datos punto 2

		x_v2 = r2*cos(theta*(M_PI/180)+anguloBeta2);
		y_v2 = r2*sin(theta*(M_PI/180)+anguloBeta2);

		r2 = sqrt(pow(x_2,2) + pow(y_2,2));

		v2 = sqrt(pow((-w*y_2),2) + pow((w*x_2),2));

		ac2 = sqrt(pow(pow(-w,2)*x_2,2) + pow(pow(-w,2)*y_2,2));

		vector_v2[0] = -w*y_v2;
		vector_v2[1] = w*x_v2;

		vector_ac2[0] = -pow(w,2)*x_v2;
		vector_ac2[1] = -pow(w,2)*y_v2;

		at2 = sqrt(pow((-alpha*y_2),2) + pow((alpha*x_2),2));

		vector_at2[0] = -alpha*y_v2;
		vector_at2[1] = alpha*x_v2;


        if(abs(w)<=1){
            wmax=w;
        }else if(w>1){
            wmax=1;
        }else if(w<-1){
			wmax=-1;
			}

		if(w>=0){
			signOmega=1;
		}
		else{
			signOmega=-1;
		}

		if(alpha>=0){
		signAlpha=1;
		}
		else{
			signAlpha=-1;
		}

		if(t>90){
			animacionCondicion2=false;
			}

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
	glRotated((anguloPhi(x_1, y_1)*(180/M_PI))-90*signOmega,0,0,1);
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


	glLineWidth(0.5);

	//Vector aceleracion tagencial punto#1

	glColor3f(0.796, 0.4, 0.003);
	glBegin(GL_LINES);
	glVertex2f(x_1,y_1); //Linea que conecta punto#1 con flecha del vector v1
	glVertex2f((x_1-alpha_max*y_1), (y_1+alpha_max*x_1));
	glEnd();

	glPushMatrix();
	glTranslatef((x_1-alpha_max*y_1),(y_1+alpha_max*x_1),0);
	glRotated((anguloPhi(x_1, y_1)*(180/M_PI))-90*signAlpha,0,0,1);
	glBegin(GL_TRIANGLES); //Triaungulo de la flecha vector verde
	glVertex2f(0,0);
	glVertex2f(0.075,0.075);
	glVertex2f(0.075,-0.075);
	glEnd();
	glPopMatrix();

	glLineWidth(2.5);

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
	glRotated((anguloPhi(x_2, y_2)*(180/M_PI))-90*signOmega,0,0,1);
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

	glLineWidth(0.5);

	//Vector aceleracion tagencial punto#2

	glColor3f(0.796, 0.4, 0.003);
	glBegin(GL_LINES);
	glVertex2f(x_2,y_2); //Linea que conecta punto#1 con flecha del vector v1
	glVertex2f((x_2-alpha_max*y_2), (y_2+alpha_max*x_2));
	glEnd();

	glPushMatrix();
	glTranslatef((x_2-alpha_max*y_2),(y_2+alpha_max*x_2),0);
	glRotated((anguloPhi(x_2, y_2)*(180/M_PI))-90*signAlpha,0,0,1);
	glBegin(GL_TRIANGLES); //Triaungulo de la flecha vector verde
	glVertex2f(0,0);
	glVertex2f(0.075,0.075);
	glVertex2f(0.075,-0.075);
	glEnd();
	glPopMatrix();

	glLineWidth(2.5);

	glPointSize(10);
	glColor3f(1,0,1);
	glBegin(GL_POINTS);
	glVertex2f(x_2,y_2); //Punto#2(rosa)
	glEnd();

	onlytext("2", x_2, y_2 ,0.874, 0.368, 0.047, true);
	}

	onlytext("1", x_1, y_1 ,0.874, 0.368, 0.047, true);

	glColor3f(0,0,0); //Color de letras

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
    glRotatef(theta*(180/M_PI),0,0,1);
    figura();
    glPopMatrix();

    //Texto complementario
    onlytext("Punto 1", -4.0, 4.7, 0, 0, 0, true);
    onlytext("Activar/pausar animacion:", -4.5, -4.22, 0,0,0, true);
    onlytext("Tecla 'x' o 'X'", -4.0, -4.52, 0,0,0, true);

    onlytext("->", -4.9, 2.63, 0,0,0, false);
    onlytext("->", -4.9, 2.23, 0,0,0, false);
	onlytext("->", -4.9, 1.43, 0,0,0, false);

	//Datos del punto tiempo y angulo
    text("t: %.3f s", t, -0.8, 4.7);
    text("angulo: %.3f deg", theta*(180/M_PI), -0.8, 4.3);
    text("w: %.2f rad/s", w, -0.8, 3.9);
    text("w : %.2f rad/s", wo, -0.8, 3.5); onlytext("0", -0.66, 3.42, 0,0,0, false);
    text("alfa: %.2f rad/s^2", alpha, -0.8, 3.1);

    //Datos del punto 1
    text("r : %.3f m", r1, -4.9, 4.5); onlytext("1", -4.83, 4.42, 0,0,0, false);
    text("w : %.3f rad/s", w, -4.9, 4.1); onlytext("1", -4.76, 4.02, 0,0,0, false);
    text("alfa : %.3f rad/s^2", alpha, -4.9, 3.7); onlytext("1", -4.59, 3.62, 0,0,0, false);
    text("v : %.3f m/s", v1, -4.9, 3.3); onlytext("1", -4.83, 3.22, 0,0,0, false);
    text("a  : %.3f m/s^2", ac1, -4.9, 2.9); onlytext("c1", -4.83, 2.82, 0,0,0, false);
    text("v : [(%.2f i) +", vector_v1[0], -4.9, 2.5); text(" (%.2f j)] m/s", vector_v1[1], -3.6, 2.5); onlytext("1", -4.83, 2.42, 0,0,0, false);
    text("a  : [(%.2f i) +", vector_ac1[0], -4.9, 2.1); text("(%.2f j)] m/s^2", vector_ac1[1], -3.5, 2.1); onlytext("c1", -4.83, 2.02, 0,0,0, false);
    text("a  : %.3f rad/s^2", at1, -4.9, 1.7); onlytext("t1", -4.81, 1.62, 0,0,0, false);
    text("a  : [(%.2f i) +", vector_at1[0], -4.9, 1.3); text("(%.2f j)] m/s^2", vector_at1[1], -3.5, 1.3); onlytext("t1", -4.81, 1.22, 0,0,0, false);

    if(punto2Habilitado==1){

	onlytext("->", 2.1, 2.63, 0,0,0, false);
    onlytext("->", 2.1, 2.23, 0,0,0, false);
    onlytext("->", 2.1, 1.43, 0,0,0, false);

    //Datos del punto 2
    onlytext("Punto 2", 3.0, 4.7, 0,0,0,true);
    text("r : %.3f m", r2, 2.1, 4.5); onlytext("2", 2.17, 4.42, 0,0,0, false);
    text("w : %.3f rad/s", w, 2.1, 4.1); onlytext("2", 2.24, 4.02, 0,0,0, false);
    text("alfa : %.3f rad/s^2", alpha, 2.1, 3.7); onlytext("2", 2.41, 3.62, 0,0,0, false);
    text("v : %.3f m/s", v2, 2.1, 3.3); onlytext("2", 2.17, 3.22, 0,0,0, false);
    text("a  : %.3f m/s^2", ac2, 2.1, 2.9); onlytext("c2", 2.17, 2.82, 0,0,0, false);
    text("v : [(%.2f i) +", vector_v2[0], 2.1, 2.5); text(" (%.2f j)] m/s", vector_v2[1], 3.4, 2.5); onlytext("2", 2.17, 2.42, 0,0,0, false);
    text("a  : [(%.2f i) +", vector_ac2[0], 2.1, 2.1); text("(%.2f j)] m/s^2", vector_ac2[1], 3.5, 2.1); onlytext("c2", 2.17, 2.02, 0,0,0, false);
	text("a  : %.3f rad/s^2", at2, 2.1, 1.7); onlytext("t2", 2.19, 1.62, 0,0,0, false);
    text("a  : [(%.2f i) +", vector_at2[0], 2.1, 1.3); text("(%.2f j)] m/s^2", vector_at2[1], 3.4, 1.3); onlytext("t2", 2.19, 1.22, 0,0,0, false);

	}

    //Cuadro de los datos del punto 1
    glBegin(GL_LINE_LOOP);
	glVertex2f(-2,1.1);
	glVertex2f(-2,5);
	glVertex2f(-5,5);
	glVertex2f(-5,1.1);
	glEnd();

    if(punto2Habilitado==1){
    //Cuadro de los datos del punto 2
    glBegin(GL_LINE_LOOP);
	glVertex2f(2,1.1);
	glVertex2f(2,5);
	glVertex2f(5,5);
	glVertex2f(5,1.1);
	glEnd();
	}

	//Cuadro de los datos generales
	glBegin(GL_LINE_LOOP);
	glVertex2f(-2,2.9);
	glVertex2f(-2,5);
	glVertex2f(2,5);
	glVertex2f(2,2.9);
	glEnd();

    //Leyenda

    onlytext("Aceleracion centripeta", 2.7, -4.05, 0,0,0, true);
    onlytext("Aceleracion tangencial", 2.7, -4.45, 0,0,0, true);
    onlytext("Velocidad tangencial", 2.7, -4.85, 0,0,0, true);

    glBegin(GL_LINES);
    glColor3f(1,0,0);
    glVertex2f(1.5, -4.0);
    glVertex2f(2.5, -4.0);
    glColor3f(0.796, 0.4, 0.003);
    glVertex2f(1.5, -4.4);
    glVertex2f(2.5, -4.4);
    glColor3f(0, 1, 0);
    glVertex2f(1.5, -4.8);
    glVertex2f(2.5, -4.8);
    glEnd();

    if(animacionCondicion2==false){
		onlytext("LIMITE DE TIEMPO ALCANZADO", -4.5, -3.7, 0,0,0, true);
		}

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

    activarOpausa*=-1;
	if(activarOpausa>0){
		animacionCondicion1 = true;
		TimerRutina(0);
		}else{
			animacionCondicion1 = false;
			}
    break;


}
    glutPostRedisplay(); // Redraw the scene
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    if(argc < 9)
    {
        cout << "Faltan " << 9 - argc << " argumentos. ¿Abrió la interfaz grafica primero?";
		return 1;
	}

    wo = atof(argv[1]);
    wmax = atof(argv[2]);
    alpha = atof(argv[3]);
    alpha_max = atof(argv[4]);
    x_1 = atof(argv[5]);
    y_1= atof(argv[6]);
    x_2 = atof(argv[7]);
    y_2 = atof(argv[8]);
    punto2Habilitado = atoi(argv[9]);

    w = wo + alpha*t;

    if(w>=0){
			signOmega=1;
		}
		else{
			signOmega=-1;
		}

		if(alpha>=0){
		signAlpha=1;
		}
		else{
			signAlpha=-1;
		}

    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(((glutGet(GLUT_SCREEN_WIDTH)-700)/2), ((glutGet(GLUT_SCREEN_HEIGHT)-700)/2));
    char *szWindowTitle = "SIMULACION ANIMADA MOVIMIENTO CIRCULAR ACELERADO";
    glutCreateWindow(szWindowTitle);
    toggleGlutWindowMaximizeBox(szWindowTitle);
    init();
    //glutIdleFunc(escena);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard); //
    glutMainLoop();
    return 0;
}
