#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include "SOIL.h"
#include "funciones_extras.h" //Biblioteca extra que contiene funciones de mapeo y dibujado extra.

using namespace std;

int nObjetos; //Cantidad de objetos a considerar para la simulación.

float vMasa[5]; //Vector que contiene el valor de las masas de los objetos.
float vCalor[5]; //Vector que contiene el valor de los calores especificos de los objetos.
float vTemperatura[5]; //Vector que contiene el valor de las temperaturas iniciales de los objetos.
float Tf[5]; //Vector que contiene el resultado del calculo de la temperatura final para n objetos.

string nombresMateriales[] = {"Hierro", "Aluminio", "Plomo", "Cobre", "Plata", "Oro"}; //Vector que almacena los nombres de los materiales que se pueden seleccionar en Qt.
float vPuntoDeFusionMateriales[] = {1808, 660, 327.3f, 1083, 960.80f, 1063.00f}; //Vector que almacena los valores de punto de fusión para los materiales hierro, cobre, bronce, plata y oro respectivamente.

string nombresFluidos[] = {"Agua", "Alcohol etilico"}; //Vector que almacena el nombre de los fluidos.
float vPuntoDeFusionFluidos[] = {0.00f, -114}; //Vector que almacena los puntos de fusión de los fluidos.
float vPuntoDeFisionFluidos[] = {100.0f, 78}; //Vector que almacena los puntos de fusión de los fluidos.

int numeroDeElementosMateriales = sizeof(nombresMateriales) / sizeof(nombresMateriales[0]); //Determina el número de elementos del vector nombresMateriales.
int numeroDeElementosFluidos = sizeof(nombresFluidos) / sizeof(nombresFluidos[0]); //Determina el número de elementos del vector nombresFluidos.

float vDensidadesObjetos[5]; //Vector que guarda las densidades de los objetos.
string vMaterialesObjetos[5]; //Vector del tipo string que guarda el nombre de los objetos recibidos desde Qt.

bool nCubos[4]; //Cantidad de cubos a tomar en cuenta.
float alpha=0; //Variable para establecer tamaño del cubo#1.
float beta=0; //Variable para establecer tamaño del cubo#2.
float gama=0; //Variable para establecer tamaño del cubo#3.
float delta=0; //Variable para establecer tamaño del cubo#4.

float centrar=0; //Variable que guarda el resultado para el translate que centrara el dibujo de los objetos.

bool animacion = false; //Condición para activar/desactivar la animación.
int activarOpausa=-1;  //Pausa de la animación.

int opc=0; //Variable para determinar que opción de simulación se realizará.
float incr=0; //Variable controlada por el timer.
float incr2=0; //Variable controlada por el timer.

float tempA[5]; //Vector que almacena la temperatura actual de los obetos (Dato simbolico).

bool msj[2]; //Vector boleano para activar mensajes.
bool activarCambioDeTemperatura = false;
bool bloquearBoton = false;

void toggleGlutWindowMaximizeBox(char *szWindowTitle) //Funci�n para evitar que el usuario intente maximizar la ventana.
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

void onlytext(string cadena, float espaciadoX, float espaciadoY) //Funcion que imprime texto en pantalla (Solo imprime texto, no variables).
{
	std::string const s(cadena);
    char onlytext[100];
    sprintf(onlytext, s.c_str());
    glColor3f(0, 0, 0);
    glRasterPos3f(espaciadoX,espaciadoY,0);

		for(int i = 0; onlytext[i] != '\0'; i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, onlytext[i]);
}

