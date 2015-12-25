#ifndef _MUSHROOM_H
#define _MUSHROOM_H
#include "object.h"
#include "MetalBlock.h"
#include "BrickGround.h"
#include "Pipe.h"
#include "Qbrick.h"
#include "sprite.h"
#include "Physics.h"
#include "MarioObject.h"
#include "animation.h"

class RedMushroom :public Object
{
public:
	static const int WIDTH;
	static const int HEIGHT;
	static const string OBJECT_NAME;
	RedMushroom(int X, int Y, int Width, int Height, int vx, int vy, int vx_last, int ax, int ay, CSprite * Sprite);
	string getName()override;
	void onCollision(Object * ob, int dir);
};

class GreenMushroom :public RedMushroom
{
public:
	static const int WIDTH;
	static const int HEIGHT;
	static const string OBJECT_NAME;
	GreenMushroom(int X, int Y, int Width, int Height, int vx, int vy, int vx_last, int ax, int ay, CSprite * Sprite);
	string getName()override;
};
#endif