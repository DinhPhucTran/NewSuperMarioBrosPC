#include "RedKoopa.h"
#include "RedKoopaAnimationFactory.h"
#include "KoopaTroopaState.h"
string const RedKoopa::OBJECT_NAME = "red_koopa";
RedKoopa::RedKoopa(int x, int y, int width, int height, float vx, float vy, float vx_last, float ax, float ay, Animation* anim, CSprite * image)
	:KoopaTroopa(x, y, width, height, vx, vy, vx_last, ax, ay, anim, image){
	if (mState == NULL)
		mState = new KoopaNomalState(this);
	mAnimationFactory = new RedKoopaAnimationFactory(this);
	if (mAnim == NULL)
		mAnim = mAnimationFactory->createAnimation();
	
}
RedKoopa::RedKoopa(int x, int y,float vx, Animation* anim, CSprite * image)
	:KoopaTroopa(x, y, KoopaTroopa::KOOPA_WIDTH, KoopaTroopa::KOOPA_HEIGHT, vx, 0, vx, 0, 0, anim, image){
	if (mState == NULL)
		mState = new KoopaNomalState(this);
	mAnimationFactory = new RedKoopaAnimationFactory(this);
	if (mAnim == NULL)
		mAnim = mAnimationFactory->createAnimation();

}


string RedKoopa::getName(){
	return RedKoopa::OBJECT_NAME;
}
void RedKoopa::update(int t){
	mState->update(t);
}


