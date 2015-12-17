#ifndef ___BRICK_GROUND_H___
#define ___BRICK_GROUND_H___


#include <string>
#include "MarioObject.h"
#include "StaticObject.h"
using namespace std;
class BrickGround :public StaticObject
{
private:

public:
	static const string OBJECT_NAME;
	BrickGround(int x, int y, int width, int height, Animation* anim, CSprite* sprite);
	BrickGround(int x, int y, int width, int height);
	virtual string getName()override;
	virtual void onCollision(Object *ob,int dir)override;
};

#endif