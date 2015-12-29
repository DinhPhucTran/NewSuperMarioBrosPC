#ifndef _KOOPA_TROOPA_STATE_
#define _KOOPA_TROOPA_STATE_
#include "RedKoopa.h"
#include <string>
using namespace std;
class KoopaTroopaState{
protected:
	KoopaTroopa* mKoopa;
	AnimationFactory* mAnimationFactory;
public:

	KoopaTroopaState(KoopaTroopa* koopa);

	virtual void onCollision(Object* ob, int dir);
	virtual string getName();
	virtual int getWidth();				//ở mổi trạng thái nhất định thì có kích thước khác nhau, trong hàm setState(NormalState) thì phải chỉnh lại kích thước của Troopa
	virtual int getHeight();			//ví dụ Normal Troopa sẽ cao hơn Sliding Stroopa
	virtual int getAnimationDelay();	//và Sliding Troopa lại có AnimationRate cao hơn và tốc độ cao hơn Normal Troopa
	virtual float getSpeed();			//trong mỗi trạng thái nên định nghĩa những thuộc thay đổi này, width, height, animationDelay,Speed;
	virtual void update(int t);
};

class KoopaNomalState :public KoopaTroopaState{//trạng thái đi lại bình thường

public:
	static const string STATE_NAME;
	void onCollision(Object* ob, int dir)override;
	string getName()override;
	KoopaNomalState(KoopaTroopa* koopa);



};

class KoopaVulnerableState :public KoopaTroopaState{//Trạng thái dể bị tổn thương, khi chui vào mai rùa
	//ở trạng thái này mario đụng vào là xong :p
private:
	DWORD mLastTime;
public:
	static const string STATE_NAME;
	virtual void onCollision(Object* ob, int dir)override;
	virtual string getName()override;
	KoopaVulnerableState(KoopaTroopa* koopa);

	int getHeight()override;//=16
	float getSpeed()override;//=0;
	void update(int t)override;
};

class KoopaSlidingState :public KoopaTroopaState{
	//trạng thái bị mario đá, trượt từ đầu này sang đầu khác
private:

public:
	static const string STATE_NAME;
	void onCollision(Object*ob, int dir)override;
	string getName()override;
	KoopaSlidingState(KoopaTroopa* koopa);

	int getHeight()override;//=16
	int getAnimationDelay()override;//=10;
	float getSpeed()override;//=0.5f
};

class KoopaParaState :public KoopaTroopaState{
private:
public:
	static const string STATE_NAME;
	void onCollision(Object* ob, int dir)override;
	string getName()override;
	KoopaParaState(KoopaTroopa* koopa);
	float getSpeed()override;//PARA_SPEED_X;
	void update(int t)override;

};
class KoopaUpsideDown :public KoopaVulnerableState{
public:
	static const string STATE_NAME;
	void onCollision(Object* ob, int dir)override;
	string getName()override;
	KoopaUpsideDown(KoopaTroopa* koopa);
	//void update(int t)override;
	//int getHeight()override;
	//float getSpeed()override;
};

#endif