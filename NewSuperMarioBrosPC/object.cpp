#include<string>
#include"MarioObject.h"
#include"MarioState.h"
#include"MarioAnimationFactory.h"
#include"sprite.h"
#include "marioGame.h"//to access global variable such at _SpriteHandler 
using namespace std;

const string Object::OBJECT_NAME = "game_object";
string Object::getName(){
	return OBJECT_NAME;
}
void Object::onCollision(Object* ob, int direction){
	//Object know nothing to response Collision
}
Object::Object(int X, int Y, int Width, int Height, float Vx, float Vy, float vx_last, float aX, float aY, Animation*anim, CSprite * Image) {
	x = X;
	y = Y;
	width = Width;
	height = Height;
	vx = Vx;
	vy = Vy;
	ax = aX;// gia tốc x
	ay = aY;// gia tốc y
	Object::vx_last = vx_last;
	mSprite = Image;
	mAnim = anim;
}
void Object::setAnimation(Animation* anim){
	if (anim!=NULL)
		mAnim = anim;
}

Animation* Object::getAnimation(){
	return mAnim;
}

void Object::setSprite(CSprite* sprite){
	Object::mSprite = sprite;
}
void Object::update(int t){
	x += vx * t;

	y += vy * t;
}
Object::~Object() {
	delete mSprite;
}

void Object::render(int vpx, int vpy){
	mSprite->Render(mAnim, x, y, vpx, vpy);
}