﻿#include<string>
#include"MarioObject.h"
#include"MarioState.h"
#include"MarioAnimationFactory.h"
#include"sprite.h"
#include "marioGame.h"//to access global variable such at _SpriteHandler 
using namespace std;


const float Object::MAX_SPEED_Y = 0.4f;
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

Object::Object(int X, int Y, int Width, int Height, float Vx, float Vy, float vx_last, float aX, float aY, CSprite * Image) {
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
}
Object::Object(int X, int Y, int Width, int Height) {
	x = X;
	y = Y;
	width = Width;
	height = Height;
	vx = 0;
	vy = 0;
	ax = 0;// gia tốc x
	ay = 0;// gia tốc y
	
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
	
	vy += ay*t;
	vx += ax*t;
	if (vy > Object::MAX_SPEED_Y || vy < -Object::MAX_SPEED_Y){
		ay = 0;
	}
	ay -= CMarioGame::GRAVITY_VELOCOTY*t;

	dx += (int)(vx * t);
	int temp = (int)dx;
	x += temp;
	dx -= temp;
	
	dy += (int)(vy*t);
	temp = (int)dy;
	y += temp;
	dy -= temp;
	
}
Object::~Object() {
	delete mSprite;
	delete mAnim;
}

void Object::render(int vpx, int vpy){
	if (mAnim!=0)
		mAnim->Update();
	if (mSprite!=NULL)
		mSprite->Render(mAnim, x, y, vpx, vpy);
}

int Object::left() {
	return x - width / 2;
}

int Object::right() {
	return x + width / 2;
}

int Object::top() {
	return y + height / 2;
}

int Object::bottom() {
	return y - height / 2;
}

void Object::die(){
	ObjectManager::getInstance()->removeObject(this);
}
int Object::isStaticObject(){
	return 0;
}