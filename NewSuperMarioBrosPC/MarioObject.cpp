﻿#include<string>
#include"MarioObject.h"
#include"MarioState.h"
#include"MarioAnimationFactory.h"
#include"sprite.h"
#include "marioGame.h"//to access global variable such at _SpriteHandler 
#include "MarioPowerBar.h"
using namespace std;



const float Mario::ACCELERATION_X = 0.0006f;//0.0015f
const float Mario::FLYING_Y_SPEED = 0.14f;
const float Mario::FLYING_X_SPEED = 0.2f;//0.18f
const float Mario::ACCELERATION_Y = 0.008f;//0.01f;
const float Mario::ACCELERATION_Y_PLUS = 0.014f;//0.0103
const float Mario::MAX_SPEED_X = 0.2f;//0.3f
const float Mario::POWER_SPEED_X_PLUS = 0.09f;//khi mario full ống power chạy ở vx = MAX_SPEED_X + POWER_SPEED_X_PLUS
const float Mario::MAX_SPEED_Y = 0.35f;//0.45
const float Mario::POWER_JUMP_UP_SPEED = 0.05f;

const int Mario::INVINCIBLE_SWITCH_STATE_TIME = 2000;
const int Mario::SITDOWN_HEIGHT = 16;
const int Mario::SITDOWN_WIDTH = 16;

MarioState* Mario::getState(){
	return mMarioState;
}
Mario::Mario(int x, int y, int width, int height, int vx, int vy, int vx_last, float aX, float aY, Animation* anim, CSprite * image, MarioState* state,AnimationFactory* animFactory) 
	: Object(x, y, width, height, vx, vy, vx_last, aX, aY, anim, image){
	if (state != NULL){
		mMarioState = state;
	}
	else{
		mMarioState = new MarioStateSmall(this);
	}
	if (animFactory != NULL){
		mAnimationFactory = animFactory;
	}
	else{
		mAnimationFactory = SmallMarioAnimationFactory::getInstance(this);
	}
	mPowerBar = new MarioPowerBar(this);
	mAnim = mAnimationFactory->createAnimation();
	
	isAButtonPressed = 0;
	isBButtonPressed = 0;
	isLeftButtonPressed = 0;
	isRightButtonPressed = 0;
	isKickKoopa.reset();
	score = 0;
}

Mario::~Mario()
{
	delete mMarioState;
	delete mPowerBar;
}
const string Mario::OBJECT_NAME = "mario_object";

void Mario::onAPress(){
	Mario::mMarioState->onAPress();
}
void Mario::onBPress(){
	Mario::mMarioState->onBPress();
}
void Mario::onCollision(Object* ob,int dir){
	Mario::mMarioState->onCollision(ob,dir);
}
string Mario::getName(){
	return Mario::OBJECT_NAME;
}

void Mario::setState(MarioState* state){
	mMarioState = state;
	string stateName = state->getName();
	width = state->getWidth();
	height = state->getHeight();
	setAnimationFactory(state->getAnimationFactory());
}
void Mario::setAnimationFactory(AnimationFactory* animFactory){
	mAnimationFactory = animFactory;
}
void Mario::render(int vpx,int vpy){
	mSprite->Render(mAnimationFactory->createAnimation(), x, y, vpx, vpy);
}

void Mario::update(int t){
	
	mMarioState->update(t);
	///for powerBar
	if ((isBButtonPressed && isLeftButtonPressed && isRightButtonPressed==0) || (isBButtonPressed && isRightButtonPressed && isLeftButtonPressed==0)){//&&isFlying ==0;
		if (!mPowerBar->isStarted()&&!mPowerBar->isPower()){
			mPowerBar->start();
		}
	}
	else{
		mPowerBar->reset();
	}
	
	mPowerBar->update();
}

MarioPowerBar* Mario::getPowerBar(){
	return mPowerBar;
}
void Mario::jumpUp(){
	if (vy==0)
		ay = Mario::ACCELERATION_Y;
}
void Mario::powerJumpUp(){
	if (vy == 0){
		ay = Mario::ACCELERATION_Y_PLUS;
	}
}
void Mario::sitDown(){
	if (vy == 0 && vx==0)
	{
		width = 16;
		height = 16;
		isSitDown = 1;
	}
}
void Mario::standUp(){
	if (isSitDown == 1){
		width = getState()->getWidth();
		height = getState()->getHeight();
		isSitDown = 0;
	}
}
void Mario::stop(){
	vx = 0;
	vy = 0;
	ax = 0;
	ay = 0;
}
void Mario::die(){
	string stateName = mMarioState->getName();
	MarioState* nextState = new MarioStateSmall(this);
	if (stateName == MarioStateInvincible::STATE_NAME){
		return;
	}
	if (stateName == MarioStateRaccoon::STATE_NAME){
		//delete nextState;
		nextState = new MarioStateLarge(this);
	}
	else if (stateName == MarioStateLarge::STATE_NAME){
		//delete nextState;
		nextState = (new MarioStateSmall(this));
	}
	else{
		setState(new MarioStateDie(this));
		lives--;
		return;
	}
	setState(new MarioStateInvincible(this, nextState));
	/*y += 50;
	string stateName = mMarioState->getName();
	MarioState* nextState = new MarioStateSmall(this);
	if (stateName == MarioStateRaccoon::STATE_NAME){
		
		nextState = new MarioStateLarge(this);
	}
	else if (stateName == MarioStateLarge::STATE_NAME){
		
		nextState = (new MarioStateSmall(this));
	}
	else{
		Object::die();
	}
	setState(nextState);*/
}