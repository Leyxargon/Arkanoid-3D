#ifndef _GIOCO
#define _GIOCO

#include "wrapper.hpp"
#include "menu.hpp"

class Gioco {
public:
	explicit Gioco(int, char **);

	void esegui();
private:
	Menu menu;

	const int LARGHEZZA_FINESTRA = 800;
	const int ALTEZZA_FINESTRA = 600;
};

#endif