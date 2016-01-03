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

	Animation *rightWalkAnim = new Animation(4, 5);//4 5
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

	Animation *kickKoopaLeft = new Animation(90, 90);
	Animation *kickKoopaRight = new Animation(91, 91);

	Animation *sitDownLeft = new Animation(22, 22);
	Animation *sitDownRight = new Animation(23, 23);

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

	Animation* RaccoonFlyingLeft = new Animation(43, 45,2);
	Animation* RaccoonFlyingRight = new Animation(40, 42,2);
	
	Animation* RaccoonFlyingUpLeft = new Animation(46, 48, 2);
	Animation* RaccoonFlyingUpRight = new Animation(50, 52, 2);

	Animation* powerRunLeft = new Animation(56, 58,2);
	Animation* powerRunRight = new Animation(53, 55,2);
	
	Animation* kickKoopaLeft = new Animation(66, 66);
	Animation* kickKoopaRight = new Animation(67, 67);

	Animation *sitDownLeft = new Animation(59, 59);
	Animation *sitDownRight = new Animation(69, 69);

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
	Animation* blankAnimation = new Animation(-1, -1);
	Animation* createAnimation()override;
	static InvincibleMarioAnimationFactory* getInstance(Mario* mario);
};

class SuperInvincibleMarioSmallAnimationFactory :public AnimationFactory{
private:
	Mario* mMario;
	SuperInvincibleMarioSmallAnimationFactory(Mario* mario);

	static SuperInvincibleMarioSmallAnimationFactory* sInstance;
public:
	Animation *rightWalkAnim = new Animation(82, 85,3);
	Animation *leftWalkAnim = new Animation(72, 75,3);
	Animation *rightStandAnim = new Animation(82, 83);
	Animation *leftStandAnim = new Animation(72, 73);
	Animation *leftJumpUpAnim = new Animation(76, 77);
	Animation *rightJumpUpAnim = new Animation(86, 87);
	Animation *leftJumpDownAnim = new Animation(76, 77);
	Animation *rightJumpDownAnim = new Animation(86, 87);
	Animation *turnRightAnimation = new Animation(80, 81);
	Animation *turnLeftAnimation = new Animation(70, 71);

	Animation *powerJumpLeft = new Animation(78, 79);
	Animation *powerJumpRight = new Animation(88, 89);

	static SuperInvincibleMarioSmallAnimationFactory* getInstance(Mario* mario);
	//contructor

	Animation* createAnimation()override;
};

class SuperRaccoonMarioAnimationFactory :public AnimationFactory{
private:
	Mario* mMario;
	SuperRaccoonMarioAnimationFactory(Mario* mario);
	static SuperRaccoonMarioAnimationFactory* sInstance;
public:
	static SuperRaccoonMarioAnimationFactory* getInstance(Mario* mario);
	Animation *rightWalkAnim = new Animation(92, 94);
	Animation *leftWalkAnim = new Animation(96, 98);
	Animation *rightStandAnim = new Animation(92, 92);
	Animation *leftStandAnim = new Animation(98, 98);
	Animation *leftJumpUpAnim = new Animation(106, 106);
	Animation *leftJumpDownAnim = new Animation(96, 96);
	Animation *rightJumpUpAnim = new Animation(107, 107);
	Animation *rightJumpDownAnim = new Animation(94, 94);
	Animation *turnRightAnimation = new Animation(95, 95);
	Animation *turnLeftAnimation = new Animation(99, 99);

	Animation* RaccoonTailBack = new Animation(100, 100);
	Animation* RaccoonTailFront = new Animation(102, 102);
	Animation* RaccoonTailLeft = new Animation(103, 103);
	Animation* RaccoonTailRight = new Animation(101, 101);

	Animation* RaccoonFlyingLeft = new Animation(127, 129, 3);
	Animation* RaccoonFlyingRight = new Animation(140, 142, 3);

	Animation* RaccoonFlyingUpLeft = new Animation(110, 112, 3);
	Animation* RaccoonFlyingUpRight = new Animation(113, 115, 3);

	Animation* powerRunLeft = new Animation(120, 122, 2);
	Animation* powerRunRight = new Animation(123, 125, 2);

	Animation* kickKoopaLeft = new Animation(109, 109);
	Animation* kickKoopaRight = new Animation(108, 108);

	Animation *sitDownLeft = new Animation(116, 116);
	Animation *sitDownRight = new Animation(117, 117);

	Animation *RollLeft = new Animation(130, 133,1);
	Animation *RollRight = new Animation(134, 137,1);

	Animation* createAnimation()override;
	~SuperRaccoonMarioAnimationFactory();
};


class SuperLargeMarioAnimationFactory :public AnimationFactory{
private:
	Mario* mMario;
	SuperLargeMarioAnimationFactory(Mario* mario);
	static SuperLargeMarioAnimationFactory* sInstance;
public:
	static SuperLargeMarioAnimationFactory* getInstance(Mario* mario);
	Animation *rightWalkAnim = new Animation(147, 149);
	Animation *leftWalkAnim = new Animation(143, 145);
	Animation *rightStandAnim = new Animation(147, 147);
	Animation *leftStandAnim = new Animation(145, 145);
	Animation *leftJumpUpAnim = new Animation(18, 18);
	Animation *rightJumpUpAnim = new Animation(19, 19);
	Animation *leftJumpDownAnim = new Animation(13, 13);
	Animation *rightJumpDownAnim = new Animation(17, 17);
	Animation *turnRightAnimation = new Animation(150, 150);
	Animation *turnLeftAnimation = new Animation(146, 146);

	Animation *powerRunLeft = new Animation(154, 156, 2);
	Animation *powerRunRight = new Animation(151, 153, 2);
	Animation *powerJumpLeft = new Animation(169, 169);
	Animation *powerJumpRight = new Animation(159, 159);

	Animation *kickKoopaLeft = new Animation(138, 138);
	Animation *kickKoopaRight = new Animation(139, 139);

	Animation *sitDownLeft = new Animation(157, 157);
	Animation *sitDownRight = new Animation(158, 158);

	Animation *RollLeft = new Animation(160, 163, 1);
	Animation *RollRight = new Animation(164, 167, 1);

	Animation* createAnimation()override;
	~SuperLargeMarioAnimationFactory();
};

#endif