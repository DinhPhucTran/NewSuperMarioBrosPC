#include"gooba.h"
#include <string>
#include "MarioState.h"
#include "MarioRaccoonTail.h"
#include "Qbrick.h"
#include "GoldBrick.h"

using namespace std;


const float Gooba::SPEED_X = 0.08f;
const int Gooba::WIDTH = 16;
const int Gooba::HEIGHT = 16;
const int Gooba::ANIMATION_DELAY = 10;
const int Gooba::DYING_HEIGHT = 9;
const float Gooba::DYING_SPEED = 0;
const int Gooba::DYING_TIME = 500;
Gooba::Gooba(int x, int y, int width, int height, float vx, float vy, float vx_last, float ax, float ay, Animation* anim, CSprite * image)
:Object(x, y, width, height, vx, vy, vx_last, ax, ay, anim, image){
	mAnimationFactory = new GoobaAnimationFactory(this);
	mState = new GoobaNomalState(this);
	mAnim = mAnimationFactory->createAnimation();
	mAnim->SetFrameDeplay(Gooba::ANIMATION_DELAY);
}

const string Gooba::OBJECT_NAME = "gooba";
string Gooba::getName(){
	return OBJECT_NAME;
}
void Gooba::onCollision(Object* ob,int dir){
	mState->onCollision(ob,dir);
}
GoobaState* Gooba::getState(){
	return mState;
}

void Gooba::setAnimationFactory(AnimationFactory* animFactory){
	mAnimationFactory = animFactory;
}

void Gooba::render(int vpx, int vpy){
	mSprite->Render(mAnimationFactory->createAnimation(), x, y, vpx, vpy);
}
void Gooba::setState(GoobaState* goobaState){
	delete mState;
	mState = goobaState;
	width = mState->getWidth();
	height = mState->getHeight();
	vx = mState->getSpeed();
}


/////////////////////GoobaState/////////////////////
string GoobaState::getName(){
	return "gooba_state";
}
GoobaState::GoobaState(Gooba* gooba){
	mGooba = gooba;
}

void GoobaState::onCollision(Object*ob,int dir){
	string objName = ob->getName();
	if (objName == BrickGround::OBJECT_NAME || objName == Pipe::OBJECT_NAME || objName == QBrick::OBJECT_NAME || objName == GoldBrick::OBJECT_NAME){
		if (dir == Physics::COLLIDED_FROM_LEFT){
			if (mGooba->vx_last < 0){
				mGooba->vx = Gooba::SPEED_X;
				mGooba->vx_last = mGooba->vx;
			}
		}
		else if (dir == Physics::COLLIDED_FROM_RIGHT){
			if (mGooba->vx_last > 0){
				mGooba->vx = -Gooba::SPEED_X;
				mGooba->vx_last = mGooba->vx;
			}
		}
		else if (dir == Physics::COLLIDED_FROM_BOTTOM){
			mGooba->vy = 0;
			mGooba->ay = 0;
			mGooba->y = ob->top() + mGooba->height / 2;// chỉnh lại tọa độ y
		}
		else if (dir == Physics::COLLIDED_FROM_TOP){
			if (mGooba->vy > 0){
				mGooba->vy = -0.000001;//gần bằng 0, không đc =0 sẽ gây ra lổi
				mGooba->ay = 0;
			}
		}
	}
}
int GoobaState::getWidth(){
	return Gooba::WIDTH;
}
int GoobaState::getHeight(){
	return Gooba::HEIGHT;
}
float GoobaState::getSpeed(){
	return Gooba::SPEED_X;
}

/////////////////////KoopaNomalState//////////////////

const string GoobaNomalState::STATE_NAME = "gooba_nomal_state";
string GoobaNomalState::getName(){
	return STATE_NAME;
}
void GoobaNomalState::onCollision(Object*ob,int dir){
	//xử lý va chạm, nếu chạm gạch thì quay đầu
	//chạm mario từ bên trái,phải hoặc bên dưới thì mario chết
	//chạm mario từ trên thì chuyển sang trạng thái Vulnerable;
	string objName = ob->getName();
	GoobaState::onCollision(ob, dir);
	if (objName == Mario::OBJECT_NAME){
		string marioState = ((Mario*)ob)->getState()->getName();
		if (marioState == MarioStateInvincible::STATE_NAME){
			return;
		}
		else if (dir == Physics::COLLIDED_FROM_TOP){
			mGooba->setState(new GoobaDyingState(mGooba));
		}
	}
	if (objName == KoopaTroopa::OBJECT_NAME || objName == RedKoopa::OBJECT_NAME){
		KoopaTroopa* koopa = (KoopaTroopa*)ob;
		string state = koopa->getState()->getName();
		if (state == KoopaSlidingState::STATE_NAME){
			if (dir == Physics::COLLIDED_FROM_LEFT || dir == Physics::COLLIDED_FROM_RIGHT){
				mGooba->setState(new GoobaDyingState(mGooba));
			}
		}
	}
	if (objName == MarioRaccoonTail::OBJECT_NAME && MarioRaccoonTail::getInstance()->getState()==MarioRaccoonTail::STATE_ACTIVE){
		mGooba->vy = 0.5f;
		mGooba->setState(new GoobaDyingUpsideDown(mGooba));
	}
}
GoobaNomalState::GoobaNomalState(Gooba* gooba)
	:GoobaState(gooba){

}

////////////////////GoobaDyingState////////////
GoobaDyingState::GoobaDyingState(Gooba*gooba) : GoobaState(gooba){
	last_time = GetTickCount();
}
const string GoobaDyingState::STATE_NAME = "gooba_dying_state";
string GoobaDyingState::getName(){
	return STATE_NAME;
}

void GoobaDyingState::onCollision(Object*ob, int dir){
	
	DWORD now = GetTickCount();
	if (now - last_time >= Gooba::DYING_TIME){
		mGooba->die();
		return;
	}
	GoobaState::onCollision(ob, dir);
}
int GoobaDyingState::getHeight(){
	return Gooba::DYING_HEIGHT;
}
float GoobaDyingState::getSpeed(){
	return Gooba::DYING_SPEED;
}
//////////////////////GoobaDyingUpsideDown//////////////
const string GoobaDyingUpsideDown::STATE_NAME = "goomba_dying_upside_down";
GoobaDyingUpsideDown::GoobaDyingUpsideDown(Gooba* gooba):GoobaState(gooba){
	mGooba = gooba;
}
string GoobaDyingUpsideDown::getName(){
	return STATE_NAME;
}
void GoobaDyingUpsideDown::onCollision(Object* ob, int dir){

}
//////////////////////GoobaAnimationFactory//////////////
Animation* GoobaAnimationFactory::createAnimation(){
	Animation* result;
	string stateName = mGooba->getState()->getName();
	if (stateName == GoobaNomalState::STATE_NAME){
		result = mGoobaWalkingAnim;
	}
	else if (stateName == GoobaDyingUpsideDown::STATE_NAME){
		result = mGoobaDyingUpsideDown;
	}
	else{//dying state
		result = mGoobaDyingAnim;
	}
	
	result->Update();
	return result;
}

GoobaAnimationFactory::GoobaAnimationFactory(Gooba*gooba){
	mGooba = gooba;
}