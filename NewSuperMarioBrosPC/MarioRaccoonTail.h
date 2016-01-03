#ifndef _MARIO_RACCOON_TAIL_H_
#define _MARIO_RACCOON_TAIL_H_
#include "MarioObject.h"
#include "StaticObject.h"
#include "Timer.h"
#include <string>
using namespace std;

class MarioRaccoonTail :public Object{
private:
	Mario* mMario;
	static MarioRaccoonTail* sIntance;
	DWORD mLastTime;
	Timer mIsCollided;
	int mCollisionX=-1;
	int mCollisionY = -1;
	MarioRaccoonTail(Mario* mario, int x, int y, int width, int height);
	MarioRaccoonTail();
	string mState;
	
public:
	Animation* explosionAnimation = new Animation(170, 175, 5);
	Animation* blankAnimation = new Animation(-1, -1);
	static const int EXPLOSION_TIME;//250ms
	static const int WIDTH;//10
	static const int HEIGHT;//5
	static const string OBJECT_NAME;
	static MarioRaccoonTail* getInstance();
	static const string DIRECTION_FRONT;
	static const string DIRECTION_BACK;
	static const string DIRECTION_LEFT;
	static const string DIRECTION_RIGHT;
	static const string STATE_ACTIVE;
	static const string STATE_INACTIVE;
	static const int ROTATION_TIME;//50;
	string mDirection;
	void setState(string state);
	string getState();
	void render(int vpx, int vpy)override;//render collision effect
	void update(int t)override;
	void onCollision(Object* ob, int dir);
	string getName()override;
	int isStaticObject()override;
	Animation* createAnimation();
	
};

#endif