#include "RedFirePiranha.h"
#include "FirePiranhaAnimationFactory.h"
const int RedFirePiranha::WIDTH = 16;
const int RedFirePiranha::HEIGHT = 32;

RedFirePiranha::RedFirePiranha(int x, int y, CSprite* image, CSprite* pipeImage):FirePiranha(x,y,image,pipeImage){
	height = HEIGHT;
	width = WIDTH;
	mAnimFactory = new RedFirePiranhaAnimationFactory(this);
	initY = y - HEIGHT / 2 - pipeImage->_Height/2 + 1;
	mDistance = HEIGHT + 5;
}
int RedFirePiranha::getHeight(){
	return RedFirePiranha::HEIGHT;
}
int RedFirePiranha::getWidth(){
	return RedFirePiranha::WIDTH;
}