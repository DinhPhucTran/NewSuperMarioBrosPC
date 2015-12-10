#include "animation.h"

const int Animation::FRAME_DELAY = 6;
Animation::Animation(int StartFrame, int EndFrame)
{
	startFrame = StartFrame;
	endFrame = EndFrame;
	index = startFrame;
	frameDelay = 0;
}

void Animation::Update()
{
	if (frameDelay >= FRAME_DELAY){
		index++;
		if (index > endFrame)
			index = startFrame;
		frameDelay = 0;
	}
	++frameDelay;
}

void Animation::SetIndex(int Index)
{
	index = Index;
}
Animation::~Animation(){
	//nothing to clean up
}