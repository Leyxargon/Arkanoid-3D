#include "livello.hpp"

void Livello::aggiungiMattone(Mattone *m) {
	mattoni.push_back(m);
}

void Livello::rimuoviMattone(list<Mattone *>::iterator &m) {
	m = mattoni.erase(m);
}

unsigned int Livello::getNumMattoni() {
	return mattoni.size();
}

list<Mattone *>::iterator Livello::begin() {
	return mattoni.begin();
}

list<Mattone *>::iterator Livello::end() {
	return mattoni.end();
}

void Livello::render() {
	glPushMatrix();
		for (auto m = mattoni.begin(); m != mattoni.end(); ++m)
			if ((*m)->getSalute() > 0)
				(*m)->render();
	glPopMatrix();
}