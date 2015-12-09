#ifndef _ANIMATION_FACTORY_
#define _ANIMATION_FACTORY_


#include "animation.h"

class AnimationFactory{
public:
	virtual Animation* createAnimation(){ return 0; }
};

#endif