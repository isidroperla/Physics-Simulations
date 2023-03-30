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

void esfera(float x, float y, float z){
	
	//glColor3f(1,0,0);
	
	material(0.1745, 0.01175, 0.01175, 0.61424, 0.04136, 0.04136, 0.727811, 0.626959, 0.626959, 0.6); //Material ruby
	glPushMatrix();
	glTranslatef(x,y,z);
	glutSolidSphere(0.25,40,40);
	glPopMatrix();

}

void cubicoSencillo(void){
	
	glColor3f(1,1,1);
	
	glEnable(GL_COLOR_MATERIAL);
	glBegin(GL_LINE_LOOP); //Cara izquierda
	glVertex3f(-2,2,-2);
	glVertex3f(-2,-2,-2);
	glVertex3f(-2,-2,2); 
	glVertex3f(-2,2,2);
	glEnd();
	
	glBegin(GL_LINE_LOOP); //Cara derecha
	glVertex3f(2,2,-2);
	glVertex3f(2,-2,-2);
	glVertex3f(2,-2,2); 
	glVertex3f(2,2,2);
	glEnd();
	
	glBegin(GL_LINE_LOOP); //Cara abajo
	glVertex3f(-2,-2,-2);
	glVertex3f(-2,-2,2);
	glVertex3f(2,-2,2); 
	glVertex3f(2,-2,-2);
	glEnd();
	
	glBegin(GL_LINE_LOOP); //Cara arriba
	glVertex3f(-2,2,-2);
	glVertex3f(-2,2,2);
	glVertex3f(2,2,2); 
	glVertex3f(2,2,-2);
	glEnd();
	glDisable(GL_COLOR_MATERIAL);
	
	esfera(-2,2,-2); //Esfera superior trasera (izquierda).
	esfera(-2,2,2); //Esfera superior enfrente (izquierda).
	
	esfera(-2,-2,2); //Esfera inferior enfrente (izquierda).
	esfera(-2,-2,-2); //Esfera inferior trasera (izquierda).
	
	esfera(2,2,2); //Esfera superior enfrente (derecha).
	esfera(2,2,-2); //Esfera superior trasera (derecha).
		
	esfera(2,-2,2); //Esfera inferior enfrente (derecha).
	esfera(2,-2,-2); //Esfera inferior trasera (derecha).
	
	
}

void cubicoCentradoEnElCuerpo(void){
	
	glColor3f(1,1,1);
	
	glEnable(GL_COLOR_MATERIAL);
	glBegin(GL_LINE_LOOP); //Cara izquierda
	glVertex3f(-2,2,-2);
	glVertex3f(-2,-2,-2);
	glVertex3f(-2,-2,2); 
	glVertex3f(-2,2,2);
	glEnd();
	
	glBegin(GL_LINE_LOOP); //Cara derecha
	glVertex3f(2,2,-2);
	glVertex3f(2,-2,-2);
	glVertex3f(2,-2,2); 
	glVertex3f(2,2,2);
	glEnd();
	
	glBegin(GL_LINE_LOOP); //Cara abajo
	glVertex3f(-2,-2,-2);
	glVertex3f(-2,-2,2);
	glVertex3f(2,-2,2);
	glVertex3f(2,-2,-2);
	glEnd();
	
	glBegin(GL_LINE_LOOP); //Cara arriba
	glVertex3f(-2,2,-2);
	glVertex3f(-2,2,2);
	glVertex3f(2,2,2); 
	glVertex3f(2,2,-2);
	glEnd();
	
	glBegin(GL_LINES);
	glVertex3f(-2,2,-2); //Lineas desde la esquina superior izquierda (fondo) hacia la inferior derecha (frente)
	glVertex3f(2,-2,2);
	
	glVertex3f(2,2,-2); //Lineas desde la esquina superior derecha (fondo) hacia la inferior izquierda (frente)
	glVertex3f(-2,-2,2);
	
	glVertex3f(-2,2,2); //Lineas desde la esquina superior izquierda (frente) hacia la inferior derecha (fondo)
	glVertex3f(2,-2,-2);
	
	glVertex3f(2,2,2); //Lineas desde la esquina superior derecha (frente) hacia la inferior izquierda (fondo)
	glVertex3f(-2,-2,-2);
	glEnd();
	glDisable(GL_COLOR_MATERIAL);
	
	esfera(-2,2,-2); //Esfera superior trasera (izquierda).
	esfera(-2,2,2); //Esfera superior enfrente (izquierda).
	
	esfera(-2,-2,2); //Esfera inferior enfrente (izquierda).
	esfera(-2,-2,-2); //Esfera inferior trasera (izquierda).
	
	esfera(2,2,2); //Esfera superior enfrente (derecha).
	esfera(2,2,-2); //Esfera superior trasera (derecha).
		
	esfera(2,-2,2); //Esfera inferior enfrente (derecha).
	esfera(2,-2,-2); //Esfera inferior trasera (derecha).
	
	esfera(0,0,0); //Esfera centro.
	
}

