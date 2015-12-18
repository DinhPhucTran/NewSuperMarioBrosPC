#ifndef _METAL_H
#define _METAL_H


#include <string>
#include "MarioObject.h"
#include "StaticObject.h"
using namespace std;
class MetalBlock :public StaticObject
{
private:

public:
	static const string OBJECT_NAME;
	MetalBlock(int x, int y, int width, int height);
	virtual string getName()override;
};

#endif