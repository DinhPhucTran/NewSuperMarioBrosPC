#include"RedKoopa.h"
#include "PiranhaPlant.h"
#include "MarioRaccoonTail.h"
#include "Physics.h"
#include "ObjectManager.h"
#include "KoopaTroopaState.h"
const string PiranhaPlant::OBJECT_NAME = "piranha_plant";
const int PiranhaPlant::HEIGHT = 24;
const int PiranhaPlant::WIDTH = 16;
const int PiranhaPlant::TIME_TO_MOVE = 1000;
const float PiranhaPlant::SPEED_Y = 0.08f;
PiranhaPlant::PiranhaPlant(int x, int y, CSprite* image, CSprite * PipeImage) :Object(x, y, WIDTH, HEIGHT, 0, 0, 0, 0, 0, image){
	mAnim = PiranhaAnimation;
	mMario = ObjectManager::getInstance()->getMario();
	mTimeToMove.start();
	mDistance = height;
	mIsGoUp = 0;
	pipeSprite = PipeImage;
	initY = y - height / 2 - PipeImage->_Height / 2 + 1;
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
			if (mDistance >= height){
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
	if (objName == KoopaTroopa::OBJECT_NAME || objName == RedKoopa::OBJECT_NAME){
		KoopaTroopa* koopa = (KoopaTroopa*)ob;
		string state = koopa->getState()->getName();
		if (state == KoopaSlidingState::STATE_NAME){
			die();
		}
	}
}

void PiranhaPlant::render(int vpx, int vpy){
	mAnim->Update();
	mSprite->Render(mAnim, x, y, vpx, vpy);
	pipeSprite->Render(pipeAnim, x, initY, vpx, vpy);
}