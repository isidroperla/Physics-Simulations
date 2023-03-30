#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <cmath>
#include <iostream>
#include <ctime>
#include "SOIL.h"
#define M_PI 3.14159265358979323846 //Definicion de la constante PI

using namespace std;

GLfloat X = 0.0f; // Translate screen to x direction (left or right)
GLfloat Y = 0.0f; // Translate screen to y direction (up or down)
GLfloat Z = 0.0f; // Translate screen to z direction (zoom in or out)
GLfloat rotX = 0.0f; // Rotate screen on x axis
GLfloat rotY = 0.0f; // Rotate screen on y axis
GLfloat rotZ = 0.0f; // Rotate screen on z axis
GLfloat rotLx = 0.0f; // Translate screen by using the glulookAt function (left or right)
GLfloat rotLy = 0.0f; // Translate screen by using the glulookAt function (up or down)
GLfloat rotLz = 0.0f; // Translate screen by using the glulookAt function (zoom in or out)

double x; //Posicion en x donde se movera el objeto con la animacion
double y; //Posicion en y donde se movera el objeto con la animacion
double r=0; //Largo de la rampa inclinada
double h=0; //Alto de la rampa
double a = 0.05; //Ancho de la rampa
double R=0.01; //radio de la esfera, cilindo
double theta; //Angulo de inclinacion de la rampa
double delta; //Angulo extra
double acm; //Aceleracion centro de masa
double vcm; //Velocidad centro de masa
double s; //Deplazamiento
double t; //Tiempo
double tMod; //t veces por p
const double g=9.8; //Constante de la gravedad en la tierra

double w; //Validacion tmax
int p=0; //Controla de precisión del tiempo

double theta_giro; //Angulo para el giro de las figuras

int opc=0; //Variable para definir que figura se va a dibujar
bool animacion = false; //Variable boleeana para activar y desactivar la animacionn
int activarOpausa=-1; //Variable para validar la animcacion
int iterations = 360; //Numero de iterasiones del timer

GLuint texture[0];

void TimerRutina(int value) //Este timer sirve para animar la rutina
{
	//La animacion pausa cuando el valor de s es mayor que cero

	w= (sqrt((2*r)/acm)/p);

	if(t+(0.001/p)>=(w)){
		animacion = false;
	}

	if (animacion==true){

		t += 0.001;
		tMod = t*p;

		glutPostRedisplay();
		glutTimerFunc(p, TimerRutina, iterations);
		--iterations;
	}
}

void text(string valor, double dato, double espaciadoX, double espaciadoY) //Funcion que imprime texto en tiempo real de las variables
{
	std::string const s(valor);
    char text[64];
    sprintf(text, s.c_str(), dato);
    glColor3f(0, 0, 0);
    glRasterPos3f(espaciadoX,espaciadoY,0);

    for(int i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
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
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, onlytext[i]);
	}else{
		for(int i = 0; onlytext[i] != '\0'; i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, onlytext[i]);
		}
}

void mapear(int map) //Funcion para definir el mapeo de las texturas de las figuras
{

    glBindTexture(GL_TEXTURE_2D, texture[map]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);

}

void glDisplayLines(void); // Did declare the function
			// so I did not have to check for order of the functions

