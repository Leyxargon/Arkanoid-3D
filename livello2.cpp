#include "livello2.hpp"

Livello2::Livello2() {
	int x = -15, y = 12;
	for (int i = 1; i <= 35; i++) {
		if (i <= 8 || i == 14 || i == 15 || i == 21 || i == 22 || i == 28 || i >= 29)
			aggiungiMattone(new MattoneOro(x, y));
		else if (i == 11 || i == 18 || i == 25)
			aggiungiMattone(new MattoneViola(x, y));
		else
			aggiungiMattone(new MattoneBlu(x, y));

		if ((x += 5) > 15) {
			x = -15;
			y -= 3;
		}
	}
}
