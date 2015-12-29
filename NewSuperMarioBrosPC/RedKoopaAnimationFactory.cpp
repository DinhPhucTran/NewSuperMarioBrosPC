#include "RedKoopaAnimationFactory.h"
#include "RedKoopa.h"
#include "KoopaTroopaState.h"
RedKoopaAnimationFactory::RedKoopaAnimationFactory(KoopaTroopa* redKoopa){
	mRedKoopa = redKoopa;
}

RedKoopaAnimationFactory::~RedKoopaAnimationFactory(){
	//delete các animation
}
Animation* RedKoopaAnimationFactory::createAnimation(){

	string stateName = mRedKoopa->getState()->getName();
	Animation* result;
	if (stateName == KoopaVulnerableState::STATE_NAME){
		result = mKoopaVulnerableAnim;
	}
	else if (stateName == KoopaUpsideDown::STATE_NAME){
		result = mKoopaUpsideDownAnim;
	}
	else if (stateName == KoopaSlidingState::STATE_NAME){
		result = mKoopaSlidingAnim;
	}
	else {///normal state
		if (mRedKoopa->vx_last < 0){
			result = mKoopaLeftWalkAnim;
		}
		else{
			result = mKoopaRightWalkAnim;
		}
	}
	result->Update();
	return result;


}