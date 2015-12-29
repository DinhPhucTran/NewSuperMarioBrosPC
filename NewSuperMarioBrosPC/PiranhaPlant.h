#ifndef _PIRANHA_PLANT_
#define _PIRANHA_PLANT_

#include "object.h"
#include "AnimationFactory.h"
#include "ObjectManager.h"
#include "Timer.h"
#include <string>
#include <stdlib.h>

using namespace std;


class PiranhaPlant :public Object
{
protected:
	Mario* mMario;
	Timer mTimeToMove;
	int mDistance;//==HEIGHT
	int mIsGoUp;
	int initY;
public:
	Animation* PiranhaAnimation = new Animation(8, 9);
	Animation* pipeAnim = new Animation(0, 0);
	CSprite * pipeSprite;
	static string const OBJECT_NAME;
	static const int HEIGHT;//24
	static const int WIDTH;//16
	static const int TIME_TO_MOVE;//1000
	static const float SPEED_Y;//0.1f;
	PiranhaPlant(int x, int y, CSprite* image, CSprite * PipeImage);

	virtual void update(int t)override;
	void onCollision(Object *ob, int dir)override;
	void render(int vpx, int vpy)override;
	virtual string getName()override;
};
#endif