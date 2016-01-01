#include "MarioState.h"
#include "MarioObject.h"
#include "BrickGround.h"
#include "Pipe.h"
#include "Physics.h"
#include "RedKoopa.h"
#include "MetalBlock.h"
#include "Qbrick.h"
#include "MarioAnimationFactory.h"
#include "Leaf.h"
#include "Mushroom.h"
#include "MarioRaccoonTail.h"
#include "ObjectManager.h"
#include "GoldBrick.h"
#include "MarioGame.h"
#include "MarioPowerBar.h"
#include "PiranhaPlant.h"
#include "FirePiranha.h"
#include <string>
#include "KoopaTroopaState.h"
#include "FireBall.h"
#include "SuperStar.h"
#include "Coin.h"
using namespace std;

//================STATE====================
MarioState::MarioState(Mario* mario){
	mMario = mario;
}
void MarioState::onAPress(){
	//if (!mMario->isFlying)
		mMario->jumpUp();
}
void MarioState::onBPress(){
	
}

void MarioState::update(int t){
	if (mMario->x <= 8)
		mMario->x = 8;
	if (mMario->x >= 2800)
		mMario->x = 2800;

	mMario->dx += (mMario->vx*t);
	int temp = (int)mMario->dx;
	mMario->x += temp;
	mMario->dx -= temp;

	mMario->dy += (mMario->vy*t);
	temp = (int)(mMario->dy);
	mMario->y += temp;
	mMario->dy -= temp;

	mMario->vx = mMario->vx + mMario->ax*t;
	mMario->vy += mMario->ay*t;

	//xử lý tăng tốc mario nếu đang power
	float powerSpeed, powerSpeedY=0;
	
	if (mMario->getPowerBar()->isPower()){
		powerSpeed = Mario::POWER_SPEED_X_PLUS;
		powerSpeedY = Mario::POWER_JUMP_UP_SPEED;
	}
	else{
		powerSpeed = (Mario::POWER_SPEED_X_PLUS)*mMario->getPowerBar()->getState();
		powerSpeedY = 0;
	}

	if (mMario->vx >= Mario::MAX_SPEED_X+ powerSpeed || mMario->vx <= -Mario::MAX_SPEED_X-powerSpeed){
		mMario->ax = 0;
		if (mMario->vx_last<0)
			mMario->vx = -Mario::MAX_SPEED_X-powerSpeed;
		else 
			mMario->vx = Mario::MAX_SPEED_X+powerSpeed;
	}
	if (mMario->vy >= Mario::MAX_SPEED_Y +powerSpeedY || mMario->vy <= -Mario::MAX_SPEED_Y)
	{
		mMario->ay = 0;
	}
	mMario->ay -= CMarioGame::GRAVITY_VELOCOTY*t;
}

