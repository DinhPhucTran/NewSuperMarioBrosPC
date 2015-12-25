#include "GoldBrick.h"
#include "ObjectManager.h"
const string GoldBrick::NORMAL_STATE = "normal_gold_brick_state";
GoldBrick::GoldBrick(int x, int y, int width, int height, Animation* anim, CSprite * image) :
StaticObject(x, y, width, height, anim, image){
	
}
void GoldBrick::setState(string state){
}
string GoldBrick::getState(){
	return mState;
}
Animation* GoldBrick::createAnimation(){
	mAnimation->Update();
	return mAnimation;
}
void GoldBrick::render(int vpx, int vpy){
	mSprite->Render(createAnimation(), x, y, vpx, vpy);
}
const string GoldBrick::OBJECT_NAME = "GoldBrick";


string GoldBrick::getName()
{
	return OBJECT_NAME;
}
