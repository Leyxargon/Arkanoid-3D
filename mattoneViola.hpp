#ifndef _MATTONE_VIOLA
#define _MATTONE_VIOLA

#include "mattone.hpp"

class MattoneViola : public Mattone {
public:
	MattoneViola(float, float);

	void render() override;

private:
	static GLuint texture;
};

#endif