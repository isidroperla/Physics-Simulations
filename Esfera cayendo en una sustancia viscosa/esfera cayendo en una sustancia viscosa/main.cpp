#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <stdio.h>
#define TIME_INTERVAL 1000
#define M_PI 3.14159265358979323846

using namespace std;

double Vt; //Velocidad terminal.
double De=0; //Densidad de la esfera.
double Df=0; //Densidad del fluido.
double R=0; //Radio de la esfera.
double n=0; //Viscosidad (kg/ms).
double k=0; //Abreviación de calculos.
double v=0; //Velocidad como función del tiempo.
double m=0; //Masa de la esfera.
double t=0; //Tiempo.
double const g = 9.81; //Constante de la aceleración debido a la gravedad en la tierra.
double x=0; //Posición en x de la esfera.
double y=0; //Desplazamiento de la esfera
double tMax=90;
double dMax=0;

double vectorY[11]; //Vector que guarda la posión en y para el texto.
float vInc[11] = {0,1,2,3,4,5,6,7,8,9,10}; //Vector que guarda un incremento para la pila.

double limiteY=0;

string tipoDeFluido; //Variable que guarda el nombre del tipo de fluido seleccionado.
float r1,g1,b1,r2,g2,b2; //Variables para definir el color.

int opc=0; //Sirve para definir que tipo de color se aplicara a la sustancia.
int iterations = 360; //Numero de iteraciones.
bool animacion = true; //Condición para activar/desactivar la animación.
int activarOpausa=-1;  //Pausa de la animación.
bool animacionCondicion1 = true; //Condición que detiene la animación.
bool animacionCondicion2 = true; //Condición que detiene la animación.
bool animacionCondicion3 = true; //Condición que detiene la animación.

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
    char text[120];
    sprintf(text, s.c_str(), dato);
    glColor3f(0, 0, 0);
    glRasterPos3f(espaciadoX,espaciadoY,0);

    for(int i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
}

void onlytext(string cadena, double espaciadoX, double espaciadoY, double r, double g, double b, bool letraNormal) //Funcion que imprime texto.
{
	std::string const s(cadena);
    char onlytext[120];
    sprintf(onlytext, s.c_str());
    glColor3f(r, g, b);
    glRasterPos3f(espaciadoX,espaciadoY,0);

    if(letraNormal==true){ //En caso que se use letra tamaño normal (GLUT_BITMAP_HELVETICA_18).
		for(int i = 0; onlytext[i] != '\0'; i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, onlytext[i]);
	}else{
		for(int i = 0; onlytext[i] != '\0'; i++) //En caso que se use otro tamaño de letra (GLUT_BITMAP_HELVETICA_12).
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, onlytext[i]);
	}
}

void TimerRutina(int value) //Este timer sirve para animar la rutina.
{
   //Si animacion es true se activara el timer, de ser el caso contrario se desactivara.
   if (animacion){

		if (animacionCondicion1==true && animacionCondicion2==true && animacionCondicion3==true){
			t += 0.025;
		}

		if(t>tMax){ //Si el tiempo es mayor a 90 segundos la animación termina.
			animacionCondicion1=false;
		}

		if(v>60){ //Si la velocidad es mayor a 60 m/s la animación termina.
			animacionCondicion2=false;
		}

		if(dMax!=0){
			if(y>dMax){
				animacionCondicion3=false;
			}
		}

		glutPostRedisplay();
		glutTimerFunc(25, TimerRutina, iterations);
		--iterations;
	}
}

void colores(void){ //Función para designar el color del fluido y la esfera según el tipo de opción recibida desde Qt.

	switch(opc){

		case 1:
		tipoDeFluido = "Plasma";
		r1=0.916;
		g1=0.988;
		b1=0.032;
		r2=1;
		g2=0;
		b2=0;
		break;

		case 2:
		tipoDeFluido = "Sangre";
		r1=1;
		g1=0;
		b1=0;
		r2=0;
		g2=0;
		b2=1;
		break;

		case 3:
		tipoDeFluido = "Etanol";
		r1=0.9216;
		g1=0.9451;
		b1=0.8000;
		r2=1;
		g2=0;
		b2=0;
		break;

		case 4:
		tipoDeFluido = "Glicerina";
		r1=0.9216;
		g1=0.9451;
		b1=0.8000;
		r2=1;
		g2=0;
		b2=0;
		break;

		case 5:
		tipoDeFluido = "Mercurio";
		r1=0.7490;
		g1=0.7804;
		b1=0.7882;
		r2=1;
		g2=0;
		b2=0;
		break;

		case 6:
		tipoDeFluido = "Agua";
		r1=0.1176;
		g1=0.7569;
		b1=0.9608;
		r2=1;
		g2=0;
		b2=0;
		break;

		case 7:
		tipoDeFluido = "Otro Fluido";
		r1=0.9216;
		g1=0.9451;
		b1=0.8000;
		r2=1;
		g2=0;
		b2=0;
		break;

	}

}