void cubicoCentradoEnLasCaras(void){
	
	glColor3f(1,1,1);
	
	glEnable(GL_COLOR_MATERIAL);
	glBegin(GL_LINE_LOOP); //Cara izquierda
	glVertex3f(-2,2,-2);
	glVertex3f(-2,-2,-2);
	glVertex3f(-2,-2,2); 
	glVertex3f(-2,2,2);
	glEnd();
	
	glBegin(GL_LINE_LOOP); //Cara derecha
	glVertex3f(2,2,-2);
	glVertex3f(2,-2,-2);
	glVertex3f(2,-2,2); 
	glVertex3f(2,2,2);
	glEnd();
	
	glBegin(GL_LINE_LOOP); //Cara abajo
	glVertex3f(-2,-2,-2);
	glVertex3f(-2,-2,2);
	glVertex3f(2,-2,2); 
	glVertex3f(2,-2,-2);
	glEnd();
	
	glBegin(GL_LINE_LOOP); //Cara arriba
	glVertex3f(-2,2,-2);
	glVertex3f(-2,2,2);
	glVertex3f(2,2,2); 
	glVertex3f(2,2,-2);
	glEnd();
	
	glBegin(GL_LINES);
	glVertex3f(-2,2,-2); //Lineas que conectan la esfera de la cara izquierda
	glVertex3f(-2,-2,2);
	glVertex3f(-2,-2,-2);
	glVertex3f(-2,2,2);
	
	glVertex3f(2,2,-2); //Lineas que conectan la esfera de la cara derecha
	glVertex3f(2,-2,2);
	glVertex3f(2,-2,-2);
	glVertex3f(2,2,2);
	
	glVertex3f(-2,-2,-2); //Lineas que conectan la esfera de la cara inferior
	glVertex3f(2,-2,2);
	glVertex3f(-2,-2,2);
	glVertex3f(2,-2,-2);
	
	glVertex3f(-2,2,-2); //Lineas que conectan la esfera de la cara superior
	glVertex3f(2,2,2);
	glVertex3f(-2,2,2);
	glVertex3f(2,2,-2);
	
	glVertex3f(-2,2,-2); //Lineas que conectan la esfera de la cara fondo
	glVertex3f(2,-2,-2);
	glVertex3f(2,2,-2);
	glVertex3f(-2,-2,-2);
	
	glVertex3f(-2,2,2); //Lineas que conectan la esfera de la cara frente
	glVertex3f(2,-2,2);
	glVertex3f(2,2,2);
	glVertex3f(-2,-2,2);
	glEnd();
	glDisable(GL_COLOR_MATERIAL);
	
	esfera(-2,2,-2); //Esfera superior trasera (izquierda).
	esfera(-2,2,2); //Esfera superior enfrente (izquierda).
	
	esfera(-2,-2,2); //Esfera inferior enfrente (izquierda).
	esfera(-2,-2,-2); //Esfera inferior trasera (izquierda).
	
	esfera(2,2,2); //Esfera superior enfrente (derecha).
	esfera(2,2,-2); //Esfera superior trasera (derecha).
		
	esfera(2,-2,2); //Esfera inferior enfrente (derecha).
	esfera(2,-2,-2); //Esfera inferior trasera (derecha).
	
	esfera(-2,0,0); //Esfera centro cara izquierda.
	esfera(2,0,0); //Esfera centro cara derecha.
	esfera(0,-2,0); //Esfera centro cara abajo.
	esfera(0,2,0); //Esfera centro cara arriba.
	esfera(0,0,-2); //Esfera centro cara atras.
	esfera(0,0,2); //Esfera centro cara frente.
	
}

