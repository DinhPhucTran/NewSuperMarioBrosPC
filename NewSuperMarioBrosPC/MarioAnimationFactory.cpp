﻿#include"MarioAnimationFactory.h"
#include "MarioPowerBar.h"
#include<string>
#include"game.h"
#include"MarioState.h"
#include "MarioRaccoonTail.h"
using namespace std;


SmallMarioAnimationFactory::SmallMarioAnimationFactory(Mario* mario){
	mMario = mario;
}

Animation* SmallMarioAnimationFactory::createAnimation(){
	Animation* result;
	int isPower;
	if (mMario->getPowerBar() == NULL){
		isPower = 0;
	}
	else
	{
		isPower = mMario->getPowerBar()->isPower();
	}
	
	if (mMario->vy > 0)//vy>0 => mario nhảy lên, vy<0 =>mario đang rớt xuống
	{
		if (mMario->vx_last < 0)//quay trái
		{
			if (isPower){
				result = powerJumpLeft;
			}
			else{
				result = leftJumpUpAnim;
			}
		}
		else{
			if (isPower){
				result = powerJumpRight;
			}
			else{
				result = rightJumpUpAnim;
			}
		}
	}
	else if (mMario->vy == 0)
	{//vy==0 mario đang đứng trên vật thể 
		if (mMario->vx_last < 0)//quay trái
		{
			if (mMario->ax > 0 && mMario->isRightButtonPressed == 1){//quay phải
				result = turnRightAnimation;
			}
			else if (mMario->vx != 0)//mario đang đi
				result = leftWalkAnim;
			else{//mario đang đứng yên
				result = leftStandAnim;
			}
		}
		else{//vx_last >0 mario đang đi trái
			if (mMario->ax < 0 && mMario->isLeftButtonPressed == 1)//đang đổi hướng
			{
				result = turnLeftAnimation;
			}
			else if (mMario->vx != 0)//đang đi phải
				result = rightWalkAnim;
			else
				result = rightStandAnim;
		}
	}
	else 
	{//mario đang rơi
		if (mMario->vx_last < 0)//quay trái
		{
			result = leftJumpDownAnim;
			if (isPower){
				result == powerJumpLeft;
			}
		}
		else{
			result = rightJumpDownAnim;
			if (isPower){
				result = powerJumpRight;
			}
		}
	}
	result->Update();
	return result;
}

SmallMarioAnimationFactory::~SmallMarioAnimationFactory(){
	
	delete leftWalkAnim;
	delete rightWalkAnim;
	delete leftStandAnim;
	delete rightStandAnim;
}
SmallMarioAnimationFactory* SmallMarioAnimationFactory::sInstance;//define singleton
SmallMarioAnimationFactory* SmallMarioAnimationFactory::getInstance(Mario* mario){
	if (SmallMarioAnimationFactory::sInstance == NULL){
		SmallMarioAnimationFactory::sInstance = new SmallMarioAnimationFactory(mario);
	}
	else
		sInstance->mMario = mario;
	return sInstance;
}
//================LargeMarioAnimationFactory========================
LargeMarioAnimationFactory::LargeMarioAnimationFactory(Mario* mario){
	mMario = mario;
}

//define singleton
LargeMarioAnimationFactory* LargeMarioAnimationFactory::sInstance;
LargeMarioAnimationFactory* LargeMarioAnimationFactory::getInstance(Mario* mario){
	if (sInstance == NULL){
		sInstance = new LargeMarioAnimationFactory(mario);
	}
	else
		sInstance->mMario = mario;
	return sInstance;
}

