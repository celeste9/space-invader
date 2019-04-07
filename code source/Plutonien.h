#ifndef PLUTONIEN_H
#define PLUTONIEN_H
#include "ExtraTerrestre.h"
class Plutonien : public ExtraTerrestre {
	bool jiggle;

public:
	Plutonien(int, int);
	void jigglePlutonien();
};
#endif