void equilibrioTermico(int value) //Este timer sirve para animar la rutina.
{

	if(opc==1){ //Si se ha seleccionado las opción de simulación "varios objetos"
		activarCambioDeTemperatura=true; //Activa un flag
		bloquearBoton=true; //Flag para desactivar acciones de la teclas (activado).
	}else if(opc==2){ //Si se ha seleccionado las opción de simulación "objeto-líquido"
		bloquearBoton=true; //Flag para desactivar acciones de la teclas (activado).
		if(incr2<9){ //Si es menor a 9, incr aumentara en 0.5, hasta llegar a ese número (Fondo del fluido).
			incr2+=0.5f;
		}
		if(incr2>=3){ //Si llega a 3, activa la animación de cambios de temperatura.
			activarCambioDeTemperatura=true;
		}

	}

	if(activarCambioDeTemperatura==true){
		if(incr<3){ //Si incr es menor a 3 seg.
			incr+=0.1f; //Aumenta en 0.1.

			msj[0] = true; //Vector flag en 0 activado (Sirve para mostrar un mensaje).

			for(int i=0; i<nObjetos; i++){ //Mienntras sea menor al número de objetos, aumentar en 1.

				if(tempA[i]<Tf[nObjetos-2]){ //Si la temperatura actual (está inicializada como la inicial) es menor a la temperatura final, tratara de alcanzarla aumentando en 0.1 durante 3 seg.
					tempA[i]+=0.1f;
				}

				if(tempA[i]>Tf[nObjetos-2]){ //Si la temperatura actual (está inicializada como la inicial) es mayor a la temperatura final, tratara de alcanzarla disminuyendo en 0.1 durante 3 seg.
					tempA[i]-=0.1f;
				}

			}
		}else{ //Cuando termina el incremento (es decir los 3 seg) llega a este else.

			msj[0] = false; //Se desactiva el primer msj.
			msj[1] = true; //Se activa el segundo msj.

			for(int i=0; i<nObjetos; i++){ //Se iguala el vector de temperatura actual con el valor general de Tempetura final del sistema recorriendo un for hasta llegar a llenar todos los datos de los objetos.
				tempA[i] = Tf[nObjetos-2];
			}
			animacion=false; //Se desactiva la animación.
			bloquearBoton =false; //Se habilitan las teclas.
		}
	}

	if(bloquearBoton==true){ //Solo se puede usar el timer cuando se preciona una tecla.
		glutPostRedisplay();
		glutTimerFunc(100, equilibrioTermico, 1000);
	}

}

float mayorMasa(void){ //Función que determina que cubo posee la mayor masa.

    float mayor = vMasa[0]; //La variable mayor contendra inicialmente el primer valor del vector masa.

	for(int i=0; i<nObjetos; i++){ //Este ciclo recorre de 0 hasta el número de objetos para ver en que posición del vector se encuentra el mayor valor de la masa.

		if(mayor < vMasa[i]){ //Si la variable mayor es menor que el siguiente valor del vector masa, este dato será el nuevo valor de la variable mayor.
			mayor = vMasa[i];
		}

	}

	return mayor; //Después de recorrer el bucle y determinar la mayor de las masas del vector, retornara un valor float de la mayor masa.
}

void cambioDeFase(){

	bool mostrar_msj=false;

	float posY=4.0f; //Variable para indicar la posión del mensaje en y.

	for(int i=0; i<nObjetos; i++){ //En este for mientras sea menor al número de objetos, se incrementa en una unidad el iterador.

		for(int j=0; j<numeroDeElementosMateriales; j++){ //Recorrera el numero de materiales que coincide con los del vector de materiales.
			if(vMaterialesObjetos[i]==nombresMateriales[j] && (Tf[nObjetos-2]>=vPuntoDeFusionMateriales[j])){ //Si se ha encontrado el fluido en la lista y tiene una Tf mayor o igual que el punto de fusion, activa un flag para el msj.
				mostrar_msj=true;
			}
		}

		if(opc==2){
			posY=7.8f; //Se establece en 7.8 el valor para la variable de posición para el mensaje.
			for(int j=0; j<numeroDeElementosFluidos; j++){
				if(vMaterialesObjetos[i]==nombresFluidos[j] && (Tf[nObjetos-2]<=vPuntoDeFusionFluidos[j])){ //Si se ha encontrado el fluido en la lista y tiene una Tf menor o igual que el punto de fusión, activa un flag para el msj.
					mostrar_msj=true;
				}
				if(vMaterialesObjetos[i]==nombresFluidos[j] && (Tf[nObjetos-2]>=vPuntoDeFisionFluidos[j])){ //Si se ha encontrado el fluido en la lista y tiene una Tf mayor o igual que la el punto de fisión, activa un flag para el msj.
					mostrar_msj=true;
				}
			}
		}

	}

	if(mostrar_msj==true && animacion==true){ //Se muestra el mensaje si el flag mostrar_msj está activo y el de animación también.
		onlytext("Habra un cambio de fase, pero esta simulacion no la toma en cuenta", -8.0f, posY);
	}

}

