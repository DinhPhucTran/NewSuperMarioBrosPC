#ifndef _MARIO_STATE_H
#define _MARIO_STATE_H
#include <string>
#include "MarioObject.h"
#include "Timer.h"

#include <string>
using namespace std;
class MarioRaccoonTail;
class MarioState{
protected:
	Mario* mMario;
public:
	virtual void onAPress();
	virtual void onBPress() ;
	virtual void onCollision(Object* ob,int dir) ;
	virtual void update(int t);
	virtual std::string getName();
	virtual int getHeight();//chiểu cao của mario ở trạng thái xác định;
	virtual int getWidth();// chiều rộng của mario ở trạng thái xác định;
	MarioState(Mario* mario);
	virtual AnimationFactory* getAnimationFactory();
};

class MarioStateSmall :public MarioState{
	int height = 16;
	int width = 16;
public:
	static const string STATE_NAME;
	int getHeight()override;
	int getWidth()override;
	MarioStateSmall(Mario* mario);
	void onAPress()override;//jump
	void onBPress()override;//do nothing
	void onCollision(Object* ob, int dir)override;
	AnimationFactory* getAnimationFactory()override;
	string getName()override;//return OBJECT_NAME
};

class MarioStateLarge  :public MarioState{

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
	AnimationFactory* getAnimationFactory()override;
	string getName()override;//return OBJECT_NAME
};

class MarioStateRaccoon : public MarioState{
	
	int height = 28;
	int width = 16;
	MarioRaccoonTail* mTail;
public:
	DWORD timeFlying;
	static const int FLYING_TIME;
	int getHeight()override;
	int getWidth()override;
	static const string STATE_NAME;
	MarioStateRaccoon(Mario* mario);
	void onAPress() override;//jump and fly
	void onBPress() override;//turn around
	void onCollision(Object* ob,int dir) override;
	AnimationFactory* getAnimationFactory()override;
	string getName()override;//return OBJECT_NAME
	void update(int t)override;//mario raccon chuyển động bay
};

class MarioStateInvincible :public MarioState{
private:
	DWORD mLastTime;
public:
	MarioState* mNextState;
	MarioState* mLastState;
	static const string STATE_NAME;
	MarioStateInvincible(Mario* mario,MarioState* nextState);
	void onCollision(Object*ob, int dir)override;
	string getName()override;
	int getWidth()override;
	int getHeight()override;
	DWORD getLastTime();
	AnimationFactory* getAnimationFactory()override;
};

class MarioStateSuperInvincible :public MarioState{
private:
	Timer mDuration;
public:
	static const int MAINTAIN_TIME;//7000
	MarioState* mLastState;
	static const string STATE_NAME;
	MarioStateSuperInvincible(Mario* mario);
	void onCollision(Object*ob, int dir)override;
	string getName()override;
	int getWidth()override;
	int getHeight()override;
	AnimationFactory* getAnimationFactory()override;
	int getRemainTime();
	void update(int t)override;
	void onAPress()override;
	void onBPress()override;
};

class MarioStateDie :public MarioState{
public:
	static const string STATE_NAME;
	MarioStateDie(Mario* mario);
	void onCollision(Object *ob, int dir)override;//rơi tự do không va chạm
	string getName();
	AnimationFactory* getAnimationFactory()override;
};

class MarioStateGoingToBonusRoom :public MarioState
{
private:
	Timer mDuration;
	int outX, outY;
public:
	static const int MAINTAIN_TIME;
	MarioState* mLastState;
	static const string STATE_NAME;
	MarioStateGoingToBonusRoom(Mario* mario, int outX, int outY);
	string getName()override;
	AnimationFactory* getAnimationFactory()override;
	int getRemainTime();
	void update(int t)override;
};
#endif