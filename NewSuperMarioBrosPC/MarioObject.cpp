#include<string>
#include"MarioObject.h"
#include"MarioState.h"
#include"MarioAnimationFactory.h"
#include"sprite.h"
#include "marioGame.h"//to access global variable such at _SpriteHandler 
using namespace std;




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

