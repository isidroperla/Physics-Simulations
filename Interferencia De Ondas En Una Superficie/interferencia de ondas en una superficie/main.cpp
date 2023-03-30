#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>
#include <iostream>

//#include <iostream>
//#include <stdio.h>

using namespace std;

double a=0;
double b=0;
double c=0;
double d=0;
double g=0;
double t=0;

//Se crean los correspondientes variables que contendran los datos que el usuario le mande desde QT

double xf1=0; //Posicion en x de la fuente 1
double yf1=0; //Posicion en y de la fuente 1
double k1=0; //Número de ondas de la fuente1
double w1=0; //Velocidad angular de la fuente 1
double xf2=0; //Posicion en x de la fuente 2
double yf2=0; //Posicion en y de la fuente 2
double k2=0; //Número de ondas de fuente 2
double w2=0; //Velocidad angular de la fuente 2

int bandera = 1;
bool activar = false;

void toggleGlutWindowMaximizeBox(char *szWindowTitle)
{
    long dwStyle;
    HWND hwndGlut;

    hwndGlut = FindWindow(NULL, szWindowTitle);

    dwStyle = GetWindowLong(hwndGlut, GWL_STYLE);
    dwStyle ^= WS_MAXIMIZEBOX;
    SetWindowLong(hwndGlut, GWL_STYLE, dwStyle);
}

void TimerRutina(int value) //Este timer sirve para animar la rutina
{
    //ESte timer estara siempre activado mientras aprete la s para encenderlo o la misma para apagarlo
    if(activar==true){ //Activar es la bandera que activa el uso del timer segun la tecla s
   // Do something here.
   if (true) {
	    t+=0.5; //El tiempo va aumentado en 0.5s
		}

    glutPostRedisplay();
	glutTimerFunc(10, TimerRutina, 5000); //Intervalo, 50, tiene 5000 iteraciones para darle bastante libertad al programa de animacion
    }
}

