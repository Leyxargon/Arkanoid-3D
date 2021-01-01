#ifndef _WRAPPER
#define _WRAPPER

#define LOAD_OGL_TEXTURE

#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <tuple>
#include <list>
#include <set>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <soil.h>

enum direzione {
	SU,
	DX,
	GIU,
	SX
};

using namespace std;
using coordinate = pair<float, float>;
using collisione = tuple<bool, direzione, coordinate>;

float clamp(float, float, float);
coordinate normalizza(coordinate);
float dot(coordinate, coordinate);

static void drawBox(GLfloat, GLenum);
void APIENTRY glutSolidCubeCustom(GLdouble);

GLuint loadTexture(string);

#endif
