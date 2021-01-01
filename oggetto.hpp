#ifndef _OGGETTO
#define _OGGETTO

#include "wrapper.hpp"

class Oggetto {
public:
	Oggetto();
	
	coordinate getPosizione();
	coordinate getVelocita();
	coordinate getDimensione();
	tuple<unsigned short, unsigned short, unsigned short> getColore();
	float getPosx();
	float getPosy();
	float getVelx();
	float getVely();
	float getDimx();
	float getDimy();
	unsigned short getRosso();
	unsigned short getVerde();
	unsigned short getBlu();
	void setPosizione(float, float);
	void setPosizione(coordinate);
	void setVelocita(float, float);
	void setVelocita(coordinate);
	void setDimensione(float, float);
	void setDimensione(coordinate);
	void setColore(unsigned short, unsigned short, unsigned short);
	void setColore(tuple<unsigned short, unsigned short, unsigned short>);
	void setPosx(float);
	void setPosy(float);
	void setVelx(float);
	void setVely(float);
	void setDimx(float);
	void setDimy(float);
	void setRosso(unsigned short);
	void setVerde(unsigned short);
	void setBlu(unsigned short);
	virtual void render() = 0;

private:
	coordinate posizione, velocita, dimensione;
	tuple<unsigned short, unsigned short, unsigned short> colore;
};

#endif