void onlytext(string cadena, double espaciadoX, double espaciadoY) //Funcion que imprime texto.
{
	std::string const s(cadena);
    char onlytext[128];
    sprintf(onlytext, s.c_str());
    glColor3f(0, 0, 0);
    glRasterPos3f(espaciadoX,espaciadoY,0);

    for(int i = 0; onlytext[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, onlytext[i]);
}

void figura(void){

	glColor3f (0, 0, 0);
    glLineWidth(3);

    glBegin(GL_QUADS);

    glVertex2f(5,2.5);
    glVertex2f(-5,2.5);
    glVertex2f(-5,-2.5);
    glVertex2f(5,-2.5);

    glEnd();

    glColor3f (1, 1, 1);
    glLineWidth(3);

    glBegin(GL_QUADS);

    glVertex2f(4.95,2.45);
    glVertex2f(-4.95,2.45);
    glVertex2f(-4.95,-2.45);
    glVertex2f(4.95,-2.45);

    glEnd();

    glPointSize(1); //Se le asigna el tamaño de 1 a los puntos
    glBegin(GL_POINTS);

    //Ondas producidas en (-5,0) y en (5.0)
	for (double j=-2.5; j<2.5; j+=0.01){ // Se barren todas los puntos en vertical desde (i, -2.5) hasta (i, +2.5)
		for (double i=-5; i<5; i+=0.01){ // Se barren todas los puntos en horizontal desde (-5, j) hasta (+5, j)

			b=sqrt(pow((i-xf1),2) + pow(j-yf1,2)); // Esto dará la distancia desde la fuente en 1 (-5,0) hasta (i,j)
			a = (sin(k1*b-w1*t)); // Ecuación de onda debido a la  en la forma sen (kr-wt), aquí arbitrariamente k = 4 y w = 0.1
			d=sqrt(pow((i-xf2),2) + pow(j-yf2,2)); // Esto dará la distancia desde la fuente 2 en (+0.4978,0) hasta (i,j)
			c = (sin(k2*d-w2*t)); // Ecuación de onda en la forma sen (kr-wt), aquí arbitrariamente k = 4 y w = 0.1
			g = abs ((a+c)/2); // La interferencia de ondas está dada por la suma  a+c. Se divide entre dos y se saca el valor absoluto para usar los colores RGB en el siguiente paso
			glColor3f (g, 0, (1-g)); // Esto le da color al punto (i,j). Los máximos son azul puro para cancelación de ondas y rojo puro para interferencia constructiva máxima.
			glVertex2f(i,j); //Se dibujan los puntos

			}

	}
		glEnd();

}

void display(void)
{
	glClearColor(1, 1, 1, 1); //El color de fondo se estable como blanco.
    glClear (GL_COLOR_BUFFER_BIT);

    figura(); //Se invoca a la función figura donde estan los calculos y partes que hacen el dibujado del programa.

    onlytext("Animar automaticamente/Pausar: tecla a o A",-6.5,-5.5);
    onlytext("Animar manualmente: mantener presionada tecla m o M",-6.5,-6.5);

    glFlush ();

}

//-------------------------------------------->

void keyboard (unsigned char key, int x, int y)
{
switch (key) {   // x,X,y,Y,z,Z uses the glRotatef() function
    case 'm': //Tecla que realiza la simulación

    case 'M': //Tecla que realiza la simulación
        t += 0.5f; //Aumentamos las variable t que es variable, y hace la animación mientras el usuario mantenga presionada la tecla.
    break;

    case  'a': //Activa la animacionm automatica del programa

    case  'A': //Activa la animacionm automatica del programa
        bandera*=-1; //Este tipo de materia cmbia cada vez que se apreta la tecla s, la activa y desactiva usando la logica de -1*-1=+1
        if(bandera==-1){
        activar = true;    //Esta bandera activa y permite la animacion
        TimerRutina(0);
        }else{ //En dado caso que bandera sea 1 positivo significa que hay que desactivar la animacion
            activar = false; //La animacion se pasuca haciendo false activar
            TimerRutina(1); //Para asegurarse que no haya animacion
        }
        break;
}
    glutPostRedisplay(); // Redraw the scene
}

// called on special key pressed
void specialKey(int key, int x, int y) {

// The keys below are using the gluLookAt() function for navigation
// Check which key is pressed

switch(key) {
    case GLUT_KEY_LEFT : // Rotate on x axis
    xf1 -= 0.1f;
    break;
    case GLUT_KEY_RIGHT : // Rotate on x axis (opposite)
    xf1 += 0.1f;
    break;
    case GLUT_KEY_UP : // Rotate on y axis
    yf1 += 0.1f;
    break;
    case GLUT_KEY_DOWN : // Rotate on y axis (opposite)
    yf1 -= 0.1f;
    break;
    case GLUT_KEY_PAGE_UP: // Rotate on z axis

    break;
    case GLUT_KEY_PAGE_DOWN:// Rotate on z axis (opposite)

    break;
}
    glutPostRedisplay(); // Redraw the scene
}


//--------------------------------------------->

void init (void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-7, 7, -7, 7, -7, 7);

}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    //Esta es una validación para que se deban recibir 9 argumentos de parte del programa de QT

     if(argc < 9)
    {
		return 1;
	}

	//Asignamos a las correspondientes variables globales, los valores que se han recibido como argumentos de QT de forma ordenada.

    xf1 = atof(argv[1]);
    yf1 = atof(argv[2]);
    k1= atof(argv[3]);
    w1 = atof(argv[4]);
    xf2 = atof(argv[5]);
    yf2 = atof(argv[6]);
    k2 = atof(argv[7]);
    w2 = atof(argv[8]);
    t = atof(argv[9]);

    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(((glutGet(GLUT_SCREEN_WIDTH)-700)/2), ((glutGet(GLUT_SCREEN_HEIGHT)-700)/2));
    char *szWindowTitle = "SIMULACION ANIMADA INTERFERENCIA DE ONDAS EN UNA SUPERFICIE";
    glutCreateWindow(szWindowTitle);
    toggleGlutWindowMaximizeBox(szWindowTitle);
    init ();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard); // set window's key callback
    glutSpecialFunc(specialKey); // set window's to specialKey callback
    glutMainLoop();
    return 0;
}
