

#include"RedKoopa.h"
#include "KoopaTroopaState.h"
#include"BrickGround.h"
#include"Physics.h"
#include <string>
#include"Qbrick.h"
#include"MarioState.h"
#include "ObjectManager.h"
#include"MarioRaccoonTail.h"
#include "MetalBlock.h"
#include "MarioGame.h"
#include "KoopaTroopaAnimationFactory.h"
#include "gooba.h"
#include"Pipe.h"
using namespace std;

KoopaTroopa::KoopaTroopa(int x, int y, int width, int height, float vx, float vy, float vx_last, float ax, float ay, Animation* anim, CSprite * image) 
	:Object(x, y, width, height, vx, vy, vx_last, ax, ay, anim, image){
	
	if(mAnimationFactory==NULL)
		mAnimationFactory = new KoopaAnimationFactory(this);
	if (mState == NULL){
		mState = new KoopaNomalState(this);
	}
	if(mAnim==NULL)
		mAnim = mAnimationFactory->createAnimation();
	
	isBringedByMario = 0;
}
KoopaTroopa::KoopaTroopa(int x, int y, float vx, Animation* anim, CSprite * image)
	:Object(x, y, KoopaTroopa::KOOPA_WIDTH, KoopaTroopa::KOOPA_HEIGHT, vx, 0, vx, 0, 0, anim, image){
	
	if (mAnimationFactory == NULL)
		mAnimationFactory = new KoopaAnimationFactory(this);
	if (mState == NULL){
		mState = new KoopaNomalState(this);
	if (mAnim == NULL)
		mAnim = mAnimationFactory->createAnimation();

	}
	isBringedByMario = 0;
}

const float KoopaTroopa::PARA_FLYING_GRAVITY = 0.000019f;
const float KoopaTroopa::PARA_MAX_SPEED_Y = 0.003f;
const float KoopaTroopa::PARA_SPEED_X = 0.085f;
const float KoopaTroopa::PARA_ACCELERATION_Y = 0.003f;
const int KoopaTroopa::KOOPA_WIDTH = 16;
const int KoopaTroopa::KOOPA_HEIGHT = 27;
const int KoopaTroopa::KOOPA_VULNERABLE_HEIGHT = 16;
const int KoopaTroopa::NORMAL_ANIMATION_DELAY = Animation::FRAME_DELAY_DEFAULT;
const int KoopaTroopa::SLIDING_ANIMATION_DELAY = 1;
const float KoopaTroopa::KOOPA_VELOCITY_X = 0.1f;
const float KoopaTroopa::KOOPA_SLIDING_SPEED_X = 0.35f;
const float KoopaTroopa::KOOPA_VULNERABLE_SPEED_X = 0;
const int KoopaTroopa::WAKE_UP_FROM_VULNERABLE_TIME = 10000;
const string KoopaTroopa::OBJECT_NAME = "koopa_troopa";
string KoopaTroopa::getName(){
	return OBJECT_NAME;
}
void KoopaTroopa::onCollision(Object* ob,int dir){
	mState->onCollision(ob,dir);
}
KoopaTroopaState* KoopaTroopa::getState(){
	return mState;
}
void KoopaTroopa::setState(KoopaTroopaState* state){
	if (state != NULL){
		mState = state;
	}
	this->width = mState->getWidth();//thay đối lại kích thước của Koopa ứng với trạng thái
	this->height = mState->getHeight();
	this->mAnim->frameDelay = mState->getAnimationDelay();
	if (vx_last < 0){
		this->vx = -mState->getSpeed();
		vx_last = vx;
	}
	else
	{
		this->vx = mState->getSpeed();;
		vx_last = vx;
	}
}

void KoopaTroopa::setAnimationFactory(AnimationFactory* animFactory){
	mAnimationFactory = animFactory;
}

void KoopaTroopa::render(int vpx, int vpy){
	mSprite->Render(mAnimationFactory->createAnimation(), x, y, vpx, vpy);
}
void KoopaTroopa::update(int t){
	mState->update(t);

		
}


