#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>
#include <string.h>
#include <stdio.h>
#define M_PI 3.14159265358979323846

using namespace std;

float va=0;
float ke = 9*pow(10,9); //Constante de Coulomb.
float a=0.5;
float q1=2; //Carga1.
float q2=2; //Carga2.
float x_1=0; //Posición en x de la carga 1.
float y_1=0; //Posición en y de la carga 1.
float x_2=0; //Posición en x de la carga 2.
float y_2=0; //Posición en x de la carga 2.
float v=0;

float phi1=0; //Angulo para las curvas de la carga 1.
float phi2=0; //Angulo para las curvas de la carga 2.
float x=0; //Valor en x
float y=0; //Valor en y
float r1=0;
float r2=0;
float Ex=0; //Campo eléctrico en x.
float Ey=0; //Campo eléctrico en y.
float E=0;

float auxX=0; //Auxiliar para x.
float auxY=0; //Auxiliar para y.
float A=0;
float B=0;

float R1=0;
float B1=0;
float R2=0;
float B2=0;

float alpha=0; //Angulo alpha.
float ac=0; //Angulo alpha corregido.

float aux_x1=0; //Auxiliar de x1.
float aux_y1=0; //Auxiliar de y1.
float aux_x2=0; //Auxliaar de x2.
float aux_y2=0; //Auxiliar de y2.

bool lineasCarga2=false; //Variable booleana para activar las lineas de carga.
bool activarLineasCampo=false; //Variable booleana para activar las lineas de campo.

void toggleGlutWindowMaximizeBox(char *szWindowTitle)
{
    long dwStyle;
    HWND hwndGlut;

    hwndGlut = FindWindow(NULL, szWindowTitle);

    dwStyle = GetWindowLong(hwndGlut, GWL_STYLE);
    dwStyle ^= WS_MAXIMIZEBOX;
    SetWindowLong(hwndGlut, GWL_STYLE, dwStyle);
}

