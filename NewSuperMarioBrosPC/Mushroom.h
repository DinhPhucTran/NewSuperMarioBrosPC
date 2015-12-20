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

class Mushroom :public Object
{
public:
	static const string OBJECT_NAME;
	Mushroom(int X, int Y, int Width, int Height, int vx, int vy, int vx_last, int ax, int ay, CSprite * Sprite);
	string getName();
	void onCollision(Object * ob, int dir);
};
#endif