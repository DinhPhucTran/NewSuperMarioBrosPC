#include<string>
#include"MarioObject.h"
#include"MarioState.h"
#include"MarioAnimationFactory.h"
#include"sprite.h"
#include "marioGame.h"//to access global variable such at _SpriteHandler 
using namespace std;



const float Mario::ACCELERATION_X = 0.0015f;
const float Mario::ACCELERATION_Y = 0.006f;//0.01f;
const float Mario::ACCELERATION_Y_PLUS = 0.004f;
const float Mario::MAX_SPEED_X = 0.3f;
const float Mario::MAX_SPEED_Y = 0.5f;//0.7f
const int Mario::INVINCIBLE_SWITCH_STATE_TIME = 1000;

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
	mAnim = mAnimationFactory->createAnimation();
	isAButtonPressed = 0;
	isBButtonPressed = 0;
	isLeftButtonPressed = 0;
	isRightButtonPressed = 0;
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
	Mario::mMarioState = state;
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
	
	
	if (x <= 10)
		x = 10;
	if (x >=2800)
		x = 2800;


	x =x+ (int)(vx*t);
	y +=(int)(vy*t);
	vx = vx + ax*t;
	vy += ay*t;
	

	if (vx >= Mario::MAX_SPEED_X || vx <= -Mario::MAX_SPEED_X){
		ax = 0;
		if (vx_last<0)
			vx = -Mario::MAX_SPEED_X;
		else vx = Mario::MAX_SPEED_X;
	}
	if (vy >= Mario::MAX_SPEED_Y || vy <= -Mario::MAX_SPEED_Y)
	{
		ay = 0;
	}
	ay -= CMarioGame::GRAVITY_VELOCOTY*t;
}
void Mario::jumpUp(){
	ay = Mario::ACCELERATION_Y;
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
	if (stateName == MarioStateRaccoon::STATE_NAME){
		//delete nextState;
		nextState = new MarioStateLarge(this);
	}
	else if (stateName == MarioStateLarge::STATE_NAME){
		//delete nextState;
		nextState = (new MarioStateSmall(this));
	}
	else{
		Object::die();
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