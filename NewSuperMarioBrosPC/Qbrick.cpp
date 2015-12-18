#include "Qbrick.h"

QBrick::QBrick(int x, int y, int width, int height, float vx, float vy, float vx_last, float ax, float ay, Animation* anim, CSprite * image) :
Object(x, y, width, height, vx, vy, vx_last, ax, ay, anim, image){
	anim = anim;
}

const string QBrick::OBJECT_NAME = "qbrick";

void QBrick::onCollision(Object *ob, int dir)
{

}

string QBrick::getName()
{
	return OBJECT_NAME;
}

void QBrick::update(int t)
{
	
}