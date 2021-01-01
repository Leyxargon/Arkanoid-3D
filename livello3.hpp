#ifndef _LIVELLO3
#define _LIVELLO3

#include "livello.hpp"

class Livello3 : public Livello {
public:
	Livello3();

	unsigned int getNumMattoni() override;

	void render() override;

private:
	list<MattoneInvisibile *> mattoniInvisibili;
};

#endif