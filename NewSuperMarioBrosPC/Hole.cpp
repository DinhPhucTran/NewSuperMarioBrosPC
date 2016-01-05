#include"Hole.h"
#include <string>


const string Hole::OBJECT_NAME = "hole";
string Hole::getName(){
	return OBJECT_NAME;
}

Hole::Hole(int x, int y, int width, int height)
: StaticObject(x, y, width, height){}