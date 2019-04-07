#include "Scores.h"
#include <iostream>


Scores::Scores() {
	this->score = 0;
}

int Scores::getScore() {
	return this->score;
}

void Scores::setScore(int point) {
	this->score += point;
}

void Scores::degats(int point) {
	this->score -= point;
}


void Scores::aucunChangement() {
	this->score = score;
}
