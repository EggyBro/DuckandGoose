#pragma once
//#define p_Timer EM::Timer::GetInstance()
namespace EM {

#define TotalSystems 6
	enum class Systems
	{
		NONE = 0,
		WINDOWS,
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