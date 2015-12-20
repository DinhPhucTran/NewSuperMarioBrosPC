#ifndef _COIN_H
#define _COIN_H
#include "StaticObject.h"
#include "animation.h"
#include <string>

class Coin :public StaticObject
{
private:
	Animation* createAnimation();
	string mState;
public:
	Animation* mCoinAnimation = new Animation(0, 2);
	static const string OBJECT_NAME;
	string getName();
	Coin(int x, int y, int width, int height, Animation* anim, CSprite * image);
	void render(int vpx, int vpy)override;
	void collision();
	~Coin();
};

#endif