void MarioState::onCollision(Object* ob,int dir){
	string objectName = ob->getName();
	if (objectName == MetalBlock::OBJECT_NAME)
	{
		if (dir == Physics::COLLIDED_FROM_BOTTOM && mMario->top() > ob->top() && mMario->bottom() + 8 >= ob ->top())//tránh trường hợp tự động đứng trên block khi chưa nhảy tới
		{
			mMario->vy = 0;
			mMario->ay = 0;
			mMario->y = ob->top() + mMario->height / 2;
			return;
		}
	}
	if (objectName == BrickGround::OBJECT_NAME || objectName == Pipe::OBJECT_NAME || objectName == QBrick::OBJECT_NAME || objectName == GoldBrick::OBJECT_NAME)
	{
		if (dir == Physics::COLLIDED_FROM_TOP){
			if (objectName == QBrick::OBJECT_NAME){
				QBrick* qBrick = (QBrick*)ob; 
				qBrick->revealHiddenObject();
				//if (qBrick->getHiddenObjectName() == Coin::OBJECT_NAME)
					mMario->score = mMario->score + 100;
			}
			mMario->y = ob->bottom() - mMario->height / 2;
			mMario->vy = -0.000001;//note: không đc =0. nếu vy =0 thì sẽ gây ra lỗi người dùng có thể cho nó bay liên tục
			mMario->ay = 0;
			return;
		}
		if (dir == Physics::COLLIDED_FROM_BOTTOM)
		{
			mMario->vy = 0;
			mMario->ay = 0;
			mMario->y = ob->top() + mMario->height / 2;
			return;
		}
		if (dir == Physics::COLLIDED_FROM_RIGHT)
		{
			mMario->x = ob->left() - mMario->width / 2;
			mMario->ax = 0;
			return;
		}
		if (dir == Physics::COLLIDED_FROM_LEFT)
		{
			mMario->x = ob->right() + mMario->width / 2;
			mMario->ax = 0;
			return;
		}
	}
	if (objectName == KoopaTroopa::OBJECT_NAME || objectName == RedKoopa::OBJECT_NAME){
		KoopaTroopa* koopa = (KoopaTroopa*)ob;
		string state = koopa->getState()->getName();
		if (state == KoopaNomalState::STATE_NAME || state == KoopaParaState::STATE_NAME){
			if (dir == Physics::COLLIDED_FROM_BOTTOM){
				mMario->y = ob->top() + mMario->height / 2;
				mMario->vy = 0;
				mMario->jumpUp();
			}
			else if (dir == Physics::COLLIDED_FROM_LEFT || dir == Physics::COLLIDED_FROM_RIGHT || dir == Physics::COLLIDED_FROM_TOP){
				mMario->die();
			}
			//nếu trái phải thì chết
		}
		else if (state == KoopaSlidingState::STATE_NAME){
			if (dir == Physics::COLLIDED_FROM_BOTTOM){
				mMario->y = ob->top() + mMario->height / 2;
				mMario->vy = 0;
				mMario->jumpUp();
			}
			else if (dir == Physics::COLLIDED_FROM_LEFT || dir == Physics::COLLIDED_FROM_RIGHT){
				mMario->die();
			}
		}
	}
	if (objectName == Gooba::OBJECT_NAME){
		string state = ((Gooba*)ob)->getState()->getName();
		if (state == GoobaNomalState::STATE_NAME || state == GoobaParaState::STATE_NAME){
			if (dir == Physics::COLLIDED_FROM_BOTTOM){
				mMario->y = ob->top() + mMario->height / 2+2;
				mMario->vy = 0;
				mMario->jumpUp();
			}
			else if (dir == Physics::COLLIDED_FROM_LEFT || dir == Physics::COLLIDED_FROM_RIGHT || dir == Physics::COLLIDED_FROM_TOP){
				mMario->die();
			}
			//nếu trái phải trên thì chết
		}
	}
	if (objectName == RedMushroom::OBJECT_NAME){
		MarioStateInvincible* stateInvincibleLarge = new MarioStateInvincible(mMario,new MarioStateLarge(mMario));
		mMario->setState(stateInvincibleLarge);
	}
	if (objectName == GreenMushroom::OBJECT_NAME){
		
	}
	if (objectName == SuperStar::OBJECT_NAME){
		MarioStateSuperInvincible* superInvincible = new MarioStateSuperInvincible(mMario);
		mMario->setState(superInvincible);
	}
	if (objectName == Leaf::OBJECT_NAME){
		MarioStateInvincible* stateInvincibleRaccoon = new MarioStateInvincible(mMario, new MarioStateRaccoon(mMario));
		mMario->setState(stateInvincibleRaccoon);
	}
	//xử lý với PiranhaPlant
	if (objectName == PiranhaPlant::OBJECT_NAME || objectName == FirePiranha::OBJECT_NAME || objectName == FireBall::OBJECT_NAME){
		mMario->die();
	}
	
}
string MarioState::getName(){
	return "mario_state";
}
int MarioState::getWidth(){
	return 16;
}
int MarioState::getHeight(){
	return 27;
}
AnimationFactory* MarioState::getAnimationFactory(){
	return 0;
}
//================STATE SMALL==============
const string MarioStateSmall::STATE_NAME = "mario_state_small";
MarioStateSmall::MarioStateSmall(Mario* mario) :MarioState(mario){

}
string MarioStateSmall::getName(){
	return STATE_NAME;
}