// Initialize the OpenGL window
void init(void)
{
	glClearColor (1.0, 1.0, 1.0, 1.0); // Clear the color
    glShadeModel (GL_FLAT); // Set the shading model to GL_FLAT
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST); // Set Line Antialiasing
    glEnable(GL_DEPTH_TEST); //Hace comparaciones de profundidad y actualizar el buffer de profundidad.

         texture[0] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
    (
        "textura_madera.bmp",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

     texture[1] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
    (
        "textura_pelota.bmp",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    texture[2] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
    (
        "textura_barril.bmp",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

}

void esfera() //Funcion para dibujar la esfera
{

	glEnable(GL_TEXTURE_2D);
	mapear(1);

    GLUquadricObj *q;
    q=gluNewQuadric();

    gluQuadricOrientation(q,GLU_INSIDE );
    gluQuadricDrawStyle(q, GLU_FILL);
    gluQuadricNormals(q, GLU_SMOOTH);
    gluQuadricTexture(q, GL_TRUE);

    glNormal3f(0.0f, 0.0f, 1.0f);
    gluSphere(q,R,16,16);
    gluDeleteQuadric(q);
    glDisable(GL_TEXTURE_2D);

}

void cilindro() //Funcion para dibujar el cilindro
{

	glEnable(GL_TEXTURE_2D);
	mapear(2);
	GLUquadricObj *q;
	q=gluNewQuadric();
	glPushMatrix();
	glTranslated(0,0,-0.015);
	gluQuadricOrientation(q,GLU_INSIDE );
	gluQuadricDrawStyle(q, GLU_FILL);
	gluQuadricNormals(q, GLU_SMOOTH);
	gluQuadricTexture(q, GL_TRUE);

	glNormal3f(0.0f, 0.0f, 1.0f);
    gluCylinder(q, R, R, 0.03, 15, 5);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,0,0.015);
	gluDisk(q,0,R,32,32);
	glPopMatrix();

	glPushMatrix();
    glTranslated(0,0,-0.015);
	gluDisk(q,0,R,32,32);
	glPopMatrix();

	gluDeleteQuadric(q);
	glDisable(GL_TEXTURE_2D);

}

void cubo() //Funcion para dibujar el cubo
{
	glColor3f(0.549, 0.549, 0.549);
	glPushMatrix();
	glRotated(abs(atan(r/h))*(180/M_PI),0,0,1);
    glutSolidCube(2*R);
	glPopMatrix();

}

void escenario() //Funcion para dibujar la rampa
{

	glEnable(GL_TEXTURE_2D);
    mapear(0);
	//plano inclinado
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0,0,a);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-r*cos(theta),h,a);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-r*cos(theta),h,-a);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0,0,-a);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
    mapear(0);
	//Parte derecha
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0,0,a);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-r*cos(theta),0,a);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-r*cos(theta),h,a);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0,0,a);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
    mapear(0);
	//Parte izquierda
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0,0,-a);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-r*cos(theta),0,-a);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-r*cos(theta),h,-a);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0,0,-a);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
    mapear(0);
	//Parte del fondo
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-r*cos(theta),0,a);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-r*cos(theta),h,a);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-r*cos(theta),h,-a);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-r*cos(theta),0,-a);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
    mapear(0);
	//Parte de abajo
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0,0,a);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-r*cos(theta),0,a);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-r*cos(theta),0,-a);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0,0,-a);
	glEnd();
	glDisable(GL_TEXTURE_2D);

}

