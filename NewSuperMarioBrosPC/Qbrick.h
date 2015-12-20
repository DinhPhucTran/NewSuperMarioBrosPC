#ifndef _Q_BRICK_H
#define _Q_BRICK_H
#include "StaticObject.h"
#include "animation.h"
#include <string>

class QBrick :public StaticObject
{
private:
	Object* mHiddenObject;
	Animation* createAnimation();
	string mState;
	int yLast;
public:
	static const float HIDDEN_OBJECT_Y_SPEED;//0.5f
	static const string NORMAL_STATE;
	static const string QUESTION_STATE;
	Animation* mQuestionAnimation = new Animation(0, 3);
	Animation* mNormalAnimation = new Animation(4, 4);
	void setState(string QbrickState);
	string getState();
	void revealHiddenObject();
	static const string OBJECT_NAME;
	string getName();
	QBrick(int x, int y, int width, int height,Object* hiddenObject, Animation* anim, CSprite * image);
	void render(int vpx, int vpy)override;
	void update(int t);
	~QBrick();
};

#endif