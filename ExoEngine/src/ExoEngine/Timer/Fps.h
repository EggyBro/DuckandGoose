/*!*************************************************************************
****
\file			Fps.h
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	CSD2400 / GAM200
\date			11-2-2022
\brief			This file contain the declaration and definiton of a fps class
				It helps to check our frametime during runtime.

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#pragma once
#include <GLFW/glfw3.h>
#include "../Core.h"

namespace EM {

	class EM_API FramePerSec
	{
	public:

		/*!*************************************************************************
		Init various frame counters
		****************************************************************************/
		void InitFrame() 
		{
			mCounter = 0.0f;
			mMaxFrameRate = 60.0f;
			mFrameRate = mMaxFrameRate;
			mFrameTime = 1 / mFrameRate;
			mMinFrameTime = 1 / mMaxFrameRate;
		}

		/*!*************************************************************************
		Start frame count using glfwGetTime()
		****************************************************************************/
		void StartFrameCount() { mStart = (float)glfwGetTime(); }

		/*!*************************************************************************
		End frame count
		****************************************************************************/
		float EndFrameCount()
		{
			while (((float)glfwGetTime() - mStart) < mMinFrameTime)
			{
				float end = (float)glfwGetTime();
				mFrameTime = end - mStart;
				mFps = 1.0f / mFrameTime;
			}
			
			return mFps;
		}

		/*!*************************************************************************
		Return fps
		****************************************************************************/
		float GetFps()const { return mFps; }
		static FramePerSec& GetInstance()
		{
			static FramePerSec instance;
			return instance;
		}
	private:
		float mCounter, mMaxFrameRate, mFrameRate, mFrameTime,
			mMinFrameTime, mStart, mFps;
	};

}