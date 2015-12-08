#include "object.h"
#include <string>

using namespace std;

class KoopaTroopaState{
	virtual void onCollision(Object* ob);

};


class KoopaTroopa : public Object{
private:
	KoopaTroopaState* mState;
public:
	//static Animation* 
	static const string OBJECT_NAME;
	string getName();
	void setState(KoopaTroopaState* state);
	void onCollision(Object* ob)override;
	KoopaTroopa(int x, int y, int width, int height, float vx, float vy, float vx_last, float ax, float ay, Animation* anim, CSprite * image);
};