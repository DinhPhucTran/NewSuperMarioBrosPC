#include "RedFirePiranha.h"
#include "FirePiranhaAnimationFactory.h"
const int RedFirePiranha::WIDTH = 16;
const int RedFirePiranha::HEIGHT = 32;

RedFirePiranha::RedFirePiranha(int x, int y, CSprite* image, CSprite* pipeImage):FirePiranha(x,y,image,pipeImage){
	height = HEIGHT;
	width = WIDTH;
	mAnimFactory = new RedFirePiranhaAnimationFactory(this);
}