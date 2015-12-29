#include "Pipe.h"
#include <string>

using namespace std;

const string Pipe::OBJECT_NAME = "pipe";
string Pipe::getName(){
	return OBJECT_NAME;
}

Pipe::Pipe(int x, int y, int width, int height)
: StaticObject(x, y, width, height){}

