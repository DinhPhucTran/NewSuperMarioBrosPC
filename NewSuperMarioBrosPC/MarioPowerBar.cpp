#include "MarioPowerBar.h"
#include "MarioState.h"

const int MarioPowerBar::INTERVAL_TIME_NEEDED = 2000;
const int MarioPowerBar::POWER_TIME = 2000;
const int MarioPowerBar::RACCOON_POWER_TIME = 5000;
MarioPowerBar::MarioPowerBar(Mario* mario){
	mMario = mario;
	mIsPower = 0;
	mTimer.reset();
	mPowerTimer.reset();
}
void MarioPowerBar::start(){
	mTimer.start();
}
void MarioPowerBar::reset(){
	mTimer.reset();
}
void MarioPowerBar::update(){
	if (mTimer.getTickCount() != 0){
		if (mTimer.getIntervalTime() >= INTERVAL_TIME_NEEDED)
		{
			mPowerTimer.start();
			mIsPower = 1;
			mTimer.reset();
		}
	}
	string state = mMario->getState()->getName();
	if (state == MarioStateRaccoon::STATE_NAME){
		if (mPowerTimer.getIntervalTime() >= RACCOON_POWER_TIME && mPowerTimer.getTickCount() != 0){
			mIsPower = 0;
			mPowerTimer.reset();
		}
	}
	else{
		if (mPowerTimer.getIntervalTime() >= POWER_TIME && mPowerTimer.getTickCount() != 0){
			mIsPower = 0;
			mPowerTimer.reset();
		}
	}
	
}
int MarioPowerBar::isPower(){
	return mIsPower;
}
int MarioPowerBar::isStarted(){
	return (mTimer.getTickCount()!=0);
}
float MarioPowerBar::getState(){
	int intervalTime = mTimer.getIntervalTime();
	if (intervalTime>0 && intervalTime<=INTERVAL_TIME_NEEDED)
	{
		return (float)intervalTime / INTERVAL_TIME_NEEDED;
	}
	return 0;
}