
#include "KoopaTroopaAnimationFactory.h"
#include "KoopaTroopaState.h"
/////////////////////////////KoopaAnimationFactory///////////////

Animation* KoopaAnimationFactory::createAnimation(){
	string stateName = mKoopa->getState()->getName();
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
	else if (stateName == KoopaNomalState::STATE_NAME){///normal state
		if (mKoopa->vx_last < 0){
			result = mKoopaLeftWalkAnim;
		}
		else{
			result = mKoopaRightWalkAnim;
		}
	}
	else
	{//Parastate
		if (mKoopa->vx_last < 0){
			result = mKoopaLeftFlyAnim;
		}
		else{
			result = mKoopaRightFlyAnim;
		}
	}
	result->Update();
	return result;
}

KoopaAnimationFactory::KoopaAnimationFactory(KoopaTroopa*koopa){
	mKoopa = koopa;
}
KoopaAnimationFactory::~KoopaAnimationFactory(){
	/*delete mKoopaLeftWalkAnim;
	delete mKoopaRightWalkAnim;
	delete mKoopaSlidingAnim;
	delete mKoopaVulnerableAnim;*/
}