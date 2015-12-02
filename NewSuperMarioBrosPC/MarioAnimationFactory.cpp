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
			if (mMario->vx!=0)//mario đang đi
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
	result->Update();//next frame
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
//========================================
LargeMarioAnimationFactory::LargeMarioAnimationFactory(Mario* mario){
	mMario = mario;
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
	result->Update();//next frame
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