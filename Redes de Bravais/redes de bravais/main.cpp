//Autor: Jos� Isidro Perla Rosa

#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include "figuras.h"

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

float ratio;

string nombreFigura = ""; //Variable string que almacena el nombre de la figura.
int value=1; //Variable que gurda valores para definir las opciones.

//Definición del modelo de una luz.
GLfloat light_Ambient [4] = { 2.0, 2.0, 2.0, 2.0};
GLfloat light_Diffuse [4] = { 10.0, 1.0, 1.0, 1.0};
GLfloat light_Position [4] = {0.0, 0.0, 5.0, 5.0};

void luces(void){ //Función que define la iluminación.
	glEnable (GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ambient );
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Diffuse );
	glLightfv(GL_LIGHT0, GL_POSITION, light_Position );
}

void glDisplayLines(void); // Did declare the function
			// so I did not have to check for order of the functions

void onlytext(string cadena, float espaciadoX, float espaciadoY, int opc)
{
	float dec=0;

	std::string const s(cadena);
    char onlytext[64];
    sprintf(onlytext, s.c_str());
    glColor3f(1, 1, 1);

    dec = cadena.length();

    dec*=0.10;

    if(opc==0){
		glRasterPos3f(-dec,espaciadoY,0);
    }else if(opc==1){
		glRasterPos3f(espaciadoX,espaciadoY,0);
	}

	for(int i = 0; onlytext[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, onlytext[i]);

}

void elementosInterfaz(void){ //Elementos decorativos de interfaz y extras.

	glColor3f(0,0.4f,0.8f);
    glBegin(GL_POLYGON); //Barra azul
    glVertex2f(-20,-9);
    glVertex2f(-20,-7);
    glVertex2f(20,-7);
    glVertex2f(20,-9);
    glEnd();

    glColor3f(1,1,1);

	glLineWidth(6);
    glBegin(GL_LINES); //Líneas para las flechas
    glVertex2f(-19,-8); //Líneas izquierdas
    glVertex2f(-18,-8);

    glVertex2f(19,-8); //Líneas derechas
    glVertex2f(18,-8);
    glEnd();

    glBegin(GL_TRIANGLES); //Triagulos para las flechas
    glVertex2f(-19.5f,-8); //Triangulo izquierdo
    glVertex2f(-19,-8.5f);
    glVertex2f(-19,-7.5f);

    glVertex2f(19.5f,-8); //Triangulo derecho
    glVertex2f(19,-8.5f);
    glVertex2f(19,-7.5f);
    glEnd();

    onlytext(nombreFigura, -3,-8.2,0); //Nombre de la figura
    onlytext("Menu (click derecho)", -2.5f,10.5f,1); //Instrucciones a mostrar en pantalla
    onlytext("Giro eje x (x-X)", -9,-10.5f,1);
    onlytext("Giro eje Y (y-Y)", -2,-10.5f,1);
    onlytext("Giro eje Z (z-Z)", 5,-10.5f,1);

    onlytext("UNIVERSIDAD DE EL SALVADOR", 12.0f, -10.0f, 1);
    onlytext("Autor: Jose Isidro Perla Rosa", 12.0f, -11.0f, 1);

}

// Initialize the OpenGL window
void init(void)
{
	glPushMatrix();
    glClearColor (0.10,0.10,0.10, 1.0); // Clear the color
	glShadeModel (GL_SMOOTH);               // Set the shading model to GL_SMOOTH
    glEnable (GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST); // Set Line Antialiasing
}

// Draw the lines (x,y,z)
void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the Color Buffer

    luces(); //Se establece la iluminación.

    glPushMatrix(); 	// It is important to push the Matrix before calling
			// glRotatef and glTranslatef

    glRotatef(rotX,1.0,0.0,0.0); // Rotate on x
    glRotatef(rotY,0.0,1.0,0.0); // Rotate on y
    glRotatef(rotZ,0.0,0.0,1.0); // Rotate on z
    glTranslatef(X, Y, Z); 	// Translates the screen left or right,
			// up or down or zoom in zoom out
    // Draw the positive side of the lines x,y,z
    glLineWidth(1);
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

    glEnable(GL_LIGHTING);  //Iniciamos la iluminación

    switch(value){ //Se evalua el valor seleccionado por el menu o con las teclas, para ver que figura se mostrara.

		case 1:
		cubicoSencillo();
		nombreFigura = "Cubico sencillo";
		break;
		case 2:
		cubicoCentradoEnElCuerpo();
		nombreFigura = "Cubico centrado en el cuerpo";
		break;
		case 3:
		cubicoCentradoEnLasCaras();
		nombreFigura = "Cubico centrado en las caras";
		break;
		case 4:
		tetragonalSencillo();
		nombreFigura = "Tetragonal sencillo";
		break;
		case 5:
		tetragonalCentradoEnElCuerpo();
		nombreFigura = "Tetragonal centrado en el cuerpo";
		break;
		case 6:
		romboedrica();
		nombreFigura = "Romboedrica";
		break;
		case 7:
		hexagono();
		nombreFigura = "Hexagono";
		break;
		case 8:
		ortorrombicoSencillo();
		nombreFigura = "Ortorrombico sencillo";
		break;
		case 9:
		ortorrombicoCentradoEnLasBases();
		nombreFigura = "Ortorrombico centrado en las bases";
		break;
		case 10:
		ortorrombicoCentradoEnLasCaras();
		nombreFigura = "Ortorrombico centrado en las caras";
		break;
		case 11:
		ortorrombicoCentradoEnElCuerpo();
		nombreFigura = "Ortorrombico centrado en el cuerpo";
		break;
		case 12:
		monoclinicoSencillo();
		nombreFigura = "Monoclinico sencillo";
		break;
		case 13:
		monoclinicoCentradoEnLasBases();
		nombreFigura = "Monoclinico centrado en las bases";
		break;
		case 14:
		triclinica();
		nombreFigura = "Triclinica";

	}

	glDisable(GL_LIGHTING);

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

    glDisable(GL_DEPTH_TEST);

    //float w  = glutGet(GLUT_WINDOW_HEIGHT)*pow(glutGet(GLUT_WINDOW_WIDTH),-1);
    float w  = glutGet(GLUT_WINDOW_WIDTH);
    float v  = glutGet(GLUT_WINDOW_HEIGHT);
    float aspect =glutGet(GLUT_SCREEN_HEIGHT)*pow(glutGet(GLUT_SCREEN_WIDTH),-1);

    elementosInterfaz(); //Se llama a esta función que agrega elementos para la interfaz del programa.

    glutSwapBuffers();

    glutPostRedisplay();
}