void MarioStateSmall::onAPress(){
	MarioState::onAPress();
}
void MarioStateSmall::onBPress(){
	//do nothing
}
void MarioStateSmall::onCollision(Object* ob,int dir){
	//xử lý va chạm khi mario ở trạng thái Small
	MarioState::onCollision(ob, dir);
}
int MarioStateSmall::getHeight(){
	return height;
}
int MarioStateSmall::getWidth(){
	return width;
}
AnimationFactory* MarioStateSmall::getAnimationFactory(){
	return SmallMarioAnimationFactory::getInstance(mMario);
}
//==================SATE_LARGE==============
const string MarioStateLarge::STATE_NAME = "mario_state_large";
MarioStateLarge::MarioStateLarge(Mario* mario) :MarioState(mario){

}
string MarioStateLarge::getName(){
	return STATE_NAME;
}

void MarioStateLarge::onAPress(){
	MarioState::onAPress();
}
void MarioStateLarge::onBPress(){
	//do nothing;
}
void MarioStateLarge::onCollision(Object* ob,int dir){
	//xử lý va chạm trong trường hợp mario Lớn
	MarioState::onCollision(ob,dir);
}
int MarioStateLarge::getHeight(){
	return height;
}
int MarioStateLarge::getWidth(){
	return width;
}
AnimationFactory* MarioStateLarge::getAnimationFactory(){
	return LargeMarioAnimationFactory::getInstance(mMario);
}
//==================SATE_RACON==============
const string MarioStateRaccoon::STATE_NAME = "mario_state_raccoon";
const int MarioStateRaccoon::FLYING_TIME = 300;


MarioStateRaccoon::MarioStateRaccoon(Mario* mario) :MarioState(mario){
	MarioRaccoonTail* mTail = MarioRaccoonTail::getInstance();
	//mTail->setSprite(mMario->mSprite);//for debug only
	ObjectManager::getInstance()->addObject(mTail);

}
string MarioStateRaccoon::getName(){
	return STATE_NAME;
}

void MarioStateRaccoon::onAPress(){
	MarioState::onAPress();
	timeFlying = GetTickCount();
}
void MarioStateRaccoon::onBPress(){
	MarioRaccoonTail* tail = MarioRaccoonTail::getInstance();
	if (tail->getState()==MarioRaccoonTail::STATE_INACTIVE)
		tail->setState(MarioRaccoonTail::STATE_ACTIVE);
}
int MarioStateRaccoon::getHeight(){
	return height;
}
int MarioStateRaccoon::getWidth(){
	return width;
}
void MarioStateRaccoon::onCollision(Object* ob,int dir){
	//xử lý va chạm trong trường hợp mario Raccoon
	MarioState::onCollision(ob,dir);
	
}
void MarioStateRaccoon::update(int t){
	if (GetTickCount() - timeFlying <= FLYING_TIME && mMario->getPowerBar()->isPower() == 1){//Flying
		mMario->isFlying = 1;//for Animation Factory know which animation to pick
		mMario->vy = Mario::FLYING_Y_SPEED;
				
		mMario->vx = mMario->vx + mMario->ax*t;
		if (mMario->vx >= Mario::FLYING_X_SPEED || mMario->vx <= -Mario::FLYING_X_SPEED){
			mMario->ax = 0;
			if (mMario->vx_last<0)
				mMario->vx = -Mario::FLYING_X_SPEED;
			else mMario->vx = Mario::FLYING_X_SPEED;
		}
		mMario->dx += (mMario->vx*t);
		int temp = (int)mMario->dx;
		mMario->x += temp;
		mMario->dx -= temp;

		mMario->dy += (mMario->vy*t);
		temp = (int)(mMario->dy);
		mMario->y += temp;
		mMario->dy -= temp;

		//mMario->y += (int)(mMario->vy*t);
		//mMario->x += (int)(mMario->vx*t);
	}
	else if (GetTickCount() - timeFlying <= FLYING_TIME && mMario->vy<0){//Flying
		mMario->isFlying = 1;//for Animation Factory know which animation to pick
		mMario->vy = -Mario::FLYING_Y_SPEED;

		mMario->vx = mMario->vx + mMario->ax*t;
		if (mMario->vx >= Mario::FLYING_X_SPEED || mMario->vx <= -Mario::FLYING_X_SPEED){
			mMario->ax = 0;
			if (mMario->vx_last<0)
				mMario->vx = -Mario::FLYING_X_SPEED;
			else mMario->vx = Mario::FLYING_X_SPEED;
		}
		mMario->dx += (mMario->vx*t);
		int temp = (int)mMario->dx;
		mMario->x += temp;
		mMario->dx -= temp;

		mMario->dy += (mMario->vy*t);
		temp = (int)(mMario->dy);
		mMario->y += temp;
		mMario->dy -= temp;
		//mMario->y += (int)(mMario->vy*t);
		//mMario->x += (int)(mMario->vx*t);

	}
	else{
		mMario->isFlying = 0;
		MarioState::update(t);
	}
}

