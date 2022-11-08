#include "empch.h"
#include "Animation.h"

namespace EM {
	struct FrameData
	{
		MultiRefs<SpriteRender> Sprite; // which spritesheet is it using
		float DisplayTimePerFrame;		// how long does the frame last before changing the next fram
		vec2D FrameIndex;				// the increment of the frame set to 0 when reach the last frame and y will always remind 0
		float MaxFrame;					//To check for the last frame
	};

	Animation::Animation()
		:CurrentFrameTime(0)
	{

	}
	void Animation::FrameIncrement()
	{
		 
	}
	bool Animation::UpdateAnimation(float deltatime)
	{
		(void)deltatime;
		return false;
	}
	void Animation::ResetFrame()
	{
		//FrameData
	}
}