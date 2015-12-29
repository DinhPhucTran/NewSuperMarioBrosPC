#ifndef _FIRE_PIRANHA_ANIMATION_FACTORY_
#define _FIRE_PIRANHA_ANIMATION_FACTORY_

class Mario;
class FirePiranha;
#include "AnimationFactory.h"
class FirePiranhaAnimationFactory : public AnimationFactory{
	FirePiranha* mPiranha;
	Mario* mMario;
public:
	FirePiranhaAnimationFactory(FirePiranha* piranha, Mario* mario=0);
	Animation* mLeftUpAnim = new Animation(10, 11);
	Animation* mLeftDownAnim = new Animation(12, 13);
	Animation* mRightUpAnim = new Animation(16, 17);
	Animation* mRightDownAnim = new Animation(14, 15);
	Animation* mShootingLeftUp = new Animation(10, 10);
	Animation* mShootingLeftDown = new Animation(12, 12);
	Animation* mShootingRightUp = new Animation(16, 16);
	Animation* mShootingRightDown = new Animation(14, 14);
	Animation* createAnimation()override;
};

class RedFirePiranhaAnimationFactory : public AnimationFactory{
	FirePiranha* mPiranha;
	Mario* mMario;
public:
	RedFirePiranhaAnimationFactory(FirePiranha* piranha, Mario* mario = 0);
	Animation* mLeftUpAnim = new Animation(2, 3);
	Animation* mLeftDownAnim = new Animation(0, 1);
	Animation* mRightUpAnim = new Animation(4, 5);
	Animation* mRightDownAnim = new Animation(6, 7);
	Animation* mShootingLeftUp = new Animation(2, 2);
	Animation* mShootingLeftDown = new Animation(0, 0);
	Animation* mShootingRightUp = new Animation(4, 4);
	Animation* mShootingRightDown = new Animation(6, 6);
	Animation* createAnimation()override;
};


#endif