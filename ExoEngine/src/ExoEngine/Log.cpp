/*!*************************************************************************
****
\file Log.cpp
\author Cheung Jun Yin Matthew
\par DP email: j.cheung@digipen.edu
\par Course: CSD2400 / GAM200 
\date 11/2/2022
\brief  This file holds the assert system for the project

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#include "empch.h"
#include "Log.h"
#include "spdlog/sinks/ostream_sink.h"

namespace EM {
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;
	std::ostringstream Log::oss; // stream for imgui logger window

	/*!*************************************************************************
	Init loop for log
	****************************************************************************/
	void Log::Init()
	{
		//set pattern output in console(Date, month, time)
		spdlog::set_pattern("%^[%b:%d %T] %n[%l]: %v%$");

		//Create a multhithreaded console logger 
		s_CoreLogger = spdlog::stdout_color_mt("ExoEngine"); // Core
		s_CoreLogger->set_level(spdlog::level::trace);
		auto& listOfSink = s_CoreLogger->sinks();
		listOfSink.emplace_back(std::make_shared<spdlog::sinks::ostream_sink_st>(oss));

		s_ClientLogger = spdlog::stdout_color_mt("Exomata"); // Client
		s_ClientLogger->set_level(spdlog::level::trace);
	}

	/*!*************************************************************************
	Log info to output to editor 
	****************************************************************************/
	std::string Log::GetImguiLog()
	{
		return oss.str();
	}
}

