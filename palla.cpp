#include "palla.hpp"

Palla::Palla() : Palla({ 0.0, -8.0 }, { 0.1, 0.1 }) {}

Palla::Palla(coordinate posizione, coordinate velocita) {
	raggio = 1;
	fermo = true;
	setPosizione(posizione.first, posizione.second);
	setDimensione(raggio, raggio);
	setVelocita(velocita.first, velocita.second);
	setColore(128, 128, 128);
}

float Palla::getRaggio() {
	return raggio;
}

bool Palla::getFermo() {
	return fermo;
}

void Palla::setRaggio(float r) {
	raggio = r;
}

void Palla::setFermo(bool var) {
	fermo = var;
}

void Palla::render() {
	glPushMatrix();
		glTranslatef(getPosx(), getPosy(), 0);
		glScalef(raggio, raggio, raggio);
		glColor3ub(getRosso(), getVerde(), getBlu());
		glutSolidSphere(1, 11, 11);
	glPopMatrix();
}

collisione Palla::collisioneAABB(Oggetto *ogg) {
	// calcola centro della palla
	coordinate centro = make_pair(getPosx() + getRaggio(), getPosy() + getRaggio());
	// calcola informazioni sulla collisione AABB (centro, half-extents)
	coordinate half_extents(ogg->getDimx() / 2.0, ogg->getDimy() / 2.0);
	coordinate aabb_centro(ogg->getPosx() + half_extents.first, ogg->getPosy() + half_extents.second);
	// calcola vettore differenza tra il centro della sfera e il centro AABB
	coordinate differenza = make_pair(centro.first - aabb_centro.first, centro.second - aabb_centro.second);
	// applica il "clamping": sposta il punto al più vicino valore disponibile tale che diff € [-half_ext, half_ext]
	coordinate clamped = make_pair(clamp(differenza.first, -half_extents.first, half_extents.first), clamp(differenza.second, -half_extents.second, half_extents.second));
	// aggiunge i valori "clamped" al centro AABB e ottiene il valore del cubo più vicino al cerchio
	coordinate vicino = make_pair(aabb_centro.first + clamped.first, aabb_centro.second + clamped.second);
	// calcola il vettore tra il centro del cerchio ed il punto AABB più vicino
	differenza = make_pair(vicino.first - centro.first, vicino.second - centro.second);

	// verifica se lunghezza = sqrt(diff.x^2 + diff.y^2) <= raggio calcolando
	if (sqrt(differenza.first * differenza.first + differenza.second * differenza.second) < getRaggio())
		return make_tuple(true, getDirezione(differenza), differenza);

	return make_tuple(false, SU, make_pair(0.0, 0.0));
}

direzione Palla::getDirezione(coordinate p) {
	vector<coordinate> compass = {
		{0.0f, 1.0f},	// SU
		{1.0f, 0.0f},	// DX
		{0.0f, -1.0f},	// GIU
		{-1.0f, 0.0f}	// SX
	};

	float max = 0.0;
	direzione ris = SU;

	for (unsigned short i = 0; i < 4; ++i) {
		float prod_scal = dot(normalizza(p), compass[i]);
		if (prod_scal > max) {
			max = prod_scal;
			ris = (direzione) i;
		}
	}
	return ris;
}

bool Palla::collide(Mattone m) {
	// rilevamento collisione
	collisione c = collisioneAABB(&m);
	if (get<0>(c) == true) {
		// risoluzione collisione
		direzione dir = get<1>(c);
		coordinate diff = get<2>(c);
		if (dir == SX || dir == DX) { // collisione orizzontale
			setVelx(-getVelx());

			float penetrazione = getRaggio() - abs(diff.first);
			if (dir == SX)
				setPosx(getPosx() + penetrazione); // muove palla a destra
			else
				setPosx(getPosx() - penetrazione); // muove palla a sinistra
		}
		else { // collisione verticale
			setVely(-getVely());
			
			float penetrazione = getRaggio() - abs(diff.second);
			if (dir == SU)
				setPosy(getPosy() - penetrazione); // muove palla su
			else
				setPosy(getPosy() + penetrazione); // muove palla giu
		}
		return true;
	}
	return false;
}

bool Palla::collide(Pedana p) {
	collisione c = collisioneAABB(&p);
	if (get<0>(c) == true && !fermo) {
		float centro = p.getPosx() + p.getDimx() / 2 + 1;
		float distanza = (getPosx() + raggio) - centro;
		float percentuale = distanza / (p.getDimx() / 2);
		
		float forza = 2.0;
		setVelx(0.1 * percentuale * forza);
		setVely(-getVely());
		return true;
	}
	return false;
}

coordinate Palla::muove(int bordosx, int bordodx, int bordosu) {
	if (!fermo) {
		// muove la palla
		setPosx(getPosx() + getVelx());
		setPosy(getPosy() + getVely());

		// verifica collisione con i bordi
		if (getPosx() <= bordosx) {
			setVelx(-getVelx());
			setPosx(bordosx);
		}
		else if (getPosx() + getDimx() >= bordodx) {
			setVelx(-getVelx());
			setPosx(bordodx - getDimx());
		}
		if (getPosy() >= bordosu) {
			setVely(-getVely());
			setPosy(bordosu);
		}
	}
	return getPosizione();
}

void Palla::reset(coordinate posizione, coordinate velocita) {
	setPosizione(posizione);
	setVelocita(velocita);
	fermo = true;
}