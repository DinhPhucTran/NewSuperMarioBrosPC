#include "Mushroom.h"

const string RedMushroom::OBJECT_NAME = "redmushroom";
const int RedMushroom::WIDTH = 16;
const int RedMushroom::HEIGHT = 16;

RedMushroom::RedMushroom(int X, int Y, int Width, int Height, int vx, int vy, int vx_last, int ax, int ay, CSprite * Sprite) :
	Object(X, Y, Width, Height, vx, vy, vx_last, ax, ay, Sprite)
{
	mAnim = new Animation(0, 0);
}

string RedMushroom::getName()
{
	return OBJECT_NAME;
}

void RedMushroom::onCollision(Object * ob, int dir)
{
	string objectName = ob->getName();
	if (objectName == BrickGround::OBJECT_NAME || objectName == Pipe::OBJECT_NAME || objectName == QBrick::OBJECT_NAME)
	{
		if (dir == Physics::COLLIDED_FROM_BOTTOM)
		{
			vy = 0;
			ay = 0;
			y = ob->top() + height / 2;
			return;
		}
		if (dir == Physics::COLLIDED_FROM_RIGHT)
		{
			x = ob->left() - width / 2;
			vx = -vx;
			return;
		}
		if (dir == Physics::COLLIDED_FROM_LEFT)
		{
			x = ob->right() + width / 2;
			vx = -vx;
			return;
		}
	}
	if (objectName == MetalBlock::OBJECT_NAME)
	{
		if (dir == Physics::COLLIDED_FROM_BOTTOM && bottom() + 8 >= ob->top())
		{
			vy = 0;
			ay = 0;
			y = ob->top() + height / 2;
			return;
		}
	}
	

	if (objectName == Mario::OBJECT_NAME)
	{
		die();
	}
}

const string GreenMushroom::OBJECT_NAME = "greenmushroom";
const int GreenMushroom::WIDTH = 16;
const int GreenMushroom::HEIGHT = 16;
GreenMushroom::GreenMushroom(int X, int Y, int Width, int Height, int vx, int vy, int vx_last, int ax, int ay, CSprite * Sprite) :
	RedMushroom(X, Y, Width, Height, vx, vy, vx_last, ax, ay, Sprite)
{
	mAnim = new Animation(0, 0);
}
string GreenMushroom::getName(){
	return OBJECT_NAME;
}