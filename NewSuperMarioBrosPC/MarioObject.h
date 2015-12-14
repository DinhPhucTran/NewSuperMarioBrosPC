﻿#ifndef _MARIO_OBJECT_H
#define _MARIO_OBJECT_H

#include <string>
#include "object.h"
using namespace std;
class MarioState;//khai báo lớp MarioState,
class AnimationFactory;//khai báo có lớp MarioAnimationFactory
class Mario :public Object{
	MarioState* mMarioState;

public:
	int isLeftButtonPress;
	int isRightButtonPress;
	static const float ACCELERATION_X;
	static const float ACCELERATION_Y;
	static const float MAX_SPEED_X;
	static const float MAX_SPEED_Y;


	AnimationFactory* mAnimationFactory;
	Mario(int x, int y, int width, int height, int vx, int vy, int vx_last, float aX, float aY, Animation* anim, CSprite* image, MarioState* state = NULL,AnimationFactory* animFactory = NULL);
	static const string OBJECT_NAME;
	void onAPress();
	void onBPress();
	void onCollision(Object* object, int dir)override;
	void setState(MarioState* state);
	string getName() override;
	void setAnimationFactory(AnimationFactory* animFactory);
	void render(int vpx,int vpy)override;
	void update(int t)override;
};

#endif