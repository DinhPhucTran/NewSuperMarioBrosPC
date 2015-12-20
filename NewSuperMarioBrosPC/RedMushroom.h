#ifndef ___RED_MUSHROOM_H___
#define ___RED_MUSHROOM_H___
#include "StaticObject.h"
#include "animation.h"
#include <string>

class RedMushroom :public StaticObject
{
private:
public:
	static const string OBJECT_NAME;
	string getName();
	RedMushroom(int x, int y, int width, int height, CSprite *image);
	void render(int vpx, int vpy)override;
	void collision();
	~RedMushroom();
};

#endif