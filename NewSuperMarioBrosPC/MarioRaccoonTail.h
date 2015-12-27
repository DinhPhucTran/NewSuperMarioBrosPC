#ifndef _MARIO_RACCOON_TAIL_H_
#define _MARIO_RACCOON_TAIL_H_
#include "MarioObject.h"
#include "StaticObject.h"
#include <string>
using namespace std;

class MarioRaccoonTail :public Object{
private:
	Mario* mMario;
	static MarioRaccoonTail* sIntance;
	DWORD mLastTime;
	MarioRaccoonTail(Mario* mario, int x, int y, int width, int height);
	MarioRaccoonTail();
	string mState;
	
public:
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
	
	
};

#endif