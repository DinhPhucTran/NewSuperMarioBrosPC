#ifndef _HOLE_H
#define _HOLE_H


#include <string>
#include "StaticObject.h"
using namespace std;
class Hole :public StaticObject
{
private:

public:
	static const string OBJECT_NAME;
	Hole(int x, int y, int width, int height);
	virtual string getName()override;
};

#endif