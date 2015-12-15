#ifndef _MARIO_STATE_H
#define _MARIO_STATE_H
#include <string>
#include "MarioObject.h"

#include <string>
using namespace std;
class MarioState{
public:
	virtual void onAPress();
	virtual void onBPress() ;
	virtual void onCollision(Object* ob,int dir) ;
	virtual std::string getName();
	virtual int getHeight();//chiểu cao của mario ở trạng thái xác định;
	virtual int getWidth();// chiều rộng của mario ở trạng thái xác định;
};

class MarioStateSmall :public MarioState{
	int height = 16;
	int width = 16;
	Mario* mMario;
public:
	static const string STATE_NAME;
	int getHeight()override;
	int getWidth()override;
	MarioStateSmall(Mario* mario);
	void onAPress()override;//jump
	void onBPress()override;//do nothing
	void onCollision(Object* ob, int dir)override;

	string getName();//return OBJECT_NAME
};

class MarioStateLarge  :public MarioState{
	Mario* mMario;
	int height = 27;
	int width = 16;
public:
	static const string STATE_NAME;
	MarioStateLarge(Mario* mario);
	int getHeight()override;
	int getWidth()override;
	void onAPress()override;//jump
	void onBPress()override;//do nothing
	void onCollision(Object* ob,int dir)override;

	string getName();//return OBJECT_NAME
};

class MarioStateRaccoon : public MarioState{
	Mario* mMario;
	int height = 28;
	int width = 16;
public:
	int getHeight()override;
	int getWidth()override;
	static const string STATE_NAME;
	MarioStateRaccoon(Mario* mario);
	void onAPress() override;//jump and fly
	void onBPress() override;//turn around
	void onCollision(Object* ob,int dir) override;

	string getName();//return OBJECT_NAME
};

#endif