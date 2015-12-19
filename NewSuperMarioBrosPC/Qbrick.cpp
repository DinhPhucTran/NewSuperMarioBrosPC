#include "Qbrick.h"
#include "ObjectManager.h"
const string QBrick::NORMAL_STATE = "normal_question_brick_state";
const string QBrick::QUESTION_STATE = "hidden_item_state";
const float QBrick::HIDDEN_OBJECT_Y_SPEED = 0.3f;
QBrick::QBrick(int x, int y, int width, int height,Object* hiddenObject, Animation* anim, CSprite * image) :
StaticObject(x, y, width, height,  anim, image){
	if (anim == NULL){
		anim = mNormalAnimation;
	}
	mHiddenObject = hiddenObject;
	if (hiddenObject == NULL){
		mState = QBrick::NORMAL_STATE;
	}
	else{
		mState = QBrick::QUESTION_STATE;
	}
}
void QBrick::setState(string state){
	if (state == QBrick::NORMAL_STATE||state == QBrick::QUESTION_STATE){
		mState = state;
	}
}
string QBrick::getState(){
	return mState;
}
Animation* QBrick::createAnimation(){
	if (mState == QBrick::NORMAL_STATE){
		mNormalAnimation->Update();
		return mNormalAnimation;
	}
	else{
		mQuestionAnimation->Update();
		return mQuestionAnimation;
	}
}
void QBrick::render(int vpx, int vpy){
	mSprite->Render(createAnimation(), x, y, vpx, vpy);
}
const string QBrick::OBJECT_NAME = "qbrick";


string QBrick::getName()
{
	return OBJECT_NAME;
}

void QBrick::revealHiddenObject(){
	if (mHiddenObject != NULL && mState == QBrick::QUESTION_STATE){
		mHiddenObject->x = x;
		mHiddenObject->y = y;
		mHiddenObject->vy = QBrick::HIDDEN_OBJECT_Y_SPEED;
		ObjectManager::getInstance()->addObject(mHiddenObject);
		mHiddenObject = NULL;
		setState(QBrick::NORMAL_STATE);
	}
}
