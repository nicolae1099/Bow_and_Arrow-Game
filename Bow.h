#include <iostream>

#include <Core/Engine.h>

using namespace std;

class Bow {
public:
	Bow();
	Bow(int posX, int posY, int circle_posY);
	~Bow();

	int line_posX;
	int line_posY;
	int circle_posY;

};