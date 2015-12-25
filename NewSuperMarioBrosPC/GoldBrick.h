#ifndef _GOLD_BRICK_H
#define _GOLD_BRICK_H
#include "StaticObject.h"
#include "animation.h"
#include <string>

class GoldBrick :public StaticObject
{
private:
	Animation* createAnimation();
	string mState;
	int yLast;
public:
	static const string NORMAL_STATE;
	Animation* mAnimation = new Animation(0, 4);
	void setState(string QbrickState);
	string getState();
	static const string OBJECT_NAME;
	string getName();
	GoldBrick(int x, int y, int width, int height, Animation* anim, CSprite * image);
	void render(int vpx, int vpy)override;
	~GoldBrick();
};

#endif