#include "livello6.hpp"

Livello6::Livello6(){
	dir = SX;
	contatore_laterale = 500;
	contatore_verticale = numMattoni = numMattoniIndistruttibili = 0;
	int x = -15, y = 12;
	for (int i = 1; i <= 35; i++) {
		if (i == 30 || i == 32 || i == 34) {
			aggiungiMattone(new MattoneIndistruttibile(x, y));
			numMattoniIndistruttibili++;
		}
		else if (i == 11 || i == 18 || i == 25 || i == 29 || i == 31 || i == 33 || i == 35) {
			MattoneInvisibile* tmp = new MattoneInvisibile(x, y);
			aggiungiMattone(tmp);
			mattoniInvisibili.push_back(tmp);
		}
		else if ((i % 2 != 0 && i <= 7) || i == 16 || i == 20)
			aggiungiMattone(new MattoneOro(x, y));
		else if ((i <= 6 && i % 2 == 0) || (i > 6 && i < 15))
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
	tot = Livello::getNumMattoni();
}

unsigned int Livello6::getNumMattoni() {
	return Livello::getNumMattoni() - (numMattoniIndistruttibili + mattoniInvisibili.size());
}

void Livello6::render() {
	// movimento laterale mattoni
	if (dir == SX)
		for (auto m = begin(); m != end(); ++m)
			(*m)->setPosx((*m)->getPosx() - 0.01);
	else
		for (auto m = begin(); m != end(); ++m)
			(*m)->setPosx((*m)->getPosx() + 0.01);

	if (contatore_laterale++ == 1000) {
		dir = dir == SX ? DX : SX;
		contatore_laterale = 0;
	}

	for (auto m = mattoniInvisibili.begin(); m != mattoniInvisibili.end();)
		if ((*m)->getSalute() < 2)
			m = mattoniInvisibili.erase(m);
		else
			++m;

	// movimento dei mattoni verso il basso
	if (tot != Livello::getNumMattoni()) {
		tot = Livello::getNumMattoni();
		contatore_verticale++;
	}

	if (contatore_verticale == 10) {
		for (auto m = begin(); m != end(); ++m)
			(*m)->setPosy((*m)->getPosy() - 3);
		contatore_verticale = 0;
	}

	glPushMatrix();
	for (auto m = begin(); m != end(); ++m)
		if ((*m)->getSalute() > 0)
			(*m)->render();
	glPopMatrix();
}
