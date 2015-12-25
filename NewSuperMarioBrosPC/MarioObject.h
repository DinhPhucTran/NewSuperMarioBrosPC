#ifndef _MARIO_OBJECT_H
#define _MARIO_OBJECT_H

#include <string>
#include "object.h"
using namespace std;
class MarioState;//khai báo lớp MarioState,
class AnimationFactory;//khai báo có lớp MarioAnimationFactory
class Mario :public Object{
	MarioState* mMarioState;

public:
	MarioState* getState();
	int isLeftButtonPressed;
	int isRightButtonPressed;
	int isAButtonPressed;
	int isBButtonPressed=0;
	int isFlying;
	static const float FLYING_Y_SPEED;
	static const float FLYING_X_SPEED;
	static const float ACCELERATION_X;
	static const float ACCELERATION_Y;
	static const float ACCELERATION_Y_PLUS;
	static const float MAX_SPEED_X;
	
	static const float MAX_SPEED_Y;
	static const int INVINCIBLE_SWITCH_STATE_TIME;//1000 ms


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
	void jumpUp();
	void powerJumpUp();
	void stop();
	void die()override;
};

#endif