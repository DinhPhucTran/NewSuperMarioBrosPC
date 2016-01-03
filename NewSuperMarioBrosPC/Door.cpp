#include "Door.h"
#include <string>

using namespace std;

const string Door::OBJECT_NAME = "door";
string Door::getName(){
	return OBJECT_NAME;
}

Door::Door(int x, int y, int width, int height, int OutX, int OutY)
: StaticObject(x, y, width, height){
	outX = OutX;
	outY = OutY;
}