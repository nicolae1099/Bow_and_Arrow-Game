#include <iostream>

#include <Core/Engine.h>

using namespace std;

class Arrow {
public:
	Arrow();
	Arrow(int posX, int posY);
	~Arrow();

	int posX;
	int posY;
};