void dibujarFlechas(float x_1, float y_1, float x_2, float y_2, float tObj1, float tObj2){ //Función que recibe posición en x_1, y_1, x_2, y_2 para dibujar un linea según el par de coordenadas.
																						   //Además de comparar la temperatura del objeto 1 y 2 para determinar a donde apuntara la flecha.
	if(animacion==true && incr<3){ //Si se acitva la animación y la variable del timer incr es menor que 3, se hará el dibujo y animación de las flechas.

		if((int)(incr*10)%2==0.0f){ //¡Efecto de parpadeo!, se dibijan las flechas solo con los multiplos de 0.2 de la variable inc que cambia con el timer, si no es así, no dibuja nada,
									//generando así un efecto de parpadeo.

			if(tObj1!=tObj2){ //Solo se dibujan las flechas en caso de que la temperatura del objeto#1 y la del objeto#2 sean diferentes.

				glLineWidth(5); //Se dibuja las líneas, con los pares de coordenadas recibidos en la función.
				glColor3f(1,1,0);
				glBegin(GL_LINES);
				glVertex2f(x_1,y_1);
				glVertex2f(x_2,y_2);
				glEnd();

				glColor3f(1,0,0);
				glLineWidth(2.5); //Se dibuja las líneas, con los pares de coordenadas recibidos en la función.
				glBegin(GL_LINES);
				glVertex2f(x_1,y_1);
				glVertex2f(x_2-0.05f,y_2);
				glEnd();

				glPushMatrix();
				if(tObj1>tObj2){ //Se determina que objeto tiene mayor masa, para trasladar la flecha que se encuentra dibujada en el origen, a la respectiva posición donde debe apuntar.
					glTranslatef(x_2+0.1f,y_2,0); //Traslada el triangulo al cubo derecho.

				}
				else if(tObj1<tObj2){
					glTranslatef(x_1-0.1f,y_1,0); //Traslada el triangulo al cubo izquierdo.
					glRotatef(180,0,0,1); //Se rota el triangulo en este caso.
				}

				glColor3f(1,1,0);
				glBegin(GL_TRIANGLES); //Aquí se dibuja el triangulo de las flechas que es dibujado en el origen y trasladado y rotado con funciones para ello.
				glVertex2f(-0.25f,0.25f);
				glVertex2f(-0.25f,-0.25f);
				glVertex2f(0,0);
				glEnd();
				glPopMatrix();

			}

		}

	}

}

