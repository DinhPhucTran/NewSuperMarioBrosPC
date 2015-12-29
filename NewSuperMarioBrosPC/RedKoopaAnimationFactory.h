#ifndef _RED_KOOPA_ANIMATION_FACTORY_
#define _RED_KOOPA_ANIMATION_FACTORY_
#include "AnimationFactory.h"

class KoopaTroopa;
class RedKoopaAnimationFactory :public AnimationFactory{

	KoopaTroopa* mRedKoopa;


public:
	Animation* mKoopaLeftWalkAnim = new Animation(0, 1);
	Animation* mKoopaRightWalkAnim = new Animation(14, 15);
	Animation* mKoopaVulnerableAnim = new Animation(32, 32);
	Animation* mKoopaSlidingAnim = new Animation(32, 35);
	Animation* mKoopaUpsideDownAnim = new Animation(44, 44);
	RedKoopaAnimationFactory(KoopaTroopa* redKoopa);

	Animation* createAnimation()override;
	~RedKoopaAnimationFactory();
};

#endif