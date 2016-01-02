#ifndef _COIN_H
#define _COIN_H
#include "StaticObject.h"
#include "sprite.h"
#include "Physics.h"
#include "MarioObject.h"
#include "animation.h"
#include "MarioGame.h"

class Coin :public Object
{
private:
	Animation* createAnimation();
	int initY;
public:
	Animation* mCoinAnimation = new Animation(1, 3);
	void render(int vpx, int vpy)override;
	static const string OBJECT_NAME;
	Coin(int X, int Y, int Width, int Height, float vx, float vy, float vx_last, float ax, float ay, CSprite * Sprite);
	Coin(int X, int Y, int Width, int Height, CSprite * Sprite);
	Coin();
	string getName();
	void onCollision(Object * ob, int dir);
};

class CoinScore :public Object
{
private:
	int initY;
public:
	Animation* mAnim = new Animation(7,7);
	CoinScore(int X, int Y, int Width, int Height, CSprite * Sprite);
	void onCollision(Object * ob, int dir);
	void render(int vpx, int vpy);
};

class StaticCoin :public StaticObject
{
private:
	Animation* createAnimation();
public:
	Animation* mCoinAnimation = new Animation(1, 3);
	void render(int vpx, int vpy)override;
	static const string OBJECT_NAME;
	StaticCoin(int X, int Y, int Width, int Height, Animation* anim, CSprite * Sprite);
	StaticCoin(int X, int Y, int Width, int Height, CSprite * Sprite);
	void switchToGoldBrick();
	string getName();
	void onCollision(Object * ob, int dir);
};

#endif