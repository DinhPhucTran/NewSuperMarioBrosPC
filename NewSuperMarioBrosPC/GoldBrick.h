#ifndef _GOLD_BRICK_H
#define _GOLD_BRICK_H
#include "StaticObject.h"
#include "animation.h"
#include <string>

class GoldBrick;
class PButton :public StaticObject{
private:

public:
	int isPressed = 0;
	
	static const string OBJECT_NAME;
	string getName()override;
	Animation* mNormalButtonAnimation = new Animation(5, 5);
	Animation* mPressedButtonAnimation = new Animation(6, 6);
	PButton(int pX, int pY, CSprite* pButtonSprite);
	void swithGoldBrickToCoin();
	void render(int vpx, int vpy)override;
	void onCollision(Object* ob, int dir)override;
};

class GoldBrick :public StaticObject
{
private:
	Animation* createAnimation();
	string mState;
	int yLast;
	int mIsContainPButton;
	int mIsStatic = 0;
public:
	static const string NORMAL_STATE;
	Animation* mAnimation = new Animation(0, 4);
	Animation* mStaticBrickAnimation = new Animation(7, 7);
	void setState(string QbrickState);
	string getState();
	static const string OBJECT_NAME;
	string getName();
	GoldBrick(int x, int y, int width, int height, Animation* anim, CSprite * image, int isContainPButton = 0);
	void render(int vpx, int vpy)override;
	void switchToCoin();
	void onCollision(Object* ob, int dir)override;
	void revealPButton();
	~GoldBrick();
};

#endif