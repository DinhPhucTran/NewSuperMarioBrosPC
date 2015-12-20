#include "Leaf.h"
#include "ObjectManager.h"
Leaf::Leaf(int x, int y, int width, int height, CSprite * image) :
StaticObject(x, y, width, height, image){
}
void Leaf::render(int vpx, int vpy){
	mSprite->Render(x, y, vpx, vpy);
}
const string Leaf::OBJECT_NAME = "leaf";


string Leaf::getName()
{
	return OBJECT_NAME;
}

void Leaf::collision(){

}