void dibujarCubos(){ //Esta es la función donde se dibujan los cubos del sistema, se establece su tamaño y se alinean de forma geometrica.

	int l=4; //Tamaño definido para el cubo más grande, (se regula para los más pequeños multiplicandolo por cierto valor).

	for(int i=0; i<nObjetos; i++){ //Se establece cuantos cubos se dibujaran haciendo true un vector boleano dependiendo del número de cubos a considerar.
		if(i<=nObjetos){
			nCubos[i] = true;
		}
	}

	if(nCubos[0]==true){
		alpha = vMasa[0]/mayorMasa(); //alpha guarda el valor de la división entre la masa del cubo#1 y el cubo que tiene mayor masa.

		if(alpha<0.25f){ //Si alpha es muy pequeño, se le pone por defecto el valor de 0.25 para que el tamaño del cubo no sea demasiado pequeño.
			alpha = 0.25f;
		}

		glPushMatrix();
        glColor3f(1,0,0);

        glTranslatef(0, -(2-(alpha*l)/2) ,0); //Se baja el cubo#1 al nivel del más grande.

        cubo(alpha*l, 0);

        onlytext("1", 0, 0);

        glPopMatrix();
	}
	if(nCubos[1]==true){
		beta = vMasa[1]/mayorMasa(); //beta guarda el valor de la división entre la masa del cubo#2 y el cubo que tiene mayor masa.

		if(beta<0.25f){ //Si beta es muy pequeño, se le pone por defecto el valor de 0.25 para que el tamaño del cubo no sea demasiado pequeño.
			beta = 0.25f;
		}

		glColor3f(0,1,0);
		glPushMatrix();
		glTranslatef((alpha*l)/2 + (beta*l)/2,0,0); //Este translate pone el segundo cubo a la derecha del primero.

		glTranslatef(0, -(2-(beta*l)/2) ,0); //Se baja el cubo#2 al nivel del más grande.

		cubo(beta*l, 1);
		onlytext("2", 0, 0);

		dibujarFlechas(-3*(beta*l/4),-(beta*l/4),-(beta*l/4),-(beta*l/4), vTemperatura[0],vTemperatura[1]); //Se dibuja una flecha para el bloque 1 y 2.

		glPopMatrix();

		centrar = (beta*l)/2; //Esta variable sirve para centrar el sistema de cubos más adelante (caso para 2 cubos).
	}
	if(nCubos[2]==true){
		gama = vMasa[2]/mayorMasa(); //gama guarda el valor de la división entre la masa del cubo#3 y el cubo que tiene mayor masa.

		if(gama<0.25f){ //Si gama es muy pequeño, se le pone por defecto el valor de 0.25 para que el tamaño del cubo no sea demasiado pequeño.
			gama = 0.25f;
		}

		glColor3f(0,0,1);
		glPushMatrix();
		glTranslatef((alpha*l)/2 + (beta*l) + (gama*l)/2,0,0); //Este translate pone el tercer cubo a la derecha del segundo.

		glTranslatef(0, -(2-(gama*l)/2) ,0); //Se baja el cubo#3 al nivel del más grande.

		cubo(gama*l, 2);
		onlytext("3", 0, 0);

		dibujarFlechas(-3*(gama*l/4),-(gama*l/4),-(gama*l/4),-(gama*l/4), vTemperatura[1],vTemperatura[2]); //Se dibuja una flecha para el bloque 2 y 3.

		glPopMatrix();

		centrar = (beta*l)/2 + (gama*l)/2; //Esta variable sirve para centrar el sistema de cubos más adelante (caso para 3 cubos).
	}
	if(nCubos[3]==true){
		delta = vMasa[3]/mayorMasa(); //delta guarda el valor de la división entre la masa del cubo#4 y el cubo que tiene mayor masa.

		if(delta<0.25f){ //Si delta es muy pequeño, se le pone por defecto el valor de 0.25 para que el tamaño del cubo no sea demasiado pequeño.
			delta = 0.25f;
		}

		glColor3f(1,0.647f,0);
		glPushMatrix();
		glTranslatef((alpha*l)/2 + (beta*l) + (gama*l) + (delta*l)/2,0,0); //Este translate pone el cuarto cubo a la derecha del tercero.

		glTranslatef(0, -(2-(delta*l)/2) ,0); //Se baja el cubo#4 al nivel del más grande.

		cubo(delta*l, 3);
		onlytext("4", 0, 0);

		dibujarFlechas(-3*(delta*l/4),-(delta*l/4),-(delta*l/4),-(delta*l/4), vTemperatura[2],vTemperatura[3]); //Se dibuja una flecha para el bloque 3 y 4.

		glPopMatrix();

		centrar = (beta*l)/2 + (gama*l)/2 + (delta*l)/2; //Esta variable sirve para centrar el sistema de cubos más adelante (caso para 4 cubos).
	}

}

void calculos(void){ //Función encargada de realizar los calculos de la temperatura final del sistema de objetos.

	if(nCubos[1]==true || opc==2){ //Calculo para 2 cubos o un cubo y un fluido.
		Tf[0] = (vMasa[0]*vCalor[0]*vTemperatura[0] + vMasa[1]*vCalor[1]*vTemperatura[1]) / (vMasa[0]*vCalor[0] + vMasa[1]*vCalor[1]); //Calculo de la temperatura final para dos objetos.
	}
	if(nCubos[2]==true){ //Calculo para 3 cubos.
		Tf[1] = (vMasa[0]*vCalor[0]*Tf[0] + vMasa[1]*vCalor[1]*Tf[0] + vMasa[2]*vCalor[2]*vTemperatura[2]) / (vMasa[0]*vCalor[0] + vMasa[1]*vCalor[1] + vMasa[2]*vCalor[2]); //Calculo de la temperatura final para tres objetos.
	}
	if(nCubos[3]==true){ //Calculo para 4 cubos.
		Tf[2] = (vMasa[0]*vCalor[0]*Tf[1] + vMasa[1]*vCalor[1]*Tf[1] + vMasa[2]*vCalor[2]*Tf[1]+ vMasa[3]*vCalor[3]*vTemperatura[3]) / (vMasa[0]*vCalor[0] + vMasa[1]*vCalor[1] + vMasa[2]*vCalor[2] + vMasa[3]*vCalor[3]); //Calculo de la temperatura final para cuatro objetos.
	}

}

