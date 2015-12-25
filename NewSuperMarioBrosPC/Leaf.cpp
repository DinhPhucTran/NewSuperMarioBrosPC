#include "Leaf.h"

const string Leaf::OBJECT_NAME = "leaf";
const int Leaf::WIDTH = 16;
const int Leaf::HEIGHT = 16;

Leaf::Leaf(int X, int Y, int Width, int Height, int vx, int vy, int vx_last, int ax, int ay, CSprite * Sprite) :
Object(X, Y, Width, Height, vx, vy, vx_last, ax, ay, Sprite)
{
	mAnim = new Animation(0, 0);
}

string Leaf::getName()
{
	return OBJECT_NAME;
}

void Leaf::onCollision(Object * ob, int dir)
{
	string objectName = ob->getName();
	if (objectName == Mario::OBJECT_NAME)
	{
		die();
	}
}