void tetragonalSencillo(void){
	
	glColor3f(1,1,1);
	
	glEnable(GL_COLOR_MATERIAL);
	glBegin(GL_LINE_LOOP); //Cara izquierda
	glVertex3f(-2,4,-2);
	glVertex3f(-2,-4,-2);
	glVertex3f(-2,-4,2); 
	glVertex3f(-2,4,2);
	glEnd();
	
	glBegin(GL_LINE_LOOP); //Cara derecha
	glVertex3f(2,4,-2);
	glVertex3f(2,-4,-2);
	glVertex3f(2,-4,2); 
	glVertex3f(2,4,2);
	glEnd();
	
	glBegin(GL_LINE_LOOP); //Cara abajo
	glVertex3f(-2,-4,-2);
	glVertex3f(-2,-4,2);
	glVertex3f(2,-4,2); 
	glVertex3f(2,-4,-2);
	glEnd();
	
	glBegin(GL_LINE_LOOP); //Cara arriba
	glVertex3f(-2,4,-2);
	glVertex3f(-2,4,2);
	glVertex3f(2,4,2); 
	glVertex3f(2,4,-2);
	glEnd();
	glDisable(GL_COLOR_MATERIAL);
	
	esfera(-2,4,-2); //Esfera superior trasera (izquierda).
	esfera(-2,4,2); //Esfera superior enfrente (izquierda).
	
	esfera(-2,-4,2); //Esfera inferior enfrente (izquierda).
	esfera(-2,-4,-2); //Esfera inferior trasera (izquierda).
	
	esfera(2,4,2); //Esfera superior enfrente (derecha).
	esfera(2,4,-2); //Esfera superior trasera (derecha).
		
	esfera(2,-4,2); //Esfera inferior enfrente (derecha).
	esfera(2,-4,-2); //Esfera inferior trasera (derecha).
	
}

void tetragonalCentradoEnElCuerpo(void){
	
	glColor3f(1,1,1);
	
	glEnable(GL_COLOR_MATERIAL);
	glBegin(GL_LINE_LOOP); //Cara izquierda
	glVertex3f(-2,4,-2);
	glVertex3f(-2,-4,-2);
	glVertex3f(-2,-4,2); 
	glVertex3f(-2,4,2);
	glEnd();
	
	glBegin(GL_LINE_LOOP); //Cara derecha
	glVertex3f(2,4,-2);
	glVertex3f(2,-4,-2);
	glVertex3f(2,-4,2); 
	glVertex3f(2,4,2);
	glEnd();
	
	glBegin(GL_LINE_LOOP); //Cara abajo
	glVertex3f(-2,-4,-2);
	glVertex3f(-2,-4,2);
	glVertex3f(2,-4,2); 
	glVertex3f(2,-4,-2);
	glEnd();
	
	glBegin(GL_LINE_LOOP); //Cara arriba
	glVertex3f(-2,4,-2);
	glVertex3f(-2,4,2);
	glVertex3f(2,4,2); 
	glVertex3f(2,4,-2);
	glEnd();
	
	glBegin(GL_LINES);
	glVertex3f(-2,4,-2); //Lineas desde la esquina superior izquierda (fondo) hacia la inferior derecha (frente)
	glVertex3f(2,-4,2);
	
	glVertex3f(2,4,-2); //Lineas desde la esquina superior derecha (fondo) hacia la inferior izquierda (frente)
	glVertex3f(-2,-4,2);
	
	glVertex3f(-2,4,2); //Lineas desde la esquina superior izquierda (frente) hacia la inferior derecha (fondo)
	glVertex3f(2,-4,-2);
	
	glVertex3f(2,4,2); //Lineas desde la esquina superior derecha (frente) hacia la inferior izquierda (fondo)
	glVertex3f(-2,-4,-2);
	glEnd();
	glDisable(GL_COLOR_MATERIAL);
	
	esfera(-2,4,-2); //Esfera superior trasera (izquierda).
	esfera(-2,4,2); //Esfera superior enfrente (izquierda).
	
	esfera(-2,-4,2); //Esfera inferior enfrente (izquierda).
	esfera(-2,-4,-2); //Esfera inferior trasera (izquierda).
	
	esfera(2,4,2); //Esfera superior enfrente (derecha).
	esfera(2,4,-2); //Esfera superior trasera (derecha).
		
	esfera(2,-4,2); //Esfera inferior enfrente (derecha).
	esfera(2,-4,-2); //Esfera inferior trasera (derecha).
	
	esfera(0,0,0); //Esfera centro.
	
}

