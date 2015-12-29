#include "FirePiranha.h"
#include "FirePiranhaAnimationFactory.h"
#include "PiranhaPlant.h"
#include "FireBall.h"

string const FirePiranha::OBJECT_NAME = "fire_piranha_plant";

const int FirePiranha::FIRE_PIRANHA_HEIGHT = 24;
const int FirePiranha::FIRE_PIRANHA_WIDTH = 16;
const int FirePiranha::FIRE_PIRANHA_TIME_TO_MOVE = 1900;

FirePiranha::FirePiranha(int x, int y, CSprite* image, CSprite* pipeImage):PiranhaPlant(x,y,image,pipeImage){
	height = FIRE_PIRANHA_HEIGHT;
	width = FIRE_PIRANHA_WIDTH;
	mAnimFactory = new FirePiranhaAnimationFactory(this, mMario);
}

string FirePiranha::getName(){
	return FirePiranha::OBJECT_NAME;
}

void FirePiranha::update(int t){
	// chuyển động lên xuống
	if (mTimeToMove.getIntervalTime() >= FIRE_PIRANHA_TIME_TO_MOVE){
		if (mDistance < 0 && abs(mMario->x - x) <= 18 + 12){
			return;
		}
		if (mMario == NULL){
			mMario = ObjectManager::getInstance()->getMario();
			return;
		}
		if (mIsGoUp == 0){
			mIsShooting = 0;
			if (mDistance < 0){
				mIsGoUp = 1;
				mTimeToMove.start();
			}
			y -= (int)(SPEED_Y*t);
			mDistance -= (int)(SPEED_Y*t);
		}
		else if (mIsGoUp == 1){
			y += (int)(SPEED_Y*t);
			mDistance += (int)(SPEED_Y*t);
			if (mDistance >= height+5){//5 là khoảng không để mario ko va chạm với cây ăn thịt
				mIsGoUp = 0;
				mTimeToMove.start();
				//if (mTimeToMove.getIntervalTime() >= FIRE_PIRANHA_TIME_TO_MOVE / 2 && mIsShooting==0){
					mIsShooting = 1;
					shooting();
				//}
				
			}
		}
	}
}
void FirePiranha::render(int vpx, int vpy){
	mSprite->Render(mAnimFactory->createAnimation(), x, y, vpx, vpy);
	pipeSprite->Render(x, initY, vpx, vpy);
}
int FirePiranha::isShooting(){
	return mIsShooting;
}
void FirePiranha::shooting(){
	//shootting a fire
	FireBall* fireBall = new FireBall(x, y, mSprite);//fireball sprite nằm chung với FirePiranha
	ObjectManager::getInstance()->addObject(fireBall);
}