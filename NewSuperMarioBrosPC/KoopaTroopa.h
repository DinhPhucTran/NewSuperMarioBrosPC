#ifndef _KOOPA_TROOPA_H
#define _KOOPA_TROOPA_H

#include "object.h"
#include <string>
#include "AnimationFactory.h"
#include "gooba.h"
#include"Pipe.h"

class RedKoopa;
using namespace std;

class KoopaTroopa;
class KoopaAnimationFactory: public AnimationFactory{
	KoopaTroopa* mKoopa;
	
public:
	
	KoopaAnimationFactory(KoopaTroopa* koopa);
	Animation* mKoopaLeftWalkAnim = new Animation(4, 5);
	Animation* mKoopaRightWalkAnim = new Animation(10,11);
	Animation* mKoopaVulnerableAnim = new Animation(36, 36);
	Animation* mKoopaSlidingAnim = new Animation(36, 39);
	Animation* mKoopaLeftFlyAnim = new Animation(20, 23);
	Animation* mKoopaRightFlyAnim = new Animation(24, 27);
	Animation* mKoopaUpsideDownAnim = new Animation(43, 43);
	Animation* createAnimation()override;
	~KoopaAnimationFactory();
};

class KoopaTroopaState{
protected:
	KoopaTroopa* mKoopa;
	AnimationFactory* mAnimationFactory;
public:

	KoopaTroopaState(KoopaTroopa* koopa);

	virtual void onCollision(Object* ob,int dir);
	virtual string getName();
	virtual int getWidth();				//ở mổi trạng thái nhất định thì có kích thước khác nhau, trong hàm setState(NormalState) thì phải chỉnh lại kích thước của Troopa
	virtual int getHeight();			//ví dụ Normal Troopa sẽ cao hơn Sliding Stroopa
	virtual int getAnimationDelay();	//và Sliding Troopa lại có AnimationRate cao hơn và tốc độ cao hơn Normal Troopa
	virtual float getSpeed();			//trong mỗi trạng thái nên định nghĩa những thuộc thay đổi này, width, height, animationDelay,Speed;
	virtual void update(int t);
};

class KoopaNomalState:public KoopaTroopaState{//trạng thái đi lại bình thường

public:
	static const string STATE_NAME;
	void onCollision(Object* ob,int dir)override;
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

public :
	static const string STATE_NAME;
	void onCollision(Object*ob,int dir)override;
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

class KoopaTroopa : public Object{
protected:
	KoopaTroopaState* mState;
public:
	int isBringedByMario;
	static const float PARA_FLYING_GRAVITY;
	static const float PARA_MAX_SPEED_Y;//0.6 MARIO 0.7
	static const float PARA_SPEED_X;
	static const float PARA_ACCELERATION_Y;
	static const int KOOPA_WIDTH;
	static const int KOOPA_HEIGHT;
	static const int KOOPA_VULNERABLE_HEIGHT;
	static const int NORMAL_ANIMATION_DELAY;
	static const int SLIDING_ANIMATION_DELAY;
	static float const KOOPA_VELOCITY_X;
	static float const KOOPA_SLIDING_SPEED_X;
	static float const KOOPA_VULNERABLE_SPEED_X; //= 0;
	static const int WAKE_UP_FROM_VULNERABLE_TIME;//10,000 ms
	AnimationFactory* mAnimationFactory;
	static const string OBJECT_NAME;
	string getName();
	KoopaTroopaState* getState();
	void setState(KoopaTroopaState* state);
	void setAnimationFactory(AnimationFactory* animFactory);
	virtual void onCollision(Object* ob,int dir)override;
	void render(int vpx,int vpy)override;
	KoopaTroopa(int x, int y, int width, int height, float vx, float vy, float vx_last, float ax, float ay, Animation* anim, CSprite * image);
	KoopaTroopa(int x, int y, float vx,  Animation* anim, CSprite * image);
	void update(int t)override;
};

#endif