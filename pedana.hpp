#ifndef _PEDANA
#define _PEDANA

#include "oggetto.hpp"

class Pedana : public Oggetto {
public:
	Pedana();
	Pedana(float, float);

	bool getMuovesx();
	bool getMuovedx();
	void setMuovesx(bool);
	void setMuovedx(bool);

	void render();
	void renderVita();

private:
	bool muovesx, muovedx;
	static GLuint texture;
};

#endif