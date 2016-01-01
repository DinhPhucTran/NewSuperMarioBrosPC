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
	static const float SPEED_Y;
	static const string OBJECT_NAME;
	static const int HEIGHT;
	static const int WIDTH;
	Leaf(int X, int Y, int Width, int Height, float vx, float vy, float vx_last, float ax, float ay, CSprite * Sprite);
	Leaf(int X, int Y, CSprite * Sprite);
	string getName()override;
	void onCollision(Object * ob, int dir);
	void update(int t)override;
};

#endif