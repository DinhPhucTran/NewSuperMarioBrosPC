#include"Brick.h"
#include <string>

using namespace std;

const string Brick::OBJECT_NAME = "brick";
string Brick::getName(){
	return OBJECT_NAME;
}
void Brick::onCollision(Object* ob){

}

Brick::Brick(int x, int y, int width, int height, Animation* anim, CSprite* sprite) 
	:Object(x, y, width, height, 0, 0, 0, 0, 0, anim, sprite){}