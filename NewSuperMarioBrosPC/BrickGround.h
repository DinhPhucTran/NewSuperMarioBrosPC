#ifndef ___BRICK_GROUND_H___
#define ___BRICK_GROUND_H___

#include "object.h"

#include <string>
using namespace std;
class BrickGround :public Object
{
private:

public:
	static const string OBJECT_NAME;
	BrickGround(int x, int y, int width, int height, Animation* anim, CSprite* sprite);
	virtual string getName()override;
	virtual void onCollision(Object *ob,int dir)override;
};

#endif