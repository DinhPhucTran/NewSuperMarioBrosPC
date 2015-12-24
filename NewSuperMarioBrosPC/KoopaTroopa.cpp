﻿

#include"RedKoopa.h"
#include"BrickGround.h"
#include"Physics.h"
#include <string>
#include"Qbrick.h"
#include"MarioState.h"
#include "ObjectManager.h"
#include"MarioRaccoonTail.h"
#include "MetalBlock.h"
#include "MarioGame.h"
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
		delete mState;// giải phóng mState hiện tại
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

/////////////////////KoopaTroopaState/////////////////////
string KoopaTroopaState::getName(){
	return "koopa_state";
}

void KoopaTroopaState::onCollision(Object*ob,int dir){
	string objName = ob->getName();
	if (objName == MarioRaccoonTail::OBJECT_NAME && MarioRaccoonTail::getInstance()->getState() == MarioRaccoonTail::STATE_ACTIVE){
		mKoopa->vy = 0.5f;
		mKoopa->setState(new KoopaVulnerableState(mKoopa));
	}
	if (objName == MetalBlock::OBJECT_NAME)
	{
		if (dir == Physics::COLLIDED_FROM_BOTTOM && mKoopa->bottom() + 8 >= ob->top())
		{
			mKoopa->vy = 0;
			mKoopa->ay = 0;
			mKoopa->y = ob->top() + mKoopa->height / 2;
			return;
		}
	}
	//Tất cả các lơp kế thừa phải gọi hàm này nếu override
	//chứa tất cả các loại va chạm chung mà mọi trạng thái đều xử lý như nhau

	
}
KoopaTroopaState::KoopaTroopaState(KoopaTroopa* koopa){
	mKoopa = koopa;
	
}

float KoopaTroopaState::getSpeed(){
	return KoopaTroopa::KOOPA_VELOCITY_X;
}
int KoopaTroopaState::getHeight(){
	return KoopaTroopa::KOOPA_HEIGHT;
}
int KoopaTroopaState::getWidth(){
	return KoopaTroopa::KOOPA_WIDTH;
}
int KoopaTroopaState::getAnimationDelay(){
	return KoopaTroopa::NORMAL_ANIMATION_DELAY;
}
void KoopaTroopaState::update(int t){
	mKoopa->vy += mKoopa->ay*t;
	mKoopa->vx += mKoopa->ax*t;
	if (mKoopa->vy > Object::MAX_SPEED_Y || mKoopa->vy < -Object::MAX_SPEED_Y){
		mKoopa->ay = 0;
	}
	mKoopa->ay -= CMarioGame::GRAVITY_VELOCOTY*t;
	mKoopa->x += (int)(mKoopa->vx * t);
	mKoopa->y += (int)(mKoopa->vy * t);
}
/////////////////////KoopaNomalState//////////////////

const string KoopaNomalState::STATE_NAME = "koopa_nomal_state";
string KoopaNomalState::getName(){
	return STATE_NAME;
}
void KoopaNomalState::onCollision(Object*ob, int dir){
	//xử lý va chạm, nếu chạm gạch thì quay đầu
	//chạm mario từ bên trái,phải hoặc bên dưới thì mario chết
	//chạm mario từ trên thì chuyển sang trạng thái Vulnerable;
	KoopaTroopaState::onCollision(ob, dir);
	string objName = ob->getName();

	if (objName == BrickGround::OBJECT_NAME || objName == Pipe::OBJECT_NAME || objName == QBrick::OBJECT_NAME){
		if (dir == Physics::COLLIDED_FROM_LEFT){
			if (mKoopa->vx_last < 0){
				mKoopa->vx = KoopaTroopa::KOOPA_VELOCITY_X;
				mKoopa->vx_last = mKoopa->vx;
			}
		}
		else if (dir == Physics::COLLIDED_FROM_RIGHT){
			if (mKoopa->vx_last > 0){
				mKoopa->vx = -KoopaTroopa::KOOPA_VELOCITY_X;
				mKoopa->vx_last = mKoopa->vx;
			}
		}
		else if (dir == Physics::COLLIDED_FROM_BOTTOM){
			mKoopa->vy = 0;
			mKoopa->ay = 0;
			mKoopa->y = ob->top() + mKoopa->height / 2;// chỉnh lại tọa độ y
		}
		else if (dir == Physics::COLLIDED_FROM_TOP){
			if (mKoopa->vy > 0){
				mKoopa->vy = -0.000001;//gần bằng 0, không đc =0 sẽ gây ra lổi
				mKoopa->ay = 0;
			}
		}
	}
	else if (objName == Mario::OBJECT_NAME)
	{
		//Nếu mario invicible thì ko xử lý tiếp nữa
		Mario* mario = (Mario*)ob;
		string stateName = (mario->getState())->getName();
		if (stateName == MarioStateInvincible::STATE_NAME){
			return;
		}

		//chạm trái phải dưới -> mario chết
		//trên thì chuyển sang vulnerable state;
		else if (dir == Physics::COLLIDED_FROM_TOP)
		{
			if (mKoopa->vy > 0){
				mKoopa->vy = -0.000001;//gần bằng 0, không đc =0 sẽ gây ra lổi
				mKoopa->ay = 0;
			}
			mKoopa->vx = 0;
			mKoopa->ax = 0;
			mKoopa->setState(new KoopaVulnerableState(mKoopa));
		}
	}
	//va chạm với rùa đang slide
	if (objName == RedKoopa::OBJECT_NAME || objName == KoopaTroopa::OBJECT_NAME){
		string stateName = ((KoopaTroopa*)ob)->getState()->getName();
		if (stateName == KoopaSlidingState::STATE_NAME){
			if (dir == Physics::COLLIDED_FROM_LEFT || dir == Physics::COLLIDED_FROM_RIGHT){
				mKoopa->die();
			}
		}
	}
	
}
KoopaNomalState::KoopaNomalState(KoopaTroopa* koopa)
	:KoopaTroopaState(koopa){
}

