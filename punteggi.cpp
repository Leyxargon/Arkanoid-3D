#include "punteggi.hpp"

Punteggi::Punteggi() {
	ifstream file("punteggirecord.txt");

	if (file.is_open()) {
		record tmp;
		for (int i = 1; i <= 12; ++i) {
			file >> tmp.first;
			file >> tmp.second;
			giocatori.insert(tmp);
		}
	}
	else {
		cerr << "Impossibile caricare i punteggi" << endl;
		exit(2);
	}

	file.close();
}

record Punteggi::getCampione() {
	return (*giocatori.begin());
}

string Punteggi::getNomeCampione() {
	return (*giocatori.begin()).first;
}

unsigned int Punteggi::getPunteggioCampione() {
	return (*giocatori.begin()).second;
}

record Punteggi::getUltimoGiocatore() {
	return (*--giocatori.end());
}

string Punteggi::getNomeUltimoGiocatore() {
	return (*--giocatori.end()).first;
}

unsigned int Punteggi::getPunteggioUltimoGiocatore() {
	return (*--giocatori.end()).second;
}

void Punteggi::nuovoGiocatore(record record) {
	giocatori.insert(record);
	giocatori.erase(getUltimoGiocatore());
	commit();
}

void Punteggi::nuovoGiocatore(string nome, unsigned int punteggio) {
	giocatori.insert({ nome, punteggio });
	giocatori.erase(getUltimoGiocatore());
	commit();
}

multiset<record>::iterator Punteggi::begin() {
	return giocatori.begin();
}

multiset<record>::iterator Punteggi::end() {
	return giocatori.end();
}

void Punteggi::commit() {
	ofstream file("punteggirecord.txt", ofstream::trunc);

	for (auto g = giocatori.begin(); g != giocatori.end(); ++g)
		file << g->first << ' ' << g->second << endl;

	file.close();
}