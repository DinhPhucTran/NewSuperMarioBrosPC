﻿#include "MarioRaccoonTail.h"
#include "ObjectManager.h"

const string MarioRaccoonTail::OBJECT_NAME = "mario_raccoon_tail";
const int MarioRaccoonTail::WIDTH = 10;
const int MarioRaccoonTail::HEIGHT = 6;
const string MarioRaccoonTail::DIRECTION_BACK = "direction_back";
const string MarioRaccoonTail::DIRECTION_FRONT = "direction_front";
const string MarioRaccoonTail::DIRECTION_LEFT = "direction_left";
const string MarioRaccoonTail::DIRECTION_RIGHT = "direction_right";
const string MarioRaccoonTail::STATE_ACTIVE = "active_tail";
const string MarioRaccoonTail::STATE_INACTIVE = "inactive_tail";

string MarioRaccoonTail::getName(){
	return OBJECT_NAME;
}
MarioRaccoonTail::MarioRaccoonTail(Mario* mario,int x, int y, int width, int height)
	:StaticObject(x,y,width,height){
	mMario = mario;
	mLastTime = GetTickCount();
	mState = STATE_INACTIVE;

}
MarioRaccoonTail::MarioRaccoonTail():StaticObject(0,0,MarioRaccoonTail::WIDTH,MarioRaccoonTail::HEIGHT){
	mLastTime = GetTickCount();
	mMario = ObjectManager::getInstance()->getMario();
	mState = STATE_INACTIVE;
}
void MarioRaccoonTail::render(int vpx, int vpy){
	//nếu va chạm thì vẽ hiệu ứng va chạm

	
}
string MarioRaccoonTail::getState(){
	return mState;
}
void MarioRaccoonTail::setState(string state){
	if (state == STATE_ACTIVE){
		mState = state;
		mLastTime = GetTickCount();
	}
	else if (state == STATE_INACTIVE){
		mState = state;
	}
	
}
void MarioRaccoonTail::update(int t){

	//if (mMario == NULL){
	//	mMario = ObjectManager::getInstance()->getMario();
	//}
	//if (mState == STATE_ACTIVE){
	//	DWORD time = GetTickCount() - mLastTime;
	//	if (time >= 70 && time < 140){
	//		width = WIDTH;
	//		height = HEIGHT;
	//		if (mMario->vx_last > 0){
	//			mDirection = MarioRaccoonTail::DIRECTION_LEFT;
	//			x = mMario->left() - width / 2;
	//			y = mMario->y - mMario->height / 4;
	//		}
	//		else{
	//			mDirection = MarioRaccoonTail::DIRECTION_RIGHT;
	//			x = mMario->right() + width / 2;
	//			y = mMario->y - mMario->height / 4;
	//		}
	//		
	//	}
	//	else if (time >= 140 && time < 210){
	//		mDirection = MarioRaccoonTail::DIRECTION_BACK;
	//		width = HEIGHT;// ở hướng này kích thước đuôi là 6x6;
	//		height = HEIGHT;
	//		x = mMario->x;
	//		y = mMario->y - mMario->height / 4;			
	//	}
	//	else if (time >= 210 && time < 280){
	//		width = WIDTH;
	//		height = HEIGHT;
	//		if (mMario->vx_last < 0){
	//			mDirection = MarioRaccoonTail::DIRECTION_LEFT;
	//			x = mMario->left() - width / 2;
	//			y = mMario->y - mMario->height / 4;
	//		}
	//		else{
	//			mDirection = MarioRaccoonTail::DIRECTION_RIGHT;
	//			x = mMario->right() + width / 2;
	//			y = mMario->y - mMario->height / 4;
	//		}
	//	}
	//	else if (time >= 280 && time < 350){
	//		mDirection = MarioRaccoonTail::DIRECTION_FRONT;
	//		width = HEIGHT;// ở hướng này kích thước đuôi là 6x6;
	//		height = HEIGHT;
	//		x = mMario->x;
	//		y = mMario->y - mMario->height / 4;
	//		
	//	}
	//	else if (time >= 420){
	//		x = -5; y = -5;
	//		mState = STATE_INACTIVE;
	//	}
	//}
	if (mMario == NULL){
		mMario = ObjectManager::getInstance()->getMario();
	}
	if (mState == STATE_ACTIVE){
		DWORD time = GetTickCount() - mLastTime;
		if (time >= 90 && time < 180){
			width = WIDTH;
			height = HEIGHT;
			if (mMario->vx_last > 0){
				mDirection = MarioRaccoonTail::DIRECTION_LEFT;
				x = mMario->left() - width / 2;
				y = mMario->y - mMario->height / 4;
			}
			else{
				mDirection = MarioRaccoonTail::DIRECTION_RIGHT;
				x = mMario->right() + width / 2;
				y = mMario->y - mMario->height / 4;
			}

		}
		else if (time >= 180 && time < 270){
			mDirection = MarioRaccoonTail::DIRECTION_BACK;
			width = HEIGHT;// ở hướng này kích thước đuôi là 6x6;
			height = HEIGHT;
			x = mMario->x;
			y = mMario->y - mMario->height / 4;
		}
		else if (time >= 270 && time < 360){
			width = WIDTH;
			height = HEIGHT;
			if (mMario->vx_last < 0){
				mDirection = MarioRaccoonTail::DIRECTION_LEFT;
				x = mMario->left() - width / 2;
				y = mMario->y - mMario->height / 4;
			}
			else{
				mDirection = MarioRaccoonTail::DIRECTION_RIGHT;
				x = mMario->right() + width / 2;
				y = mMario->y - mMario->height / 4;
			}
		}
		else if (time >= 360 && time < 450){
			mDirection = MarioRaccoonTail::DIRECTION_FRONT;
			width = HEIGHT;// ở hướng này kích thước đuôi là 6x6;
			height = HEIGHT;
			x = mMario->x;
			y = mMario->y - mMario->height / 4;

		}
		else if (time >= 450){
			x = -5; y = -5;
			mState = STATE_INACTIVE;
		}
	}
}
MarioRaccoonTail* MarioRaccoonTail::sIntance;
MarioRaccoonTail* MarioRaccoonTail::getInstance(){
	if (sIntance == NULL){
		sIntance = new MarioRaccoonTail();
	}
	
	return sIntance;
}
int MarioRaccoonTail::isStaticObject(){
	return 0;
}