void romboedrica(void){
	
	glColor3f(1,1,1);
	
	glPushMatrix();
	glTranslatef(-2.00f,-1.16f,-0.82f);
	
	glEnable(GL_COLOR_MATERIAL);
	glBegin(GL_LINES);
	glVertex3f(0,0,0); //O->PA
	glVertex3f(2,0,0);
	
	glVertex3f(0,0,0); //O->PB
	glVertex3f(1,1.73f,0);
	
	glVertex3f(0,0,0); //O->PC
	glVertex3f(1,0.58f,1.63);
	
	glVertex3f(2,0,0); //PA->PA+PC
	glVertex3f(3,0.58f,1.63);
	
	glVertex3f(1,0.58f,1.63); //PC->PC+PA
	glVertex3f(3,0.58,1.63);
	
	glVertex3f(1,1.73f,0); //PB->PB+PC
	glVertex3f(2,2.31f,1.63);
	
	glVertex3f(1,0.58f,1.63); //PC->PB+PC
	glVertex3f(2,2.31f,1.63);
	
	glVertex3f(2,0,0); //PA->PA+PB
	glVertex3f(3,1.73f,0);
	
	glVertex3f(1,1.73f,0); //PB->PA+PB
	glVertex3f(3,1.73,0);
	
	glVertex3f(3,1.73f,0); //PA+PB->PA+PB+PC
	glVertex3f(4,2.31f,1.63);
	
	glVertex3f(3,0.58f,1.63); //PA+PC->PA+PB+PC
	glVertex3f(4,2.31f,1.63);
	
	glVertex3f(2,2.31f,1.63); //PB+PC->PA+PB+PC
	glVertex3f(4,2.31f,1.63);
	glEnd();
	
	glDisable(GL_COLOR_MATERIAL);
	
	esfera(2,2.31f,1.63); //Esfera superior trasera (izquierda).
	esfera(1,1.73f,0); //Esfera superior enfrente (izquierda).
	esfera(1,0.58f,1.63); //Esfera inferior enfrente (izquierda).
	esfera(0,0,0); //Esfera inferior trasera (izquierda).
	
	esfera(4,2.31f,1.63); //Esfera superior enfrente (derecha).
	esfera(3,1.73f,0); //Esfera superior trasera (derecha).
		
	esfera(3,0.58f,1.63); //Esfera inferior enfrente (derecha).
	esfera(2,0,0); //Esfera inferior trasera (derecha).
	
	glPopMatrix();

}

void hexagono(void){
	
	glColor3f(1,1,1);
	
	glEnable(GL_COLOR_MATERIAL);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-1,-3,-2); //Exagono inferior
	glVertex3f(-2,-3,0);
	glVertex3f(-1,-3,2);
	glVertex3f(-1,-3,2);
	glVertex3f(1,-3,2);
	glVertex3f(2,-3,0);
	glVertex3f(1,-3,-2);
	glVertex3f(-1,-3,-2);
	
	glVertex3f(-1,3,-2); //Superior inferior
	glVertex3f(-2,3,0);
	glVertex3f(-1,3,2);
	glVertex3f(-1,3,2);
	glVertex3f(1,3,2);
	glVertex3f(2,3,0);
	glVertex3f(1,3,-2);
	glVertex3f(-1,3,-2);
	glEnd();
	
	glBegin(GL_LINES); //Lineas que conectan la parte de abajo con la de arriba
	glVertex3f(-2,-3,0);
	glVertex3f(-2,3,0);
	glVertex3f(-1,-3,2);
	glVertex3f(-1,3,2);
	glVertex3f(-1,-3,2);
	glVertex3f(-1,3,2);
	glVertex3f(1,-3,2);
	glVertex3f(1,3,2);
	glVertex3f(2,-3,0);
	glVertex3f(2,3,0);
	glVertex3f(1,-3,-2);
	glVertex3f(1,3,-2);
	glEnd();
		
	glBegin(GL_LINES);
	glVertex3f(-1,-3,-2); //Línea diagonal de izquierda (fondo) a derecha (frente), cara inferior
	glVertex3f(1,-3,2);
	
	glVertex3f(1,-3,-2); //Línea diagonal de derecha (fondo) a izquierda (frente), cara inferior
	glVertex3f(-1,-3,2);
	
	glVertex3f(-2,-3,0); //Línea horizontal de izquierda a derecha, cara inferior
	glVertex3f(2,-3,0);
	
	glVertex3f(-1,3,-2); //Línea diagonal de izquierda (fondo) a derecha (frente), cara superior
	glVertex3f(1,3,2);
	
	glVertex3f(1,3,-2); //Línea diagonal de derecha (fondo) a izquierda (frente), cara superior
	glVertex3f(-1,3,2);
	
	glVertex3f(-2,3,0); //Línea horizontal de izquierda a derecha, cara superior
	glVertex3f(2,3,0);
	glEnd();
	glDisable(GL_COLOR_MATERIAL);
	
	//Dibujo de las esferas
	esfera(-1,-3,-2); //Esferas para el exagono inferior
	esfera(-2,-3,0);
	esfera(-1,-3,2);
	esfera(1,-3,2);
	esfera(2,-3,0);
	esfera(1,-3,-2);
	esfera(0,-3,0); //Centro
	
	esfera(-1,3,-2); //Esferas para el exagono superior
	esfera(-2,3,0);
	esfera(-1,3,2);
	esfera(1,3,2);
	esfera(2,3,0);
	esfera(1,3,-2);
	esfera(0,3,0); //Centro
}

