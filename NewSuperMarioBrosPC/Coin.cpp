#include "Coin.h"

const string Coin::OBJECT_NAME = "coin";

Coin::Coin():Object(0,0,0,0,0,0,0,0,0,NULL){
}

Coin::Coin(int X, int Y, int Width, int Height, float vx, float vy, float vx_last, float ax, float ay, CSprite * Sprite) :
Object(X, Y, Width, Height, vx, vy, vx_last, ax, ay, Sprite){
	initY = Y;
}

Coin::Coin(int X, int Y, int Width, int Height, CSprite * Sprite) : Object(X, Y, Width, Height, 0, 0.4f, 0, 0, 0, Sprite){
	initY = y;
}

string Coin::getName()
{
	return OBJECT_NAME;
}

void Coin::onCollision(Object * ob, int dir)
{
	if (vy < 0 && y <= initY + 6)
	{
		die();
		CoinScore *score = new CoinScore(x, y, 16, 16, CMarioGame::getInstance()->itemsSprite);
		ObjectManager::getInstance()->addObject(score);
	}
		
	
}
Animation* Coin::createAnimation(){
	mCoinAnimation->Update();
	return mCoinAnimation;
}
void Coin::render(int vpx, int vpy){
	mSprite->Render(createAnimation(), x, y, vpx, vpy);
}

CoinScore::CoinScore(int X, int Y, int Width, int Height, CSprite * Sprite):
Object(X, Y, Width, Height,0,0.3f,0,0,0,Sprite)
{
	initY = Y;
}

void CoinScore::render(int vpx, int vpy) {
	mSprite->Render(mAnim, x, y, vpx, vpy);
}

void CoinScore::onCollision(Object *b, int dir)
{
	if (y >= initY + 10)
		die();
}


const string StaticCoin::OBJECT_NAME = "static_coin";

StaticCoin::StaticCoin(int X, int Y, int Width, int Height, Animation* anim, CSprite * Sprite) :
StaticObject(X, Y, Width, Height, anim, Sprite){
}

StaticCoin::StaticCoin(int X, int Y, int Width, int Height, CSprite * Sprite) :
StaticObject(X, Y, Width, Height, mCoinAnimation, Sprite){
}

string StaticCoin::getName()
{
	return OBJECT_NAME;
}

void StaticCoin::onCollision(Object * ob, int dir)
{
	string objectName = ob->getName();
	if (objectName == Mario::OBJECT_NAME)
	{
		die();
	}
}
Animation* StaticCoin::createAnimation(){
	mCoinAnimation->Update();
	return mCoinAnimation;
}
void StaticCoin::render(int vpx, int vpy){
	mSprite->Render(createAnimation(), x, y, vpx, vpy);
}