Animation* LargeMarioAnimationFactory::createAnimation(){
	Animation* result;
	int isPower = mMario->getPowerBar()->isPower();
	if (mMario->vy > 0)//vy>0 => mario nhảy lên, vy<0 =>mario đang rớt xuống
	{
		if (isPower){
			if (mMario->vx_last < 0)//quay trái
				result = powerJumpLeft;
			else
				result = powerJumpRight;
		}
		else{
			if (mMario->vx_last < 0)//quay trái
				result = leftJumpUpAnim;
			else
				result = rightJumpUpAnim;
		}
		
	}
	else if (mMario->isKickKoopa.isReset() == 0 && mMario->isBButtonPressed == 0){
		if (mMario->vx_last < 0)//quay trái
			result = kickKoopaLeft;
		else
			result = kickKoopaRight;
	}
	else if (mMario->isSitDown){
		if (mMario->vx_last < 0)//quay trái
			result = sitDownLeft;
		else
			result = sitDownRight;
	}
	else if (mMario->vy == 0)
	{//vy==0 mario đang đứng trên vật thể 
		if (mMario->vx_last < 0)//quay trái
		{
			if (mMario->ax > 0 && mMario->isRightButtonPressed == 1){//quay phải
				result = turnRightAnimation;
			}
			else if (mMario->vx != 0)//mario đang đi
			{
				if (isPower){
					result = powerRunLeft;
				}
				else{
					result = leftWalkAnim;
				}
			}
			else{//mario đang đứng yên
				result = leftStandAnim;
			}
		}
		else{//vx_last >0 mario đang đi trái
			if (mMario->ax < 0 && mMario->isLeftButtonPressed == 1)//đang đổi hướng
			{
				result = turnLeftAnimation;
			}
			else if (mMario->vx != 0)//đang đi phải
			{
				if (isPower){
					result = powerRunRight;
				}
				else{
					result = rightWalkAnim;
				}
			}
			else
				result = rightStandAnim;
		}
	}
	else {//mario đang rơi
		if (mMario->vx_last < 0)//quay trái
		{
			result = leftJumpDownAnim;
		}
		else
			result = rightJumpDownAnim;
	}
	result->Update();
	return result;
}

LargeMarioAnimationFactory::~LargeMarioAnimationFactory(){

	delete leftWalkAnim;
	delete rightWalkAnim;
	delete leftStandAnim;
	delete rightStandAnim;
	
}

///==============================Mario Raccoon============================
RaccoonMarioAnimationFactory::RaccoonMarioAnimationFactory(Mario* mario){
	mMario = mario;
}

//define singleton
RaccoonMarioAnimationFactory* RaccoonMarioAnimationFactory::sInstance;
RaccoonMarioAnimationFactory* RaccoonMarioAnimationFactory::getInstance(Mario* mario){
	if (sInstance == NULL){
		sInstance = new RaccoonMarioAnimationFactory(mario);
	}
	else
		sInstance->mMario = mario;
	return sInstance;
}

Animation* RaccoonMarioAnimationFactory::createAnimation(){
	Animation* result;
	MarioRaccoonTail* tail = MarioRaccoonTail::getInstance();
	if (tail->getState()==MarioRaccoonTail::STATE_ACTIVE){
		if (tail->mDirection == MarioRaccoonTail::DIRECTION_FRONT){
			result = RaccoonTailFront;
		}
		else if (tail->mDirection == MarioRaccoonTail::DIRECTION_BACK){
			result = RaccoonTailBack;
		} 
		else if (tail->mDirection == MarioRaccoonTail::DIRECTION_LEFT){
			result = RaccoonTailLeft;
		}
		else {
			result = RaccoonTailRight;
		}
	}
	else if (mMario->isFlying==1){
		if (mMario->vy > 0){//flying up
			if (mMario->vx_last < 0)//quay trái
			{
				result = RaccoonFlyingUpLeft;
				result->Update();
				return result;
			}
			else{
				result = RaccoonFlyingUpRight;
				result->Update();
				return result;
			}
		}
		else {//flying down
			if (mMario->vx_last < 0)//quay trái
			{
				result = RaccoonFlyingLeft;
				result->Update();
				return result;
			}
			else{
				result = RaccoonFlyingRight;
				result->Update();
				return result;
			}
		}
	}
	else if (mMario->isSitDown){
		if (mMario->vx_last < 0)//quay trái
			result = sitDownLeft;
		else
			result = sitDownRight;
	}
	else if (mMario->isKickKoopa.isReset()==0 && mMario->isBButtonPressed == 0){
		if (mMario->vx_last < 0)//quay trái
			result = kickKoopaLeft;
		else
			result = kickKoopaRight;
	}
	else if (mMario->getPowerBar()->isPower()&&mMario->vx!=0){
		if (mMario->vx_last > 0){
			result = powerRunRight;
		}
		else{
			result = powerRunLeft;
		}
	}
	else if (mMario->vy > 0)//vy>0 => mario nhảy lên, vy<0 =>mario đang rớt xuống
	{
		if (mMario->vx_last < 0)//quay trái
			result = leftJumpUpAnim;
		else
			result = rightJumpUpAnim;
	}
	else if(mMario->vy==0)
	{//vy==0 mario đang đứng trên vật thể 
		if (mMario->vx_last < 0)//quay trái
		{
			if (mMario->ax > 0 && mMario->isRightButtonPressed == 1){//quay phải
				result = turnRightAnimation;
			}
			else if (mMario->vx != 0)//mario đang đi
				result = leftWalkAnim;
			else{//mario đang đứng yên
				result = leftStandAnim;
			}
		}
		else{//vx_last >0 mario đang đi trái
			if (mMario->ax < 0 && mMario->isLeftButtonPressed==1)//đang đổi hướng
			{
				result = turnLeftAnimation;
			}else if (mMario->vx != 0)//đang đi phải
				result = rightWalkAnim;
			else
				result = rightStandAnim;
		}
	}
	else {//mario đang rơi
		if (mMario->vx_last < 0)//quay trái
		{
			result = leftJumpDownAnim;
		}else
			result = rightJumpDownAnim;
	}
	
	int frameDelay = result->frameDelay;
	float statePower = mMario->getPowerBar()->getState();
	if (statePower >= 0.1){
		if (frameDelay == Animation::FRAME_DELAY_DEFAULT){
			//result->SetFrameDeplay(Animation::FRAME_DELAY_DEFAULT- (float)(Animation::FRAME_DELAY_DEFAULT*statePower));
			result->SetFrameDeplay(4);
		}
	}
	else if (statePower >= 0.4){
		result->SetFrameDeplay(3);
	}
	else if (statePower >= 0.8 ){
		result->SetFrameDeplay(2);
	}
	else{
		result->SetFrameDeplay(Animation::FRAME_DELAY_DEFAULT);
	}
	result->Update();
	return result;
}

