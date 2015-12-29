#include "FirePiranha.h"
#include "FirePiranhaAnimationFactory.h"
#include "PiranhaPlant.h"

string const FirePiranha::OBJECT_NAME = "fire_piranha_plant";

const int FirePiranha::FIRE_PIRANHA_HEIGHT = 24;
const int FirePiranha::FIRE_PIRANHA_WIDTH = 16;
const int FirePiranha::FIRE_PIRANHA_TIME_TO_MOVE = 1800;

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
		if (mMario == NULL){
			mMario = ObjectManager::getInstance()->getMario();
			return;
		}
		if (mIsGoUp == 0){
			mIsShooting = 0;
			if (mDistance < 0){
				if (abs(mMario->x - x) <= 18 + 8){
					return;
				}
				mIsGoUp = 1;
				mTimeToMove.start();
			}
			y -= (int)(SPEED_Y*t);
			mDistance -= (int)(SPEED_Y*t);
		}
		else if (mIsGoUp == 1){
			y += (int)(SPEED_Y*t);
			mDistance += (int)(SPEED_Y*t);
			if (mDistance >= height){
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
}