///////////////////KoopaVulnerableState///////////////
KoopaVulnerableState::KoopaVulnerableState(KoopaTroopa* koopa)
	: KoopaTroopaState(koopa){
	mLastTime = GetTickCount();
}


const string KoopaVulnerableState::STATE_NAME = "koopa_vulnerable_state";
string KoopaVulnerableState::getName(){
	return STATE_NAME;
}
int KoopaVulnerableState::getHeight(){
	return KoopaTroopa::KOOPA_VULNERABLE_HEIGHT;
}
float KoopaVulnerableState::getSpeed(){
	return KoopaTroopa::KOOPA_VULNERABLE_SPEED_X;
}

void KoopaVulnerableState::onCollision(Object*ob, int dir){
	//xử lý va chạm 
	//nếu chạm mario chuyển sang trạng thái bị đá SlidingState
	//Va chạm dưới với gạch, 
	//va chạm trên dưới trái phải với mario;
	DWORD now = GetTickCount();
	if (now - mLastTime >= 10000){
		Mario* mario = ObjectManager::getInstance()->getMario();
		if (mario == 0){//mario dead already
			return;
		}
		if (mario->x > mKoopa->x){//khi wake up thì rùa đi hướng về phía mario;
			mKoopa->vx = KoopaTroopa::KOOPA_VELOCITY_X;
			mKoopa->vx_last = mKoopa->vx;
		}
		else
		{
			mKoopa->vx = -KoopaTroopa::KOOPA_VELOCITY_X;
			mKoopa->vx_last = mKoopa->vx;
		}
		if (mKoopa->isBringedByMario == 1){//mKoopa wake up mà mario vẫn cầm thì mario chết
			mario->die();
			mKoopa->isBringedByMario = 0;
		}
		mKoopa->setState(new KoopaNomalState(mKoopa));
		return;
	}

	KoopaTroopaState::onCollision(ob, dir);
	string objName = ob->getName();
	if (objName == BrickGround::OBJECT_NAME){
		if (dir == Physics::COLLIDED_FROM_BOTTOM){
			mKoopa->vy = 0;
			mKoopa->ay = 0;
			mKoopa->y = ob->top() + mKoopa->height / 2;// chỉnh lại tọa độ y
		}
		else if (dir == Physics::COLLIDED_FROM_TOP){
			if (mKoopa->vy > 0){
				mKoopa->vy = -0.000001;//gần bằng 0, không đc =0 sẽ gây ra lổi
				mKoopa->ay = 0;
			}
		}
	}
	//xử lý va chạm vs Mario
	
	if (ob->getName() == Mario::OBJECT_NAME){
		//Nếu mario invicible thì ko xử lý tiếp nữa
		Mario* mario = (Mario*)ob;
		string stateName = (mario->getState())->getName();
		if (stateName == MarioStateInvincible::STATE_NAME){
			return;
		}
		else if (dir == Physics::COLLIDED_FROM_LEFT&& mKoopa->isBringedByMario == 0){
			if (mario->isBButtonPressed){//nếu B pressed thì mario cầm rùa chứ ko đá rùa
				//xử lý trường hợp mario cầm rùa
				mKoopa->isBringedByMario = 1;
				return;
			}
			mKoopa->x = ob->right() + mKoopa->width / 2 + 2;
			mKoopa->vx = KoopaTroopa::KOOPA_SLIDING_SPEED_X;
			mKoopa->vx_last = mKoopa->vx;
			mKoopa->setState(new KoopaSlidingState(mKoopa));
		}
		else if (dir == Physics::COLLIDED_FROM_RIGHT && mKoopa->isBringedByMario == 0){
			if (mario->isBButtonPressed){//nếu B pressed thì mario cầm rùa chứ ko đá rùa
				//xử lý trường hợp mario cầm rùa
				mKoopa->isBringedByMario = 1;
				return;
			}
			mKoopa->x = ob->left() - mKoopa->width / 2 - 2;
			mKoopa->vx = -KoopaTroopa::KOOPA_SLIDING_SPEED_X;
			mKoopa->vx_last = mKoopa->vx;
			mKoopa->setState(new KoopaSlidingState(mKoopa));
		}
		else if (dir == Physics::COLLIDED_FROM_TOP || dir == Physics::COLLIDED_FROM_BOTTOM ){
			if (mKoopa->isBringedByMario == 1){
				return;
			}
			if (ob->x >= mKoopa->x){
				//slide qua trái
				ob->y = mKoopa->top() + ob->height / 2 + 2;
				mKoopa->x = ob->left() - mKoopa->width / 2 - 2;
				mKoopa->vx = -KoopaTroopa::KOOPA_SLIDING_SPEED_X;
				mKoopa->vx_last = mKoopa->vx;
				mKoopa->setState(new KoopaSlidingState(mKoopa));
			}
			else{
				//slide qua phải
				ob->y = mKoopa->top() +ob->height/2 + 2;
				mKoopa->x = ob->right() + mKoopa->width / 2 + 2;
				mKoopa->vx = KoopaTroopa::KOOPA_SLIDING_SPEED_X;
				mKoopa->vx_last = mKoopa->vx;
				mKoopa->setState(new KoopaSlidingState(mKoopa));
			}
		}
		
	}
	
	//va chạm với rùa đang slide
	if (objName == RedKoopa::OBJECT_NAME || objName == KoopaTroopa::OBJECT_NAME){
		string stateName = ((KoopaTroopa*)ob)->getState()->getName();
		if (stateName == KoopaSlidingState::STATE_NAME){
			if (dir == Physics::COLLIDED_FROM_LEFT || dir == Physics::COLLIDED_FROM_RIGHT){
				mKoopa->die();
			}
		}
	}
}

