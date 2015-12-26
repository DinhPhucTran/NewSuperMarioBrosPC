#ifndef _ANIMATION_H
#define _ANIMATION_H

class Animation
{
private:
	int frameDelayCounter;
public:
	static const int FRAME_DELAY_DEFAULT;//default =5
	int startFrame, endFrame;
	int index;
	int frameDelay;		//để kiểm soát tốc độ chuyển frame, 
						//ở một số trạng thái thì object có animation nhanh chậm khác nhau
						//ví dụ khi mario chạy thì animation nhanh hơn bình thường
						//hay Rùa ở khi Slide Anim nhanh hơn Rùa đi bộ

	Animation(int startFrame, int endFrame, int frameDelay = Animation::FRAME_DELAY_DEFAULT);
	~Animation();
	virtual void Update();
	void SetIndex(int index);
	void SetFrameDeplay(int frameDelay);
};

#endif