RaccoonMarioAnimationFactory::~RaccoonMarioAnimationFactory(){

	delete leftWalkAnim;
	delete rightWalkAnim;
	delete leftStandAnim;
	delete rightStandAnim;

}
////////////////////////////////InvincibleMarioAnimationFactory////////
InvincibleMarioAnimationFactory::InvincibleMarioAnimationFactory(Mario* mario){
	mMario = mario;
	isBlanked = false;
}
InvincibleMarioAnimationFactory* InvincibleMarioAnimationFactory::sInstance;
InvincibleMarioAnimationFactory* InvincibleMarioAnimationFactory::getInstance(Mario* mario){
	if (sInstance == NULL){
		sInstance = new InvincibleMarioAnimationFactory(mario);
	}
	else
		sInstance->mMario = mario;
	return sInstance;
}

Animation* InvincibleMarioAnimationFactory::createAnimation(){
	Animation* result;
	DWORD now = GetTickCount();
	MarioStateInvincible * state =(MarioStateInvincible*)mMario->getState();
	MarioState* lastState = state->mLastState;
	MarioState* nextState = state->mNextState;
	if ((now - state->getLastTime()) <= Mario::INVINCIBLE_SWITCH_STATE_TIME / 2){
		result = lastState->getAnimationFactory()->createAnimation();
	}
	else{
		result = nextState->getAnimationFactory()->createAnimation();
	}
	if (isBlanked){
		isBlanked = false;
		return result;
	}
	else{
		isBlanked = true;
		return blankAnimation;
	}
	
}


///////////////////////////////
SuperInvincibleMarioSmallAnimationFactory::SuperInvincibleMarioSmallAnimationFactory(Mario* mario){
	mMario = mario;
}

Animation* SuperInvincibleMarioSmallAnimationFactory::createAnimation(){
	Animation* result;
	int isPower;
	if (mMario->getPowerBar() == NULL){
		isPower = 0;
	}
	else
	{
		isPower = mMario->getPowerBar()->isPower();
	}

	if (mMario->vy > 0)//vy>0 => mario nhảy lên, vy<0 =>mario đang rớt xuống
	{
		if (mMario->vx_last < 0)//quay trái
		{
			if (isPower){
				result = powerJumpLeft;
			}
			else{
				result = leftJumpUpAnim;
			}
		}
		else{
			if (isPower){
				result = powerJumpRight;
			}
			else{
				result = rightJumpUpAnim;
			}
		}
	}
	else if (mMario->vy == 0)
	{//vy==0 mario đang đứng trên vật thể 
		if (mMario->vx_last < 0)//quay trái
		{
			if (mMario->ax > 0 && mMario->isRightButtonPressed == 1){//quay phải
				result = turnRightAnimation;
			}
			else if (mMario->vx != 0)//mario đang đi
				result = leftWalkAnim;
			else{//mario đang đứng yên
				result = leftStandAnim;
			}
		}
		else{//vx_last >0 mario đang đi trái
			if (mMario->ax < 0 && mMario->isLeftButtonPressed == 1)//đang đổi hướng
			{
				result = turnLeftAnimation;
			}
			else if (mMario->vx != 0)//đang đi phải
				result = rightWalkAnim;
			else
				result = rightStandAnim;
		}
	}
	else
	{//mario đang rơi
		if (mMario->vx_last < 0)//quay trái
		{
			result = leftJumpDownAnim;
			if (isPower){
				result == powerJumpLeft;
			}
		}
		else{
			result = rightJumpDownAnim;
			if (isPower){
				result = powerJumpRight;
			}
		}
	}
	result->Update();
	return result;
}



