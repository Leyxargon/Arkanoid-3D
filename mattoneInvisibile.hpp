#ifndef _MATTONE_INVISIBILE
#define _MATTONE_INVISIBILE

#include "mattone.hpp"

class MattoneInvisibile : public Mattone {
public:
	MattoneInvisibile(float, float);

	void render() override;

private:
	static GLuint texture;
};

#endif