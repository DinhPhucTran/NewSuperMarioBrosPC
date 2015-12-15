#include "RedKoopa.h"


string const RedKoopa::OBJECT_NAME = "red_koopa";
RedKoopa::RedKoopa(int x, int y, int width, int height, float vx, float vy, float vx_last, float ax, float ay, Animation* anim, CSprite * image)
	:KoopaTroopa(x, y, width, height, vx, vy, vx_last, ax, ay, anim, image){
	if (mState == NULL)
		mState = new KoopaNomalState(this);
	mAnimationFactory = new RedKoopaAnimationFactory(this);
	if (mAnim == NULL)
		mAnim = mAnimationFactory->createAnimation();
	
}
void RedKoopa::onCollision(Object* ob,int dir){
	//xử lý va chạm của Rùa Đỏ
}

string RedKoopa::getName(){
	return RedKoopa::OBJECT_NAME;
}
void RedKoopa::update(int t){
	x += vx*t;
	y += vy*t;
}
////////////////////////////////

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