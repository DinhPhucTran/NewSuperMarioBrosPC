#ifndef _KOOPA_TROOPA_ANIMATION_FACTORY_
#define _KOOPA_TROOPA_ANIMATION_FACTORY_
#include "AnimationFactory.h"
class KoopaTroopa;
class KoopaAnimationFactory : public AnimationFactory{
	KoopaTroopa* mKoopa;

public:

	KoopaAnimationFactory(KoopaTroopa* koopa);
	Animation* mKoopaLeftWalkAnim = new Animation(4, 5);
	Animation* mKoopaRightWalkAnim = new Animation(10, 11);
	Animation* mKoopaVulnerableAnim = new Animation(36, 36);
	Animation* mKoopaSlidingAnim = new Animation(36, 39);
	Animation* mKoopaLeftFlyAnim = new Animation(20, 23);
	Animation* mKoopaRightFlyAnim = new Animation(24, 27);
	Animation* mKoopaUpsideDownAnim = new Animation(43, 43);
	Animation* createAnimation()override;
	~KoopaAnimationFactory();
};
#endif