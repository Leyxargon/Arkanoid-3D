#ifndef _LIVELLO
#define _LIVELLO

#include "wrapper.hpp"

#include "mattoneBlu.hpp"
#include "mattoneVerde.hpp"
#include "mattoneViola.hpp"
#include "mattoneOro.hpp"
#include "mattoneIndistruttibile.hpp"
#include "mattoneInvisibile.hpp"

class Livello {
public:
	Livello() {};

	void aggiungiMattone(Mattone *);
	void rimuoviMattone(list<Mattone *>::iterator &);
	virtual unsigned int getNumMattoni();

	list<Mattone *>::iterator begin();
	list<Mattone *>::iterator end();

	virtual void render();

private:
	list<Mattone *> mattoni;
};

#endif