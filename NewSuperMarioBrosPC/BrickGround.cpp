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
	:Object(x, y, width, height, 0, 0, 0, 0, 0, anim, sprite){}