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

	
	static SmallMarioAnimationFactory* getInstance(Mario* mario =NULL);
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
	static LargeMarioAnimationFactory* getInstance(Mario* mario=NULL);
	Animation *rightWalkAnim = new Animation(15, 17);
	Animation *leftWalkAnim = new Animation(11, 13);
	Animation *rightStandAnim = new Animation(15, 15);
	Animation *leftStandAnim = new Animation(11, 11);
	Animation *leftJumpUpAnim = new Animation(18, 18);
	Animation *rightJumpUpAnim = new Animation(19, 19);
	Animation *leftJumpDownAnim = new Animation(14, 14);
	Animation *rightJumpDownAnim = new Animation(17, 17);
	Animation *turnRightAnimation = new Animation(14, 14);
	Animation *turnLeftAnimation = new Animation(10, 10);


	Animation* createAnimation()override;
	~LargeMarioAnimationFactory();
};

class RaccoonMarioAnimationFactory :public AnimationFactory{
private:
	Mario* mMario;
	RaccoonMarioAnimationFactory(Mario* mario);
	static RaccoonMarioAnimationFactory* sInstance;
public:
	static RaccoonMarioAnimationFactory* getInstance(Mario* mario = NULL);
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

	Animation* createAnimation()override;
	~RaccoonMarioAnimationFactory();
};

#endif