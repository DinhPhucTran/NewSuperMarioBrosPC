#include"MarioAnimationFactory.h"
#include<string>
using namespace std;

Animation* MarioAnimationFactory::createAnimation(){
	return NULL;
}

SmallMarioAnimationFactory::SmallMarioAnimationFactory(Mario* mario){
	mMario = mario;
}

Animation* SmallMarioAnimationFactory::createAnimation(){
	Animation* result;
	if (mMario->vy > 0)//vy>0 => mario nhảy lên, vy<0 =>mario đang rớt xuống
	{
		if (mMario->vx_last < 0)//quay trái
			result = leftJumpAnim;
		else
			result = rightJumpAnim;
	}
	else{
		if (mMario->vy == 0){
			//vy==0 mario đang đứng trên vật thể 
			if (mMario->vx_last < 0)//quay trái
			{
				if (mMario->vx != 0)//mario đang đi
					result = leftWalkAnim;
				else{//mario đang đứng yên
					result = leftStandAnim;
				}
			}
			else{
				if (mMario->vx != 0)//đang đi phải
					result = rightWalkAnim;
				else
					result = rightStandAnim;
			}
		}
		else{
			if (mMario->vx_last < 0)//quay trái
				result = leftJumpAnim;
			else
				result = rightJumpAnim;
		}
	}
	result->Update();
	return result;
}

SmallMarioAnimationFactory::~SmallMarioAnimationFactory(){
	delete leftJumpAnim;
	delete rightJumpAnim;
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
	if (mMario->vy != 0)//vy>0 => mario nhảy lên, vy<0 =>mario đang rớt xuống
	{
		if (mMario->vx_last < 0)//quay trái
			result = leftJumpAnim;
		else
			result = rightJumpAnim;
	}
	else{//vy==0 mario đang đứng trên vật thể 
		if (mMario->vx_last < 0)//quay trái
		{
			if (mMario->vx != 0)//mario đang đi
				result = leftWalkAnim;
			else{//mario đang đứng yên
				result = leftStandAnim;
			}
		}
		else{
			if (mMario->vx != 0)//đang đi phải
				result = rightWalkAnim;
			else
				result = rightStandAnim;
		}
	}
	result->Update();
	return result;
}

LargeMarioAnimationFactory::~LargeMarioAnimationFactory(){
	delete leftJumpAnim;
	delete rightJumpAnim;
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
	if (mMario->vy != 0)//vy>0 => mario nhảy lên, vy<0 =>mario đang rớt xuống
	{
		if (mMario->vx_last < 0)//quay trái
			result = leftJumpUpAnim;
		else
			result = rightJumpUpAnim;
	}
	else{//vy==0 mario đang đứng trên vật thể 
		if (mMario->vx_last < 0)//quay trái
		{
			if (mMario->vx != 0)//mario đang đi
				result = leftWalkAnim;
			else{//mario đang đứng yên
				result = leftStandAnim;
			}
		}
		else{
			if (mMario->vx != 0)//đang đi phải
				result = rightWalkAnim;
			else
				result = rightStandAnim;
		}
	}
	result->Update();
	return result;
}

RaccoonMarioAnimationFactory::~RaccoonMarioAnimationFactory(){
	delete leftJumpAnim;
	delete rightJumpAnim;
	delete leftWalkAnim;
	delete rightWalkAnim;
	delete leftStandAnim;
	delete rightStandAnim;

}