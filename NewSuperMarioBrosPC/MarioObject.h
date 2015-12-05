#ifndef _MARIO_OBJECT_H
#define _MARIO_OBJECT_H

#include <string>
#include "object.h"
using namespace std;
class MarioState;//khai báo lớp MarioState,
class MarioAnimationFactory;//khai báo có lớp MarioAnimationFactory
class Mario :public Object{
	MarioState* mMarioState;
public:
	MarioAnimationFactory* mAnimationFactory;
	Mario(int x, int y, int width, int height, int vx, int vy, int vx_last, float aX, float aY, Animation* anim, CSprite* image, MarioState* state = NULL,MarioAnimationFactory* animFactory = NULL);
	static const string OBJECT_NAME;
	void onAPress();
	void onBPress();
	void onCollision(Object* object);
	void setState(MarioState* state);
	string getName() override;
	void setAnimationFactory(MarioAnimationFactory* animFactory);
};

#endif