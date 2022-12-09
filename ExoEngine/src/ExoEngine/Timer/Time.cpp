/*!*************************************************************************
****
\file			Time.cpp
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	CSD2400 / GAM200
\date			11-2-2022
\brief			This file contain the definition for time which uses chrono
				to create a timer and use it as a tracker for our system
				during runtime. It also have a deltatime for update and other
				math implementation.
****************************************************************************
***/
#include "empch.h"
#include "Time.h"

namespace EM {

	/*!*************************************************************************
	Constructor for timer
	****************************************************************************/
	Timer::Timer()
	{
		GlobalTimeStarter();
		for (int i = 0; i < t_StartTime.size(); i++)
			Start(static_cast<Systems>(i));

		for (int i = 0; i < m_SystemDT.size(); i++)
			m_SystemDT[i] = 0.016f;

		m_GlobalDT = (float)(1.0f / 60.0f);
	}

	/*!*************************************************************************
	Start run timer
	****************************************************************************/
	void Timer::RunTimeStarter()
	{
		RuntimeStart = clock();
	}

	/*!*************************************************************************
	Start global timer
	****************************************************************************/
	void Timer::GlobalTimeStarter()
	{
		GlobalStart = clock();
	}

	/*!*************************************************************************
	Begin each system's start time
	****************************************************************************/
	void Timer::Start(Systems system)
	{
		if (t_StartTime.size())
		{
			t_StartTime[static_cast<int>(system)] = std::chrono::system_clock::now();
		}
	}

	/*!*************************************************************************
	Update timer 
	****************************************************************************/
	void Timer::Update(Systems system)
	{
		m_End = std::chrono::system_clock::now();
		m_Start = GetStartTime(system);
		m_DT = m_End - m_Start;
		SetDeltaTime(system, m_DT.count() / 1000.f);
	}

	/*!*************************************************************************
	Set delta time 
	****************************************************************************/
	void Timer::SetDeltaTime(Systems system, float deltatime)
	{
		if (m_SystemDT.size())
			m_SystemDT[static_cast<int>(system)] = deltatime;
	}

	/*!*************************************************************************
	Retrieve start time info
	****************************************************************************/
	std::chrono::system_clock::time_point Timer::GetStartTime(Systems system)
	{
		return t_StartTime[static_cast<int>(system)];
	}

	/*!*************************************************************************
	Retrive time info
	****************************************************************************/
	time_t Timer::GetSystemTimeNow()
	{
		return std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()); // converts current time to seconds
	}

	/*!*************************************************************************
	Update global time
	****************************************************************************/
	void Timer::GlobalUpdate()
	{
		m_TotalRuntime = (float)(clock() - RuntimeStart) / 1000.0f;
		m_GlobalDT = (float)(clock() - GlobalStart);
		if (m_GlobalDT > 0)
			m_fps = 1000.0f / m_GlobalDT;

		m_GlobalDT = 1.0f / m_fps;
	}

}