#include "SuperStar.h"
#include "BrickGround.h"
#include "Pipe.h"
#include "MetalBlock.h"
#include "Qbrick.h"
const string SuperStar::OBJECT_NAME = "super_star";
const float SuperStar::SPEED_Y = -0.0005f;
const int SuperStar::WIDTH = 16;
const int SuperStar::HEIGHT = 16;

SuperStar::SuperStar(int X, int Y, int Width, int Height, float vx, float vy, float vx_last, float ax, float ay, CSprite * Sprite) :
Object(X, Y, Width, Height, vx, vy, vx_last, ax, ay, Sprite)
{
	mAnim = new Animation(0, 0);
	vy = SPEED_Y;
	vx = -0.002f;
}
SuperStar::SuperStar(int X, int Y, CSprite * Sprite) :
Object(X, Y, WIDTH, HEIGHT, 0, 0, 0, 0, 0, Sprite)
{
	mAnim = new Animation(0, 0);
}

void SuperStar::update(int t){

	vy += ay*t;
	vx += ax*t;
	if (vy > 0.001f || vy < -0.001f){
		ay = 0;
	}

	ay -= 0.0001f;
	

	dx += (int)(vx * t);
	int temp = (int)dx;
	x += temp;
	dx -= temp;

	dy += (int)(vy*t);
	temp = (int)dy;
	y += temp;
	dy -= temp;
}

string SuperStar::getName()
{
	return OBJECT_NAME;
}



void SuperStar::onCollision(Object * ob, int dir)
{
	string objectName = ob->getName();
	if (objectName == Mario::OBJECT_NAME)
	{
		die();
	}
	if (objectName == BrickGround::OBJECT_NAME || objectName == Pipe::OBJECT_NAME)
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



}
