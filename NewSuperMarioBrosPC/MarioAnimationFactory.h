#ifndef __MARIO_ANIMATION_FACTORY_H__
#define __MARIO_ANIMATION_FACTORY_H__

#include"animation.h"
#include"MarioObject.h"
#include <string>
using namespace std;
class MarioAnimationFactory{
public:
	virtual Animation* createAnimation();
};

class SmallMarioAnimationFactory :public MarioAnimationFactory{
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

class LargeMarioAnimationFactory :public MarioAnimationFactory{
private:
	Mario* mMario;
	LargeMarioAnimationFactory(Mario* mario);
	static LargeMarioAnimationFactory* sInstance;
public:
	static LargeMarioAnimationFactory* getInstance(Mario* mario=NULL);
	Animation *rightWalkAnim = new Animation(8, 13);
	Animation *leftWalkAnim = new Animation(1, 5);
	Animation *rightStandAnim = new Animation(8, 8);
	Animation *leftStandAnim = new Animation(6, 6);
	Animation *leftJumpAnim = new Animation(15, 21);
	Animation *rightJumpAnim = new Animation(23, 29);


	Animation* createAnimation()override;
	~LargeMarioAnimationFactory();
};

#endif