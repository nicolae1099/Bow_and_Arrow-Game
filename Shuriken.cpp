#include "Shuriken.h"

Shuriken::Shuriken(int posX, int posY) {
	this->posX = posX;
	this->posY = posY;
	this->scaleX = 1;
	this->scaleY = 1;
	this->dead = false;
}

Shuriken::~Shuriken() {

}