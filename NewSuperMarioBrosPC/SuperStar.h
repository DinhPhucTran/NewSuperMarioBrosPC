#ifndef _SUPER_START_
#define _SUPER_START_
#include "object.h"
#include "sprite.h"
#include "Physics.h"
#include "MarioObject.h"
#include "animation.h"

class SuperStar :public Object
{
public:
	static const string OBJECT_NAME;
	static const int HEIGHT;
	static const int WIDTH;
	static const float SPEED_Y;
	SuperStar(int X, int Y, int Width, int Height, float vx, float vy, float vx_last, float ax, float ay, CSprite * Sprite);
	SuperStar(int X, int Y, CSprite * Sprite);
	string getName()override;
	void onCollision(Object * ob, int dir);
	void update(int t);
};

#endif