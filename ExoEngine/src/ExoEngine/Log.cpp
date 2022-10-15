/*!*************************************************************************
****
\file Log.cpp
\author Cheung Jun Yin Matthew
\par DP email: j.cheung@digipen.edu
\par Course: csd2400
\par Section: a
\par Milestone 1
\date 28-9-2022
\brief  This file holds the assert system for the project

****************************************************************************
***/
#include "empch.h"
#include "Log.h"

namespace EM {
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		//set pattern output in console(Date, month, time)
		spdlog::set_pattern("%^[%b:%d %T] %n[%l]: %v%$");

		//Create a multhithreaded console logger 
		s_CoreLogger = spdlog::stdout_color_mt("ExoEngine"); // Core
		s_CoreLogger->set_level(spdlog::level::trace);
		s_ClientLogger = spdlog::stdout_color_mt("Exomata"); // Client
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}

