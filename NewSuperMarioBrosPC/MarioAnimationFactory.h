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

	Animation *rightWalkAnim = new Animation(14, 16);
	Animation *leftWalkAnim = new Animation(1, 3);
	Animation *rightStandAnim = new Animation(17, 17);
	Animation *leftStandAnim = new Animation(0, 0);
	Animation *leftJumpAnim = new Animation(4, 4);
	Animation *rightJumpAnim = new Animation(13, 13);
	
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
	Animation *rightWalkAnim = new Animation(8, 13);
	//Animation *leftWalkAnim = new Animation(1, 5);
	Animation *leftWalkAnim = new Animation(60, 65);
	Animation *rightStandAnim = new Animation(8, 8);
	Animation *leftStandAnim = new Animation(6, 6);
	Animation *leftJumpAnim = new Animation(15, 21);
	Animation *rightJumpAnim = new Animation(23, 29);


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
	Animation *rightWalkAnim = new Animation(99, 103);
	Animation *leftWalkAnim = new Animation(91, 95);
	Animation *rightStandAnim = new Animation(98, 98);
	Animation *leftStandAnim = new Animation(96, 96);
	Animation *leftJumpAnim = new Animation(122, 126);
	Animation *rightJumpAnim = new Animation(128, 132);
	Animation *leftJumpUpAnim = new Animation(136, 136);
	Animation *leftJumpDownAnim = new Animation(150, 150);
	Animation *rightJumpUpAnim = new Animation(148, 148);
	Animation *rightJumpDownAnim = new Animation(164, 164);

	Animation* createAnimation()override;
	~RaccoonMarioAnimationFactory();
};

#endif