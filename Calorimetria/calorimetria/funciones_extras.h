GLuint texture[5];

void mapear(int map) //Funcion para definir el mapeo de las texturas de las figuras
{
	
    glBindTexture(GL_TEXTURE_2D, texture[map]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
	
}

void cubo(float l, int map){
	
	glEnable(GL_TEXTURE_2D);
    mapear(map);
	
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(-l/2,l/2);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(-l/2,-l/2);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(l/2,-l/2);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(l/2,l/2);
	glEnd();
	
	glDisable(GL_TEXTURE_2D);
}
