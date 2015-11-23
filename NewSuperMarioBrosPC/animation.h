#ifndef _ANIMATION_H
#define _ANIMATION_H

class Animation
{
public:
	int startFrame, endFrame;
	int index;
	int frameSpeed;

	Animation(int startFrame, int endFrame);
	~Animation();
	void Update();
	void SetIndex(int index);
};
#endif