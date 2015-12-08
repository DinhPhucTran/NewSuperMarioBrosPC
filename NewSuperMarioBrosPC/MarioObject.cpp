#include<string>
#include"MarioObject.h"
#include"MarioState.h"
#include"MarioAnimationFactory.h"
#include"sprite.h"
#include "marioGame.h"//to access global variable such at _SpriteHandler 
using namespace std;



const float Mario::ACCELERATION_X = 0.0015f;
const float Mario::MAX_SPEED_X = 0.5f;
const float Mario::MAX_SPEED_Y = 0.5f;

Mario::Mario(int x, int y, int width, int height, int vx, int vy, int vx_last, float aX, float aY, Animation* anim, CSprite * image, MarioState* state,MarioAnimationFactory* animFactory) 
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
}
const string Mario::OBJECT_NAME = "mario_object";

void Mario::onAPress(){
	Mario::mMarioState->onAPress();
}
void Mario::onBPress(){
	Mario::mMarioState->onBPress();
}
void Mario::onCollision(Object* ob){
	Mario::mMarioState->onCollision(ob);
}
string Mario::getName(){
	return Mario::OBJECT_NAME;
}

void Mario::setState(MarioState* state){
	Mario::mMarioState = state;
}
void Mario::setAnimationFactory(MarioAnimationFactory* animFactory){
	mAnimationFactory = animFactory;
}
void Mario::render(int vpx,int vpy){
	mSprite->Render(mAnimationFactory->createAnimation(), x, y, vpx, vpy);
}

void Mario::update(int t){
	x += vx*t;
	y += vy*t;
	vx = vx + ax*t;
	vy = vy + ay*t;
	if (vx >= Mario::MAX_SPEED_X || vx <= -Mario::MAX_SPEED_X){
		ax = 0;
		if (vx_last<0)
			vx = -Mario::MAX_SPEED_X;
		else vx = Mario::MAX_SPEED_X;
	}
	if (vy >= Mario::MAX_SPEED_Y || vy <= -Mario::MAX_SPEED_Y)
	{
		ay = 0;
		//vy = MAX_SPEED_Y;
	}
}