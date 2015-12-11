#include "object.h"
#include <string>
#include "AnimationFactory.h"
using namespace std;

class Gooba;
class GoobaAnimationFactory : public AnimationFactory{
	Gooba* mGooba;
public:
	Animation* mGoobaLeftWalkAnim = new Animation(0, 3);
	Animation* mGoobaRightWalkAnim = new Animation(4, 7);
	/*Animation* mKoopaVulnerableAnim = new Animation(36, 36);
	Animation* mKoopaSlidingAnim = new Animation(36, 39);*/
	Animation* createAnimation()override;
	GoobaAnimationFactory(Gooba* gooba);
};

class GoobaState{
public:
	virtual void onCollision(Object* ob);
	virtual string getName();
};

class GoobaNomalState :public GoobaState{//trạng thái đi lại bình thường
public:
	static const string STATE_NAME;
	void onCollision(Object* ob)override;
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