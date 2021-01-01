#include "pedana.hpp"

GLuint Pedana::texture = 0;

Pedana::Pedana() : Pedana(-4.0, -20) {}

Pedana::Pedana(float x, float y) {
	setPosizione(x, y);
	setDimensione(8, 2.5);
	setVelx(0.2);
	texture = 0;
	muovesx = false;
	muovedx = false;
}

bool Pedana::getMuovesx() {
	return muovesx;
}

bool Pedana::getMuovedx() {
	return muovedx;
}

void Pedana::setMuovesx(bool var) {
	muovesx = var;
}

void Pedana::setMuovedx(bool var) {
	muovedx = var;
}

void Pedana::render() {
	if (texture == 0)
		texture = loadTexture("texture/pedana.png");

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glTranslatef(getPosx() + getDimx() / 2, getPosy() + getDimy() / 2, 0);
	glScalef(getDimx(), getDimy(), 2);
	glColor3ub(getRosso(), getVerde(), getBlu());
	glutSolidCubeCustom(1);

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void Pedana::renderVita() {
	if (texture == 0)
		texture = loadTexture("texture/pedana.png");

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glTranslatef(getPosx() + 4, getPosy() + 1.3, 0);
	glScalef(getDimx(), getDimy(), 2);
	glColor3ub(getRosso(), getVerde(), getBlu());
	glutSolidCubeCustom(0.2);

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}