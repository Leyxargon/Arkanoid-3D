#include "livello1.hpp"

Livello1::Livello1() {
	int x = -20, y = 12;
	for (int i = 1; i <= 36; i++) {
		if (i == 11 || i == 12 || i == 16 || i == 17 || i == 20 || i == 21 || i == 25 || i == 26)
			aggiungiMattone(new MattoneOro(x, y));
		else if (i <= 18)
			aggiungiMattone(new MattoneVerde(x, y));
		else
			aggiungiMattone(new MattoneBlu(x, y));

		if ((x += 5) > 20) {
			x = -20;
			y -= 3;
		}
	}
}
