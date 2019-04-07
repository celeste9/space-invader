#include "Jauges.h"

Jauges::Jauges() {
	Jauges::pv = 500;
}

int Jauges::getPv() {
	return Jauges::pv;
}

void Jauges::setPv(int degats) {
	this->pv = degats;
}

void Jauges::reduirePv(int degats) {
	this->pv -= degats;
}
