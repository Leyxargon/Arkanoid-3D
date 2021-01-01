#include "mattone.hpp"

Mattone::Mattone(coordinate pos, tuple<unsigned short, unsigned short, unsigned short> colore) {
	setPosizione(pos.first, pos.second);
	setDimensione(4, 2);
	setColore(get<0>(colore), get<1>(colore), get<2>(colore));
}

Mattone::Mattone(float x, float y) {
	setPosizione(x, y);
	setDimensione(4, 2);
	setColore(1.0, 1.0, 1.0);
}

unsigned int Mattone::getSalute() {
	return salute;
}

unsigned int Mattone::getValore() {
	return valore;
}

void Mattone::setSalute(unsigned int ps) {
	salute = ps;
}

void Mattone::setValore(unsigned int val) {
	valore = val;
}