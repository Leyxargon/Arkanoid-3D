#ifndef _LIVELLO5
#define _LIVELLO5

#include "livello.hpp"

class Livello5 : public Livello {
public:
	Livello5();

	unsigned int getNumMattoni() override;

	void render() override;

private:
	enum direzione {
		SX,
		DX
	} dir;
	list<MattoneInvisibile *> mattoniInvisibili;
	unsigned short numMattoni, numMattoniIndistruttibili, contatore;
};

#endif