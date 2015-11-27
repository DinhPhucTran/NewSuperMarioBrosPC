#ifndef _OBJECT_H
#define _OBJECT_H
#include "sprite.h"
#include "game.h"
#include <string>
using namespace std;


class Object {
public:
	int x, y;
	float ax;
	float ay;
	int width, height;
	float vx, vy;
	float vx_last;//vx của mario trước khi dừng, để xác định hướng di chuyển của mario
	CSprite * mSprite;
	Animation* mAnim;
	Object(int x, int y, int width, int height, float vx, float vy, float vx_last,  float ax, float ay, Animation* anim, CSprite * image);
	void setAnimation(Animation* anim);
	virtual Animation* getAnimation();
	void update(int t);

	~Object();
};
#endif