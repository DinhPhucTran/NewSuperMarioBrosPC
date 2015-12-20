#include "GreenMushroom.h"
#include "ObjectManager.h"
GreenMushroom::GreenMushroom(int x, int y, int width, int height, CSprite * image) :
StaticObject(x, y, width, height, image){
}
void GreenMushroom::render(int vpx, int vpy){
	mSprite->Render(x, y, vpx, vpy);
}
const string GreenMushroom::OBJECT_NAME = "green_mushroom";


string GreenMushroom::getName()
{
	return OBJECT_NAME;
}

void GreenMushroom::collision(){

}
