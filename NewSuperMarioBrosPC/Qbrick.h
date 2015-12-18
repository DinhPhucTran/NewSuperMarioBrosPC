#ifndef _Q_BRICK_H
#define _Q_BRICK_H
#include "object.h"
#include "animation.h"
#include <string>

class QBrick :public Object
{
public:
	Animation *anim;
	static const string OBJECT_NAME;
	string getName();
	void onCollision(Object* ob, int dir)override;
	QBrick(int x, int y, int width, int height, float vx, float vy, float vx_last, float ax, float ay, Animation* anim, CSprite * image);
	void update(int t);
};

#endif