#include <iostream>
#include <Core/Engine.h>

using namespace std;

class Shuriken
{
public:
	Shuriken(int posX, int posY);
	~Shuriken();

	int posX;
	int posY;
	float scaleX;
	float scaleY;
	bool killer;
	bool dead;

private:

};