void ortorrombicoSencillo(void){
	
	glColor3f(1,1,1);
	
	glEnable(GL_COLOR_MATERIAL);
	glBegin(GL_LINE_LOOP); //Cara izquierda
	glVertex3f(-2,2.5,-1.5);
	glVertex3f(-2,-2.5,-1.5);
	glVertex3f(-2,-2.5,1.5); 
	glVertex3f(-2,2.5,1.5);
	glEnd();
	
	glBegin(GL_LINE_LOOP); //Cara derecha
	glVertex3f(2,2.5,-1.5);
	glVertex3f(2,-2.5,-1.5);
	glVertex3f(2,-2.5,1.5); 
	glVertex3f(2,2.5,1.5);
	glEnd();
	
	glBegin(GL_LINE_LOOP); //Cara abajo
	glVertex3f(-2,-2.5,-1.5);
	glVertex3f(-2,-2.5,1.5);
	glVertex3f(2,-2.5,1.5); 
	glVertex3f(2,-2.5,-1.5);
	glEnd();
	
	glBegin(GL_LINE_LOOP); //Cara arriba
	glVertex3f(-2,2.5,-1.5);
	glVertex3f(-2,2.5,1.5);
	glVertex3f(2,2.5,1.5); 
	glVertex3f(2,2.5,-1.5);
	glEnd();
	glDisable(GL_COLOR_MATERIAL);
	
	esfera(-2,2.5,-1.5); //Esfera superior trasera (izquierda).
	esfera(-2,2.5,1.5); //Esfera superior enfrente (izquierda).
	
	esfera(-2,-2.5,-1.5); //Esfera inferior enfrente (izquierda).
	esfera(-2,-2.5,1.5); //Esfera inferior trasera (izquierda).
	
	esfera(2,2.5,-1.5); //Esfera superior enfrente (derecha).
	esfera(2,2.5,1.5); //Esfera superior trasera (derecha).
		
	esfera(2,-2.5,-1.5);; //Esfera inferior enfrente (derecha).
	esfera(2,-2.5,1.5); //Esfera inferior trasera (derecha).
	
}

void ortorrombicoCentradoEnLasBases(void){
	
	glColor3f(1,1,1);
	
	glEnable(GL_COLOR_MATERIAL);
	glBegin(GL_LINE_LOOP); //Cara izquierda
	glVertex3f(-2,2.5,-1.5);
	glVertex3f(-2,-2.5,-1.5);
	glVertex3f(-2,-2.5,1.5); 
	glVertex3f(-2,2.5,1.5);
	glEnd();
	
	glBegin(GL_LINE_LOOP); //Cara derecha
	glVertex3f(2,2.5,-1.5);
	glVertex3f(2,-2.5,-1.5);
	glVertex3f(2,-2.5,1.5); 
	glVertex3f(2,2.5,1.5);
	glEnd();
	
	glBegin(GL_LINE_LOOP); //Cara abajo
	glVertex3f(-2,-2.5,-1.5);
	glVertex3f(-2,-2.5,1.5);
	glVertex3f(2,-2.5,1.5); 
	glVertex3f(2,-2.5,-1.5);
	glEnd();
	
	glBegin(GL_LINE_LOOP); //Cara arriba
	glVertex3f(-2,2.5,-1.5);
	glVertex3f(-2,2.5,1.5);
	glVertex3f(2,2.5,1.5); 
	glVertex3f(2,2.5,-1.5);
	glEnd();
	
	glBegin(GL_LINES);
	glVertex3f(-2,-2.5,-1.5); //Lineas base inferior que conectan la esfera del centro
	glVertex3f(2,-2.5,1.5);
	glVertex3f(-2,-2.5,1.5);
	glVertex3f(2,-2.5,-1.5);
	
	glVertex3f(-2,2.5,-1.5); //Lineas base superior que conectan la esfera del centro
	glVertex3f(2,2.5,1.5);
	glVertex3f(-2,2.5,1.5);
	glVertex3f(2,2.5,-1.5);
	glEnd();
	glDisable(GL_COLOR_MATERIAL);
	
	esfera(-2,2.5,-1.5); //Esfera superior trasera (izquierda).
	esfera(-2,2.5,1.5); //Esfera superior enfrente (izquierda).
	
	esfera(-2,-2.5,-1.5); //Esfera inferior enfrente (izquierda).
	esfera(-2,-2.5,1.5); //Esfera inferior trasera (izquierda).
	
	esfera(2,2.5,-1.5); //Esfera superior enfrente (derecha).
	esfera(2,2.5,1.5); //Esfera superior trasera (derecha).
		
	esfera(2,-2.5,-1.5);; //Esfera inferior enfrente (derecha).
	esfera(2,-2.5,1.5); //Esfera inferior trasera (derecha).
	
	esfera(0,2.5,0);; //Esfera superior centro (base).
	esfera(0,-2.5,0); //Esfera inferior centro (base).
	
}

