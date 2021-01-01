#ifndef _PALLA
#define _PALLA

#include "oggetto.hpp"
#include "mattone.hpp"
#include "pedana.hpp"

class Palla : public Oggetto {
public:
	Palla();
	Palla(coordinate, coordinate);

	float getRaggio();
	bool getFermo();
	void setRaggio(float);
	void setFermo(bool);
	
	void render() override;

	bool collide(Mattone);
	bool collide(Pedana);
	coordinate muove(int, int, int);
	void reset(coordinate, coordinate);

private:
	float raggio;
	bool fermo;

	collisione collisioneAABB(Oggetto *);
	direzione getDirezione(coordinate);
};

#endif