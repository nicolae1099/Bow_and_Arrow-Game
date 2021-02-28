#include "Ballon.h"


Ballon::Ballon(int posX, int posY, bool isColorRed)
{
	this->posX = posX;
	this->posY = posY;
	this->scaleX = 1;
	this->scaleY = 1.3f;
	this->spart = false;
	this->isColorRed = isColorRed;
	this->radius = 35;


}

Ballon::~Ballon()
{
}
