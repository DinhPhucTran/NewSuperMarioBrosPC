#include "MetalBlock.h"
#include <string>

using namespace std;

const string MetalBlock::OBJECT_NAME = "metal_block";
string MetalBlock::getName(){
	return OBJECT_NAME;
}

MetalBlock::MetalBlock(int x, int y, int width, int height)
: StaticObject(x, y, width, height){}