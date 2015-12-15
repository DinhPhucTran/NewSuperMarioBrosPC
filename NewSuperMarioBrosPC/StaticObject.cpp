#include "StaticObject.h"

const string StaticObject::OBJECT_NAME = "static_object";
StaticObject::StaticObject(int x, int y, int width, int height, Animation* anim, CSprite * image) 
	:Object(x,y,width,height,0,0,0,0,0, anim, image)
{

}

void StaticObject::update(int t){
	//do nothing
}
string StaticObject::getName(){
	return OBJECT_NAME;
}