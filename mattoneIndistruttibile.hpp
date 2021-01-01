#ifndef _MATTONE_INDISTRUTTIBILE
#define _MATTONE_INDISTRUTTIBILE

#include "mattone.hpp"

class MattoneIndistruttibile : public Mattone {
public:
	MattoneIndistruttibile(float, float);

	void render() override;

private:
	static GLuint texture;
};

#endif