void dibujoCuboLiquido(void){ //Dibujo de recipiente.

	glBegin(GL_POLYGON); //Dibujo del liquido (Rectangulo azulado).
	glColor3f(0.0f,0.730f,0.855f);
	glVertex2f(-10,-4);
	glVertex2f(-10,-10);
	glVertex2f(10,-10);
	glVertex2f(10,-4);
	glEnd();

	glPushMatrix();
	glTranslatef(0,-incr2,0); //Este translate mueve el cubo para sumergirlo hasta el fondo del líquido usando la variable del timer para la opción 2 de simulación.
	cubo(2,3);

	if(incr2>=4){
		dibujarFlechas(1,0,2,0,vTemperatura[0],vTemperatura[1]); //Dibuja una flecha para saber si el cubo sede calor al líquido o el líquido sede calor al cubo (apunta en sentido contrario).
		dibujarFlechas(-2,0,-1,0,vTemperatura[1],vTemperatura[0]); //Aquí se uso un truco, se invertieron los valores para que esta flecha apuntase hacía el cubo.
	}

	glPopMatrix();

}

void tabla(void){ //Función que dibuja una tabla que muestra los respectivos datos de interes en esta simulación.

	if(nCubos[1]==true){ //Para el caso de 2 objetos.
		glBegin(GL_POLYGON);
		glColor3f(0.298f, 0.624f, 0.953f);
		glVertex2f(-10,-2.9f);
		glVertex2f(-10,-3.5f);
		glVertex2f(10,-3.5f);
		glVertex2f(10,-2.9f);
		glEnd();

		onlytext("Cubo #1",-6,-3.35f); //Titulos de las columnas.
		onlytext("Cubo #2",4.4,-3.35f);

		onlytext("Material: " + vMaterialesObjetos[0],-9,-4.1f); //Datos a mostrar.
		text("Masa: %.2f kg", vMasa[0], -9,-4.8f);
		text("Temperatura inicial: %.2f °C", vTemperatura[0], -9,-5.5f);
		text("Temperatura actual: %.2f °C", tempA[0], -9,-6.2f);

		onlytext("Material: " + vMaterialesObjetos[1],1.4f,-4.1f);
		text("Masa: %.2f kg", vMasa[1], 1.4f,-4.8f);
		text("Temperatura inicial: %.2f °C", vTemperatura[1], 1.4f,-5.5f);
		text("Temperatura actual: %.2f °C", tempA[1], 1.4f,-6.2f);

		glPointSize(10); //Dibuja indicadores de color para los cubos 1 y 2.
		glBegin(GL_POINTS);
		glColor3f(0.047f,0.968f,0.941f); //Punto aqua.
		glVertex2f(-6.3f,-3.2f);
		glColor3f(0,1,0); //Punto verde.
		glVertex2f(4.1f,-3.2f);
		glEnd();
	}

	if(nCubos[2]==true){ //Para el caso de 3 objetos.
		glBegin(GL_POLYGON);
		glColor3f(0.298f, 0.624f, 0.953f);
		glVertex2f(-10,-6.5f);
		glVertex2f(-10,-7.2f);
		glVertex2f(10,-7.2f);
		glVertex2f(10,-6.5f);
		glEnd();

		onlytext("Cubo #3",-6,-7.05f); //Titulo de la columna.
		onlytext("Material: " + vMaterialesObjetos[2], -9,-7.8f); //Datos a mostrar.
		text("Masa: %.2f kg", vMasa[2], -9,-8.5f);
		text("Temperatura inicial: %.2f °C", vTemperatura[2], -9,-9.2f);
		text("Temperatura actual: %.2f °C", tempA[2], -9,-9.9f);

		glBegin(GL_POINTS); //Dibuja un indicador de color para el cubo#3.
		glColor3f(0.961f,0.047f,0.945f); //Punto morado.
		glVertex2f(-6.3f,-6.9f);
		glEnd();
	}

	if(nCubos[3]==true){ //Para el caso de 4 objetos.
		onlytext("Cubo #4",4.4f,-7.05f); //Titulo de la columna.
		onlytext("Material: " + vMaterialesObjetos[3], 1.4f,-7.8f); //Datos a mostrar.
		text("Masa: %.2f kg", vMasa[3], 1.4f,-8.5f);
		text("Temperatura inicial: %.2f °C", vTemperatura[3], 1.4f,-9.2f);
		text("Temperatura actual: %.2f °C", tempA[3], 1.4f,-9.9f);

		glBegin(GL_POINTS); //Dibuja un indicador de color para el cubo#4.
		glColor3f(1,0,0); //Punto rojo.
		glVertex2f(4.1f,-6.9f);
		glEnd();
	}

	if(opc==2){ //Si es el caso para un cubo y fluido se dibuja esta tabla.
		glBegin(GL_POLYGON);
		glColor3f(0.298f, 0.624f, 0.953f);
		glVertex2f(-10,-2.9f);
		glVertex2f(-10,-3.5f);
		glVertex2f(10,-3.5f);
		glVertex2f(10,-2.9f);
		glEnd();

		onlytext("Cubo",-6,-3.35f); //Titulos de las columnas.
		onlytext("Fluido",4.4f,-3.35f);

		onlytext("Material: " + vMaterialesObjetos[0],-9,-4.1f); //Datos a mostrar.
		text("Masa: %.2f kg", vMasa[0], -9,-4.8f);
		text("Temperatura inicial: %.2f °C", vTemperatura[0], -9,-5.5f);
		text("Temperatura actual: %.2f °C", tempA[0], -9,-6.2f);

		onlytext("Fluido: " + vMaterialesObjetos[1],1.4f,-4.1f);
		text("Masa: %.2f kg", vMasa[1], 1.4f,-4.8f);
		text("Temperatura inicial: %.2f °C", vTemperatura[1], 1.4f,-5.5f);
		text("Temperatura actual: %.2f °C", tempA[1], 1.4f,-6.2f);

		glPointSize(10);
		glBegin(GL_POINTS); //Dibuja indicadores de color para el cubo y el fluido.
		glColor3f(1,0,0); //Punto rojo.
		glVertex2f(-6.3f,-3.2f);
		glColor3f(0.047f,0.968f,0.941f); //Punto aqua.
		glVertex2f(4.1f,-3.2f);
		glEnd();
	}

}

