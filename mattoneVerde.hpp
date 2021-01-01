#ifndef _MATTONE_VERDE
#define _MATTONE_VERDE

#include "mattone.hpp"

class MattoneVerde : public Mattone {
public:
	MattoneVerde(float, float);

	void render() override;

private:
	static GLuint texture;
};

#endif