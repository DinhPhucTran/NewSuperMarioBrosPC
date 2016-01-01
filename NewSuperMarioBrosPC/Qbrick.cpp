#include "Qbrick.h"
#include "Leaf.h"
#include "ObjectManager.h"
#include "Mushroom.h"
#include "MarioState.h"
#include "MarioGame.h"
#include "Coin.h"
const string QBrick::NORMAL_STATE = "normal_question_brick_state";
const string QBrick::QUESTION_STATE = "hidden_item_state";
const float QBrick::HIDDEN_OBJECT_Y_SPEED = 0.1f;
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
	yLast = y;
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
	vy = 0;
	ay = 0.01f;

	if (mHiddenObject != NULL && mState == QBrick::QUESTION_STATE){
		if (mHiddenObject->getName() == RedMushroom::OBJECT_NAME || mHiddenObject->getName() == Leaf::OBJECT_NAME){
			Mario* mario = (Mario*)ObjectManager::getInstance()->getMario();
			string state = mario->getState()->getName();
			if (state == MarioStateSmall::STATE_NAME){
				mHiddenObject = 
					new RedMushroom(x, y + 16, RedMushroom::WIDTH, RedMushroom::HEIGHT, QBrick::HIDDEN_OBJECT_Y_SPEED, 0, HIDDEN_OBJECT_Y_SPEED, 0, 0, CMarioGame::getInstance()->itemsSprite);
				//mHiddenObject->vx = QBrick::HIDDEN_OBJECT_Y_SPEED;
				ObjectManager::getInstance()->addObject(mHiddenObject);
				mHiddenObject = NULL;
				setState(QBrick::NORMAL_STATE);
			}
			else {
				mHiddenObject = new Leaf(x, y + 16, RedMushroom::WIDTH, RedMushroom::HEIGHT, 0, Leaf::SPEED_Y, 0, 0, 0, CMarioGame::getInstance()->itemsSprite);
				//mHiddenObject->vy = Leaf::SPEED_Y;
				ObjectManager::getInstance()->addObject(mHiddenObject);
				mHiddenObject = NULL;
				setState(QBrick::NORMAL_STATE);
			}
		}
		else {
			mHiddenObject->x = x;
			mHiddenObject->y = y + 16;
			if (mHiddenObject->getName() == Coin::OBJECT_NAME){
				mHiddenObject->vx = 0.3;
			}
			ObjectManager::getInstance()->addObject(mHiddenObject);
			mHiddenObject = NULL;
			setState(QBrick::NORMAL_STATE);
		}
	}
}

void QBrick::update(int t)
{	
	y += (int)(vy * t);
	vy += ay*t;
	ay -= 0.006f;
	if (y <= yLast)
		y = yLast;
}