// Draw the lines (x,y,z)
void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the Color Buffer

    text("h:%.3f m", h, (-0.2)*(r*cos(theta)), 0.3*r);
	text("r:%.3f m", r, (0.08)*(r*cos(theta)), 0.282*r);
	text("t:%.3f s", tMod, (0.22)*(r*cos(theta)), 0.2*r);
	text("s:%.3f m", (s+r), (0.222)*(r*cos(theta)), 0.17*r);
	text("vcm:%.3f m/s", vcm, (0.225)*(r*cos(theta)), 0.14*r);
	text("acm:%.3f m/s^2", acm, (0.2278)*(r*cos(theta)), 0.11*r);

	onlytext("Girar eje x: 'x' y 'X'", (-1.57)*(r*cos(theta)), -1.10*r, 0,0,0, true);
	onlytext("Girar eje y: 'y' y 'Y'", (-1.69)*(r*cos(theta)), -1.32*r, 0,0,0, true);
	onlytext("Girar eje z: 'z' y 'Z'", (-1.83)*(r*cos(theta)), -1.59*r, 0,0,0, true);
	onlytext("Resetear vista: 'o'", (-1.94)*(r*cos(theta)), -1.84*r, 0,0,0, true);

	onlytext("Animar 'n' o 'N'", (0.31)*(r*cos(theta)), -0.20*r, 0,0,0, true);

	onlytext("Arriba: 'Tecla arriba'", (0.27)*(r*cos(theta)), -0.27*r, 0,0,0, true);
	onlytext("Abajo: 'Tecla abajo'", (0.28)*(r*cos(theta)), -0.32*r, 0,0,0, true);
	onlytext("Izquierda: 'Tecla izquierda'", (0.20)*(r*cos(theta)), -0.43*r, 0,0,0, true);
	onlytext("Derecha: 'Tecla derecha'", (0.23)*(r*cos(theta)), -0.48*r, 0,0,0, true);

    glPushMatrix(); 	// It is important to push the Matrix before calling
			// glRotatef and glTranslatef

    glRotatef(rotX,1.0,0.0,0.0); // Rotate on x
    glRotatef(rotY,0.0,1.0,0.0); // Rotate on y
    glRotatef(rotZ,0.0,0.0,1.0); // Rotate on z
    glTranslatef(X, Y, Z); 	// Translates the screen left or right,
			// up or down or zoom in zoom out
    // Draw the positive side of the lines x,y,z

    glBegin(GL_LINES);
    glColor3f (0.0, 1.0, 0.0); // Green for x axis
    glVertex3f(0,0,0);
    glVertex3f(10,0,0);
    glColor3f(1.0,0.0,0.0); // Red for y axis
    glVertex3f(0,0,0);
    glVertex3f(0,10,0);
    glColor3f(0.0,0.0,1.0); // Blue for z axis
    glVertex3f(0,0,0);
    glVertex3f(0,0,10);
    glEnd();

	escenario(); //Esta funcion llama a la figura de la rampa

    theta = asin(abs(h/r));
	delta = (M_PI/2)-theta;

	if(opc==1){

		acm = (0.7143)*g*sin(theta);

		s = -r + (0.5)*acm*pow(tMod,2);

		vcm = acm*tMod;

		x = s*cos(theta);
		y = s*sin(theta);

		//Formulas de la rotacion del objeto
		theta_giro = ((0.5)*(acm/R)*pow(tMod,2))*(180/M_PI);

		glPushMatrix();
		glTranslated((x+R*cos(delta)), (abs(y)+R*sin(delta)), 0);
		glRotatef(-theta_giro,0,0,1);
		esfera();
		glPopMatrix();

	}else if(opc==2){

		acm = (0.6667)*g*sin(theta);

		s = -r + (0.5)*acm*pow(tMod,2);

		vcm = acm*tMod;

		x = s*cos(theta);
		y = s*sin(theta);

		//Formulas de la rotacion del objeto
		theta_giro = ((0.5)*(acm/R)*pow(tMod,2))*(180/M_PI);

		glPushMatrix();
		glTranslated((x+R*cos(delta)), (abs(y)+R*sin(delta)), 0);
		glRotatef(-theta_giro,0,0,1);
		cilindro();
		glPopMatrix();

	}else if(opc==3){

		acm = g*sin(theta);

		s = -r + (0.5)*acm*pow(tMod,2);

		vcm = acm*tMod;

		x = s*cos(theta);
		y = s*sin(theta);

		//Formulas de la rotacion del objeto
		theta_giro = ((0.5)*(acm/R)*pow(tMod,2))*(180/M_PI);

		glPushMatrix();
		glTranslated((x+R*cos(delta)), (abs(y)+R*sin(delta)), 0);
		cubo();
		glPopMatrix();

	}

    // Dotted lines for the negative sides of x,y,z
    glEnable(GL_LINE_STIPPLE); 	// Enable line stipple to use a
				// dotted pattern for the lines
    glLineStipple(1, 0x0101); 	// Dotted stipple pattern for the lines
    glBegin(GL_LINES);
    glColor3f (0.0, 1.0, 0.0); 	// Green for x axis
    glVertex3f(-10,0,0);
    glVertex3f(0,0,0);
    glColor3f(1.0,0.0,0.0); 	// Red for y axis
    glVertex3f(0,0,0);
    glVertex3f(0,-10,0);
    glColor3f(0.0,0.0,1.0); 	// Blue for z axis
    glVertex3f(0,0,0);
    glVertex3f(0,0,-10);
    glEnd();
    glDisable(GL_LINE_STIPPLE); 	// Disable the line stipple
    glPopMatrix(); 		// Don't forget to pop the Matrix
    glFlush();
    glutSwapBuffers();
    glutPostRedisplay(); // Redraw the scene
}

