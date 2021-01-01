#include "oggetto.hpp"

Oggetto::Oggetto() {
	posizione = {0.0, 0.0};
	dimensione = {1.0, 1.0};
	velocita = {0.0, 0.0};
}

coordinate Oggetto::getPosizione() {
	return posizione;
}

coordinate Oggetto::getVelocita() {
	return velocita;
}

coordinate Oggetto::getDimensione() {
	return dimensione;
}

tuple<unsigned short, unsigned short, unsigned short> Oggetto::getColore() {
	return colore;
}

float Oggetto::getPosx() {
	return posizione.first;
}

float Oggetto::getPosy() {
	return posizione.second;
}

float Oggetto::getVelx() {
	return velocita.first;
}

float Oggetto::getVely() {
	return velocita.second;
}

float Oggetto::getDimx() {
	return dimensione.first;
}

float Oggetto::getDimy() {
	return dimensione.second;
}

unsigned short Oggetto::getRosso() {
	return get<0>(colore);
}

unsigned short Oggetto::getVerde() {
	return get<1>(colore);
}

unsigned short Oggetto::getBlu() {
	return get<2>(colore);
}

void Oggetto::setPosizione(float x, float y) {
	posizione = {x, y};
}

void Oggetto::setPosizione(coordinate pos) {
	posizione = pos;
}

void Oggetto::setVelocita(float x, float y) {
	velocita = { x, y };
}

void Oggetto::setVelocita(coordinate vel) {
	velocita = vel;
}

void Oggetto::setDimensione(float x, float y) {
	dimensione = { x, y };
}

void Oggetto::setDimensione(coordinate dim) {
	dimensione = dim;
}

void Oggetto::setColore(unsigned short r, unsigned short g, unsigned short b) {
	colore = make_tuple(r, g, b);
}

void Oggetto::setColore(tuple<unsigned short, unsigned short, unsigned short> c) {
	colore = c;
}

void Oggetto::setPosx(float x) {
	posizione.first = x;
}

void Oggetto::setPosy(float y) {
	posizione.second = y;
}

void Oggetto::setVelx(float x) {
	velocita.first = x;
}

void Oggetto::setVely(float y) {
	velocita.second = y;
}

void Oggetto::setDimx(float x) {
	dimensione.first = x;
}

void Oggetto::setDimy(float y) {
	dimensione.second = y;
}

void Oggetto::setRosso(unsigned short rosso) {
	get<0>(colore) = rosso;
}

void Oggetto::setVerde(unsigned short verde) {
	get<1>(colore) = verde;
}

void Oggetto::setBlu(unsigned short blu) {
	get<2>(colore) = blu;
}