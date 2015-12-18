#ifndef _GOOBA_H_
#define _GOOBA_H_

#include "object.h"
#include <string>
#include "AnimationFactory.h"
#include"BrickGround.h"
#include "Physics.h"
#include "Pipe.h"
#include"RedKoopa.h"

using namespace std;

class Gooba;
class GoobaAnimationFactory : public AnimationFactory{
	Gooba* mGooba;
public:
	/*Animation* mGoobaLeftWalkAnim = new Animation(0, 3);
	Animation* mGoobaRightWalkAnim = new Animation(4, 7);*///original value
	Animation* mGoobaWalkingAnim = new Animation(40, 41);
	Animation* mGoobaDyingAnim = new Animation(42, 42);
	Animation* createAnimation()override;
	GoobaAnimationFactory(Gooba* gooba);
};

class GoobaState{
protected:
	Gooba* mGooba;
public:
	GoobaState(Gooba* gooba);
	virtual void onCollision(Object* ob,int dir);
	virtual string getName();
};

class GoobaNomalState :public GoobaState{//trạng thái đi lại bình thường
public:
	GoobaNomalState(Gooba* goooba);
	static const string STATE_NAME;
	void onCollision(Object* ob,int dir)override;
	string getName()override;
};
//
//class KoopaVulnerableState :public KoopaTroopaState{//Trạng thái dể bị tổn thương, khi chui vào mai rùa
//	//ở trạng thái này mario đụng vào là xong :p
//public:
//	static const string STATE_NAME;
//	void onCollision(Object* ob)override;
//	string getName()override;
//};
//
//class KoopaSlidingState :public KoopaTroopaState{
//	//trạng thái bị mario đá, trượt từ đầu này sang đầu khác
//public:
//	static const string STATE_NAME;
//	void onCollision(Object*ob)override;
//	string getName()override;
//};

class Gooba : public Object{
private:
	GoobaState* mState;
public:
	static const float SPEED_X;
	static const int WIDTH;//16
	static const int HEIGHT;//16
	static const int ANIMATION_DELAY;//=10
	AnimationFactory* mAnimationFactory;
	//static Animation* 
	static const string OBJECT_NAME;
	string getName();
	GoobaState* getState();
	void setState(GoobaState* state);
	void setAnimationFactory(AnimationFactory* animFactory);
	void onCollision(Object* ob, int dir)override;
	void render(int vpx, int vpy)override;
	Gooba(int x, int y, int width, int height, float vx, float vy, float vx_last, float ax, float ay, Animation* anim, CSprite * image);
};

#endif