SuperInvincibleMarioSmallAnimationFactory* SuperInvincibleMarioSmallAnimationFactory::sInstance;//define singleton
SuperInvincibleMarioSmallAnimationFactory* SuperInvincibleMarioSmallAnimationFactory::getInstance(Mario* mario){
	if (SuperInvincibleMarioSmallAnimationFactory::sInstance == NULL){
		SuperInvincibleMarioSmallAnimationFactory::sInstance = new SuperInvincibleMarioSmallAnimationFactory(mario);
	}
	else
		sInstance->mMario = mario;
	return sInstance;
}
////////////////////////////////////////////////////////////
SuperRaccoonMarioAnimationFactory::SuperRaccoonMarioAnimationFactory(Mario* mario){
	mMario = mario;
}

//define singleton
SuperRaccoonMarioAnimationFactory* SuperRaccoonMarioAnimationFactory::sInstance;
SuperRaccoonMarioAnimationFactory* SuperRaccoonMarioAnimationFactory::getInstance(Mario* mario){
	if (sInstance == NULL){
		sInstance = new SuperRaccoonMarioAnimationFactory(mario);
	}
	else
		sInstance->mMario = mario;
	return sInstance;
}

Animation* SuperRaccoonMarioAnimationFactory::createAnimation(){
	Animation* result;
	MarioRaccoonTail* tail = MarioRaccoonTail::getInstance();
	if (tail->getState() == MarioRaccoonTail::STATE_ACTIVE){
		if (tail->mDirection == MarioRaccoonTail::DIRECTION_FRONT){
			result = RaccoonTailFront;
		}
		else if (tail->mDirection == MarioRaccoonTail::DIRECTION_BACK){
			result = RaccoonTailBack;
		}
		else if (tail->mDirection == MarioRaccoonTail::DIRECTION_LEFT){
			result = RaccoonTailLeft;
		}
		else {
			result = RaccoonTailRight;
		}
	}
	else if (mMario->isFlying == 1){
		if (mMario->vy > 0){//flying up
			if (mMario->vx_last < 0)//quay trái
				result = RaccoonFlyingUpLeft;				
			else
				result = RaccoonFlyingUpRight;
		}
		else {//flying down
			if (mMario->vx_last < 0)//quay trái
			{//result = RaccoonFlyingLeft;
				result = RollLeft;
				result->Update();
				return result;
			}				
			else{
				//result = RaccoonFlyingRight;
				result = RollRight;
				result->Update();
				return result;
			}	
		}
	}
	else if (mMario->isSitDown){
		if (mMario->vx_last < 0)//quay trái
			result = sitDownLeft;
		else
			result = sitDownRight;
	}
	else if (mMario->isKickKoopa.isReset() == 0 && mMario->isBButtonPressed == 0){
		if (mMario->vx_last < 0)//quay trái
			result = kickKoopaLeft;
		else
			result = kickKoopaRight;
	}
	else if (mMario->getPowerBar()->isPower() && mMario->vx != 0){
		if (mMario->vx_last > 0){
			result = powerRunRight;
		}
		else{
			result = powerRunLeft;
		}
	}
	else if (mMario->vy > 0)//vy>0 => mario nhảy lên, vy<0 =>mario đang rớt xuống
	{
		if (mMario->vx_last < 0)//quay trái
		{
			//result = leftJumpUpAnim;
			result = RollLeft;
			result->Update();
			return result;
		}
		else{
			//result = rightJumpUpAnim;
			result = RollRight;
			result->Update();
			return result;
		}
	}
	else if (mMario->vy == 0)
	{//vy==0 mario đang đứng trên vật thể 
		if (mMario->vx_last < 0)//quay trái
		{
			if (mMario->ax > 0 && mMario->isRightButtonPressed == 1){//quay phải
				result = turnRightAnimation;
			}
			else if (mMario->vx != 0)//mario đang đi
				result = leftWalkAnim;
			else{//mario đang đứng yên
				result = leftStandAnim;
			}
		}
		else{//vx_last >0 mario đang đi trái
			if (mMario->ax < 0 && mMario->isLeftButtonPressed == 1)//đang đổi hướng
			{
				result = turnLeftAnimation;
			}
			else if (mMario->vx != 0)//đang đi phải
				result = rightWalkAnim;
			else
				result = rightStandAnim;
		}
	}
	else {//mario đang rơi
		if (mMario->vx_last < 0)//quay trái
		{
			//result = leftJumpDownAnim;
			result = RollLeft;
			result->Update();
			return result;
		}
		else{
			//result = rightJumpDownAnim;
			result = RollRight;
			result->Update();
			return result;
		}
			
	}

	int frameDelay = result->frameDelay;
	float statePower = mMario->getPowerBar()->getState();
	if (statePower >= 0.1){
		if (frameDelay == Animation::FRAME_DELAY_DEFAULT){
			//result->SetFrameDeplay(Animation::FRAME_DELAY_DEFAULT- (float)(Animation::FRAME_DELAY_DEFAULT*statePower));
			result->SetFrameDeplay(4);
		}
	}
	else if (statePower >= 0.4){
		result->SetFrameDeplay(3);
	}
	else if (statePower >= 0.8){
		result->SetFrameDeplay(2);
	}
	else{
		result->SetFrameDeplay(Animation::FRAME_DELAY_DEFAULT);
	}
	result->Update();
	return result;
}