// This function is called whenever the window size is changed
void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h); // Set the viewport
    glMatrixMode (GL_PROJECTION); 	// Set the Matrix mode
    glLoadIdentity ();
    gluPerspective(75, (GLfloat) w /(GLfloat) h , 0.10, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt (0.3*r+ rotLx,0.2*r+  rotLy, 0.5*r + rotLz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

//This function is used for the navigation keys
void keyboard (unsigned char key, int x, int y)
{
switch (key){   // x,X,y,Y,z,Z uses the glRotatef() function
    case 'x': // Rotates screen on x axis
    rotX -= 0.5f;
    break;
    case 'X': // Opposite way
    rotX += 0.5f;
    break;
    case 'y': // Rotates screen on y axis
    rotY -= 0.5f;
    break;
    case 'Y': // Opposite way
    rotY += 0.5f;
    break;
    case 'z': // Rotates screen on z axis
    rotZ -= 0.5f;
	break;

	case 'n':

	case 'N':

	activarOpausa*=-1;

	if(activarOpausa>0){
		animacion = true;
		TimerRutina(0);
		}
		else{
			animacion = false;
		}

	break;

    case 'o': // Default, resets the translations vies from starting view
    X = Y = 0.0f;
    Z = 0.0f;
    rotX = 0.0f;
    rotY = 0.0f;
    rotZ = 0.0f;
    rotLx = 0.0f;
    rotLy = 0.0f;
    rotLz = 0.0f;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt (0.3*r+ rotLx,0.2*r+  rotLy, 0.5*r + rotLz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    break;
	}
    glutPostRedisplay(); // Redraw the scene
}

// called on special key pressed
void specialKey(int key, int x, int y)
{

// The keys below are using the gluLookAt() function for navigation
// Check which key is pressed

switch(key){
    case GLUT_KEY_LEFT : // Rotate on x axis
    X += 0.1f;
    break;
    case GLUT_KEY_RIGHT : // Rotate on x axis (opposite)
    X -= 0.1f;
    break;
    case GLUT_KEY_UP : // Rotate on y axis
    Y -= 0.1f;
    break;
    case GLUT_KEY_DOWN : // Rotate on y axis (opposite)
    Y += 0.1f;
    break;
    case GLUT_KEY_PAGE_UP: // Rotate on z axis
    Z -= 0.1f;
    break;
    case GLUT_KEY_PAGE_DOWN:// Rotate on z axis (opposite)
    Z += 0.1f;
    break;
	}
    glutPostRedisplay(); // Redraw the scene
}

// Main entry point of the program
int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    if(argc < 3)
    {
        cout << "Faltan " << 3 - argc << " argumentos. ¿Abrió la interfaz grafica primero?";
		return 1;
	}

    h = atof(argv[1]);
    r = atof(argv[2]);
    opc = atoi(argv[3]);
    p = atoi(argv[4]);

    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 	// Setup display mode to
						// double buffer and RGB color
    glutInitWindowSize (glutGet(GLUT_SCREEN_WIDTH),glutGet(GLUT_SCREEN_HEIGHT)); // Set the screen size
    glutCreateWindow("SIMULACION ANIMADA MOVIMIENTO RECTILINEO UNIFORMEMENTE VARIADO");
    init ();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard); // set window's key callback
    glutSpecialFunc(specialKey); // set window's to specialKey callback
    glutMainLoop();

    return 0;
}
