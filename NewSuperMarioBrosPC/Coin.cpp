#include "Coin.h"

const string Coin::OBJECT_NAME = "coin";

Coin::Coin(int X, int Y, int Width, int Height, Animation* anim, CSprite * Sprite) :
	StaticObject(X, Y, Width, Height, anim, Sprite){
}

Coin::Coin(int X, int Y, int Width, int Height, CSprite * Sprite) :
	StaticObject(X, Y, Width, Height, mCoinAnimation, Sprite){
}

string Coin::getName()
{
	return OBJECT_NAME;
}

void Coin::onCollision(Object * ob, int dir)
{
	string objectName = ob->getName();
	if (objectName == Mario::OBJECT_NAME)
	{
		die();
	}
}
Animation* Coin::createAnimation(){
	mCoinAnimation->Update();
	return mCoinAnimation;
}
void Coin::render(int vpx, int vpy){
	mSprite->Render(createAnimation(), x, y, vpx, vpy);
}
