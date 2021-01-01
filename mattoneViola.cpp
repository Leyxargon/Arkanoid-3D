#include "mattoneViola.hpp"

GLuint MattoneViola::texture = 0;

MattoneViola::MattoneViola(float x, float y) : Mattone(x, y) {
	setValore(100);
	setSalute(1);
	MattoneViola::texture = 0;
}

void MattoneViola::render() {
	if (texture == 0)
		texture = loadTexture("texture/05-Breakout-Tiles.png");

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glTranslatef(getPosx(), getPosy(), 0);
	glScalef(getDimx(), getDimy(), 2);
	glutSolidCubeCustom(1);

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}