#ifndef _ANIMATION_H
#define _ANIMATION_H

class Animation
{
public:
	static const int FRAME_DELAY;
	int startFrame, endFrame;
	int index;
	int frameDelay;

	Animation(int startFrame, int endFrame);
	~Animation();
	void Update();
	void SetIndex(int index);
};
#endif