void elementosDeIntefaz(){ //Dibujos de otros detalles extras de la interfaz.
	glColor3f(0.298f, 0.624f, 0.953f); //Pestaña izquierda de instrucción de control de teclas.
	glBegin(GL_POLYGON);
	glVertex2f(-10,10);
	glVertex2f(-10,9);
	glVertex2f(-4.5f,9);
	glVertex2f(-3.0f,10);
	glEnd();

	glBegin(GL_POLYGON); //Pestaña derecha de instrucción de control de teclas.
	glVertex2f(10,10);
	glVertex2f(10,9);
	glVertex2f(4.5,9);
	glVertex2f(3.5,10);
	glEnd();

	onlytext("Iniciar animacion x o X", -9.7f,9.35f); //Texto que indica con que tecla activar la animación.
	onlytext("Reiniciar animacion r o R", 4.2f,9.35f); //Texto que indica con que tecla reiniciar la animación.
}

void display(void)
{
	glClearColor(1, 1, 1, 1);
    glClear (GL_COLOR_BUFFER_BIT);

    elementosDeIntefaz(); //Se llama esta función que dibuja algunos elementos para la interfaz.

    float posY=5.4f; //Variable para indicar la posión del mensaje en y.

    calculos(); //Función que realiza los calculos del sistema termodinamico.
    cambioDeFase(); //Se llama la función que indica si existe un cambio de fase en el sistema termodinamico.

    if(opc==1){ //Si es el caso de la simulación para varios objetos solidos.

		glColor3f(1,0.498f,0.314f);
		glBegin(GL_POLYGON);
		for(double i=0; i<360; i+=0.005){
			float x = cos(i*(2*3.1416f)/360);
			float y = sin(i*(2*3.1416f)/360);
			glVertex2f(3*incr*x, incr*y);
		}
		glEnd();

		glPushMatrix();
		glTranslatef(-(centrar),0,0); //Este translate se encarga de centrar el dibujo de los cubos, para alinearlos con simetria en la pantalla.
		dibujarCubos(); //Se llama a la función que dibuja los cubos para varios objetos (pueden ser hasta 4).
		glPopMatrix();

		tabla(); //Se llama a esta función que dibuja una tabla para que muestra distintos valores para los diferentes cubos.

	}else if(opc==2){ //Si es el caso de la simulación para un solido sumergiendose en un fluido.

		dibujoCuboLiquido(); //Se llama a la función que dibujo el cubo y su animación, también dibuja el líquido.

		glPushMatrix();
		glTranslatef(0,10,0);
		tabla();
		glPopMatrix();

		posY=0; //Se establece en cero el valor para la variable de posición para el mensaje.

	}

	if(msj[0]==true){ //Mensaje que se activa mientras está activa la simulación.
		onlytext("TRANSFIRIENDO CALOR...",-3.3f,posY);
	}
	if(msj[1]==true){ //Mensaje que se activa cuando finaliza la simulación.
		text("TEMPERATURA FINAL DEL SISTEMA: %.2f °C", Tf[nObjetos-2], -5.6f,posY);
	}

    glFlush ();

    glutPostRedisplay();

}

