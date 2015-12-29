#ifndef _RED_KOOPA_H_
#define _RED_KOOPA_H_
#include "KoopaTroopa.h"

class RedKoopa :public KoopaTroopa{
public:
	
	RedKoopa(int x, int y, int width, int height, float vx, float vy, float vx_last, float ax, float ay, Animation* anim, CSprite * image);
	RedKoopa(int x, int y, float vx, Animation* anim, CSprite * image);
	static const string OBJECT_NAME;
	string getName()override;
	void update(int t)override;
};


#endif