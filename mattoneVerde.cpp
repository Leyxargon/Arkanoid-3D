#include "mattoneVerde.hpp"

GLuint MattoneVerde::texture = 0;

MattoneVerde::MattoneVerde(float x, float y) : Mattone(x, y) {
	setValore(75);
	setSalute(1);
	MattoneVerde::texture = 0;
}

void MattoneVerde::render() {
	if (texture == 0)
		texture = loadTexture("texture/15-Breakout-Tiles.png");

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