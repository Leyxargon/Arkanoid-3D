#include "mattoneOro.hpp"

GLuint MattoneOro::texture1 = 0;
GLuint MattoneOro::texture2 = 0;

MattoneOro::MattoneOro(float x, float y) : Mattone(x, y) {
	setSalute(2);
	setValore(150);
	MattoneOro::texture1 = 0;
	MattoneOro::texture2 = 0;
}

void MattoneOro::render() {
	if (texture1 == 0)
		texture1 = loadTexture("texture/13-Breakout-Tiles.png");
	if (texture2 == 0)
		texture2 = loadTexture("texture/14-Breakout-Tiles.png");

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);

	// Render Settings
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, getSalute() < 2 ? texture2 : texture1);

	glTranslatef(getPosx(), getPosy(), 0);
	glScalef(getDimx(), getDimy(), 2);
	glutSolidCubeCustom(1);

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}