void regla(void){ //Función que dibuja parte de la regla (lo demás es autogenerado).

	 for(int i=1; i<=10; i++){
		glColor3f(1,0,0);
		glLineWidth(2);
		glBegin(GL_LINES);
		glVertex2f(3.3, i);
		glVertex2f(3.7, i);
		glEnd();
	}

	glColor3f(1,0,0);
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex2f(3.5,10);
	glVertex2f(3.5,-11);
	glEnd();

    glPopMatrix();

}

void imprimirMedidas(void){ //Función que se usa como una pila de posiciones para las medidas impresas como texto.

	repetir:

	for(int i=0; i<=10; i++){ //Asignación de posición en Y para 10 posisciones.
		vectorY[i] = y*100-vInc[i];
	}

	for(int i=0; i<=10; i++){ //Verificación 1, sirve para volver al inicio un dato que salga de la pantalla (es mayor a 10).

		if(vectorY[i]>=10){
			vInc[i]+=11;
			goto repetir;
			system("pause>nul");
		}

	}

	for(int i=0; vectorY[i]>=10; i++){ // verificación 2, sirve para forzar al vectorY que respete la condición de que no pase de 10.

		vInc[i]+=1;

		if(vectorY[i]>=10){
			goto repetir;
			system("pause>nul");
		}
	}

	for(int i=0; i<=10; i++){ //Asignación de posición en Y para 10 posisciones.
		vectorY[i] = y*100-vInc[i];
	}

	for(int i=0; i<=10; i++){ //Función que dibuja el texto y las lineas horizontales (rojas y azules) de acuerdo a la posición de la pila.

		text("%.2f m", vInc[i]/100, 4, vectorY[i]-0.15f);

		if((fmod((vInc[i]/100),1)==0.0f)){ //Lineas rojas.
			glLineWidth(4);
			glColor3f(0,0,1);
			glBegin(GL_LINES);
			glVertex2f(3.2, vectorY[i]);
			glVertex2f(3.8, vectorY[i]);
			glEnd();
		}else if(fmod((vInc[i]/100),1)!=0.0f || vInc[i]==0.0f){ //Lineas azules.
			glLineWidth(2);
			glColor3f(1,0,0);
			glBegin(GL_LINES);
			glVertex2f(3.3, vectorY[i]);
			glVertex2f(3.7, vectorY[i]);
			glEnd();
		}

	}

}

void calculos(void){ //En esta función se realizan los principales calculos de ecuaciones para la simulación.

	//Calculos

    Vt = (2*g*(De-Df)*pow(R,2))/(9*n); //Formula de la velocidad terminal.

    k = 6*M_PI*R*n; //Abreviación de valores.

    m = De*((1.333)*M_PI*pow(R,3)); //Calulo de la masa.

    //t = -(m/k)*log(1-(v/Vt));

    v = Vt*(1- exp((-k*t/m))); //Calculo de la velocidad como función del tiempo.

    y = Vt* (t - (m/k)*(1 - exp((-k*t/m)))); //Formula del desplazamiento de la particula.

    limiteY = Vt* (90 - (m/k)*(1 - exp((-k*90/m)))); //Formula del desplazamiento de la particula.

}

