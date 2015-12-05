#ifndef _OBJECT_H
#define _OBJECT_H
#include <string>
#include "object.h"
#include "sprite.h"
#include "animation.h"


using namespace std;
class MarioState;//khai báo lớp MarioState,
class MarioAnimationFactory;//khai báo có lớp MarioAnimationFactory



class Object {
public:
	static const string OBJECT_NAME;
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
	Animation* getAnimation();
	void setSprite(CSprite* sprite);
	void update(int t);
	virtual string getName();
	~Object();
};
#endif