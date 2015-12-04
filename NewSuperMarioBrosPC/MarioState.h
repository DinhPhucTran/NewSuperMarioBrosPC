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
	virtual void onCollision(Object* ob) ;
	virtual std::string getName();
};

class MarioStateSmall :public MarioState{
	Mario* mMario;
public:
	static const string STATE_NAME;;
	MarioStateSmall(Mario* mario);
	void onAPress()override;//jump
	void onBPress()override;//do nothing
	void onCollision(Object* ob)override;

	string getName();//return OBJECT_NAME
};

class MarioStateLarge  :public MarioState{
	Mario* mMario;
public:
	static const string STATE_NAME;
	MarioStateLarge(Mario* mario);
	void onAPress()override;//jump
	void onBPress()override;//do nothing
	void onCollision(Object* ob)override;

	string getName();//return OBJECT_NAME
};

class MarioStateRaccoon : public MarioState{
	Mario* mMario;
public:
	static const string STATE_NAME;
	MarioStateRaccoon(Mario* mario);
	void onAPress() override;//jump and fly
	void onBPress() override;//turn around
	void onCollision(Object* ob) override;

	string getName();//return OBJECT_NAME
};

#endif