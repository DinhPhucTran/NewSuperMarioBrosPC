#ifndef _FIRE_PIRANHA_
#define _FIRE_PIRANHA_

#include "PiranhaPlant.h"
class AnimationFactory;
class FirePiranha :public PiranhaPlant{
protected:
	AnimationFactory* mAnimFactory;
	int mIsShooting;
public:
	FirePiranha(int x, int y, CSprite* image, CSprite* pipeImage);
	static const string OBJECT_NAME;
	static const int FIRE_PIRANHA_HEIGHT;//24 // REd 32
	static const int FIRE_PIRANHA_WIDTH;//16
	static const int FIRE_PIRANHA_TIME_TO_MOVE;//2000ms
	
	string getName()override;
	
	void update(int t)override;
	void render(int vpx, int vpy)override;
	void shooting();
	int isShooting();

};

#endif
