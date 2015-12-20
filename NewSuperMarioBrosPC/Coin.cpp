#include "Coin.h"
#include "ObjectManager.h"
Coin::Coin(int x, int y, int width, int height, Animation* anim, CSprite * image) :
StaticObject(x, y, width, height, anim, image){
}
Animation* Coin::createAnimation(){
	mCoinAnimation->Update();
	return mCoinAnimation;
}
void Coin::render(int vpx, int vpy){
	mSprite->Render(createAnimation(), x, y, vpx, vpy);
}
const string Coin::OBJECT_NAME = "coin";


string Coin::getName()
{
	return OBJECT_NAME;
}

void Coin::collision(){

}

