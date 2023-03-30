#include <iostream>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <string.h>
#include <stdio.h>
#include <cmath>

using namespace std;

GLfloat X = 0.0f; //Trasladar la pantalla a la dirección x (izquierda o derecha)
GLfloat Y = 0.0f; //Trasladar la pantalla a la dirección y (arriba o abajo)
GLfloat Z = 0.0f; //Trasladar la pantalla a la dirección z (acercar o alejar)
GLfloat rotX = 0.0f; //Rotar pantalla en el eje x.
GLfloat rotY = 0.0f; //Rotar pantalla en el eje y.
GLfloat rotZ = 0.0f; //Rotar pantalla en el eje z.
GLfloat rotLx = 0.0f; //Trasladar la pantalla usando la funciín glulookAt  (izquierda o derecha).
GLfloat rotLy = 0.0f; //Trasladar la pantalla usando la funciín glulookAt  (arriba o abajo).
GLfloat rotLz = 0.0f; //Trasladar la pantalla usando la funciín glulookAt  (acercar o alejar).

float radioEsferaGaussiana = 2.0f; //Radio objeto principal.
float radioEsferaPrincipal = 0.0f; //Radio superficie gaussiana.
float E=0.0f; //Campo eléctrico.
float ke = 9*pow(10,9); //Constante de Coulomb.
float Q=0.0f; //Carga.
float a=0.0f; //a
float lambda=0.0f; //Densidad lineal de carga.
float e0 = 8.854*pow(10,-12); //Permitividad del espacio libre.
float sigma = 0.0f; //Densidad superficial de carga.
int obj=1; //Objeto seleccionado.
bool activarLineas=false; //Variable boleana para activar las lineas de campo.
int transparenciaA=1; //Variable para activar/desactivar transparencia del objeto principal.
int transparenciaB=0; //Variable para activar/desactivar transparencia del objeto gaussiano.
bool girar = false;

void glDisplayLines(void); //Se declara la funcion.
			//Así que no se tiene que verificar el orden de las funciones.