void keyboard (unsigned char key, int x, int y){
	switch (key){   // x,X,y,Y,z,Z uses the glRotatef() function

		case 'x': //Tecla que inicia/pausa la simulación.

		case 'X':
		animacion = true;
		if(animacion==true && bloquearBoton==false){
			equilibrioTermico(0);
		}

		break;

		case 'r': //Tecla para reiniciar la animación.

		case 'R':

		for(int i=0; i<nObjetos; i++){ //Se vuelve a establecer la temperatura actual como la inicial.
			tempA[i] = vTemperatura[i];
		}

		incr=0; //Se limpia incr e incr2;
		incr2=0;
		activarCambioDeTemperatura = false; //Se hacen falsas estas variables boleanas.
		msj[0]=false;
		msj[1]=false;
		break;

	}
	glutPostRedisplay(); //Redibujar la escena.
}

void init (void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10, 10, -10, 10, -10, 10); //Se establece la vista ortogonal del programa.

         texture[0] = SOIL_load_OGL_texture //Carga un archivo de imagen directamente como una nueva textura OpenGL (gradiente aqua).
    (
        "Textura cubo gradiente aqua.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

         texture[1] = SOIL_load_OGL_texture //Carga un archivo de imagen directamente como una nueva textura OpenGL (gradiente verde).
    (
        "Textura cubo gradiente verde.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

         texture[2] = SOIL_load_OGL_texture //Carga un archivo de imagen directamente como una nueva textura OpenGL (gradiente morado).
    (
        "Textura cubo gradiente morado.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

         texture[3] = SOIL_load_OGL_texture //Carga un archivo de imagen directamente como una nueva textura OpenGL (gradiente rojo).
    (
        "Textura cubo gradiente rojo.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    if(argc < 10)
    {
        cout << "Faltan " << 10 << " argumentos. Abrio la interfaz grafica primero?";
		return 1;
	}

	opc = atoi(argv[1]); //Se recibe un valor de 1 para las simulación de varios objetos o 2 para simulación de objeto-solido.
    nObjetos = atoi(argv[2]); //Se recibe el número de objetos ha tomar en cuenta en esta simulación.

	int inc=0; //Variable para incrementar la posición de los argumentos a recibir.

	for(int i=0; i<nObjetos; i++){ //Según el número de obetos se define cuantos datos guardaran los vectores de datos necesarios.

		vMasa[i] = atof(argv[3+inc]); //Se reciben valores que se usan para definir las masas, esto se almacenan en un vector para masas mandados en orden desde Qt.
		vCalor[i] = atof(argv[4+inc]); //Se reciben valores que se usan para definir las calores específicos, esto se almacenan en un vector para masas mandados en orden desde Qt.
		vTemperatura[i] = atof(argv[5+inc]); //Se reciben valores que se usan para definir las temperaturas iniciales, esto se almacenan en un vector para masas mandados en orden desde Qt.
		vMaterialesObjetos[i] = argv[6+inc]; //Se reciben valores que se usan para definir el tipo de material de los objetos, esto se almacenan en un vector para masas mandados en orden desde Qt.

		tempA[i] = vTemperatura[i]; //Se inicializa  el vector de la temperatura actual con la inicial.

		inc+=4; //Se incrementa en 5, para que el primer elemento reciva el octavo argumento y así sucesivamente.

	}

    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 700); //Se establece el tamaño de la ventana.
    glutInitWindowPosition(((glutGet(GLUT_SCREEN_WIDTH)-700)/2), ((glutGet(GLUT_SCREEN_HEIGHT)-700)/2)); //Se establece la posición de la ventana (En este caso se ha centrado).

    char *szWindowTitle = "SIMULACION ANIMADA CALORIMETRIA"; //Se establece el titulo de la ventana.
    glutCreateWindow(szWindowTitle);
    toggleGlutWindowMaximizeBox(szWindowTitle);

    init ();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard); //Establecer la devolución de llamada clave de la ventana.
    glutMainLoop();
    return 0;
}
