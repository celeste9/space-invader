#include "Plutonien.h"

Plutonien::Plutonien(int type, int valeur) :ExtraTerrestre(type, valeur)
{
	jiggle = true;
}

void Plutonien::jigglePlutonien()
{
	removeExtraTerrestre();

	if (jiggle)
		coord.setPositionX(coord.getPositionX() - 1);
	else
		coord.setPositionX(coord.getPositionX() + 1);

	jiggle = !jiggle;

	putExtraTerrestre();
}