//Inicializar la ventana de OpenGL.
void init(void)
{
    glClearColor(0.10,0.10,0.10, 1.0); //Limpiar el color.
    glShadeModel (GL_SMOOTH); //Se establece el modelo de sombreado en GL_SMOOTH.
    glEnable (GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST); //Establece línea Antialiasing

    GLfloat light_ambient[] = {0.5, 0.5, 0.5, 1.0}; //Parámetros de la iluminación
    GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_position[] = {-2, 1.0, 0.0, 0.0};

    glLightfv (GL_LIGHT0, GL_AMBIENT, light_ambient); //Establecemos los parametros a la luz.
    glLightfv (GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv (GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv (GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING); //Iniciamos la iluminación.
    glEnable(GL_LIGHT0);    //Establecemos una fuente de luz.
    glEnable(GL_NORMALIZE); //Establecemos text("E: %.3f N/C", 4.5, -3.9-(rotLz/3.6), 4.5+(rotLz/3.6));la normalización de los vectores. Esto sirve para la iluminación de los polígonos.
}

void text(string valor, float dato, float espaciadoX, float espaciadoY)
{
	std::string const s(valor);
    char text[100];
    sprintf(text, s.c_str(), dato);
    glColor3f(1, 1, 1);
    glRasterPos3f(espaciadoX,espaciadoY,0);

    for(int i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
}

void onlytext(string cadena, double espaciadoX, double espaciadoY)
{
	std::string const s(cadena);
    char onlytext[100];
    sprintf(onlytext, s.c_str());
    glColor3f(1, 1, 1);
    glRasterPos3f(espaciadoX,espaciadoY,0);

		for(int i = 0; onlytext[i] != '\0'; i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, onlytext[i]);
}

void material(GLfloat ar, GLfloat ag, GLfloat ab, GLfloat dr, GLfloat dg, GLfloat db, GLfloat sr, GLfloat sg, GLfloat sb, GLfloat shiness)
{
    GLfloat ambient[] = {ar, ag, ab}; //Creamos loa arrays con los parámetros.
    GLfloat diffuse[] = {dr, dg, db};
    GLfloat specular[] = {sr, sg, sb};
    GLfloat shine[] = {shiness};

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient); //Establecemos el material, ponemos GL_FRONT_AND_BACK para que el material se establezca en ambos lados.
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shine);
}

void lineasDeCampoEsfera(void){

	float r = 2*radioEsferaGaussiana;

	glEnable(GL_COLOR_MATERIAL);
	glColor3f(0.8314,0.6862,0.2157); //Color dorado.

	//Parte I
	glBegin(GL_LINES);
	glVertex3f(0,0,0);
	glVertex3f(r,r,r);

	glVertex3f(0,0,0);
	glVertex3f(r,r,-r);

	glVertex3f(0,0,0);
	glVertex3f(r,-r,r);

	glVertex3f(0,0,0);
	glVertex3f(-r,r,r);

	glVertex3f(0,0,0);
	glVertex3f(r,-r,-r);

	glVertex3f(0,0,0);
	glVertex3f(-r,r,-r);

	glVertex3f(0,0,0);
	glVertex3f(-r,-r,r);

	glVertex3f(0,0,0);
	glVertex3f(-r,-r,-r);

	//Parte II
	glVertex3f(0,0,0);
	glVertex3f(r,0,0);

	glVertex3f(0,0,0);
	glVertex3f(-r,0,0);

	glVertex3f(0,0,0);
	glVertex3f(0,r,0);

	glVertex3f(0,0,0);
	glVertex3f(0,-r,0);

	glVertex3f(0,0,0);
	glVertex3f(0,0,r);

	glVertex3f(0,0,0);
	glVertex3f(0,0,-r);
	glEnd();

	glDisable(GL_COLOR_MATERIAL);

}

void lineasDeCampoVarilla(void){

	float r = 2*radioEsferaGaussiana;
	float h_medio = 2.5;

	glEnable(GL_COLOR_MATERIAL);
	glColor3f(0.8314,0.6862,0.2157); //Color dorado.

	glBegin(GL_LINES);
	//Parte I
	glVertex3f(0,0,0);
	glVertex3f(r,0,r);

	glVertex3f(0,0,0);
	glVertex3f(-r,0,r);

	glVertex3f(0,0,0);
	glVertex3f(-r,0,-r);

	glVertex3f(0,0,0);
	glVertex3f(r,0,-r);

	//Parte II
	glVertex3f(0,h_medio,0);
	glVertex3f(r,h_medio,0);

	glVertex3f(0,h_medio,0);
	glVertex3f(-r,h_medio,0);

	glVertex3f(0,h_medio,0);
	glVertex3f(0,h_medio,r);

	glVertex3f(0,h_medio,0);
	glVertex3f(0,h_medio,-r);

	//Parte III
	glVertex3f(0,-h_medio,0);
	glVertex3f(r,-h_medio,0);

	glVertex3f(0,-h_medio,0);
	glVertex3f(-r,-h_medio,0);

	glVertex3f(0,-h_medio,0);
	glVertex3f(0,-h_medio,r);

	glVertex3f(0,-h_medio,0);
	glVertex3f(0,-h_medio,-r);
	glEnd();

	glDisable(GL_COLOR_MATERIAL);

}

void lineasDeCampoPlano(void){

	float r = 4.5*radioEsferaGaussiana;
	float a = 2.5;

	glEnable(GL_COLOR_MATERIAL);
	glColor3f(0.8314,0.6862,0.2157); //Color dorado.

	glPushMatrix();
	glTranslated(-(r/2),0,0);
	glBegin(GL_LINES);
	glVertex3f(0,0,0);
	glVertex3f(r,0,0);

	glVertex3f(0,a,0);
	glVertex3f(r,a,0);

	glVertex3f(0,-a,0);
	glVertex3f(r,-a,0);

	glVertex3f(0,0,a);
	glVertex3f(r,0,a);

	glVertex3f(0,a,a);
	glVertex3f(r,a,a);

	glVertex3f(0,-a,a);
	glVertex3f(r,-a,a);

	glVertex3f(0,0,-a);
	glVertex3f(r,0,-a);

	glVertex3f(0,a,-a);
	glVertex3f(r,a,-a);

	glVertex3f(0,-a,-a);
	glVertex3f(r,-a,-a);
	glEnd();
	glPopMatrix();

	glDisable(GL_COLOR_MATERIAL);

}

void esferaAislante(void){

	if(transparenciaA==1){
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		material(0.1, 0.18725, 0.1745, 0.396, 0.74151, 0.69102, 0.297254, 0.30829, 0.306678, 0.1); //Material turquoise
		glutSolidSphere(radioEsferaGaussiana,80,80);
		glDisable (GL_BLEND);
	}
	else if(transparenciaA==0){
		material(0.1, 0.18725, 0.1745, 0.396, 0.74151, 0.69102, 0.297254, 0.30829, 0.306678, 0.1); //Material turquoise
		glutSolidSphere(radioEsferaGaussiana,80,80);
	}

	if(transparenciaB==0){
		material(0.1745, 0.01175, 0.01175, 0.61424, 0.04136, 0.04136, 0.727811, 0.626959, 0.626959, 0.6); //Material ruby
		glutSolidSphere(radioEsferaPrincipal,80,80);
	}
	else if(transparenciaB==1){
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		material(0.1745, 0.01175, 0.01175, 0.61424, 0.04136, 0.04136, 0.727811, 0.626959, 0.626959, 0.6); //Material ruby
		glutSolidSphere(radioEsferaPrincipal,80,80);
		glDisable (GL_BLEND);
	}

	if(radioEsferaGaussiana>=a){
		E = ke*(Q/(pow(radioEsferaGaussiana,2)));
	}
	else if(radioEsferaGaussiana<a and radioEsferaGaussiana>0){
		E = ke*(Q/pow(a,3))*radioEsferaGaussiana;
	}
	else{
		E = 0;
	}

}

void esferaConductora(void){

	if(transparenciaA==1){
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		material(0.1, 0.18725, 0.1745, 0.396, 0.74151, 0.69102, 0.297254, 0.30829, 0.306678, 0.1); //Material turquoise
		glutSolidSphere(radioEsferaGaussiana,80,80);
		glDisable(GL_BLEND);
	}
	else if(transparenciaA==0){
		material(0.1, 0.18725, 0.1745, 0.396, 0.74151, 0.69102, 0.297254, 0.30829, 0.306678, 0.1); //Material turquoise
		glutSolidSphere(radioEsferaGaussiana,80,80);
	}

	if(transparenciaB==0){
		material(0.19225, 0.19225, 0.19225, 0.50754, 0.50754, 0.50754, 0.508273, 0.508273, 0.508273, 0.4); //Silver
		glutSolidSphere(radioEsferaPrincipal,80,80);
	}
	else if(transparenciaB==1){
		glEnable(GL_BLEND);
		material(0.19225, 0.19225, 0.19225, 0.50754, 0.50754, 0.50754, 0.508273, 0.508273, 0.508273, 0.4); //Silver
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glutSolidSphere(radioEsferaPrincipal,80,80);
	}

	if(radioEsferaGaussiana>=a){
		E = ke*(Q/(pow(radioEsferaGaussiana,2)));
	}
	else if(radioEsferaGaussiana<a){
		E = 0;
	}

}

void esferaAislanteHueca(void){

	if(transparenciaA==1){
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		material(0.1, 0.18725, 0.1745, 0.396, 0.74151, 0.69102, 0.297254, 0.30829, 0.306678, 0.1); //Material turquoise
		glutSolidSphere(radioEsferaGaussiana,80,80);
		glDisable(GL_BLEND);
	}
	else if(transparenciaA==0){
		material(0.1, 0.18725, 0.1745, 0.396, 0.74151, 0.69102, 0.297254, 0.30829, 0.306678, 0.1); //Material turquoise
		glutSolidSphere(radioEsferaGaussiana,80,80);
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	material(0.2295, 0.08825, 0.0275, 0.5508, 0.2118, 0.066, 0.580594, 0.223257, 0.0695701, 51.2); //Material Polished copper
	glutSolidSphere(radioEsferaPrincipal,80,80);
	glDisable(GL_BLEND);

	if(radioEsferaGaussiana>=a){
		E = ke*(Q/(pow(radioEsferaGaussiana,2)));
	}
	else if(radioEsferaGaussiana<a){
		E = 0;
	}

}

void varilla(void){

	radioEsferaPrincipal = 0.2;

	material(0.2295, 0.08825, 0.0275, 0.5508, 0.2118, 0.066, 0.580594, 0.223257, 0.0695701, 51.2); //Material Polished copper
	GLUquadricObj *obj1 = gluNewQuadric();
	glPushMatrix();
	glRotated(270,1,0,0);
	glTranslatef(0,0,-15);
    gluCylinder(obj1, radioEsferaPrincipal, radioEsferaPrincipal, 30, 30, 30);
    gluDeleteQuadric(obj1);
	glPopMatrix();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	GLUquadricObj *obj2 = gluNewQuadric();
	material(0.1, 0.18725, 0.1745, 0.396, 0.74151, 0.69102, 0.297254, 0.30829, 0.306678, 0.1); //Material turquoise
	GLUquadricObj *obj = gluNewQuadric();
	glPushMatrix();
	glRotated(270,1,0,0);
	glTranslatef(0,0,-5);
    gluCylinder(obj2, radioEsferaGaussiana, radioEsferaGaussiana, 10, 30, 30);
    gluDeleteQuadric(obj2);
	glPopMatrix();
	glDisable (GL_BLEND);

	E = (2*ke)*(lambda/radioEsferaGaussiana);

}

void planoCargado(void){

	if(girar==false){
		rotY = -10.0f;
	}
	glEnable(GL_DEPTH_TEST); //Hace comparaciones de profundidad y actualizar el buffer de profundidad.

	material(0.2295, 0.08825, 0.0275, 0.5508, 0.2118, 0.066, 0.580594, 0.223257, 0.0695701, 51.2); //Material Polished copper
	glBegin(GL_POLYGON);
	glVertex3f(0,10,10);
	glVertex3f(0,-10,10);
	glVertex3f(0,-10,-10);
	glVertex3f(0,10,-10);
	glEnd();

	material(0.1, 0.18725, 0.1745, 0.396, 0.74151, 0.69102, 0.297254, 0.30829, 0.306678, 0.1); //Material turquoise
	GLUquadricObj *obj1 = gluNewQuadric();
	glPushMatrix();
	glRotated(90,0,1,0);
	glTranslated(0,0,-2);
    gluCylinder(obj1, 1, 1, 4, 30, 30);
	glPopMatrix();

	glPushMatrix();
    glRotated(90,0,1,0);
    glTranslated(0,0,2);
	gluDisk(obj1,0,1,32,32);
	glPopMatrix();

	glPushMatrix();
    glRotated(90,0,1,0);
    glTranslated(0,0,-2);
	gluDisk(obj1,0,1,32,32);
	glPopMatrix();

	gluDeleteQuadric(obj1);
	glDisable(GL_DEPTH_TEST);

	E = sigma/(2*e0);

}

void imprimirDatos(void){

	switch(obj){
		case 1:
		glEnable(GL_COLOR_MATERIAL);
		glColor3f(1,1,1);
		text("E: %.3f N/C", E, -11.0-(rotLz/1.4), 9.8+(rotLz/1.4));
		text("Radio Esfera Aislante: %.2f m", radioEsferaPrincipal, -11.0-(rotLz/1.2), -8.6-(rotLz/1.5));
		text("Radio Esfera Gaussiana: %.2f m", abs(radioEsferaGaussiana), -11.0-(rotLz/1.2), -9.8-(rotLz/1.5));
		onlytext("Tecla 'x' y 'X': girar camara eje X.", 3.5+(rotLz/3.5), -6.8-(rotLz/1.8));
        onlytext("Tecla 'y' y 'Y': girar camara eje Y.", 3.5+(rotLz/3.5), -7.8-(rotLz/1.8));
        onlytext("Tecla despl. arriba: aumentar radio superficie gaussiana.", 3.5+(rotLz/3.5), -8.8-(rotLz/1.8));
        onlytext("Tecla despl. abajo: disminuir radio superficie gaussiana.", 3.5+(rotLz/3.5), -9.8-(rotLz/1.8));
		glDisable(GL_COLOR_MATERIAL);
		break;

		case 2:
		glEnable(GL_COLOR_MATERIAL);
		glColor3f(1,1,1);
		text("E: %.3f N/C", E, -11.0-(rotLz/1.4), 9.8+(rotLz/1.4));
		text("Radio Esfera Conductora: %.2f m", radioEsferaPrincipal, -11.0-(rotLz/1.2), -8.6-(rotLz/1.5));
		text("Radio Esfera Gaussiana: %.2f m", abs(radioEsferaGaussiana), -11.0-(rotLz/1.2), -9.8-(rotLz/1.5));
		onlytext("Tecla 'x' y 'X': girar camara eje X.", 3.5+(rotLz/3.5), -6.8-(rotLz/1.8));
        onlytext("Tecla 'y' y 'Y': girar camara eje Y.", 3.5+(rotLz/3.5), -7.8-(rotLz/1.8));
        onlytext("Tecla despl. arriba: aumentar radio superficie gaussiana.", 3.5+(rotLz/3.5), -8.8-(rotLz/1.8));
        onlytext("Tecla despl. abajo: disminuir radio superficie gaussiana.", 3.5+(rotLz/3.5), -9.8-(rotLz/1.8));
		glDisable(GL_COLOR_MATERIAL);
		break;

		case 3:
		glEnable(GL_COLOR_MATERIAL);
		glColor3f(1,1,1);
		text("E: %.3f N/C", E, -11.0-(rotLz/1.4), 9.8+(rotLz/1.4));
		text("Radio Esfera Aislante Hueca: %.2f m", radioEsferaPrincipal, -11.0-(rotLz/1.2), -8.6-(rotLz/1.5));
		text("Radio Esfera Gaussiana: %.2f m", abs(radioEsferaGaussiana), -11.0-(rotLz/1.2), -9.8-(rotLz/1.5));
		onlytext("Tecla 'x' y 'X': girar camara eje X.", 3.5+(rotLz/3.5), -6.8-(rotLz/1.8));
        onlytext("Tecla 'y' y 'Y': girar camara eje Y.", 3.5+(rotLz/3.5), -7.8-(rotLz/1.8));
        onlytext("Tecla despl. arriba: aumentar radio superficie gaussiana.", 3.5+(rotLz/3.5), -8.8-(rotLz/1.8));
        onlytext("Tecla despl. abajo: disminuir radio superficie gaussiana.", 3.5+(rotLz/3.5), -9.8-(rotLz/1.8));
		glDisable(GL_COLOR_MATERIAL);
		break;

		case 4:
		glEnable(GL_COLOR_MATERIAL);
		glColor3f(1,1,1);
		text("E: %.3f N/C", E, -11.0-(rotLz/1.4), 9.8+(rotLz/1.4));
		text("Radio Varilla: %.2f m", radioEsferaPrincipal, -11.0-(rotLz/1.2), -8.6-(rotLz/1.5));
		text("Radio Cilindro Gaussiano: %.2f m", abs(radioEsferaGaussiana), -11.0-(rotLz/1.2), -9.8-(rotLz/1.5));
		onlytext("No aplica a los extremos circulares del cilindro gaussiano.", 0.8, 9.8+(rotLz/1.5));
		onlytext("Tecla 'x' y 'X': girar camara eje X.", 3.5+(rotLz/3.5), -6.8-(rotLz/1.8));
        onlytext("Tecla 'y' y 'Y': girar camara eje Y.", 3.5+(rotLz/3.5), -7.8-(rotLz/1.8));
        onlytext("Tecla despl. arriba: aumentar radio superficie gaussiana.", 3.5+(rotLz/3.5), -8.8-(rotLz/1.8));
        onlytext("Tecla despl. abajo: disminuir radio superficie gaussiana.", 3.5+(rotLz/3.5), -9.8-(rotLz/1.8));
		glDisable(GL_COLOR_MATERIAL);
		break;

		case 5:
		glEnable(GL_COLOR_MATERIAL);
		glColor3f(1,1,1);
		text("E: %.3f N/C", E, -11.0-(rotLz/1.4), 9.8+(rotLz/1.4));
        onlytext("Tecla 'x' y 'X': girar camara eje X..", 3.5+(rotLz/3.5), -7.8-(rotLz/1.8));
        onlytext("Tecla 'y' y 'Y': girar camara eje Y.", 3.5+(rotLz/3.5), -8.8-(rotLz/1.8));
		glDisable(GL_COLOR_MATERIAL);
		break;
	}

}

//Dibuja las líneas (x, y, z).
void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Limpiar el color de Buffer

	imprimirDatos(); //Función que imprime en pantalla los datos.

    glPushMatrix(); //Es importante hacer push en la matriz antes de llamar
			//glRotatef y glTranslatef
    glRotatef(rotX,1.0,0.0,0.0); // Rotar en x.
    glRotatef(rotY,0.0,1.0,0.0); // Rotar en y.
    glRotatef(rotZ,0.0,0.0,1.0); // Rotar en z.
    glTranslatef(X, Y, Z); 	//Traslada la pantalla hacia la izquierda o hacia la derecha,
			//arriba o abajo o acercar alejar.
    //Dibuja el lado positivo de las líneas x, y, z.
    glEnable(GL_COLOR_MATERIAL);
    glBegin(GL_LINES);
    glColor3f (0.0, 1.0, 0.0); //Verde para el eje x.
    glVertex3f(0,0,0);
    glVertex3f(10,0,0);
    glColor3f(1.0,0.0,0.0); //Rojo para el eje y.
    glVertex3f(0,0,0);
    glVertex3f(0,10,0);
    glColor3f(0.0,0.0,1.0); //Azul para el eje z.
    glVertex3f(0,0,0);
    glVertex3f(0,0,10);
    glEnd();
    glDisable(GL_COLOR_MATERIAL);

    switch(obj){
		case 1:
			esferaAislante(); //Invoca la función para la esfera aislante.
			if(activarLineas==true){
				lineasDeCampoEsfera();

			}
		break;
		case 2:
			esferaConductora(); //Invoca la función para la esfera conductora.
			if(activarLineas==true){
				lineasDeCampoEsfera();
			}
		case 3:
			esferaAislanteHueca(); //Invoca la función para la esfera conductora.
			if(activarLineas==true){
				lineasDeCampoEsfera();
			}
		break;
		case 4:
			varilla(); //Invoca la función para la varilla.
			if(activarLineas==true){
				lineasDeCampoVarilla();
			}
		break;
		case 5:
			planoCargado(); //Invoca la función de un plano cargado.
			if(activarLineas==true){
				lineasDeCampoPlano();
			}
		break;
	}

    //Líneas punteadas para los lados negativos de x, y, z.
    glEnable(GL_LINE_STIPPLE); 	//Habilitar punteado de línea para usar un
				//patrón punteado para las líneas
    glLineStipple(1, 0x0101); //Patrón punteado para las líneas.
    glBegin(GL_LINES);
    glColor3f (0.0, 1.0, 0.0); // Verde para el eje x.
    glVertex3f(-10,0,0);
    glVertex3f(0,0,0);
    glColor3f(1.0,0.0,0.0); //Rojo para el eje y.
    glVertex3f(0,0,0);
    glVertex3f(0,-10,0);
    glColor3f(0.0,0.0,1.0); //Azul para el eje z.
    glVertex3f(0,0,0);
    glVertex3f(0,0,-10);
    glEnd();
    glDisable(GL_LINE_STIPPLE); //Deshabilitar la línea punteada.
    glPopMatrix(); 		//No olvidar hacer el pop Matrix.
    glutSwapBuffers();

    glutPostRedisplay();

}

//Esta función se llama cada vez que se cambia el tamaño de la ventana.
void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h); //Establecer la ventana gráfica.
    glMatrixMode (GL_PROJECTION); 	//Establecer el modo Matriz.
    glLoadIdentity ();
    gluPerspective(75, (GLfloat) w /(GLfloat) h , 0.10, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt (rotLx, rotLy, 15.0 + rotLz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

//Esta función se utiliza para las teclas de navegación.
void keyboard (unsigned char key, int x, int y)
{
switch (key) {
    case 'x': //Rotar pantalla en el eje x.
    rotX -= 0.5f;
    break;
    case 'X': //Sentido contrario.
    rotX += 0.5f;
    break;
    case 'y': //Rotar pantalla en el eje y.
	girar = true;
	rotY -= 0.5f;
    break;
    case 'Y': //Sentido contrario.
    girar = true;
    rotY += 0.5f;

}
    glutPostRedisplay(); //Redibujar la escena.
}

// called on special key pressed
void specialKey(int key, int x, int y) {

// The keys below are using the gluLookAt() function for navigation
// Check which key is pressed

switch(key) {
    case GLUT_KEY_LEFT : //Rotar en eje x.
    X -= 0.1f;
    break;
    case GLUT_KEY_RIGHT : //Rotar en eje x (contrario).
    X += 0.1f;
    break;
    case GLUT_KEY_UP : //Aumantar el tamaño de los objetos gaussianos.

    switch(obj){
		case 1: //Caso esfera aislante.

		case 2: //Caso esfera conductora.
		if(radioEsferaGaussiana<=4.9){
			radioEsferaGaussiana+=0.1f;
			rotLz += 0.1f;
			if(radioEsferaGaussiana>=radioEsferaPrincipal){
				transparenciaA=1;
				transparenciaB=0;
			}else{
				transparenciaA=0;
				transparenciaB=1;
				}
		}
		break;

		case 3: //Caso esfera ailante hueca.
		if(radioEsferaGaussiana<=4.9){
			radioEsferaGaussiana+=0.1f;
			rotLz += 0.1f;
			if(radioEsferaGaussiana>=radioEsferaPrincipal){
				transparenciaA=1;
				transparenciaB=0;
			}else{
				transparenciaA=0;
				transparenciaB=1;
				}
		}
		break;

		case 4: //Caso varilla.
			if(radioEsferaGaussiana<4.9){
				radioEsferaGaussiana+=0.1f;
				rotLz += 0.1f;
			}
		break;

		case 5:
		break;

	}

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt (rotLx, rotLy, 15.0 + rotLz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    break;
    case GLUT_KEY_DOWN : //Disminuir el tamaño de los objetos gaussianos.

    switch(obj){

		case 1: //Caso esfera aislante.

		case 2: //Caso esfera conductora.
		if(radioEsferaGaussiana>=0.0){
			radioEsferaGaussiana-=0.1f;
			rotLz -= 0.1f;
			if(radioEsferaGaussiana<radioEsferaPrincipal){
				transparenciaA=0;
				transparenciaB=1;
			}else{
				transparenciaA=1;
				transparenciaB=0;
				}
		}
		break;

		case 3: //Caso esfera aislante hueca.
		if(radioEsferaGaussiana>=0.0){
			radioEsferaGaussiana-=0.1f;
			rotLz -= 0.1f;
			if(radioEsferaGaussiana<radioEsferaPrincipal){
				transparenciaA=0;
				transparenciaB=1;
			}else{
				transparenciaA=1;
				transparenciaB=0;
				}
		}
		break;

		case 4: //Caso varilla
			if(radioEsferaGaussiana>0.2){
				radioEsferaGaussiana-=0.1f;
				rotLz -= 0.1f;
			}
		break;

		case 5:
		break;

	}

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt (rotLx, rotLy, 15.0 + rotLz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    break;
    case GLUT_KEY_PAGE_UP: //Rotate on z axis
    Z -= 0.1f;
    break;
    case GLUT_KEY_PAGE_DOWN://Rotate on z axis (opposite)
    Z += 0.1f;
    break;
}
    glutPostRedisplay(); //Redibujar la escena.
}

//Principal punto de entrada del programa.
int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    if(argc < 4)
    {
        cout << "Faltan " << 5 - argc << " argumentos. ¿Abrió la interfaz grafica primero?";
		return 1;
	}

	obj = atoi(argv[1]);
    Q = atof(argv[2]);
    radioEsferaPrincipal = atof(argv[3]);
    activarLineas = atoi(argv[4]);

    a=radioEsferaPrincipal;
    lambda = Q;
    sigma = Q;

    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 	//Configurar el modo de visualización a
						//double buffer, color RGB y glut depth
    glutInitWindowSize (glutGet(GLUT_SCREEN_WIDTH),glutGet(GLUT_SCREEN_HEIGHT)); //Establecer el tamaño de la pantalla.
    glutCreateWindow("SIMULACION ANIMADA CAMPOS ELECTRICOS");
    init ();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard); //Establecer la devolución de llamada clave de la ventana.
    glutSpecialFunc(specialKey); //Establecer ventanas a la devolución de llamada especial.
    glutMainLoop();

    return 0;
}
