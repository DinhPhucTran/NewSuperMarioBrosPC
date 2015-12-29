#ifndef _FIRE_BALL_H_
#define _FIRE_BALL_H_

#include "object.h"
#include <string>
using namespace std;
class Mario;
class FireBall :public Object{
	Mario* mMario;
	int isUp;
	int isRight;
	float dx=0, dy=0;//để chứa giá trị bị mất khi chuyển kiểu float->int
public:
	static const int HEIGHT;
	static const int WIDTH;
	static const int ANIMATION_DELAY;//=2
	static const float SPEED_X;//0.1f
	static const string OBJECT_NAME;
	Animation* mFireBallAnimation;
	void update(int t)override;
	void onCollision(Object *ob, int dir)override;
	string getName()override;
	FireBall(int x, int y, CSprite* image);
	void render(int vpx, int vpy);
};

#endif