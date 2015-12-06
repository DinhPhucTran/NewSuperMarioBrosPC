#ifndef ___BRICK_H___
#define ___BRICK_H___

#include "object.h"
#include <string>
using namespace std;
class Brick :public Object
{
private:

public:
	static const string OBJECT_NAME;
	Brick(int x, int y, int width, int height, Animation* anim, CSprite* sprite);
	virtual string getName()override;
	virtual void onCollision(Object *ob)override;
};

#endif