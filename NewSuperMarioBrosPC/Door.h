#ifndef _DOOR_H
#define _DOOR_H
#include "StaticObject.h"

class Door :public StaticObject
{
public:
	int outX, outY;
	static const string OBJECT_NAME;
	Door(int x, int y, int width, int height, int outX, int outY);
	virtual string getName()override;
};
#endif