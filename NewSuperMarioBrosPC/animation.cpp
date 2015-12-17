#include "animation.h"

const int Animation::FRAME_DELAY_DEFAULT=6;
Animation::Animation(int StartFrame, int EndFrame,int frDelay )
{

	startFrame = StartFrame;
	endFrame = EndFrame;
	frameDelay = frDelay;
	index = startFrame;
	frameDelayCounter = 1;
}

void Animation::Update()
{
	if (frameDelayCounter >= frameDelay){
		index++;
		if (index > endFrame)
			index = startFrame;
		frameDelayCounter = 0;//reset counter
	}
	++frameDelayCounter;
}

void Animation::SetIndex(int Index)
{
	index = Index;
}
void Animation::SetFrameDeplay(int frDelay){
	frameDelay = frDelay;
}
Animation::~Animation(){
	//nothing to clean up
}