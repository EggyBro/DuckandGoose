/*!*************************************************************************
****
\file			Fps.h
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	CSD2400 / GAM200
\date			11-2-2022
\brief			This file contain the declaration and definiton of a fps class
				It helps to check our frametime during runtime.
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
			m_counter = 0.0f;
			MaxFrameRate = 60.0f;
			m_FrameRate = MaxFrameRate;
			m_FrameTime = 1 / m_FrameRate;
			MinFrameTime = 1 / MaxFrameRate;
		}

		/*!*************************************************************************
		Start frame count using glfwGetTime()
		****************************************************************************/
		void StartFrameCount() { m_start = (float)glfwGetTime(); }

		/*!*************************************************************************
		End frame count
		****************************************************************************/
		float EndFrameCount()
		{
			while (((float)glfwGetTime() - m_start) < MinFrameTime)
			{
				float end = (float)glfwGetTime();
				m_FrameTime = end - m_start;
				m_Fps = 1.0f / m_FrameTime;
			}
			
			return m_Fps;
		}

		/*!*************************************************************************
		Return fps
		****************************************************************************/
		float GetFps()const { return m_Fps; }
		static FramePerSec& GetInstance()
		{
			static FramePerSec instance;
			return instance;
		}
	private:
		float m_counter, MaxFrameRate, m_FrameRate, m_FrameTime,
			MinFrameTime, m_start, m_Fps;
	};

}