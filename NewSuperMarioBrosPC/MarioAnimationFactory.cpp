﻿#include"MarioAnimationFactory.h"
#include<string>
#include"game.h"
using namespace std;


SmallMarioAnimationFactory::SmallMarioAnimationFactory(Mario* mario){
	mMario = mario;
}

Animation* SmallMarioAnimationFactory::createAnimation(){
	Animation* result;
	if (mMario->vy > 0)//vy>0 => mario nhảy lên, vy<0 =>mario đang rớt xuống
	{
		if (mMario->vx_last < 0)//quay trái
			result = leftJumpUpAnim;
		else
			result = rightJumpUpAnim;
	}
	else if (mMario->vy == 0)
	{//vy==0 mario đang đứng trên vật thể 
		if (mMario->vx_last < 0)//quay trái
		{
			if (mMario->ax > 0 && mMario->isRightButtonPress == 1){//quay phải
				result = turnRightAnimation;
			}
			else if (mMario->vx != 0)//mario đang đi
				result = leftWalkAnim;
			else{//mario đang đứng yên
				result = leftStandAnim;
			}
		}
		else{//vx_last >0 mario đang đi trái
			if (mMario->ax < 0 && mMario->isLeftButtonPress == 1)//đang đổi hướng
			{
				result = turnLeftAnimation;
			}
			else if (mMario->vx != 0)//đang đi phải
				result = rightWalkAnim;
			else
				result = rightStandAnim;
		}
	}
	else {//mario đang rơi
		if (mMario->vx_last < 0)//quay trái
		{
			result = leftJumpDownAnim;
		}
		else
			result = rightJumpDownAnim;
	}
	result->Update();
	return result;
}

SmallMarioAnimationFactory::~SmallMarioAnimationFactory(){
	
	delete leftWalkAnim;
	delete rightWalkAnim;
	delete leftStandAnim;
	delete rightStandAnim;
}
SmallMarioAnimationFactory* SmallMarioAnimationFactory::sInstance;//define singleton
SmallMarioAnimationFactory* SmallMarioAnimationFactory::getInstance(Mario* mario){
	if (SmallMarioAnimationFactory::sInstance == NULL){
		SmallMarioAnimationFactory::sInstance = new SmallMarioAnimationFactory(mario);
	}
	else
		sInstance->mMario = mario;
	return sInstance;
}
//========================================
LargeMarioAnimationFactory::LargeMarioAnimationFactory(Mario* mario){
	mMario = mario;
}

//define singleton
LargeMarioAnimationFactory* LargeMarioAnimationFactory::sInstance;
LargeMarioAnimationFactory* LargeMarioAnimationFactory::getInstance(Mario* mario){
	if (sInstance == NULL){
		sInstance = new LargeMarioAnimationFactory(mario);
	}
	else
		sInstance->mMario = mario;
	return sInstance;
}

Animation* LargeMarioAnimationFactory::createAnimation(){
	Animation* result;
	if (mMario->vy > 0)//vy>0 => mario nhảy lên, vy<0 =>mario đang rớt xuống
	{
		if (mMario->vx_last < 0)//quay trái
			result = leftJumpUpAnim;
		else
			result = rightJumpUpAnim;
	}
	else if (mMario->vy == 0)
	{//vy==0 mario đang đứng trên vật thể 
		if (mMario->vx_last < 0)//quay trái
		{
			if (mMario->ax > 0 && mMario->isRightButtonPress == 1){//quay phải
				result = turnRightAnimation;
			}
			else if (mMario->vx != 0)//mario đang đi
				result = leftWalkAnim;
			else{//mario đang đứng yên
				result = leftStandAnim;
			}
		}
		else{//vx_last >0 mario đang đi trái
			if (mMario->ax < 0 && mMario->isLeftButtonPress == 1)//đang đổi hướng
			{
				result = turnLeftAnimation;
			}
			else if (mMario->vx != 0)//đang đi phải
				result = rightWalkAnim;
			else
				result = rightStandAnim;
		}
	}
	else {//mario đang rơi
		if (mMario->vx_last < 0)//quay trái
		{
			result = leftJumpDownAnim;
		}
		else
			result = rightJumpDownAnim;
	}
	result->Update();
	return result;
}

LargeMarioAnimationFactory::~LargeMarioAnimationFactory(){

	delete leftWalkAnim;
	delete rightWalkAnim;
	delete leftStandAnim;
	delete rightStandAnim;
	
}

///==============================Mario Raccoon============================
RaccoonMarioAnimationFactory::RaccoonMarioAnimationFactory(Mario* mario){
	mMario = mario;
}

//define singleton
RaccoonMarioAnimationFactory* RaccoonMarioAnimationFactory::sInstance;
RaccoonMarioAnimationFactory* RaccoonMarioAnimationFactory::getInstance(Mario* mario){
	if (sInstance == NULL){
		sInstance = new RaccoonMarioAnimationFactory(mario);
	}
	else
		sInstance->mMario = mario;
	return sInstance;
}

Animation* RaccoonMarioAnimationFactory::createAnimation(){
	Animation* result;
	if (mMario->vy > 0)//vy>0 => mario nhảy lên, vy<0 =>mario đang rớt xuống
	{
		if (mMario->vx_last < 0)//quay trái
			result = leftJumpUpAnim;
		else
			result = rightJumpUpAnim;
	}
	else if(mMario->vy==0)
	{//vy==0 mario đang đứng trên vật thể 
		if (mMario->vx_last < 0)//quay trái
		{
			if (mMario->ax > 0 && mMario->isRightButtonPress == 1){//quay phải
				result = turnRightAnimation;
			}
			else if (mMario->vx != 0)//mario đang đi
				result = leftWalkAnim;
			else{//mario đang đứng yên
				result = leftStandAnim;
			}
		}
		else{//vx_last >0 mario đang đi trái
			if (mMario->ax < 0 && mMario->isLeftButtonPress==1)//đang đổi hướng
			{
				result = turnLeftAnimation;
			}else if (mMario->vx != 0)//đang đi phải
				result = rightWalkAnim;
			else
				result = rightStandAnim;
		}
	}
	else {//mario đang rơi
		if (mMario->vx_last < 0)//quay trái
		{
			result = leftJumpDownAnim;
		}else
			result = rightJumpDownAnim;
	}
	result->Update();
	return result;
}

RaccoonMarioAnimationFactory::~RaccoonMarioAnimationFactory(){

	delete leftWalkAnim;
	delete rightWalkAnim;
	delete leftStandAnim;
	delete rightStandAnim;

}