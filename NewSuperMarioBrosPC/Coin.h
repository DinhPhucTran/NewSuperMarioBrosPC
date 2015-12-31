#ifndef _COIN_H
#define _COIN_H
#include "StaticObject.h"
#include "sprite.h"
#include "Physics.h"
#include "MarioObject.h"
#include "animation.h"

class Coin :public StaticObject
{
private:
	Animation* createAnimation();
public:
	Animation* mCoinAnimation = new Animation(0, 2);
	void render(int vpx, int vpy)override;
	static const string OBJECT_NAME;
	Coin(int X, int Y, int Width, int Height, Animation* anim, CSprite * Sprite);
	Coin(int X, int Y, int Width, int Height, CSprite * Sprite);
	string getName();
	void onCollision(Object * ob, int dir);
};
#endif