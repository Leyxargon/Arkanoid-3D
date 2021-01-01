#ifndef _PUNTEGGI
#define _PUNTEGGI

#include "wrapper.hpp"

using record = pair<string, unsigned int>;

class Punteggi {
public:
	Punteggi();

	record getCampione();
	string getNomeCampione();
	unsigned int getPunteggioCampione();

	record getUltimoGiocatore();
	string getNomeUltimoGiocatore();
	unsigned int getPunteggioUltimoGiocatore();

	void nuovoGiocatore(record);
	void nuovoGiocatore(string, unsigned int);

	multiset<record>::iterator begin();
	multiset<record>::iterator end();

private:
	struct compara {
		bool operator() (const record& x, const record& y) const {
			return x.second > y.second;
		}
	};
	multiset<record, compara> giocatori;

	void commit();
};

#endif