#ifndef _TIMER_H_
#define _TIMER_H_


class Timer{
private:
	DWORD mLastTime;
public:
	void start(){
		mLastTime = GetTickCount();
	};
	int getIntervalTime(){
		return (GetTickCount() - mLastTime);
	}

};

#endif