void KoopaVulnerableState::update(int t){
	Mario* mario = ObjectManager::getInstance()->getMario();
	if (mario == NULL){
		mKoopa->isBringedByMario = 0;
		return;
	}
	if (mKoopa->isBringedByMario == 1 && mario->isBButtonPressed == 1){
		mKoopa->y = mario->y;
		if (mario->vx_last > 0){
			mKoopa->x = mario->right();
		}
		else{
			mKoopa->x = mario->left();
		}
	}
	else{
		mKoopa->isBringedByMario = 0;
		KoopaTroopaState::update(t);
	}
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

	KoopaTroopaState::onCollision(ob, dir);
	string objName = ob->getName();
	if (ob->getName() == BrickGround::OBJECT_NAME||ob->getName()==Pipe::OBJECT_NAME||QBrick::OBJECT_NAME == objName){
		if (dir == Physics::COLLIDED_FROM_LEFT){
			if (mKoopa->vx_last < 0){
				mKoopa->vx = KoopaTroopa::KOOPA_SLIDING_SPEED_X;
				mKoopa->vx_last = mKoopa->vx;
			}
		}
		else if (dir == Physics::COLLIDED_FROM_RIGHT){
			if (mKoopa->vx_last > 0){
				mKoopa->vx = -KoopaTroopa::KOOPA_SLIDING_SPEED_X;
				mKoopa->vx_last = mKoopa->vx;
			}
		}
		else if (dir == Physics::COLLIDED_FROM_BOTTOM){
			mKoopa->vy = 0;
			mKoopa->ay = 0;
			mKoopa->y = ob->top() + mKoopa->height / 2;// chỉnh lại tọa độ y
		}
		else if (dir == Physics::COLLIDED_FROM_TOP){
			if (mKoopa->vy > 0){
				mKoopa->vy = -0.000001;//gần bằng 0, không đc =0 sẽ gây ra lổi
				mKoopa->ay = 0;
			}
		}
	}
	//xử lý với mario
	if (objName == Mario::OBJECT_NAME){
		//Nếu mario invicible thì ko xử lý tiếp nữa
		Mario* mario = (Mario*)ob;
		string stateName = (mario->getState())->getName();
		if (stateName == MarioStateInvincible::STATE_NAME){
			return;
		}
		else if (dir == Physics::COLLIDED_FROM_TOP){
			mKoopa->vx = 0;
			mKoopa->ax = 0;
			mKoopa->setState(new KoopaVulnerableState(mKoopa));
		}
	}
	
	if (objName == QBrick::OBJECT_NAME){
		QBrick* qBrick = (QBrick*)ob;
		if (dir == Physics::COLLIDED_FROM_LEFT || dir == Physics::COLLIDED_FROM_RIGHT){
			qBrick->revealHiddenObject();
		}
	}
	
}
KoopaSlidingState::KoopaSlidingState(KoopaTroopa* koopa) 
	:KoopaTroopaState(koopa){

}
int KoopaSlidingState::getAnimationDelay(){
	return KoopaTroopa::SLIDING_ANIMATION_DELAY;
}
int KoopaSlidingState::getHeight(){
	return KoopaTroopa::KOOPA_VULNERABLE_HEIGHT;
}
float KoopaSlidingState::getSpeed(){
	return KoopaTroopa::KOOPA_SLIDING_SPEED_X;
}