void ortorrombicoCentradoEnLasCaras(void){
	
	glColor3f(1,1,1);
	
	glEnable(GL_COLOR_MATERIAL);
	glBegin(GL_LINE_LOOP); //Cara izquierda
	glVertex3f(-2,2.5,-1.5);
	glVertex3f(-2,-2.5,-1.5);
	glVertex3f(-2,-2.5,1.5); 
	glVertex3f(-2,2.5,1.5);
	glEnd();
	
	glBegin(GL_LINE_LOOP); //Cara derecha
	glVertex3f(2,2.5,-1.5);
	glVertex3f(2,-2.5,-1.5);
	glVertex3f(2,-2.5,1.5); 
	glVertex3f(2,2.5,1.5);
	glEnd();
	
	glBegin(GL_LINE_LOOP); //Cara abajo
	glVertex3f(-2,-2.5,-1.5);
	glVertex3f(-2,-2.5,1.5);
	glVertex3f(2,-2.5,1.5); 
	glVertex3f(2,-2.5,-1.5);
	glEnd();
	
	glBegin(GL_LINE_LOOP); //Cara arriba
	glVertex3f(-2,2.5,-1.5);
	glVertex3f(-2,2.5,1.5);
	glVertex3f(2,2.5,1.5); 
	glVertex3f(2,2.5,-1.5);
	glEnd();
	
	glBegin(GL_LINES);
	glVertex3f(-2,2.5,-1.5); //Lineas que conectan la esfera de la cara izquierda
	glVertex3f(-2,-2.5,1.5);
	glVertex3f(-2,-2.5,-1.5);
	glVertex3f(-2,2.5,1.5);
	
	glVertex3f(2,2.5,-1.5); //Lineas que conectan la esfera de la cara derecha
	glVertex3f(2,-2.5,1.5);
	glVertex3f(2,-2.5,-1.5);
	glVertex3f(2,2.5,1.5);
	
	glVertex3f(-2,-2.5,-1.5); //Lineas base inferior que conectan la esfera del centro
	glVertex3f(2,-2.5,1.5);
	glVertex3f(-2,-2.5,1.5);
	glVertex3f(2,-2.5,-1.5);
	
	glVertex3f(-2,2.5,-1.5); //Lineas base superior que conectan la esfera del centro
	glVertex3f(2,2.5,1.5);
	glVertex3f(-2,2.5,1.5);
	glVertex3f(2,2.5,-1.5);
	
	glVertex3f(-2,2.5,-1.5); //Lineas que conectan la esfera de la cara fondo
	glVertex3f(2,-2.5,-1.5);
	glVertex3f(2,2.5,-1.5);
	glVertex3f(-2,-2.5,-1.5);
	
	glVertex3f(-2,2.5,1.5); //Lineas que conectan la esfera de la cara frente
	glVertex3f(2,-2.5,1.5);
	glVertex3f(2,2.5,1.5);
	glVertex3f(-2,-2.5,1.5);
	glEnd();
	glDisable(GL_COLOR_MATERIAL);

	esfera(-2,2.5,-1.5); //Esfera superior trasera (izquierda).
	esfera(-2,2.5,1.5); //Esfera superior enfrente (izquierda).
	
	esfera(-2,-2.5,-1.5); //Esfera inferior enfrente (izquierda).
	esfera(-2,-2.5,1.5); //Esfera inferior trasera (izquierda).
	
	esfera(2,2.5,-1.5); //Esfera superior enfrente (derecha).
	esfera(2,2.5,1.5); //Esfera superior trasera (derecha).
		
	esfera(2,-2.5,-1.5); //Esfera inferior enfrente (derecha).
	esfera(2,-2.5,1.5); //Esfera inferior trasera (derecha).
	
	esfera(0,-2.5,0); //Esfera inferior centro (base).
	esfera(0,2.5,0);; //Esfera superior centro (base).
	esfera(-2,0,0);; //Esfera cara izquierda centro.
	esfera(2,0,0); //Esfera cara derecha centro.
	esfera(0,0,-1.5);; //Esfera cara fondo centro.
	esfera(0,0,1.5); //Esfera cara frente centro.
	
}