//Definimos el menu.
void menu (int valor)
{
	value=valor; //Se captura el valor en la variable global "value".
}

//Definimos las opciones del menu
void menu_opciones (void)
{
  glutCreateMenu(menu);
  glutAddMenuEntry("Cubico sencillo",1);
  glutAddMenuEntry("Cubico centrado en el cuerpo",2);
  glutAddMenuEntry("Cubico centrado en las caras",3);
  glutAddMenuEntry("Tetragonal sencillo",4);
  glutAddMenuEntry("Tetragonal centrado en el cuerpo",5);
  glutAddMenuEntry("Romboedrica",6);
  glutAddMenuEntry("Hexagono",7);
  glutAddMenuEntry("Ortorrombico sencillo",8);
  glutAddMenuEntry("Ortorrombico centrado en las bases",9);
  glutAddMenuEntry("Ortorrombico centrado en las caras",10);
  glutAddMenuEntry("Ortorrombico centrado en el cuerpo",11);
  glutAddMenuEntry("Monoclinico sencillo",12);
  glutAddMenuEntry("Monoclinico centrado en las bases",13);
  glutAddMenuEntry("Triclinica",14);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// This function is called whenever the window size is changed
void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h); // Set the viewport
    glMatrixMode (GL_PROJECTION); 	// Set the Matrix mode
    glLoadIdentity ();
    //glOrtho(-1,1,-1,1,-1,1);
    gluPerspective(75, (GLfloat) w *pow((GLfloat) h,-1) , 0.10, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt (rotLx, rotLy, 15.0 + rotLz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

//Esta función es usada para la navegación a portir de la opción tecleada.
void keyboard (unsigned char key, int x, int y)
{
switch (key) {   // x,X,y,Y,z,Z usa la función glRotatef()
    case 'x': //Rota la pantalla en el eje x
    rotX -= 0.5f;
    break;
    case 'X': //Sentido opuesto
    rotX += 0.5f;
    break;
    case 'y': //Rota la pantalla en el eje y
    rotY -= 0.5f;
    break;
    case 'Y': //Sentido opuesto
    rotY += 0.5f;
    break;
    case 'z': //Rota la pantalla en el eje z
    rotZ -= 0.5f;
    break;
    case 'Z': //Sentido opuesto
    rotZ += 0.5f;
    break;
}
    glutPostRedisplay(); // Redraw the scene
}

//Función de teclas especiales para definir las opciones con las teclas de desplazamiento.
void specialKey(int key, int x, int y) {

switch(key) {
    case GLUT_KEY_LEFT : //Desplaza las opciones con la tecla de desplazamiento izquierda.
	if(value>1){
		value--;
	}
    break;
    case GLUT_KEY_RIGHT : //Desplaza las opciones con la tecla de desplazamiento derecha.
	if(value>=1 && value<=13){
		value++;
	}
    break;
}
    glutPostRedisplay(); // Redraw the scene
}

// Main entry point of the program
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB); 	// Setup display mode to
						// double buffer and RGB color

	//ratio = glutGet(GLUT_SCREEN_HEIGHT)*pow(glutGet(GLUT_SCREEN_WIDTH),-1);
    //glutInitWindowSize (600,600*ratio); // Set the screen size
    glutInitWindowSize (glutGet(GLUT_SCREEN_WIDTH),glutGet(GLUT_SCREEN_HEIGHT)); // Set the screen size
    glutCreateWindow("SIMULACION REDES DE BRAVAIS"); //recursosbiblio.url.edu.gt/Libros/2013/cmI/3-Estructuras_Cristalinas.pdf
    init ();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    menu_opciones(); //Se llama a la funci�n que establece las opciones del menu.
    glutKeyboardFunc(keyboard); // set window's key callback
    glutSpecialFunc(specialKey); // set window's to specialKey callback
    glutMainLoop();

    return 0;
}
