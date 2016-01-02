#include "GoobaFactory.h"
#include "gooba.h"
#include "BrickGround.h"
#include "ObjectManager.h"
#include "MarioGame.h"
#include "MarioObject.h"

const string GoobaFactory::OBJECT_NAME = "goomba_factory";

const int GoobaFactory::WIDTH = 32;
const int GoobaFactory::HEIGHT = 32;
const int GoobaFactory::PRODUCTION_TIME = 3000;
const int GoobaFactory::DIRECTION_LEFT = -1;
const int GoobaFactory::DIRECTION_RIGHT = 1;

string GoobaFactory::getName(){
	return OBJECT_NAME;
}

GoobaFactory::GoobaFactory(int x, int y,int direction, CSprite* pipe):StaticObject(x,y,WIDTH,HEIGHT,pipe){
	mProductionTime.start();
	mGround = new BrickGround(x, y - 12, WIDTH, 8);//nền để goom đứng bên trong Factory;
	ObjectManager::getInstance()->addObject(mGround);
	mDirection = direction;
	if (direction == DIRECTION_RIGHT){
		mAnim = new Animation(0, 0);
	}
	else{
		mAnim = new Animation(1, 1);
	}
	if (pipe == 0){
		mSprite = CMarioGame::getInstance()->horizontalPipe;
	}
	
}

Gooba* GoobaFactory::produceGooba(){
	if (mProductionTime.getIntervalTime() >= PRODUCTION_TIME){
		int goombaX=0;
		if (mDirection){
			goombaX = x + 20;
		}
		else
		{
			goombaX = x - 20;
		}
		Gooba* gooba = new Gooba(goombaX, y, Gooba::SPEED_X*mDirection);
		ObjectManager::getInstance()->addObject(gooba);
		mProductionTime.start();
		return gooba;
	}
	return 0;
}
void GoobaFactory::update(int t){
	if (mMario == 0){
		mMario = ObjectManager::getInstance()->getMario();
		return;
	}
	if (abs(mMario->x - x) <=350){//mario lại gần mới kích hoạt sản xuất Goomba
		produceGooba();
	}
}
void GoobaFactory::die(){
	ObjectManager::getInstance()->removeObject(mGround);
	ObjectManager::getInstance()->removeObject(this);
}