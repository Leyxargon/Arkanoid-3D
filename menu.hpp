#ifndef _MENU
#define _MENU

#include "glutAPI.hpp"

#include "arkanoid.hpp"
#include "punteggi.hpp"

class Menu : public glutAPI::GlutAPI {
public:
	Menu();
	Menu(unsigned int);

	void render();

private:
	enum schermata {
		MAIN,
		SETTINGS,
		SCORES,
		GAMEOVER
	} scena;
	vector<GLuint> scene;
	GLuint *img;
	Punteggi punteggi;

	bool cam3D;

	unsigned int punteggio;
	string input;

	void visualizzaPunteggi();
	void immettiNomeGiocatore();
	bool tastoPremuto(int, int, int, int, int, int);

	void display() override;
	void reshape(int, int) override;
	void mousePress(int, int, int, int) override;
	void mouseMotion(int, int) override;
	void mousePassiveMotion(int, int) override;
	void keyboard(unsigned char, int, int) override;
};

#endif 