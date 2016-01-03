#include "DoorPipe.h"

DoorPipe::DoorPipe(int X, int Y, int Width, int Height, int Dir, CSprite * sprite, int OutX, int OutY) :Object(X, Y, Width, Height, 0, 0, 0, 0, 0, sprite)
{
	dir = Dir;
	if (dir == 1)
		anim = new Animation(0, 0);
	else if (dir == -1)
		anim = new Animation(2, 2);
	else if (dir == 2)
		anim = new Animation(1, 1);
	else
		anim = new Animation(3, 3);
	outX = OutX;
	outY = OutY;
}

const string DoorPipe::OBJECT_NAME = "door_pipe";
string DoorPipe::getName(){
	return OBJECT_NAME;
}

void DoorPipe::update(int t)
{

}

void DoorPipe::render(int vpx, int vpy)
{
	mSprite->Render(anim, x, y, vpx, vpy);
}