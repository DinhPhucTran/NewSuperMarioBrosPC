#include "FireBall.h"
#include "MarioObject.h"
#include "ObjectManager.h"
const string FireBall::OBJECT_NAME = "fire_ball";
const float FireBall::SPEED_X = 0.13f;
const int FireBall::HEIGHT = 9;
const int FireBall::WIDTH = 9;
const int FireBall::ANIMATION_DELAY = 2;
string FireBall::getName(){
	return OBJECT_NAME;
}

FireBall::FireBall(int x, int y, CSprite* image) :Object(x, y, WIDTH, HEIGHT, SPEED_X, 0, SPEED_X, 0, 0, image){
	mMario = ObjectManager::getInstance()->getMario();
	float dX=1, dY = 1;
	int marioX = 0, marioY = 0;
	if (mMario == 0){
		isRight = -1;
		isUp = -1;
		
	}
	else{
		marioX = mMario->x;
		marioY = mMario->y;
		if (marioX > x){
			isRight = 1;
		}
		else{
			isRight = -1;
		}
		if (marioY > y){
			isUp = 1;
		}
		else{
			isUp = -1;
		}
	}
	
	dX = abs(marioX - x);
	if (dX == 0){
		dX = 1;
	}
	dY = abs(marioY - y);
	if (dY == 0){
		dY = 1;
	}
	float ratioXY = dX / dY;
	vx = SPEED_X*isRight;
	if (ratioXY > 2.5f ){
		vy = (SPEED_X / 3)*isUp;
	}
	else{
		vy = (SPEED_X / 2)*isUp;
	}
	mFireBallAnimation = new Animation(20, 23, ANIMATION_DELAY);
	mAnim = mFireBallAnimation;
}

void FireBall::update(int t){
	//float dx = vx*t-(int)(vx*t);
	//float dy = vy*t - (int)(vx*t);
	
	dx += (vx*t);
	dy += (vy*t);
	int temp = (int)(dx);
	x += temp;
	dx -= temp;
	temp = (int)(dy);
	y += temp;
	dy -= temp;

	if (mMario == 0){
		return;
	}
	else{
		if (abs(x - mMario->x) >= 640 || abs(y - mMario->y) >= 480){
			die();
		}
	}
}
void FireBall::onCollision(Object* ob, int dir){
	
}
void FireBall::render(int vpx, int vpy){
	Object::render(vpx, vpy);
}