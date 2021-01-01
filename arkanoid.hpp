#ifndef _ARKANOID
#define _ARKANOID

#include "wrapper.hpp"

#include "glutAPI.hpp"

#include "livello1.hpp"
#include "livello2.hpp"
#include "livello3.hpp"
#include "livello4.hpp"
#include "livello5.hpp"
#include "livello6.hpp"
#include "palla.hpp"
#include "pedana.hpp"
#include "punteggi.hpp"
#include "menu.hpp"

class Arkanoid : public glutAPI::GlutAPI {
public:
	Arkanoid();
	Arkanoid(bool);

	void render();

private:
	vector<Livello *> livelli;
	Palla palla;
	Pedana pedana;

	int x, y, z;
	bool cam3D, pausa;

	Livello* livello;
	unsigned short vite, i_livello;
	unsigned int punteggio, cont_vite_punteggio;
	vector<Pedana> viteHUD;
	Punteggi topPunteggi;

	static GLuint sfondo, bordo_v, bordo_o;
	
	const int BORDOSX = -24;
	const int BORDODX = 24;
	const int BORDOSU = 18;
	const int BORDOGIU = -18;

	void renderHUD();
	void cambiaCamera();

	void renderScene();
	void display() override;
	void reshape(int, int) override;
	void keyboard(unsigned char, int, int) override;
	void specialKeyboardDown(int, int, int) override;
	void specialKeyboardUp(int, int, int) override;
};

#endif