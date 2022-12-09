/*!*************************************************************************
****
\file			ResourceManager.cpp
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	Gam200
\section		A
\date			11-11-2022
\brief			This file sets frame data for animations
****************************************************************************
***/
#include "empch.h"
#include "Animation.h"


namespace EM {
	
	/*!*************************************************************************
	Constructor for animation
	****************************************************************************/
	Animation::Animation()
		:frames(0), CurrentFrameIndex(0), currentFrameTime(0)
	{

	}

	/*!*************************************************************************
	Add frame information
	****************************************************************************/
	void Animation::AddFrameInfo(Sprite& sprite)
	{
		FrameData data;
		data.TextureId = GETTEXTURE(sprite.GetTexture())->GetRendererID();
		data.DisplayTime = sprite.GetDisplayTime();
		data.FrameIndex = sprite.GetIndex();
		sprite.SetIndex(CurrentFrameIndex);
		data.MaxFrame = 8.0f;
		frames.push_back(data);
		//std::cout <<"Addframeinfo" << data.DisplayTime << std::endl;
	}

	/*!*************************************************************************
	Increment frame index
	****************************************************************************/
	void Animation::FrameIncrement()
	{
		CurrentFrameIndex++;
	}

	/*!*************************************************************************
	Return frame index if frame size > 0
	****************************************************************************/
	const Animation::FrameData* Animation::GetCurrentFrame() const
	{
		if (frames.size() > 0)
			return &frames[(int)CurrentFrameIndex];

		return nullptr;
	}

	/*!*************************************************************************
	Update animations based on delta time
	****************************************************************************/
	bool Animation::UpdateAnimation(float deltatime)
	{
		if (frames.size() > 0)
		{
			currentFrameTime += deltatime;
			
			if (currentFrameTime >= frames[(int)CurrentFrameIndex].DisplayTime )
			{
				//std::cout <<"Updateanimation" << frames[(int)CurrentFrameIndex].DisplayTime << std::endl;
				currentFrameTime = 0.0f;
				FrameIncrement();

				if (CurrentFrameIndex >= 8.0f)
					ResetFrame();
				return true;
			}
		}
		return false;
	}

	/*!*************************************************************************
	Set frame index and frame time to 0
	****************************************************************************/
	void Animation::ResetFrame()
	{
		CurrentFrameIndex = 0;
		currentFrameTime = 0;
	}
}