AnimationFactory* MarioStateRaccoon::getAnimationFactory(){
	return RaccoonMarioAnimationFactory::getInstance(mMario);
}

/////////////////////////MarioStateInvincible///////////////////////
const string MarioStateInvincible::STATE_NAME = "mario_invincible";
MarioStateInvincible::MarioStateInvincible(Mario* mario, MarioState* nextState):MarioState(mario){
	mLastTime = GetTickCount();
	mLastState = mario->getState();
	mNextState = nextState;
}
string MarioStateInvincible::getName(){
	return STATE_NAME;
}
void MarioStateInvincible::onCollision(Object* ob, int dir){
	DWORD now = GetTickCount();
	if (now - mLastTime >= Mario::INVINCIBLE_SWITCH_STATE_TIME){
		mMario->setState(mNextState);
	}
	string objectName = ob->getName();
	if (objectName == MetalBlock::OBJECT_NAME)
	{
		if (dir == Physics::COLLIDED_FROM_BOTTOM && mMario->top() > ob->top() && mMario->bottom() + 8 >= ob->top())//tránh trường hợp tự động đứng trên block khi chưa nhảy tới
		{
			mMario->vy = 0;
			mMario->ay = 0;
			mMario->y = ob->top() + mMario->height / 2;
			return;
		}
	}
	if (objectName == BrickGround::OBJECT_NAME || objectName == Pipe::OBJECT_NAME || objectName == QBrick::OBJECT_NAME || objectName == GoldBrick::OBJECT_NAME)
	{
		if (dir == Physics::COLLIDED_FROM_TOP){
			if (objectName == QBrick::OBJECT_NAME){
				QBrick* qBrick = (QBrick*)ob;
				qBrick->revealHiddenObject();
			}
			mMario->y = ob->bottom() - mMario->height / 2;
			mMario->vy = -0.000001;//note: không đc =0. nếu vy =0 thì sẽ gây ra lỗi người dùng có thể cho nó bay liên tục
			mMario->ay = 0;
			return;
		}
		if (dir == Physics::COLLIDED_FROM_BOTTOM)
		{
			mMario->vy = 0;
			mMario->ay = 0;
			mMario->y = ob->top() + mMario->height / 2;
			return;
		}
		if (dir == Physics::COLLIDED_FROM_RIGHT)
		{
			mMario->x = ob->left() - mMario->width / 2;
			mMario->ax = 0;
			return;
		}
		if (dir == Physics::COLLIDED_FROM_LEFT)
		{
			mMario->x = ob->right() + mMario->width / 2;
			mMario->ax = 0;
			return;
		}
	}
}

