#include"KoopaTroopa.h"
#include"BrickGround.h"
#include"Physics.h"
#include <string>
using namespace std;

KoopaTroopa::KoopaTroopa(int x, int y, int width, int height, float vx, float vy, float vx_last, float ax, float ay, Animation* anim, CSprite * image) 
	:Object(x, y, width, height, vx, vy, vx_last, ax, ay, anim, image){
	if (mState == NULL){
		mState = new KoopaNomalState(this);
	}
	if(mAnimationFactory==NULL)
		mAnimationFactory = new KoopaAnimationFactory(this);
	if(mAnim==NULL)
		mAnim = mAnimationFactory->createAnimation();
	
}

const float KoopaTroopa::KOOPA_VELOCITY_X = 0.1f;
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
	if(state!=NULL)
		mState = state;
}

void KoopaTroopa::setAnimationFactory(AnimationFactory* animFactory){
	mAnimationFactory = animFactory;
}

void KoopaTroopa::render(int vpx, int vpy){
	mSprite->Render(mAnimationFactory->createAnimation(), x, y, vpx, vpy);
}
void KoopaTroopa::update(int t){
	x += vx*t;
	y += vy*t;
}


/////////////////////KoopaTroopaState/////////////////////
string KoopaTroopaState::getName(){
	return "koopa_state";
}

void KoopaTroopaState::onCollision(Object*ob,int dir){

	//khong xử lý va chạm, vì đây là trạng thái ảo
}
KoopaTroopaState::KoopaTroopaState(KoopaTroopa* koopa){
	mKoopa = koopa;
}
/////////////////////KoopaNomalState//////////////////

const string KoopaNomalState::STATE_NAME = "koopa_nomal_state";
string KoopaNomalState::getName(){
	return STATE_NAME;
}
void KoopaNomalState::onCollision(Object*ob,int dir){
	//xử lý va chạm, nếu chạm gạch thì quay đầu
	//chạm mario từ bên trái,phải hoặc bên dưới thì mario chết
	//chạm mario từ trên thì chuyển sang trạng thái Vulnerable;
	if (ob->getName() == BrickGround::OBJECT_NAME){
		if (dir == Physics::COLLIDED_FROM_LEFT){
			if (mKoopa->vx_last < 0){
				mKoopa->vx = KoopaTroopa::KOOPA_VELOCITY_X;
				mKoopa->vx_last = mKoopa->vx;
			}
		}
	}
}
KoopaNomalState::KoopaNomalState(KoopaTroopa* koopa)
	:KoopaTroopaState(koopa){
	
}

///////////////////KoopaVulnerableState///////////////

const string KoopaVulnerableState::STATE_NAME = "koopa_vulnerable_state";
string KoopaVulnerableState::getName(){
	return STATE_NAME;
}
void KoopaVulnerableState::onCollision(Object*ob,int dir){
	//xử lý va chạm 
	//nếu chạm mario chuyển sang trạng thái bị đá SlidingState
}

KoopaVulnerableState::KoopaVulnerableState(KoopaTroopa* koopa) 
	:KoopaTroopaState(koopa){
	
}


/////////////////////////////////////////////////
const string KoopaSlidingState::STATE_NAME = "koopa_sliding_state";
string KoopaSlidingState::getName(){
	return STATE_NAME;
}
void KoopaSlidingState::onCollision(Object*ob,int dir){
	//xử lý va chạm 
	//nếu chạm mario từ trái hoặc phải thì mario chết
	//nếu chạm mario từ trên xuống thì dừng lại chuyển sang trạng thái vulnerable
	//nếu chạm gạch vở đc thì gach vở, đổi hướng.
	//nếu chạm kẻ thù (Goomba, koopa..) thì kẻ thù chết.

	
}
KoopaSlidingState::KoopaSlidingState(KoopaTroopa* koopa) 
	:KoopaTroopaState(koopa){

}

/////////////////////////////KoopaAnimationFactory///////////////

Animation* KoopaAnimationFactory::createAnimation(){
	string stateName = mKoopa->getState()->getName();
	Animation* result;
	if (stateName == KoopaVulnerableState::STATE_NAME){
		result = mKoopaVulnerableAnim;
	}
	else if (stateName == KoopaSlidingState::STATE_NAME){
		result = mKoopaSlidingAnim;
	}
	else {///normal state
		if (mKoopa->vx_last < 0){
			result = mKoopaLeftWalkAnim;
		}
		else{
			result = mKoopaRightWalkAnim;
		}
	}
	result->Update();
	return result;
}

KoopaAnimationFactory::KoopaAnimationFactory(KoopaTroopa*koopa){
	mKoopa = koopa;
}
KoopaAnimationFactory::~KoopaAnimationFactory(){
	delete mKoopaLeftWalkAnim;
	delete mKoopaRightWalkAnim;
	delete mKoopaSlidingAnim;
	delete mKoopaVulnerableAnim;
}