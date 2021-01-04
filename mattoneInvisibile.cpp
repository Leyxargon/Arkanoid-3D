#include "mattoneInvisibile.hpp"

GLuint MattoneInvisibile::texture = 0;

MattoneInvisibile::MattoneInvisibile(float x, float y) : Mattone(x, y) {
	setValore(120);
	setSalute(2);
	texture = 0;
}

void MattoneInvisibile::render() {
	if (texture == 0)
		texture = loadTexture("texture/08-Breakout-Tiles.png");

	if (getSalute() == 1) {
		glEnable(GL_TEXTURE_2D);
		glPushMatrix();
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
			glBindTexture(GL_TEXTURE_2D, texture);

			glTranslatef(getPosx(), getPosy(), 0);
			glScalef(getDimx(), getDimy(), 2);
			glutSolidCubeCustom(1);
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	}
}
