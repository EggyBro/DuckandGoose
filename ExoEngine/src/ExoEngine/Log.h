#pragma once
#include "core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace EM {
	class EM_API Log
	{
	public:
		
		static void Init();

		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }


	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}
//Macros for logger
//Core aka ExoEngine
//Trace is to track variable changes during execution like Window Size etc
#define EM_EXO_TRACE(...)	 ::EM::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define EM_EXO_INFO(...)	 ::EM::Log::GetCoreLogger()->info(__VA_ARGS__)
#define EM_EXO_WARN(...)	 ::EM::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define EM_EXO_ERROR(...)	 ::EM::Log::GetCoreLogger()->error(__VA_ARGS__)
#define EM_EXO_CRITICAL(...) ::EM::Log::GetCoreLogger()->critical(__VA_ARGS__)

//Assertion failed, it will track where it happened and print it in console (for debug)
#define EM_EXO_ASSERT(x, ...) {if((x)) { EM_EXO_CRITICAL("Assert Failed: {} {}\n\tIn File:{}\n\tLine: {}",x, __VA_ARGS__,__FILE__,__LINE__);__debugbreak();}}

//Client aka Exomata
#define EM_TRACE(...) ::EM::Log::GetClientLogger()->trace(__VA_ARGS__)
#define EM_INFO(...)  ::EM::Log::GetClientLogger()->info(__VA_ARGS__)
#define EM_WARN(...)  ::EM::Log::GetClientLogger()->warn(__VA_ARGS__)
#define EM_ERROR(...) ::EM::Log::GetClientLogger()->error(__VA_ARGS__)
#define EM_CRITICAL(...) ::EM::Log::GetClientLogger()->critical(__VA_ARGS__)
