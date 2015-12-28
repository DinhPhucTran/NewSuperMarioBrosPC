#include "PiranhaPlant.h"
#include "MarioRaccoonTail.h"
#include "Physics.h"
#include "ObjectManager.h"
const string PiranhaPlant::OBJECT_NAME = "piranha_plant";
const int PiranhaPlant::HEIGHT = 24;
const int PiranhaPlant::WIDTH = 16;
const int PiranhaPlant::TIME_TO_MOVE = 1000;
const float PiranhaPlant::SPEED_Y = 0.08f;
PiranhaPlant::PiranhaPlant(int x, int y, CSprite* image) :Object(x,y,WIDTH,HEIGHT,0,0,0,0,0,image){
	mAnim = PiranhaAnimation;
	mMario = ObjectManager::getInstance()->getMario();
	mTimeToMove.start();
	mDistance = HEIGHT;
	mIsGoUp = 0;
}

string PiranhaPlant::getName(){
	return OBJECT_NAME;
}

void PiranhaPlant::update(int t){
	// chuyển động lên xuống
	if (mTimeToMove.getIntervalTime() >= TIME_TO_MOVE){
		if (mMario == NULL){
			mMario = ObjectManager::getInstance()->getMario();
			return;
		}
		if (mIsGoUp==0){				
			if (mDistance < 0){
				if (abs(mMario->x - x) <= 18+8){
					return;
				}
				mIsGoUp = 1;
				mTimeToMove.start();
			}
			y -= (int)(SPEED_Y*t);
			mDistance -= (int)(SPEED_Y*t);
		}
		else if (mIsGoUp == 1 ){
			y += (int)(SPEED_Y*t);
			mDistance += (int)(SPEED_Y*t);
			if (mDistance >= HEIGHT){
				mIsGoUp = 0;
				mTimeToMove.start();
			}
		}
	}

}

void PiranhaPlant::onCollision(Object* ob, int dir){
	//va chạm với mario thì mario chết
	//va cham đuôi mario thì chết
	string objName = ob->getName();
	if (objName == MarioRaccoonTail::OBJECT_NAME ){
		MarioRaccoonTail* tail = (MarioRaccoonTail*)ob;

		string state = tail->getState();
		if (state == MarioRaccoonTail::STATE_ACTIVE){
			die();
		}
	}
}
int PiranhaPlant::isStaticObject(){//để đc render phía sau ống khói
	return 1;
}
void PiranhaPlant::render(int vpx, int vpy){
	mAnim->Update();
	mSprite->Render(mAnim, x, y, vpx, vpy);
}