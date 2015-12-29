#ifndef _KOOPA_TROOPA_H
#define _KOOPA_TROOPA_H

#include "object.h"
#include <string>
class AnimationFactory;



using namespace std;

class KoopaTroopa;
class KoopaAnimationFactory;
class KoopaTroopaState;



class KoopaTroopa : public Object{
protected:
	KoopaTroopaState* mState;
public:
	int isBringedByMario;
	static const float PARA_FLYING_GRAVITY;
	static const float PARA_MAX_SPEED_Y;//0.6 MARIO 0.7
	static const float PARA_SPEED_X;
	static const float PARA_ACCELERATION_Y;
	static const int KOOPA_WIDTH;
	static const int KOOPA_HEIGHT;
	static const int KOOPA_VULNERABLE_HEIGHT;
	static const int NORMAL_ANIMATION_DELAY;
	static const int SLIDING_ANIMATION_DELAY;
	static float const KOOPA_VELOCITY_X;
	static float const KOOPA_SLIDING_SPEED_X;
	static float const KOOPA_VULNERABLE_SPEED_X; //= 0;
	static const int WAKE_UP_FROM_VULNERABLE_TIME;//10,000 ms
	AnimationFactory* mAnimationFactory;
	static const string OBJECT_NAME;
	string getName();
	KoopaTroopaState* getState();
	void setState(KoopaTroopaState* state);
	void setAnimationFactory(AnimationFactory* animFactory);
	virtual void onCollision(Object* ob,int dir)override;
	void render(int vpx,int vpy)override;
	KoopaTroopa(int x, int y, int width, int height, float vx, float vy, float vx_last, float ax, float ay, Animation* anim, CSprite * image);
	KoopaTroopa(int x, int y, float vx,  Animation* anim, CSprite * image);
	void update(int t)override;
};

#endif