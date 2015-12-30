#ifndef _RED_FIRE_PIRANHA_
#define _RED_FIRE_PIRANHA_

#include"FirePiranha.h"

class RedFirePiranha :public FirePiranha{
public:
	static const int WIDTH;
	static const int HEIGHT;
	RedFirePiranha(int x, int y, CSprite* image, CSprite* pipe);
	virtual int getHeight()override;
	virtual int getWidth()override;
};

#endif