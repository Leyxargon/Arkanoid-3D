#include "livello4.hpp"

Livello4::Livello4() {
	contatore = 0;
	int x = -15, y = 12;
	for (int i = 1; i <= 28; i++) {
		if (i <= 7)
			aggiungiMattone(new MattoneOro(x, y));
		else if (i <= 14)
			aggiungiMattone(new MattoneViola(x, y));
		else if (i <= 21)
			aggiungiMattone(new MattoneVerde(x, y));
		else
			aggiungiMattone(new MattoneBlu(x, y));

		if ((x += 5) > 15) {
			x = -15;
			y -= 3;
		}
	}
	tot = getNumMattoni();
}

void Livello4::render() {
	if (tot != getNumMattoni()) {
		tot = getNumMattoni();
		++contatore;
	}

	if (contatore == 10) {
		for (auto m = begin(); m != end(); ++m)
			(*m)->setPosy((*m) -> getPosy() - 3);
		contatore = 0;
	}

	glPushMatrix();
		for (auto m = begin(); m != end(); ++m)
			if ((*m)->getSalute() > 0)
				(*m)->render();
	glPopMatrix();
}