#include "mattoneIndistruttibile.hpp"

GLuint MattoneIndistruttibile::texture = 0;

MattoneIndistruttibile::MattoneIndistruttibile(float x, float y) : Mattone(x, y) {
	setValore(0);
	setSalute(numeric_limits<int>::max());
	MattoneIndistruttibile::texture = 0;
}

void MattoneIndistruttibile::render() {
	if (texture == 0)
		texture = loadTexture("texture/17-Breakout-Tiles.png");

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