int MarioStateInvincible::getHeight(){
	return mNextState->getHeight();
}
int MarioStateInvincible::getWidth(){
	return mNextState->getWidth();
}
AnimationFactory* MarioStateInvincible::getAnimationFactory(){
	return InvincibleMarioAnimationFactory::getInstance(mMario);
}

DWORD MarioStateInvincible::getLastTime(){
	return mLastTime;
}

/////////////////////////MarioStateSuperInvincible///////////////////////
const string MarioStateSuperInvincible::STATE_NAME = "mario_super_invincible";
const int MarioStateSuperInvincible::MAINTAIN_TIME = 7000;
MarioStateSuperInvincible::MarioStateSuperInvincible(Mario* mario) :MarioState(mario){
	mDuration.start();
	if (mario!=0)
		mLastState = mario->getState();
	
}
string MarioStateSuperInvincible::getName(){
	return STATE_NAME;
}
void MarioStateSuperInvincible::onCollision(Object* ob, int dir){
	DWORD now = GetTickCount();
	if (mDuration.getIntervalTime() >= MAINTAIN_TIME){
		if (mLastState != 0){
			mMario->setState(mLastState);
		}
		else{
			mMario->setState(new MarioStateSmall(mMario));
		}
		
	}
	string objectName = ob->getName();
	if (objectName == MetalBlock::OBJECT_NAME)
	{
		if (dir == Physics::COLLIDED_FROM_BOTTOM && mMario->top() > ob->top() && mMario->bottom() + 8 >= ob->top())//tránh trường hợp tự động đứng trên block khi chưa nhảy tới
		{
			mMario->vy = 0;
			mMario->ay = 0;
			mMario->y = ob->top() + mMario->height / 2;
			return;
		}
	}
	if (objectName == BrickGround::OBJECT_NAME || objectName == Pipe::OBJECT_NAME || objectName == QBrick::OBJECT_NAME || objectName == GoldBrick::OBJECT_NAME)
	{
		if (dir == Physics::COLLIDED_FROM_TOP){
			if (objectName == QBrick::OBJECT_NAME){
				QBrick* qBrick = (QBrick*)ob;
				qBrick->revealHiddenObject();
			}
			mMario->y = ob->bottom() - mMario->height / 2;
			mMario->vy = -0.000001;//note: không đc =0. nếu vy =0 thì sẽ gây ra lỗi người dùng có thể cho nó bay liên tục
			mMario->ay = 0;
			return;
		}
		if (dir == Physics::COLLIDED_FROM_BOTTOM)
		{
			mMario->vy = 0;
			mMario->ay = 0;
			mMario->y = ob->top() + mMario->height / 2;
			return;
		}
		if (dir == Physics::COLLIDED_FROM_RIGHT)
		{
			mMario->x = ob->left() - mMario->width / 2;
			mMario->ax = 0;
			return;
		}
		if (dir == Physics::COLLIDED_FROM_LEFT)
		{
			mMario->x = ob->right() + mMario->width / 2;
			mMario->ax = 0;
			return;
		}
	}
	
}

int MarioStateSuperInvincible::getHeight(){
	return mLastState->getHeight();
}
int MarioStateSuperInvincible::getWidth(){
	return mLastState->getWidth();
}
AnimationFactory* MarioStateSuperInvincible::getAnimationFactory(){
	//return SuperInvincibleMarioAnimationFactory::getInstance(mMario);
	if (mLastState->getName() == MarioStateSmall::STATE_NAME){
		return SuperInvincibleMarioSmallAnimationFactory::getInstance(mMario);
	}
	return mLastState->getAnimationFactory();
}

int MarioStateSuperInvincible::getRemainTime(){
	return mDuration.getIntervalTime();
}

void MarioStateSuperInvincible::update(int t){
	mLastState->update(t);
}
void MarioStateSuperInvincible::onAPress(){
	mLastState->onAPress();
}
void MarioStateSuperInvincible::onBPress(){
	mLastState->onBPress();
}