﻿#ifndef _MARIO_OBJECT_H
#define _MARIO_OBJECT_H

#include <string>
#include "object.h"
#include "Timer.h"
using namespace std;
class MarioState;//khai báo lớp MarioState,
class AnimationFactory;//khai báo có lớp MarioAnimationFactory
class MarioPowerBar;
class Mario :public Object{
	MarioState* mMarioState;
	MarioPowerBar* mPowerBar;
public:
	MarioState* getState();
	int isLeftButtonPressed;
	int isRightButtonPressed;
	int isAButtonPressed=0;
	int isBButtonPressed=0;
	int isFlying;
	Timer isKickKoopa;
	int isSitDown = 0;
	int isGoingDown = 0;
	int canSitDown = 1;
	int score;
	int lives;
	DWORD timeToDie;
	static const float FLYING_Y_SPEED;
	static const float FLYING_X_SPEED;
	static const float ACCELERATION_X;
	static const float ACCELERATION_Y;
	static const float ACCELERATION_Y_PLUS;
	static const float MAX_SPEED_X;
	static const float POWER_SPEED_X_PLUS;
	static const float MAX_SPEED_Y;
	static const float POWER_JUMP_UP_SPEED;
	static const int INVINCIBLE_SWITCH_STATE_TIME;//1000 ms
	static const int SITDOWN_WIDTH;
	static const int SITDOWN_HEIGHT;


	AnimationFactory* mAnimationFactory;
	Mario(int x, int y, int width, int height, int vx, int vy, int vx_last, float aX, float aY, Animation* anim, CSprite* image, MarioState* state = NULL,AnimationFactory* animFactory = NULL);
	~Mario();
	static const string OBJECT_NAME;
	void onAPress();
	void onBPress();
	void onCollision(Object* object, int dir)override;
	void setState(MarioState* state);
	string getName() override;
	void setAnimationFactory(AnimationFactory* animFactory);
	void render(int vpx,int vpy)override;
	void update(int t)override;
	void jumpUp();
	void powerJumpUp();
	void sitDown();
	void standUp();
	void stop();
	void die()override;
	MarioPowerBar* getPowerBar();
};

#endif