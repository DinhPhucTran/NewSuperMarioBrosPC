#ifndef _MARIO_POWER_BAR_
#define _MARIO_POWER_BAR_
#include "MarioObject.h"
#include "Timer.h"
class MarioPowerBar{
	Mario* mMario;
	Timer mTimer;
	Timer mPowerTimer;
	int mIsPower;
	
public:
	static const int POWER_TIME;//2500ms quảng thời gian ống P đầy, thời gian này mario bay lên đc
	static const int RACCOON_POWER_TIME;//6000ms
	static const int INTERVAL_TIME_NEEDED;//2000ms quảng thời gian cần để power bar đầy

	MarioPowerBar(Mario* mario);
	void start();
	float getState();
	void reset();
	void update();
	int isPower();
	int isStarted();
};

#endif