#ifndef _TIMER_H_
#define _TIMER_H_


class Timer{
private:
	DWORD mLastTime;
	int mIsReset;
public:
	Timer(){
		mLastTime = 0;
	}
	void start(){
		mLastTime = GetTickCount();
	}
	void reset(){
		mLastTime = 0;
		mIsReset = 1;
	}
	int getIntervalTime(){
		return (GetTickCount() - mLastTime);
	}
	DWORD getTickCount(){
		return mLastTime;
	}
	int isReset(){
		return mIsReset;
	}
};

#endif