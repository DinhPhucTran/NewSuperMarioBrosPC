#ifndef _GOOMBA_FACTORY_
#define _GOOMBA_FACTORY_
#include "StaticObject.h"
#include "Timer.h"

class Gooba;
class Mario;
class BrickGround;
class GoobaFactory :public StaticObject{
	Timer mProductionTime;
	int mDirection;
	Mario* mMario;
	BrickGround* mGround;
public:
	static const string OBJECT_NAME;
	string getName()override;
	static const int PRODUCTION_TIME;
	static const int WIDTH;
	static const int HEIGHT;
	static const int DIRECTION_LEFT;
	static const int DIRECTION_RIGHT;
	GoobaFactory(int x, int y, int direction, CSprite* pipe=0);
	void update(int t)override;
	Gooba* produceGooba();
	void die()override;
};


#endif