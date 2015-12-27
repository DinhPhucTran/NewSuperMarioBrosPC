#ifndef __MARIO_ANIMATION_FACTORY_H__
#define __MARIO_ANIMATION_FACTORY_H__

#include "AnimationFactory.h"

#include"MarioObject.h"
#include <string>
using namespace std;


class SmallMarioAnimationFactory :public AnimationFactory{
private:
	Mario* mMario;
	SmallMarioAnimationFactory(Mario* mario);

	static SmallMarioAnimationFactory* sInstance;
public:

	//Animation *rightWalkAnim = new Animation(0, 1);
	//Animation *leftWalkAnim = new Animation(9, 10);
	//Animation *rightStandAnim = new Animation(0, 0);
	//Animation *leftStandAnim = new Animation(9, 9);
	//Animation *leftJumpUpAnim = new Animation(13, 13);
	//Animation *rightJumpUpAnim = new Animation(4, 4);
	//Animation *leftJumpDownAnim = new Animation(13, 13);
	//Animation *rightJumpDownAnim = new Animation(4, 4);
	//Animation *turnRightAnimation = new Animation(22, 22);
	//Animation *turnLeftAnimation = new Animation(31, 31);
	//animation for file smallMario.png

	Animation *rightWalkAnim = new Animation(4, 5);
	Animation *leftWalkAnim = new Animation(2, 3);
	Animation *rightStandAnim = new Animation(4, 4);
	Animation *leftStandAnim = new Animation(2, 2);
	Animation *leftJumpUpAnim = new Animation(6, 6);
	Animation *rightJumpUpAnim = new Animation(7, 7);
	Animation *leftJumpDownAnim = new Animation(6, 6);
	Animation *rightJumpDownAnim = new Animation(7, 7);
	Animation *turnRightAnimation = new Animation(1, 1);
	Animation *turnLeftAnimation = new Animation(0, 0);

	Animation *powerJumpLeft = new Animation(9, 9);
	Animation *powerJumpRight = new Animation(8, 8);
	
	static SmallMarioAnimationFactory* getInstance(Mario* mario);
	//contructor
	
	Animation* createAnimation()override;
	~SmallMarioAnimationFactory();
};

class LargeMarioAnimationFactory :public AnimationFactory{
private:
	Mario* mMario;
	LargeMarioAnimationFactory(Mario* mario);
	static LargeMarioAnimationFactory* sInstance;
public:
	static LargeMarioAnimationFactory* getInstance(Mario* mario);
	Animation *rightWalkAnim = new Animation(15, 17);
	Animation *leftWalkAnim = new Animation(11, 13);
	Animation *rightStandAnim = new Animation(15, 15);
	Animation *leftStandAnim = new Animation(11, 11);
	Animation *leftJumpUpAnim = new Animation(18, 18);
	Animation *rightJumpUpAnim = new Animation(19, 19);
	Animation *leftJumpDownAnim = new Animation(13, 13);
	Animation *rightJumpDownAnim = new Animation(17, 17);
	Animation *turnRightAnimation = new Animation(14, 14);
	Animation *turnLeftAnimation = new Animation(10, 10);

	Animation *powerRunLeft = new Animation(63, 65, 2);
	Animation *powerRunRight = new Animation(60, 62, 2);
	Animation *powerJumpLeft = new Animation(49, 49);
	Animation *powerJumpRight = new Animation(34, 34);

	Animation* createAnimation()override;
	~LargeMarioAnimationFactory();
};

class RaccoonMarioAnimationFactory :public AnimationFactory{
private:
	Mario* mMario;
	RaccoonMarioAnimationFactory(Mario* mario);
	static RaccoonMarioAnimationFactory* sInstance;
public:
	static RaccoonMarioAnimationFactory* getInstance(Mario* mario);
	Animation *rightWalkAnim = new Animation(30, 32);
	Animation *leftWalkAnim = new Animation(25, 27);
	Animation *rightStandAnim = new Animation(30, 30);
	Animation *leftStandAnim = new Animation(27, 27);
	//Animation *leftJumpAnim = new Animation(122, 126);
	//Animation *rightJumpAnim = new Animation(128, 132);
	Animation *leftJumpUpAnim = new Animation(35, 35);
	Animation *leftJumpDownAnim = new Animation(25, 25);
	Animation *rightJumpUpAnim = new Animation(33, 33);
	Animation *rightJumpDownAnim = new Animation(32, 32);
	Animation *turnRightAnimation = new Animation(28, 28);
	Animation *turnLeftAnimation = new Animation(24, 24);

	Animation* RaccoonTailBack = new Animation(36, 36);
	Animation* RaccoonTailFront = new Animation(37, 37);
	Animation* RaccoonTailLeft = new Animation(38, 38);
	Animation* RaccoonTailRight = new Animation(39, 39);

	Animation* RaccoonFlyingLeft = new Animation(43, 45,3);
	Animation* RaccoonFlyingRight = new Animation(40, 42,3);
	
	Animation* RaccoonFlyingUpLeft = new Animation(46, 48, 3);
	Animation* RaccoonFlyingUpRight = new Animation(50, 52, 3);

	Animation* powerRunLeft = new Animation(56, 58,2);
	Animation* powerRunRight = new Animation(53, 55,2);

	Animation* createAnimation()override;
	~RaccoonMarioAnimationFactory();
};

class InvincibleMarioAnimationFactory : public AnimationFactory{
private:
	Mario* mMario;
	InvincibleMarioAnimationFactory(Mario* mario);
	static InvincibleMarioAnimationFactory* sInstance;
	bool isBlanked;
public:
	Animation* blankAnimation = new Animation(69, 69);
	Animation* createAnimation()override;
	static InvincibleMarioAnimationFactory* getInstance(Mario* mario);
};

#endif