void ortorrombicoCentradoEnElCuerpo(void){
	
	glColor3f(1,1,1);
	
	glEnable(GL_COLOR_MATERIAL);
	glBegin(GL_LINE_LOOP); //Cara izquierda
	glVertex3f(-2,2.5,-1.5);
	glVertex3f(-2,-2.5,-1.5);
	glVertex3f(-2,-2.5,1.5); 
	glVertex3f(-2,2.5,1.5);
	glEnd();
	
	glBegin(GL_LINE_LOOP); //Cara derecha
	glVertex3f(2,2.5,-1.5);
	glVertex3f(2,-2.5,-1.5);
	glVertex3f(2,-2.5,1.5); 
	glVertex3f(2,2.5,1.5);
	glEnd();
	
	glBegin(GL_LINE_LOOP); //Cara abajo
	glVertex3f(-2,-2.5,-1.5);
	glVertex3f(-2,-2.5,1.5);
	glVertex3f(2,-2.5,1.5); 
	glVertex3f(2,-2.5,-1.5);
	glEnd();
	
	glBegin(GL_LINE_LOOP); //Cara arriba
	glVertex3f(-2,2.5,-1.5);
	glVertex3f(-2,2.5,1.5);
	glVertex3f(2,2.5,1.5);
	glVertex3f(2,2.5,-1.5);
	glEnd();
	
	glBegin(GL_LINES);
	glVertex3f(-2,2.5,-1.5); //Lineas desde la esquina superior izquierda (fondo) hacia la inferior derecha (frente)
	glVertex3f(2,-2.5,1.5);
	
	glVertex3f(2,2.5,-1.5); //Lineas desde la esquina superior derecha (fondo) hacia la inferior izquierda (frente)
	glVertex3f(-2,-2.5,1.5);
	
	glVertex3f(-2,2.5,1.5); //Lineas desde la esquina superior izquierda (frente) hacia la inferior derecha (fondo)
	glVertex3f(2,-2.5,-1.5);
	
	glVertex3f(2,2.5,1.5); //Lineas desde la esquina superior derecha (frente) hacia la inferior izquierda (fondo)
	glVertex3f(-2,-2.5,-1.5);
	glEnd();
	glDisable(GL_COLOR_MATERIAL);
	
	
	esfera(-2,2.5,-1.5); //Esfera superior trasera (izquierda).
	esfera(-2,2.5,1.5); //Esfera superior enfrente (izquierda).
	
	esfera(-2,-2.5,-1.5); //Esfera inferior enfrente (izquierda).
	esfera(-2,-2.5,1.5); //Esfera inferior trasera (izquierda).
	
	esfera(2,2.5,-1.5); //Esfera superior enfrente (derecha).
	esfera(2,2.5,1.5); //Esfera superior trasera (derecha).
		
	esfera(2,-2.5,-1.5);; //Esfera inferior enfrente (derecha).
	esfera(2,-2.5,1.5); //Esfera inferior trasera (derecha).
	
	esfera(0,0,0);; //Esfera centro
	
}

void monoclinicoSencillo(void){
	
	glColor3f(1,1,1);
	
	glEnable(GL_COLOR_MATERIAL);
	glBegin(GL_LINE_LOOP); //Cara izquierda
	glVertex3f(-3,2.5,-1.5);
	glVertex3f(-2,-2.5,-1.5);
	glVertex3f(-2,-2.5,1.5); 
	glVertex3f(-3,2.5,1.5);
	glEnd();
	
	glBegin(GL_LINE_LOOP); //Cara derecha
	glVertex3f(1,2.5,-1.5);
	glVertex3f(2,-2.5,-1.5);
	glVertex3f(2,-2.5,1.5); 
	glVertex3f(1,2.5,1.5);
	glEnd();
	
	glBegin(GL_LINE_LOOP); //Cara abajo
	glVertex3f(-2,-2.5,-1.5);
	glVertex3f(-2,-2.5,1.5);
	glVertex3f(2,-2.5,1.5); 
	glVertex3f(2,-2.5,-1.5);
	glEnd();
	
	glBegin(GL_LINE_LOOP); //Cara arriba
	glVertex3f(-3,2.5,-1.5);
	glVertex3f(-3,2.5,1.5);
	glVertex3f(1,2.5,1.5); 
	glVertex3f(1,2.5,-1.5);
	glEnd();
	glDisable(GL_COLOR_MATERIAL);
	
	esfera(-3,2.5,-1.5); //Esfera superior trasera (izquierda).
	esfera(-3,2.5,1.5); //Esfera superior enfrente (izquierda).
	
	esfera(-2,-2.5,-1.5); //Esfera inferior enfrente (izquierda).
	esfera(-2,-2.5,1.5); //Esfera inferior trasera (izquierda).
	
	esfera(1,2.5,-1.5); //Esfera superior enfrente (derecha).
	esfera(1,2.5,1.5); //Esfera superior trasera (derecha).
		
	esfera(2,-2.5,-1.5);; //Esfera inferior enfrente (derecha).
	esfera(2,-2.5,1.5); //Esfera inferior trasera (derecha).
	
}

