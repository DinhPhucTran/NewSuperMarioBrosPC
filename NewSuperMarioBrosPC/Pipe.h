#ifndef _PIPE_H
#define _PIPE_H


#include <string>
#include "MarioObject.h"
#include "StaticObject.h"
using namespace std;
class Pipe :public StaticObject
{
private:

public:
	static const string OBJECT_NAME;
	Pipe(int x, int y, int width, int height);
	virtual string getName()override;
	int isStaticObject();
};

#endif