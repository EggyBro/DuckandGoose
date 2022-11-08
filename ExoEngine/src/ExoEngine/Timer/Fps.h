#pragma once
#include <GLFW/glfw3.h>
#include "../Core.h"

namespace EM {

	class EM_API FramePerSec
	{
	public:
		void InitFrame() 
		{
			m_counter = 0.0f;
			MaxFrameRate = 60.0f;
			m_FrameRate = MaxFrameRate;
			m_FrameTime = 1 / m_FrameRate;
			MinFrameTime = 1 / MaxFrameRate;
		}

		void StartFrameCount() { m_start = (float)glfwGetTime(); }

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