void figura(void){

	glPushMatrix();

    if(y*100<10){
		glTranslated(0,y*100,0);

	}else{
		glTranslated(0,10,0);
	}

	//Dibujo del recipiente.
    glColor3f(0.488f,0.592f,0.584f);
    glBegin(GL_POLYGON);
    glVertex2f(-2.2,2);
    glVertex2f(-2.2,-20);
    glVertex2f(2.2,-20);
    glVertex2f(2.2,2);
    glEnd();

    colores(); //Se llama esta función para definir el color del fluido y de la esfera.

    //Dibujo de la sustancia.
    glColor3f(r1,g1,b1);
    glBegin(GL_POLYGON);
    glVertex2f(-2,0);
    glVertex2f(-2,-20);
    glVertex2f(2,-20);
    glVertex2f(2,0);
    glEnd();

    //Traslación de regla metrica.
    regla(); //Se dibuja una regla de medir.

    glPopMatrix();

    //Dibujo de la esfera.
    glColor3f(r2,g2,b2);
    glutSolidSphere(1,30,30);

    imprimirMedidas(); //Se imprime el valor de las medidas de la regla.

    //Cuadro de los datos del punto 1
    glColor3f(0,0,0);
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
	glVertex2f(-10,10);
	glVertex2f(-10,4);
	glVertex2f(-3.0,4);
	glVertex2f(-3.0,10);
	glEnd();

    //Impresión de textos.
    onlytext(tipoDeFluido, -9.5, 9, 0, 0, 1, true); //Se imprime el nombre del fluido en pantalla.
    text("vt: %.2f m/s", Vt, -9.5, 8); //Se imprime el valor de la velocidad terminal.
    text("v: %.2f m/s", v, -9.5, 7); //Se imprime el valor de la velocidad como función del tiempo.
    text("t: %.2f s", t, -9.5, 6); //Se imprime el valor del tiempo.
    text("y: %.2f m", y, -9.5, 5); //Se imprime el valor del desplazamiento de la esfera.
    onlytext("Activar/Pausar Animacion (x o X)", -8.9, -8.3, 0,0,0, false);
    onlytext("Reiniciar Animacion (r o R)", -8.9, -9.1, 0,0,0, false);

    //Textos mostrados en caso de que la simulación finalize.
    if(animacionCondicion1==false){ //Mensaje que indica que la animación se ha pausado después de un tiempo determinado de 90 s.
		onlytext("LIMITE DE TIEMPO ALCANZADO", -9.0, -6.4, 0.9373,0.3843,0, false);
	}
	if(animacionCondicion2==false){ //Mensaje que indica que la animación se ha pausado después de una velocidad determinada de 60 m/s.
		onlytext("LIMITE DE VELOCIDAD ALCANZADO", -9.3, -6.4, 0.9373,0.3843,0, false);
	}
	if(animacionCondicion3==false){ //Mensaje que indica que la animación se ha pausado después de una cieta distancia recorrida (opcional).
		onlytext("LIMITE DE DISTANCIA ALCANZADA", -9.3, -6.4, 0.9373,0.3843,0, false);
	}

}

void display(void)
{
	glClearColor(1, 1, 1, 1); //El color de fondo se estable como blanco.
    glClear (GL_COLOR_BUFFER_BIT);

    calculos(); //Función que realiza los correspondientes calculos antes de hacer el dibujado.

    figura(); //Función que dibuja los objetos y animaciones.

    glFlush ();

}

void keyboard (unsigned char key, int x, int y){
	switch (key){   // x,X,y,Y,z,Z uses the glRotatef() function

		case 'x': //Tecla que inicia/pausa la simulación.

		case 'X':

		activarOpausa*=-1;

		if(activarOpausa>0){
			animacion = true;
			TimerRutina(0);
		}
		else{
			animacion = false;
		}

		break;

		case 'r': //Tecla para reiniciar la simulación.

		case 'R':

		v=0;
		t=0;
		y=0;

		for(int i=0; i<=10; i++){
			vectorY[i]= 0;
			vInc[i]=i;
		}

		activarOpausa*=-1;

		if(activarOpausa>0){
			animacion = true;
			TimerRutina(0);
		}
		else{
			animacion = false;
		}

		animacionCondicion1=true;
		animacionCondicion2=true;
		animacionCondicion3=true;

		break;

	}
	glutPostRedisplay(); //Redibujar la escena.
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

    if(argc < 5)
    {
        cout << "Faltan " << 3 - argc << " argumentos. ¿Abrió la interfaz grafica primero?";
		return 1;
	}

	opc = atoi(argv[1]); //Se recibe un valor que se usa para definir el tipo de fluido.
    R = atof(argv[2]); //Se recibe el valor del radio de la esfera.
    De = atof(argv[3]); //Se recibe el valor de la densidad de la esfera.
    Df = atof(argv[4]); //Se recibe el valor de la densidad del fluido.
    n = atof(argv[5]); //Se recibe el valor de la viscosidad.
    tMax = atof(argv[6]); //Se recibe el valor para limitar el tiempo maximo que dure la animación (opcional).
    dMax = atof(argv[7]); //Se recibe el valor para limitar la distancia maxima que alcance la animación (opcional).

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(((glutGet(GLUT_SCREEN_WIDTH)-700)/2), ((glutGet(GLUT_SCREEN_HEIGHT)-700)/2));
    char *szWindowTitle = "SIMULACION ANIMADA ESFERA CAYENDO EN UNA SUSTANCIA VISCOSA";
    glutCreateWindow(szWindowTitle);
    toggleGlutWindowMaximizeBox(szWindowTitle);
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard); //Establecer la devolución de llamada clave de la ventana.
    glutMainLoop();
    return 0;
}
