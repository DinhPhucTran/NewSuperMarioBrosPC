#include"BrickGround.h"
#include <string>

using namespace std;

const string BrickGround::OBJECT_NAME = "brick_ground";
string BrickGround::getName(){
	return OBJECT_NAME;
}
void BrickGround::onCollision(Object* ob,int dir){

}

BrickGround::BrickGround(int x, int y, int width, int height, Animation* anim, CSprite* sprite) 
	:StaticObject(x, y, width, height, anim, sprite){}

BrickGround::BrickGround(int x, int y, int width, int height)
: StaticObject(x, y, width, height){}