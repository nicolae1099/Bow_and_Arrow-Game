#include <iostream>
#include <Core/Engine.h>

using namespace std;

class Ballon
{
public:
	Ballon();
	Ballon(int posX, int posY, bool isColorRed);
	~Ballon();

	int posX;
	int posY;
	bool spart;
	float scaleX;
	float scaleY;
	bool isColorRed;
	float radius;


private:

};