void monoclinicoCentradoEnLasBases(void){
	
	glColor3f(1,1,1);
	
	glEnable(GL_COLOR_MATERIAL);
	glBegin(GL_LINE_LOOP); //Cara izquierda
	glVertex3f(-3,2.5,-1.5);
	glVertex3f(-2,-2.5,-1.5);
	glVertex3f(-2,-2.5,1.5); 
	glVertex3f(-3,2.5,1.5);
	glEnd();
	
	glBegin(GL_LINE_LOOP); //Cara derecha
	glVertex3f(1,2.5,-1.5);
	glVertex3f(2,-2.5,-1.5);
	glVertex3f(2,-2.5,1.5); 
	glVertex3f(1,2.5,1.5);
	glEnd();
	
	glBegin(GL_LINE_LOOP); //Cara abajo
	glVertex3f(-2,-2.5,-1.5);
	glVertex3f(-2,-2.5,1.5);
	glVertex3f(2,-2.5,1.5); 
	glVertex3f(2,-2.5,-1.5);
	glEnd();
	
	glBegin(GL_LINE_LOOP); //Cara arriba
	glVertex3f(-3,2.5,-1.5);
	glVertex3f(-3,2.5,1.5);
	glVertex3f(1,2.5,1.5); 
	glVertex3f(1,2.5,-1.5);
	glEnd();
	
	glBegin(GL_LINES);
	glVertex3f(-2,-2.5,-1.5); //Lineas base inferior que conectan la esfera del centro
	glVertex3f(2,-2.5,1.5);
	glVertex3f(-2,-2.5,1.5);
	glVertex3f(2,-2.5,-1.5);
	
	glVertex3f(-3,2.5,-1.5); //Lineas base superior que conectan la esfera del centro
	glVertex3f(1,2.5,1.5);
	glVertex3f(-3,2.5,1.5);
	glVertex3f(1,2.5,-1.5);
	glEnd();
	glDisable(GL_COLOR_MATERIAL);
	
	esfera(-3,2.5,-1.5); //Esfera superior trasera (izquierda).
	esfera(-3,2.5,1.5); //Esfera superior enfrente (izquierda).
	
	esfera(-2,-2.5,-1.5); //Esfera inferior enfrente (izquierda).
	esfera(-2,-2.5,1.5); //Esfera inferior trasera (izquierda).
	
	esfera(1,2.5,-1.5); //Esfera superior enfrente (derecha).
	esfera(1,2.5,1.5); //Esfera superior trasera (derecha).
		
	esfera(2,-2.5,-1.5);; //Esfera inferior enfrente (derecha).
	esfera(2,-2.5,1.5); //Esfera inferior trasera (derecha).
	
	esfera(-1,2.5,0);; //Esfera superior centro (base).
	esfera(0,-2.5,0); //Esfera inferior centro (base).
	
}

void triclinica(void){
	
	glColor3f(1,1,1);
	
	glPushMatrix();
	glTranslatef(-2.50,-1,-2);
	
	glEnable(GL_COLOR_MATERIAL);
	glBegin(GL_LINE_LOOP); //Cara izquierda
	glVertex3f(1,2,0);
	glVertex3f(0,0,0);
	glVertex3f(1,0,4);
	glVertex3f(2,2,4);
	glEnd();
	
	glBegin(GL_LINE_LOOP); //Cara derecha
	glVertex3f(4,2,0);
	glVertex3f(3,0,0);
	glVertex3f(4,0,4);
	glVertex3f(5,2,4);
	glEnd();
	
	glBegin(GL_LINE_LOOP); //Cara abajo
	glVertex3f(0,0,0);
	glVertex3f(1,0,4);
	glVertex3f(4,0,4);
	glVertex3f(3,0,0);
	glEnd();
	
	glBegin(GL_LINE_LOOP); //Cara arriba
	glVertex3f(1,2,0);
	glVertex3f(2,2,4);
	glVertex3f(5,2,4);
	glVertex3f(4,2,0);
	glEnd();
	glDisable(GL_COLOR_MATERIAL);
	
	esfera(1,2,0); //Esfera superior trasera (izquierda).
	esfera(2,2,4); //Esfera superior enfrente (izquierda).
	
	esfera(1,0,4); //Esfera inferior enfrente (izquierda).
	esfera(0,0,0); //Esfera inferior trasera (izquierda).
	
	esfera(5,2,4); //Esfera superior enfrente (derecha).
	esfera(4,2,0); //Esfera superior trasera (derecha).
		
	esfera(4,0,4); //Esfera inferior enfrente (derecha).
	esfera(3,0,0); //Esfera inferior trasera (derecha).
	
	glPopMatrix();
	
}