void text(string valor, double dato, double espaciadoX, double espaciadoY) //Funcion que imprime texto en tiempo real de las variables.
{
	std::string const s(valor);
    char text[64];
    sprintf(text, s.c_str(), dato);
    glColor3f(0, 0, 0);
    glRasterPos3f(espaciadoX,espaciadoY,0);

    for(int i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
}

void onlytext(string cadena, float espaciadoX, float espaciadoY) //Funcion que solo imprime texto en pantalla.
{
	std::string const s(cadena);
    char onlytext[100];
    sprintf(onlytext, s.c_str());
    glColor3f(1, 1, 1);
    glRasterPos3f(espaciadoX,espaciadoY,0);

		for(int i = 0; onlytext[i] != '\0'; i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, onlytext[i]);
}

float redondear(float valor){ //Función para redondear a dos decimales.

	return (roundf(valor * 10000)/10000);

}

void correccion_phi1(void){ //Función que corrige el angulo phi1.

	if(x>=x_1 && y>=y_1){
		//Nada
	}else if(x<x_1 && y>=y_1){
		phi1 = M_PI - phi1;
	}else if(x<x_1 && y<y_1){
		phi1 = M_PI + phi1;
	}else if(x>=x_1 && y<y_1){
		phi1 = 2*M_PI - phi1;
	}
}

void correccion_phi2(void){ //Función que corrige el angulo phi2.

	if(x>=x_2 && y>=y_2){
		//Nada
	}else if(x<x_2 && y>=y_2){
		phi2 = M_PI - phi2;
	}else if(x<x_2 && y<y_2){
		phi2 = M_PI + phi2;
	}else if(x>=x_2 && y<y_2){
		phi2 = 2*M_PI - phi2;
	}
}

void correccion_alpha(void){ //Función que corrige el angulo alpha.

	if(x_2>=x_1 && y_2>=y_1){
		ac = alpha;
	}else if(x_2<x_1 && y_2>=y_1){
		ac = M_PI - alpha;
	}else if(x_2<x_1 && y_2<y_1){
		ac = M_PI + alpha;
	}else if(x_2>=x_1 && y_2<y_1){
		ac = 2*M_PI - alpha;
	}

	ac = redondear(ac);
}

void validarCargas(void){ //Función que valida las cargas con distintas condiciones.

	if(q1>=0 && q2<0){
		//Nada
	}else if(q1<0 && q2>=0){
		q1*=-1;
		q2*=-1;
	}else if(q1>=0 && q2>=0){
		//Nada
		lineasCarga2=true;
	}else if(q1<0 && q2<0){
		q1*=-1;
		q2*=-1;
		lineasCarga2=true;
	}

}

void calculosCurvasEquipotenciales(void){ //Función que dibuja las curvas equipotenciales.

	for(int n=1; n*a<=10; n++){

		va = ke*(q1/pow((pow((x_1-n*a),2)),0.5)) + ke*(q2/pow((pow((x_2-n*a),2)+pow((y_2-y_1),2)),0.5));

		glColor3f(0,0,0);
		glPointSize(2);
		glBegin(GL_POINTS);
		glVertex2f(n*a,y_1);
		glEnd();

		for(float j=0; j<=10; j+=0.02){ // Se barren todas los puntos en vertical.

			for(float i=0; i<=10; i+=0.02){ // Se barren todas los puntos en horizontal.

				if((i==x_1 and j==y_1) || (i==x_2 and j==y_2)){

				}else{

					if(va>=0){

						if(v>=(0.995*va) and v<=(1.005*va)){

							glColor3f(0,0,0);
							glPointSize(2);
							glBegin(GL_POINTS);
							glVertex2f(i,j);
							glEnd();

						}

					}
					else if(va<=0){

						if(v<=(0.995*va) and v>=(1.005*va)){

							glColor3f(0,0,0);
							glPointSize(2);
							glBegin(GL_POINTS);
							glVertex2f(i,j);
							glEnd();

						}

					}

				}

				v = ke*(q1/pow((pow((x_1-i),2)+pow((y_1-j),2)),0.5)) + ke*(q2/pow((pow((x_2-i),2)+pow((y_2-j),2)),0.5));

			}

		}

	}

	a=0.5;
	v=0;
	va=0;

	for(int n=1; n*a<=10; n++){

		va = ke*(q1/pow((pow((x_1-n*a),2) + pow((y_2-y_1),2)),0.5)) + ke*(q2/pow((pow((x_2-n*a),2)),0.5));

		glColor3f(0,0,0);
		glPointSize(2);
		glBegin(GL_POINTS);
		glVertex2f(n*a,y_2);
		glEnd();

		for(float j=0; j<=10; j+=0.02){ // Se barren todas los puntos en vertical.

			for(float i=0; i<=10; i+=0.02){ // Se barren todas los puntos en horizontal.

				if((i==x_1 and j==y_1) || (i==x_2 and j==y_2)){

				}else{

					if(va>=0){

						if(v>=(0.995*va) and v<=(1.005*va)){

							glColor3f(0,0,0);
							glPointSize(2);
							glBegin(GL_POINTS);
							glVertex2f(i,j);
							glEnd();

						}

					}
					else if(va<=0){

						if(v<=(0.995*va) and v>=(1.005*va)){

							glColor3f(0,0,0);
							glPointSize(2);
							glBegin(GL_POINTS);
							glVertex2f(i,j);
							glEnd();

						}

					}

				}

				v = ke*(q1/pow((pow((x_1-i),2)+pow((y_1-j),2)),0.5)) + ke*(q2/pow((pow((x_2-i),2)+pow((y_2-j),2)),0.5));

			}

		}

	}

}

void calculosLineasDeCampoElectrico(void){ //Función que dibuja las lineas de campo eléctrico.

	validarCargas();

	alpha = atan(abs((y_2-y_1)/(x_2-x_1)));

	correccion_alpha();

	for(int i=1; i<=16; i++){

		switch(i){

			case 1:
				if(ac!= 0.7854f && ac!= 3.9270f){
					A=0.1; B=0.1;
				}
			break;
			case 2:
				if(ac!=0.0000f && ac!=3.1416f){
					A=0.1; B=0;
				}
			break;
			case 3:
				if(ac!=2.3562f && ac!=5.4978f){
					A=0.1; B=-0.1;
				}
			break;
			case 4:
				if(ac!=1.5708f && ac!=4.7124f){
					A=0; B=-0.1;
				}
			break;
			case 5:
				if(ac!=0.7854f && ac!=3.9270f){
					A=-0.1; B=-0.1;
				}
			break;
			case 6:
				if(ac!=0.0000f && ac!=3.1416f){
					A=-0.1; B=-0;
				}
			break;
			case 7:
				if(ac!=2.3562f && ac!=5.4978f){
					A=-0.1; B=0.1;
				}
			break;
			case 8:
				if(ac!=1.5708f && ac!=4.7124f){
					A=0; B=0.1;
				}
			break;
			case 9:
				if(ac!=0.4636f && ac!=3.6052f){
					A=0.1; B=0.05;
				}
			break;
			case 10:
				if(ac!=2.6780f && ac!=5.8195f){
					A=0.1; B=-0.05;
				}
			break;
			case 11:
				if(ac!=2.0344f && ac!=5.1760f){
					A=0.05; B=-0.1;
				}
			break;
			case 12:
				if(ac!=1.1071f && ac!=4.2487f){
					A=-0.05; B=-0.1;
				}
			break;
			case 13:
				if(ac!=0.4636f && ac!=3.6052f){
					A=-0.1; B=-0.05;
				}
			break;
			case 14:
				if(ac!=2.6780f && ac!=5.8195f){
					A=-0.1; B=0.05;
				}
			break;
			case 15:
				if(ac!=2.0344f && ac!=5.1760f){
					A=-0.05; B=0.1;
				}
			break;
			case 16:
				if(ac!=1.1071f && ac!=4.2487f){
					A=0.05; B=0.1;
				}
			break;
		}

		x = x_1 + A;
		y = y_1 + B;

		glColor3f(1,1,0);
		glLineWidth(1.5);
		glBegin(GL_LINES);
		glVertex2f(x_1,y_1);
		glVertex2f(x,y);
		glEnd();

		for(int i=0; i<300; i++){

			auxX = x;
			auxY = y;

			phi1 = atan(abs((y-y_1)/(x-x_1)));
			phi2 = atan(abs((y-y_2)/(x-x_2)));

			correccion_phi1();
			correccion_phi2();

			r1 = sqrt(pow((x-x_1),2) + pow((y-y_1),2));
			r2 = sqrt(pow((x-x_2),2) + pow((y-y_2),2));

			Ex = (q1/pow(r1,2))*cos(phi1) + (q2/pow(r2,2))*cos(phi2);
			Ey = (q1/pow(r1,2))*sin(phi1) + (q2/pow(r2,2))*sin(phi2);

			E = sqrt(pow(Ex,2) + pow(Ey,2));

			x = ((Ex/E)*0.1) + auxX;
			y = ((Ey/E)*0.1) + auxY;

			glColor3f(1,0,1);
			glBegin(GL_LINES);
			glVertex2f(auxX,auxY);
			glVertex2f(x,y);
			glEnd();

		}

	}

}

void figura(void){ //Aquí se llaman las funciones de calculos y dibujados.

	calculosCurvasEquipotenciales();

	if(activarLineasCampo==true){

		calculosLineasDeCampoElectrico();

		if(lineasCarga2==true){

			float auxX_2 = x_2;
			float auxY_2 = y_2;

			x_2 = x_1;
			y_2 = y_1;

			x_1 = auxX_2;
			y_1 = auxY_2;

			calculosLineasDeCampoElectrico();
		}
	}

	//Se dibujan las cargas 1 y 2 con su respectiva numeración y color.
	glColor3f(R1,0,B1);
    glPushMatrix();
    glTranslated(aux_x1,aux_y1,0);
    glutSolidSphere(0.15,40,40);
	glPopMatrix();

	glColor3f(R2,0,B2);
    glPushMatrix();
    glTranslated(aux_x2,aux_y2,0);
    glutSolidSphere(0.15,40,40);
	glPopMatrix();

	onlytext("1", (aux_x1-0.05f), (aux_y1-0.05f));
	onlytext("2", (aux_x2-0.05f), (aux_y2-0.05f));

}

void display(void)
{
	glClearColor(1, 1, 1, 1);
    glClear (GL_COLOR_BUFFER_BIT);

    figura();

    glFlush ();
}
void init (void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 10, 0, 10, 0, 10);

}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    if(argc < 7)
    {
        cout << "Faltan " << 8 - argc << " argumentos. ¿Abrió la interfaz grafica primero?";
		return 1;
	}

	//Guardar los valores recibidos desde qt en variables.
    x_1 = atof(argv[1]);
    y_1 = atof(argv[2]);
    q1 = atof(argv[3]);

    x_2 = atof(argv[4]);
    y_2 = atof(argv[5]);
    q2 = atof(argv[6]);

    activarLineasCampo = atoi(argv[7]);

    //Variables auxilares para las posiciones.
    aux_x1 = atof(argv[1]);
    aux_y1 = atof(argv[2]);
    aux_x2 = atof(argv[4]);
    aux_y2 = atof(argv[5]);

    //Resivar si las cargas son positivas, y asignar valor a R1, B1, R2, B2.
    if(q1>=0){
		R1=0; B1=1;
	}else{
		R1=1; B1=0;
	}

	if(q2>=0){
		R2=0; B2=1;
	}else{
		R2=1; B2=0;
	}

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(((glutGet(GLUT_SCREEN_WIDTH)-700)/2), ((glutGet(GLUT_SCREEN_HEIGHT)-700)/2));

    char *szWindowTitle = "ANIMACION SIMULACION CURVAS EQUIPOTENCIALES";
    glutCreateWindow(szWindowTitle);
    toggleGlutWindowMaximizeBox(szWindowTitle);
    init ();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