SuperRaccoonMarioAnimationFactory::~SuperRaccoonMarioAnimationFactory(){

	delete leftWalkAnim;
	delete rightWalkAnim;
	delete leftStandAnim;
	delete rightStandAnim;

}


//================SuperLargeMarioAnimationFactory========================
SuperLargeMarioAnimationFactory::SuperLargeMarioAnimationFactory(Mario* mario){
	mMario = mario;
}

//define singleton
SuperLargeMarioAnimationFactory* SuperLargeMarioAnimationFactory::sInstance;
SuperLargeMarioAnimationFactory* SuperLargeMarioAnimationFactory::getInstance(Mario* mario){
	if (sInstance == NULL){
		sInstance = new SuperLargeMarioAnimationFactory(mario);
	}
	else
		sInstance->mMario = mario;
	return sInstance;
}

Animation* SuperLargeMarioAnimationFactory::createAnimation(){
	Animation* result;
	int isPower = mMario->getPowerBar()->isPower();
	if (mMario->vy > 0)//vy>0 => mario nhảy lên, vy<0 =>mario đang rớt xuống
	{
		if (isPower){
			if (mMario->vx_last < 0)//quay trái
			{
				result = powerJumpLeft;
			}
			else
				result = powerJumpRight;
		}
		else{
			if (mMario->vx_last < 0)//quay trái
			{
				//left jump UP
				result = RollLeft;
				result->Update();
				return result;
			}
			else{
				//result = rightJumpUpAnim;
				result = RollLeft;
				result->Update();
				return result;
			}
		}

	}
	else if (mMario->isKickKoopa.isReset() == 0 && mMario->isBButtonPressed == 0){
		if (mMario->vx_last < 0)//quay trái
			result = kickKoopaLeft;
		else
			result = kickKoopaRight;
	}
	else if (mMario->isSitDown){
		if (mMario->vx_last < 0)//quay trái
			result = sitDownLeft;
		else
			result = sitDownRight;
	}
	else if (mMario->vy == 0)
	{//vy==0 mario đang đứng trên vật thể 
		if (mMario->vx_last < 0)//quay trái
		{
			if (mMario->ax > 0 && mMario->isRightButtonPressed == 1){//quay phải
				result = turnRightAnimation;
			}
			else if (mMario->vx != 0)//mario đang đi
			{
				if (isPower){
					result = powerRunLeft;
				}
				else{
					result = leftWalkAnim;
				}
			}
			else{//mario đang đứng yên
				result = leftStandAnim;
			}
		}
		else{//vx_last >0 mario đang đi trái
			if (mMario->ax < 0 && mMario->isLeftButtonPressed == 1)//đang đổi hướng
			{
				result = turnLeftAnimation;
			}
			else if (mMario->vx != 0)//đang đi phải
			{
				if (isPower){
					result = powerRunRight;
				}
				else{
					result = rightWalkAnim;
				}
			}
			else
				result = rightStandAnim;
		}
	}
	else {//mario đang rơi
		if (mMario->vx_last < 0)//quay trái
		{
			//result = leftJumpDownAnim;
			result = RollLeft;
			result->Update();
			return result;
		}
		else{
			//result = rightJumpDownAnim;
			result = RollRight;
			result->Update();
			return result;
		}
	}
	result->Update();
	return result;
}

