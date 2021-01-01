#include "livello3.hpp"

Livello3::Livello3() {
	int x = -20, y = 12;
	for (int i = 1; i <= 45; i++) {
		if (i == 1 || i == 9 || i == 10 || i == 18 || i == 19 || i == 27 || i == 28 || i == 36 || i == 37 || i == 45) {
			MattoneInvisibile* tmp = new MattoneInvisibile(x, y);
			aggiungiMattone(tmp);
			mattoniInvisibili.push_back(tmp);
		}
		else if (i == 5 || i == 14 || i == 23 || i == 32 || i == 41)
			aggiungiMattone(new MattoneOro(x, y));
		else if (i < 9)
			aggiungiMattone(new MattoneViola(x, y));
		else if (i < 27)
			aggiungiMattone(new MattoneVerde(x, y));
		else
			aggiungiMattone(new MattoneBlu(x, y));
		if ((x += 5) > 20) {
			x = -20;
			y -= 3;
		}
	}
}

unsigned int Livello3::getNumMattoni() {
	return Livello::getNumMattoni() - mattoniInvisibili.size();
}

void Livello3::render() {
	for (auto m = mattoniInvisibili.begin(); m != mattoniInvisibili.end();)
		if ((*m)->getSalute() < 2)
			m = mattoniInvisibili.erase(m);
		else
			++m;

	glPushMatrix();
	for (auto m = begin(); m != end(); ++m)
		if ((*m)->getSalute() > 0)
			(*m)->render();
	glPopMatrix();
}
