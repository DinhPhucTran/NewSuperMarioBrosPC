#include "animation.h"

Animation::Animation(int StartFrame, int EndFrame)
{
	startFrame = StartFrame;
	endFrame = EndFrame;
	index = startFrame;
}

void Animation::Update()
{
	index++;
	if (index > endFrame)
		index = startFrame;
}

void Animation::SetIndex(int Index)
{
	index = Index;
}
Animation::~Animation(){
	//nothing to clean up
}