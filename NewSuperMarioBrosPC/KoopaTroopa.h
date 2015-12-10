#include "object.h"
#include <string>
#include "AnimationFactory.h"
using namespace std;

class KoopaTroopa;
class KoopaAnimationFactory: public AnimationFactory{
	KoopaTroopa* mKoopa;
public:
	Animation* mKoopaLeftWalkAnim = new Animation(4, 5);
	Animation* mKoopaRightWalkAnim = new Animation(10,11);
	Animation* mKoopaVulnerableAnim = new Animation(36, 36);
	Animation* mKoopaSlidingAnim = new Animation(36, 39);
	Animation* createAnimation()override;
	KoopaAnimationFactory(KoopaTroopa* koopa);
};

class KoopaTroopaState{
public:
	virtual void onCollision(Object* ob);
	virtual string getName();
};

class KoopaNomalState:public KoopaTroopaState{//trạng thái đi lại bình thường
public:
	static const string STATE_NAME;
	void onCollision(Object* ob)override;
	string getName()override;
};

class KoopaVulnerableState :public KoopaTroopaState{//Trạng thái dể bị tổn thương, khi chui vào mai rùa
	//ở trạng thái này mario đụng vào là xong :p
public:
	static const string STATE_NAME;
	void onCollision(Object* ob)override;
	string getName()override;
};

class KoopaSlidingState :public KoopaTroopaState{
	//trạng thái bị mario đá, trượt từ đầu này sang đầu khác
public :
	static const string STATE_NAME;
	void onCollision(Object*ob)override;
	string getName()override;
};

class KoopaTroopa : public Object{
private:
	KoopaTroopaState* mState;
public:
	AnimationFactory* mAnimationFactory;
	//static Animation* 
	static const string OBJECT_NAME;
	string getName();
	KoopaTroopaState* getState();
	void setState(KoopaTroopaState* state);
	void setAnimationFactory(AnimationFactory* animFactory);
	void onCollision(Object* ob)override;
	void render(int vpx,int vpy)override;
	KoopaTroopa(int x, int y, int width, int height, float vx, float vy, float vx_last, float ax, float ay, Animation* anim, CSprite * image);
};