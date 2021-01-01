#ifndef _LIVELLO6
#define _LIVELLO6

#include "livello.hpp"

class Livello6 : public Livello {
public:
	Livello6();

	unsigned int getNumMattoni() override;

	void render() override;

private:
	enum direzione {
		SX,
		DX
	} dir;
	list<MattoneInvisibile *> mattoniInvisibili;
	unsigned short numMattoni, numMattoniIndistruttibili, contatore_verticale, contatore_laterale, tot;
};

#endif 
