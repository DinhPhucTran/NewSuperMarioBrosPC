#ifndef _LEAF_H
#define _LEAF_H
#include "object.h"
#include "sprite.h"
#include "Physics.h"
#include "MarioObject.h"
#include "animation.h"

class Leaf :public Object
{
public:
	static const string OBJECT_NAME;
	static const int HEIGHT;
	static const int WIDTH;
	Leaf(int X, int Y, int Width, int Height, int vx, int vy, int vx_last, int ax, int ay, CSprite * Sprite);
	string getName()override;
	void onCollision(Object * ob, int dir);
};

#endif