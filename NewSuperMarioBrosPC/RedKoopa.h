#ifndef _RED_KOOPA_H_
#define _RED_KOOPA_H_
#include "KoopaTroopa.h"

class RedKoopa :public KoopaTroopa{
public:
	
	RedKoopa(int x, int y, int width, int height, float vx, float vy, float vx_last, float ax, float ay, Animation* anim, CSprite * image);
	static const string OBJECT_NAME;;
	string getName()override;
	void update(int t)override;
	void onCollision(Object* ob)override;
};

class RedKoopaAnimationFactory :public AnimationFactory{

	RedKoopa* mRedKoopa;
	

public:
	Animation* mKoopaLeftWalkAnim = new Animation(0, 1);
	Animation* mKoopaRightWalkAnim = new Animation(14, 15);
	Animation* mKoopaVulnerableAnim = new Animation(32, 32);
	Animation* mKoopaSlidingAnim = new Animation(32, 35);

	RedKoopaAnimationFactory(RedKoopa* redKoopa);

	static RedKoopaAnimationFactory* getInstance(RedKoopa* redKoopa);
	Animation* createAnimation()override;
	~RedKoopaAnimationFactory();
};
#endif