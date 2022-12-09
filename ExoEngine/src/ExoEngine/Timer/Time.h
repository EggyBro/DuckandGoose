/*!*************************************************************************
****
\file			Time.h
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	CSD2400 / GAM200
\date			11-2-2022
\brief			This file contain the declare for time which uses chrono
				to create a timer and use it as a tracker for our system
				during runtime. It also have a deltatime for update and other
				math implementation.
****************************************************************************
***/
#pragma once
namespace EM {

#define TotalSystems 6
	enum class Systems
	{
		NONE = 0,
		COLLISION,
		GRAPHIC,
		PHYSICS,
		LOGIC,
		API		
	};

	class Timer {

	public:
		Timer();
		~Timer() = default;

		//for global calculations
		void RunTimeStarter();
		void GlobalTimeStarter();
		void GlobalUpdate();

		// returns global delta time
		float GetGlobalDT() const { return m_GlobalDT; }
		float GetDT(Systems system) { return m_SystemDT[static_cast<int>(system)]; }
		float GetFps() const { return m_fps; }

		//Timer for system runtime
		void Start(Systems system);
		void Update(Systems system);
		void SetDeltaTime(Systems system, float deltatime);

		std::chrono::system_clock::time_point GetStartTime(Systems system);

		static Timer& GetInstance()
		{
			static Timer instance;
			return instance;
		}

	public:
		std::array<std::chrono::system_clock::time_point, TotalSystems> t_StartTime;
		std::array<float, TotalSystems> m_SystemDT;

	private:
		std::chrono::system_clock::time_point m_Start, m_End;
		std::chrono::duration<float, std::milli> m_DT;
		clock_t GlobalStart, RuntimeStart;
		float m_GlobalDT, m_TotalRuntime, m_fps, m_dt;

	private:
		time_t GetSystemTimeNow();
	};

}