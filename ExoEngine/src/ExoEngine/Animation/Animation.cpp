/*!*************************************************************************
****
\file			ResourceManager.cpp
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	Gam200
\section		A
\date			11-11-2022
\brief			This file sets frame data for animations

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#include "empch.h"
#include "Animation.h"


namespace EM {
	
	/*!*************************************************************************
	Constructor for animation
	****************************************************************************/
	Animation::Animation()
		:mFrame(0), mCurrentFrameIndex(0), mCurrentFrameTime(0)
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
		sprite.SetIndex(mCurrentFrameIndex);
		data.MaxFrame = 8.0f;
		mFrame.push_back(data);
		//std::cout <<"Addframeinfo" << data.DisplayTime << std::endl;
	}

	/*!*************************************************************************
	Increment frame index
	****************************************************************************/
	void Animation::FrameIncrement()
	{
		mCurrentFrameIndex++;
	}

	/*!*************************************************************************
	Return frame index if frame size > 0
	****************************************************************************/
	const Animation::FrameData* Animation::GetCurrentFrame() const
	{
		if (mFrame.size() > 0)
			return &mFrame[(int)mCurrentFrameIndex];

		return nullptr;
	}

	/*!*************************************************************************
	Update animations based on delta time
	****************************************************************************/
	bool Animation::UpdateAnimation(float deltatime)
	{
		if (mFrame.size() > 0)
		{
			mCurrentFrameTime += deltatime;
			
			if (mCurrentFrameTime >= mFrame[(int)mCurrentFrameIndex].DisplayTime )
			{
				//std::cout <<"Updateanimation" << mFrame[(int)mCurrentFrameIndex].DisplayTime << std::endl;
				mCurrentFrameTime = 0.0f;
				FrameIncrement();

				if (mCurrentFrameIndex >= 8.0f)
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
		mCurrentFrameIndex = 0;
		mCurrentFrameTime = 0;
	}
}