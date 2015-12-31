#include "GoldBrick.h"
#include "KoopaTroopaState.h"
#include "ObjectManager.h"
#include "Coin.h"
#include "MarioGame.h"
#include "MarioRaccoonTail.h"
const string GoldBrick::NORMAL_STATE = "normal_gold_brick_state";
GoldBrick::GoldBrick(int x, int y, int width, int height, Animation* anim, CSprite * image,int isContainPButton) :
StaticObject(x, y, width, height, anim, image){
	mIsContainPButton = isContainPButton;
}
void GoldBrick::setState(string state){
}
string GoldBrick::getState(){
	return mState;
}
Animation* GoldBrick::createAnimation(){
	if (mIsStatic){
		mAnim = mStaticBrickAnimation;
	}
	else{
		mAnim = mAnimation;
	}
	mAnim->Update();
	return mAnimation;
}
void GoldBrick::render(int vpx, int vpy){
	mSprite->Render(createAnimation(), x, y, vpx, vpy);
}
const string GoldBrick::OBJECT_NAME = "GoldBrick";


string GoldBrick::getName()
{
	return OBJECT_NAME;
}
void GoldBrick::switchToCoin(){
	if (mIsStatic){
		return;
	}
	CMarioGame* marioGame = CMarioGame::getInstance();
	CSprite* coinSprite = marioGame->coinSprite;
	Coin* coin = new Coin(x, y, 16, 16, coinSprite);
	ObjectManager::getInstance()->addObject(coin);
	die();
}

void GoldBrick::revealPButton(){
	if (mIsContainPButton){
		PButton * pButton = new PButton(x, y + 16, CMarioGame::getInstance()->goldBrickAndPButton);
		ObjectManager::getInstance()->addObject(pButton);
		mIsStatic = 1;
		mIsContainPButton = 0;
	}
}
void GoldBrick::onCollision(Object* ob, int dir){
	string objName = ob->getName();
	if (objName == Mario::OBJECT_NAME){
		if (dir == Physics::COLLIDED_FROM_BOTTOM){
			if (mIsContainPButton){
				revealPButton();
			}
			else if (mIsStatic){
				return;
			}
			else{
				die();
			}
		}
	}
	if (objName == MarioRaccoonTail::OBJECT_NAME){
		MarioRaccoonTail* tail = (MarioRaccoonTail*)ob;
		if (tail->getState() == MarioRaccoonTail::STATE_ACTIVE){
			if (mIsContainPButton){
				revealPButton();
			}
			else if (mIsStatic){
				return;
			}
			else{
				die();
			}
		}
	}
	if (objName == KoopaTroopa::OBJECT_NAME || objName == RedKoopa::OBJECT_NAME){
		KoopaTroopa* koopa = (KoopaTroopa*)ob;
		if (koopa->getState()->getName() == KoopaSlidingState::STATE_NAME){
			if (dir == Physics::COLLIDED_FROM_LEFT || dir == Physics::COLLIDED_FROM_RIGHT){
				die();
			}
		}
	}
}


const string PButton::OBJECT_NAME = "p_button";
string PButton::getName(){
	return OBJECT_NAME;
}

void PButton::swithGoldBrickToCoin(){
	vector<Object*> listStaticObject = ObjectManager::getInstance()->getStaticObjectList();
	for (vector<Object*>::iterator itr = listStaticObject.begin(); itr != listStaticObject.end(); itr++){
		Object* ob = (*itr);
		if (ob == 0){
			continue;
		}
		else
		{
			if (ob->getName() == GoldBrick::OBJECT_NAME){
				GoldBrick* goldBrick = (GoldBrick*)ob;
				goldBrick->switchToCoin();
			}
		}
	}
	isPressed = 1;
}
void PButton::render(int vpx, int vpy){
	if (isPressed){
		mAnim = mPressedButtonAnimation;
		
	}
	else{
		mAnim = mNormalButtonAnimation;
	}
	mSprite->Render(mAnim, x, y, vpx, vpy);
}

void PButton::onCollision(Object* ob, int dir){
	if (ob->getName() == Mario::OBJECT_NAME){
		if (dir == Physics::COLLIDED_FROM_TOP && isPressed ==0){
			isPressed = 1;
			swithGoldBrickToCoin();
			y -= 8;
		}
	}
}
PButton::PButton(int x,int y, CSprite*pButtonSprite) :StaticObject(x, y, 16, 16, pButtonSprite){

}