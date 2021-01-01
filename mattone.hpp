#ifndef _MATTONE
#define _MATTONE

#include "oggetto.hpp"

class Mattone : public Oggetto {
public:
	Mattone(coordinate, tuple<unsigned short, unsigned short, unsigned short>);
	Mattone(float, float);

	unsigned int getSalute();
	unsigned int getValore();
	void setSalute(unsigned int);
	void setValore(unsigned int);

	virtual void render() {};

private:
	unsigned int salute, valore;
};

#endif