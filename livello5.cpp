#include "livello5.hpp"

Livello5::Livello5() {
	dir = SX;
	contatore = 500;
	numMattoni = numMattoniIndistruttibili = 0;
	int x = -15, y = 12;
	for (int i = 1; i <= 28; i++) {
		if (i == 4 || i == 11 || i == 18 || i == 25) {
			aggiungiMattone(new MattoneIndistruttibile(x, y));
			numMattoniIndistruttibili++;
		}
		else if (i == 9 || i == 10 || i == 12 || i == 13 || i == 16 || i == 17 || i == 19 || i == 20) {
			MattoneInvisibile* tmp = new MattoneInvisibile(x, y);
			aggiungiMattone(tmp);
			mattoniInvisibili.push_back(tmp);
		}
		else {
			if (i <= 7)
				aggiungiMattone(new MattoneOro(x, y));
			else if (i <= 14)
				aggiungiMattone(new MattoneViola(x, y));
			else if (i <= 21)
				aggiungiMattone(new MattoneVerde(x, y));
			else
				aggiungiMattone(new MattoneBlu(x, y));
			numMattoni++;
		}
		if ((x += 5) > 15) {
			x = -15;
			y -= 3;
		}
	}
}

unsigned int Livello5::getNumMattoni() {
	return Livello::getNumMattoni() - (numMattoniIndistruttibili + mattoniInvisibili.size());
}

void Livello5::render() {
	if (dir == SX)
		for (auto m = begin(); m != end(); ++m)
			(*m)->setPosx((*m)->getPosx() - 0.01);
	else
		for (auto m = begin(); m != end(); ++m)
			(*m)->setPosx((*m)->getPosx() + 0.01);

	if (contatore++ == 1000) {
		dir = dir == SX ? DX : SX;
		contatore = 0;
	}

	for (auto m = mattoniInvisibili.begin(); m != mattoniInvisibili.end();)
		if ((*m)->getSalute() < 2)
			m = mattoniInvisibili.erase(m);
		else
			++m;

	glPushMatrix();
	for (auto m = begin(); m != end(); ++m) {
		if ((*m)->getSalute() > 0)
			(*m)->render();
	}
	glPopMatrix();
}