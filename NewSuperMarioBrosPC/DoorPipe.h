#ifndef _DOOR_PIPE_H
#define _DOOR_PIPE_H


#include <string>
#include "MarioObject.h"
#include "StaticObject.h"
#include "sprite.h"
using namespace std;
class DoorPipe :public Object
{
private:
	Animation * anim;
	Animation* createAnimation();
public:
	int dir;
	int outX, outY;
	static const string OBJECT_NAME;
	DoorPipe(int x, int y, int width, int height, int dir, CSprite * sprite, int outX, int outY);
	virtual string getName()override;
	void update(int t)override;
	void render(int vpx, int vpy)override;
};

#endif