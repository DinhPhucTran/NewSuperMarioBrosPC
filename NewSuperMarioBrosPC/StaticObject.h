#ifndef _STATIC_OBJECT_H_
#define _STATIC_OBJECT_H_
#include "object.h"
#include <string>
using namespace std;

class StaticObject :public Object{
public:
	static const string OBJECT_NAME;
	StaticObject(int x, int y, int width, int height, Animation* anim, CSprite * image);
	StaticObject(int x, int y, int width, int height);
	StaticObject(int x, int y, int width, int height, CSprite * image);
	virtual void update(int t)override;
	virtual string getName()override;
	virtual int isStaticObject()override;
};

#endif