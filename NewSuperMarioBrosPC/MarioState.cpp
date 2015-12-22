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

#include <string>
using namespace std;

//================STATE====================
MarioState::MarioState(Mario* mario){
	mMario = mario;
}
void MarioState::onAPress(){
	mMario->jumpUp();
}
void MarioState::onBPress(){
	
}
void MarioState::onCollision(Object* ob,int dir){
	string objectName = ob->getName();
	if (objectName == MetalBlock::OBJECT_NAME)
	{
		if (dir == Physics::COLLIDED_FROM_BOTTOM && mMario->top() >= ob->top())
		{
			mMario->vy = 0;
			mMario->ay = 0;
			mMario->y = ob->top() + mMario->height / 2;
			return;
		}
	}
	if (objectName == BrickGround::OBJECT_NAME || objectName == Pipe::OBJECT_NAME || objectName == QBrick::OBJECT_NAME)
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
	if (objectName == KoopaTroopa::OBJECT_NAME || objectName == RedKoopa::OBJECT_NAME){
		KoopaTroopa* koopa = (KoopaTroopa*)ob;
		string state = koopa->getState()->getName();
		if (state == KoopaNomalState::STATE_NAME){
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
		if (state == GoobaNomalState::STATE_NAME){
			if (dir == Physics::COLLIDED_FROM_BOTTOM){
				mMario->y = ob->top() + mMario->height / 2;
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
		mMario->setState(new MarioStateLarge(mMario));
	}
	if (objectName == GreenMushroom::OBJECT_NAME){
		
	}
	if (objectName == Leaf::OBJECT_NAME){
		mMario->setState(new MarioStateRaccoon(mMario));
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
	mMario->jumpUp();
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
	mMario->jumpUp();
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
MarioStateRaccoon::MarioStateRaccoon(Mario* mario) :MarioState(mario){

}
string MarioStateRaccoon::getName(){
	return STATE_NAME;
}

void MarioStateRaccoon::onAPress(){
	mMario->jumpUp();
}
void MarioStateRaccoon::onBPress(){
	//do nothing;
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
	if (objectName == BrickGround::OBJECT_NAME || objectName == Pipe::OBJECT_NAME)
	{
		if (dir == Physics::COLLIDED_FROM_TOP){
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