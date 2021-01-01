#include "wrapper.hpp"

// rif: https://en.wikipedia.org/wiki/Clamping_(graphics)
float clamp(float value, float min, float max) {
	return std::max(min, std::min(max, value));
}

// x^2 / sqrt(x^2 + y^2) + y^2 / sqrt(x^2 + y^2)
coordinate normalizza(const coordinate t) {
	float tt = sqrt((t.first * t.first) + (t.second * t.second));
	return make_pair(t.first / tt, t.second / tt);
}

float dot(coordinate a, coordinate b) {
	return a.first * b.first + a.second * b.second;
}

static void drawBox(GLfloat size, GLenum type) {
	static GLfloat n[6][3] = {
	  {-1.0, 0.0, 0.0},
	  {0.0, 1.0, 0.0},
	  {1.0, 0.0, 0.0},
	  {0.0, -1.0, 0.0},
	  {0.0, 0.0, 1.0},
	  {0.0, 0.0, -1.0}
	};
	static GLint faces[6][4] = {
	  {0, 1, 2, 3},
	  {3, 2, 6, 7},
	  {7, 6, 5, 4},
	  {4, 5, 1, 0},
	  {5, 6, 2, 1},
	  {7, 4, 0, 3}
	};
	GLfloat v[8][3];
	GLint i;

	v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
	v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
	v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

	for (i = 5; i >= 0; i--) {
		glBegin(type);
		glTexCoord2f(0.0, 0.0);
		glVertex3fv(&v[faces[i][0]][0]);
		glTexCoord2f(0.0, 1.0);
		glVertex3fv(&v[faces[i][1]][0]);
		glTexCoord2f(1.0, 1.0);
		glVertex3fv(&v[faces[i][2]][0]);
		glTexCoord2f(1.0, 0.0);
		glVertex3fv(&v[faces[i][3]][0]);
		glEnd();
	}
}

void APIENTRY glutSolidCubeCustom(GLdouble size) {
	drawBox(size, GL_QUADS);
}

GLuint loadTexture(string filename) {
	GLuint texture = SOIL_load_OGL_texture (
		filename.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	if (texture == 0)
		cerr << "Errore nel caricamento della texture: " << string(filename) << endl;

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return texture;
}