#ifndef _OBJECT_H
#define _OBJECT_H
#include "sprite.h"
#include "game.h"
#include <string>
using namespace std;


class Object {
public:
	int x, y;
	int width, height;
	int vx, vy;
	int vx_last;//vx của mario trước khi dừng, để xác định hướng di chuyển của mario
	CSprite * mSprite;
	Animation* mAnim;
	Object(int x, int y, int width, int height, int vx, int vy,int vx_last,Animation* anim, CSprite * image);
	void setAnimation(Animation* anim);
	virtual Animation* getAnimation();
	~Object();
};
#endif