/////////////////////KoopaParaState////////////////////

float KoopaParaState::getSpeed(){
	return KoopaTroopa::PARA_SPEED_X;
}
KoopaParaState::KoopaParaState(KoopaTroopa* koopa)
	:KoopaTroopaState(koopa){

}
void KoopaParaState::onCollision(Object*ob, int dir){
	KoopaTroopaState::onCollision(ob, dir);
	string objName = ob->getName();

	if (objName == BrickGround::OBJECT_NAME || objName == Pipe::OBJECT_NAME || objName == QBrick::OBJECT_NAME){
		if (dir == Physics::COLLIDED_FROM_LEFT){
			if (mKoopa->vx_last < 0){
				mKoopa->vx = KoopaTroopa::PARA_SPEED_X;
				mKoopa->vx_last = mKoopa->vx;
			}
		}
		else if (dir == Physics::COLLIDED_FROM_RIGHT){
			if (mKoopa->vx_last > 0){
				mKoopa->vx = -KoopaTroopa::PARA_SPEED_X;
				mKoopa->vx_last = mKoopa->vx;
			}
		}
		else if (dir == Physics::COLLIDED_FROM_BOTTOM){
			mKoopa->vy = 0;
			mKoopa->ay = 0;
			mKoopa->y = ob->top() + mKoopa->height / 2;// chỉnh lại tọa độ y
		}
		else if (dir == Physics::COLLIDED_FROM_TOP){
			if (mKoopa->vy > 0){
				mKoopa->vy = -0.000001;//gần bằng 0, không đc =0 sẽ gây ra lổi
				mKoopa->ay = 0;
			}
		}
	}
	else if (objName == Mario::OBJECT_NAME)
	{
		//Nếu mario invicible thì ko xử lý tiếp nữa
		Mario* mario = (Mario*)ob;
		string stateName = (mario->getState())->getName();
		if (stateName == MarioStateInvincible::STATE_NAME){
			return;
		}

		//chạm trái phải dưới -> mario chết
		//trên thì chuyển sang vulnerable state;
		else if (dir == Physics::COLLIDED_FROM_TOP)
		{
			if (mKoopa->vy > 0){
				mKoopa->vy = -0.000001;//gần bằng 0, không đc =0 sẽ gây ra lổi
				mKoopa->ay = 0;
			}
			mKoopa->vx = 0;
			mKoopa->ax = 0;
			mKoopa->setState(new KoopaNomalState(mKoopa));
		}
	}
	//va chạm với rùa đang slide
	if (objName == RedKoopa::OBJECT_NAME || objName == KoopaTroopa::OBJECT_NAME){
		string stateName = ((KoopaTroopa*)ob)->getState()->getName();
		if (stateName == KoopaSlidingState::STATE_NAME){
			if (dir == Physics::COLLIDED_FROM_LEFT || dir == Physics::COLLIDED_FROM_RIGHT){
				mKoopa->die();
			}
		}
	}
}
const string KoopaParaState::STATE_NAME = "koopa_para_state";

string KoopaParaState::getName(){
	return STATE_NAME;
}
void KoopaParaState::update(int t){
	if (mKoopa->vy == 0){
		mKoopa->ay = KoopaTroopa::PARA_ACCELERATION_Y;
	}
	if (mKoopa->x <= 10)
		mKoopa->x = 10;
	if (mKoopa->x >= 2800)
		mKoopa->x = 2800;


	mKoopa->vy += mKoopa->ay*t;
	mKoopa->vx += mKoopa->ax*t;
	if (mKoopa->vy > Object::MAX_SPEED_Y || mKoopa->vy < -Object::MAX_SPEED_Y){
		mKoopa->ay = 0;
	}
	mKoopa->ay -= KoopaTroopa::PARA_FLYING_GRAVITY*t;
	mKoopa->x += (int)(mKoopa->vx * t);
	mKoopa->y += (int)(mKoopa->vy * t);
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
	else if(stateName == KoopaNomalState::STATE_NAME){///normal state
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