SuperLargeMarioAnimationFactory::~SuperLargeMarioAnimationFactory(){

	delete leftWalkAnim;
	delete rightWalkAnim;
	delete leftStandAnim;
	delete rightStandAnim;

}
///////////////////////////DieAnimationFactory

DieAnimationFactory* DieAnimationFactory::sInstance;
DieAnimationFactory::DieAnimationFactory(Mario* mario){
	mMario - mario;
}
DieAnimationFactory* DieAnimationFactory::getInstance(Mario* mario){
	if (sInstance == 0){
		sInstance = new DieAnimationFactory(mario);
	}
	return sInstance;
}
Animation* DieAnimationFactory::createAnimation(){
	mDieAnimation->Update();
	return mDieAnimation;
}


/////MarioGoingToBonusRoomAnimationFactories
MarioSmallGoingToBonusRoomAnimationFactory::MarioSmallGoingToBonusRoomAnimationFactory(Mario* mario){
	mMario = mario;
}

Animation* MarioSmallGoingToBonusRoomAnimationFactory::createAnimation(){
	Animation* result;
	result = anim;
	return result;
}

MarioSmallGoingToBonusRoomAnimationFactory* MarioSmallGoingToBonusRoomAnimationFactory::sInstance;//define singleton
MarioSmallGoingToBonusRoomAnimationFactory* MarioSmallGoingToBonusRoomAnimationFactory::getInstance(Mario* mario){
	if (MarioSmallGoingToBonusRoomAnimationFactory::sInstance == NULL){
		MarioSmallGoingToBonusRoomAnimationFactory::sInstance = new MarioSmallGoingToBonusRoomAnimationFactory(mario);
	}
	else
		sInstance->mMario = mario;
	return sInstance;
}

MarioBigGoingToBonusRoomAnimationFactory::MarioBigGoingToBonusRoomAnimationFactory(Mario* mario){
	mMario = mario;
}

Animation* MarioBigGoingToBonusRoomAnimationFactory::createAnimation(){
	Animation* result;
	result = anim;
	return result;
}

MarioBigGoingToBonusRoomAnimationFactory* MarioBigGoingToBonusRoomAnimationFactory::sInstance;//define singleton
MarioBigGoingToBonusRoomAnimationFactory* MarioBigGoingToBonusRoomAnimationFactory::getInstance(Mario* mario){
	if (MarioBigGoingToBonusRoomAnimationFactory::sInstance == NULL){
		MarioBigGoingToBonusRoomAnimationFactory::sInstance = new MarioBigGoingToBonusRoomAnimationFactory(mario);
	}
	else
		sInstance->mMario = mario;
	return sInstance;
}

MarioRaccoonGoingToBonusRoomAnimationFactory::MarioRaccoonGoingToBonusRoomAnimationFactory(Mario* mario){
	mMario = mario;
}

Animation* MarioRaccoonGoingToBonusRoomAnimationFactory::createAnimation(){
	Animation* result;
	result = anim;
	return result;
}

MarioRaccoonGoingToBonusRoomAnimationFactory* MarioRaccoonGoingToBonusRoomAnimationFactory::sInstance;//define singleton
MarioRaccoonGoingToBonusRoomAnimationFactory* MarioRaccoonGoingToBonusRoomAnimationFactory::getInstance(Mario* mario){
	if (MarioRaccoonGoingToBonusRoomAnimationFactory::sInstance == NULL){
		MarioRaccoonGoingToBonusRoomAnimationFactory::sInstance = new MarioRaccoonGoingToBonusRoomAnimationFactory(mario);
	}
	else
		sInstance->mMario = mario;
	return sInstance;
}