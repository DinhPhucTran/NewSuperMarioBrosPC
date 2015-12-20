#include "RedMushroom.h"
#include "ObjectManager.h"
RedMushroom::RedMushroom(int x, int y, int width, int height, CSprite * image) :
StaticObject(x, y, width, height, image){
}
void RedMushroom::render(int vpx, int vpy){
	mSprite->Render(x, y, vpx, vpy);
}
const string RedMushroom::OBJECT_NAME = "red_mushroom";


string RedMushroom::getName()
{
	return OBJECT_NAME;
}

void RedMushroom::collision(){

}
