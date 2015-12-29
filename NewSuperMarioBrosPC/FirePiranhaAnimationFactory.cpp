#include "FirePiranhaAnimationFactory.h"
#include "FirePiranha.h"
#include "MarioObject.h"
#include "ObjectManager.h"

FirePiranhaAnimationFactory::FirePiranhaAnimationFactory(FirePiranha* piranha, Mario* mario){
	if (mario != NULL){
		mMario = mario;
	}
	else{
		mMario = ObjectManager::getInstance()->getMario();
	}
	mPiranha = piranha;
}
Animation* FirePiranhaAnimationFactory::createAnimation(){
	Animation* result = 0; 
	if (mMario == NULL){
		mMario = ObjectManager::getInstance()->getMario();
	}
	else{
		if (mPiranha->x > mMario->x){//Mario bên trái => quay trái
			if (mPiranha->isShooting()){
				if (mMario->y >= mPiranha->y){//Mario phia tren
					result = mShootingLeftUp;
				}
				else{
					result = mShootingLeftDown;
				}
			}
			else {
				if (mMario->y >= mPiranha->y){//Mario phia tren
					result = mLeftUpAnim;
				}
				else{
					result = mLeftDownAnim;
				}
			}
		}
		else{//Mario bên phải =>quay phải
			if (mPiranha->isShooting()){
				if (mMario->y >= mPiranha->y){//Mario phia tren
					result = mShootingRightUp;
				}
				else{
					result = mShootingRightDown;
				}
			}
			else {
				if (mMario->y >= mPiranha->y){//Mario phia tren
					result = mRightUpAnim;
				}
				else{
					result = mRightDownAnim;
				}
			}
		}
	}
	if (result == 0){
		result = mLeftDownAnim;
	}
	result->Update();
	return result;
}