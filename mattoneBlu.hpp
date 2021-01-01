#ifndef _MATTONE_BLU
#define _MATTONE_BLU

#include "mattone.hpp"

class MattoneBlu : public Mattone {
public:
	MattoneBlu(float, float);

	void render() override;

private:
	static GLuint texture;
};

#endif