#ifndef _LEAF_H
#define _LEAF_H
#include "StaticObject.h"
#include "animation.h"
#include <string>

class Leaf :public StaticObject
{
private:
public:
	static const string OBJECT_NAME;
	string getName();
	Leaf(int x, int y, int width, int height, CSprite *image);
	void render(int vpx, int vpy)override;
	void collision();
	~Leaf();
};

#endif