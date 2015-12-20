#ifndef ___GREEN_MUSHROOM_H___
#define ___GREEN_MUSHROOM_H___
#include "StaticObject.h"
#include "animation.h"
#include <string>

class GreenMushroom :public StaticObject
{
private:
public:
	static const string OBJECT_NAME;
	string getName();
	GreenMushroom(int x, int y, int width, int height, CSprite *image);
	void render(int vpx, int vpy)override;
	void collision();
	~GreenMushroom();
};

#endif