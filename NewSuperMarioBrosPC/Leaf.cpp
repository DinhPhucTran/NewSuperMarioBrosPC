#include "Leaf.h"
#include "BrickGround.h"
#include "Pipe.h"
#include "MetalBlock.h"
#include "Qbrick.h"
const string Leaf::OBJECT_NAME = "leaf";
const float Leaf::SPEED_Y = -0.0005f;
const int Leaf::WIDTH = 16;
const int Leaf::HEIGHT = 16;

Leaf::Leaf(int X, int Y, int Width, int Height, float vx, float vy, float vx_last, float ax, float ay, CSprite * Sprite) :
	Object(X, Y, Width, Height, vx, vy, vx_last, ax, ay, Sprite)
{
	mAnim = new Animation(0, 0);
	vy = SPEED_Y;
	vx = -0.002f;
}
Leaf::Leaf(int X, int Y, CSprite * Sprite) :
Object(X, Y, WIDTH, HEIGHT, 0, 0, 0, 0, 0, Sprite)
{
	mAnim = new Animation(0, 0);
}

void Leaf::update(int t){
	
	vy += ay*t;
	vx += ax*t;
	if (vy > 0.0008f || vy < -0.0008f){
		ay = 0;
	}
	if (vx > 0.35f || vx < -0.35f){
		ax = -ax;
	}
	if (ax > 0){
		ax = 0.005;
	}
	else{
		ax = -0.005;
	}
	ay -= 0.0007f;
	

	dx += (int)(vx * t);
	int temp = (int)dx;
	x += temp;
	dx -= temp;

	dy += (int)(vy*t);
	temp = (int)dy;
	y += temp;
	dy -= temp;
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
	if (objectName == BrickGround::OBJECT_NAME || objectName == Pipe::OBJECT_NAME )
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
