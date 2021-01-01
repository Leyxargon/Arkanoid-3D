#ifndef _LIVELLO4
#define _LIVELLO4

#include "livello.hpp"

class Livello4 : public Livello {
public:
	Livello4();

	void render() override;

private:
	unsigned short contatore, tot;
};

#endif