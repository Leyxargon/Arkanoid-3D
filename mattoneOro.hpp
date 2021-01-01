#ifndef _MATTONE_ORO
#define _MATTONE_ORO

#include "mattone.hpp"

class MattoneOro : public Mattone {
public:
	MattoneOro(float, float);

	void render() override;

private:
	static GLuint texture1, texture2;
};

#endif