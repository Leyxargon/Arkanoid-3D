#include "mattoneBlu.hpp"

GLuint MattoneBlu::texture = 0;

MattoneBlu::MattoneBlu(float x, float y) : Mattone(x, y) {
	setValore(50);
	setSalute(1);
	MattoneBlu::texture = 0;
}

void MattoneBlu::render() {
	if (texture == 0)
		texture = loadTexture("texture/01-Breakout-Tiles.png");
	
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

		glTranslatef(getPosx(), getPosy(), 0);
		glScalef(getDimx(), getDimy(), 2);
		glutSolidCubeCustom(1);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}