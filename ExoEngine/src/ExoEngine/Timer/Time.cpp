#include "empch.h"
#include "Time.h"

namespace EM {


	Timer::Timer()
	{
		GlobalTimeStarter();
		for (int i = 0; i < t_StartTime.size(); i++)
			Start(static_cast<Systems>(i));

		for (int i = 0; i < m_SystemDT.size(); i++)
			m_SystemDT[i] = 0.016f;

		m_GlobalDT = (float)(1.0f / 60.0f);
	}

	void Timer::RunTimeStarter()
	{
		RuntimeStart = clock();
	}

	void Timer::GlobalTimeStarter()
	{
		GlobalStart = clock();
	}

	//begin each system's start time
	void Timer::Start(Systems system)
	{
		if (t_StartTime.size())
		{
			t_StartTime[static_cast<int>(system)] = std::chrono::system_clock::now();
		}
	}

	void Timer::Update(Systems system)
	{
		m_End = std::chrono::system_clock::now();
		m_Start = GetStartTime(system);
		m_DT = m_End - m_Start;
		SetDeltaTime(system, m_DT.count() / 1000.f);
	}

	void Timer::SetDeltaTime(Systems system, float deltatime)
	{
		if (m_SystemDT.size())
			m_SystemDT[static_cast<int>(system)] = deltatime;
	}

	std::chrono::system_clock::time_point Timer::GetStartTime(Systems system)
	{
		return t_StartTime[static_cast<int>(system)];
	}

	time_t Timer::GetSystemTimeNow()
	{
		return std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()); // converts current time to seconds
	}

	void Timer::GlobalUpdate()
	{
		m_TotalRuntime = (float)(clock() - RuntimeStart) / 1000.0f;
		m_GlobalDT = (float)(clock() - GlobalStart);
		if (m_GlobalDT > 0)
			m_fps = 1000.0f / m_GlobalDT;

		m_GlobalDT = 1.0f / m_fps;
	}

}