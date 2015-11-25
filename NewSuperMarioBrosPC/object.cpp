#include "object.h"

Object::Object(int X, int Y, int Width, int Height, int Vx, int Vy,int vx_last,Animation*anim, CSprite * Image) {
	x = X;
	y = Y;
	width = Width;
	height = Height;
	vx = Vx;
	vy = Vy;
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

Object::~Object() {
	delete mSprite;
}