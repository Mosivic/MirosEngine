#pragma once

#include <memory.h>
#include "Core.h"
#include "spdlog/spdlog.h"


namespace Miros {
	class MIROS_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger(){ return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

//Core Log maccors
#define  MRS_CORE_ERROR(...) Miros::Log::GetCoreLogger()->error(__VA_ARGS__)
#define  MRS_CORE_INFO(...) Miros::Log::GetCoreLogger()->info(__VA_ARGS__)
#define  MRS_CORE_WARN(...) Miros::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define  MRS_CORE_TRACE(...) Miros::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define  MRS_CORE_FATAL(...) Miros::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Client Log maccors
#define  MRS_CLIENT_ERROR(...) Miros::Log::GetClientLogger()->error(__VA_ARGS__)
#define  MRS_CLEINT_INFO(...)  Miros::Log::GetClientLogger()->info(__VA_ARGS__)
#define  MRS_CLIENT_WARN(...)  Miros::Log::GetClientLogger()->warn(__VA_ARGS__)
#define  MRS_CLIENT_TRACE(...) Miros::Log::GetClientLogger()->trace(__VA_ARGS__)
#define  MRS_CLIENT_FATAL(...) Miros::Log::GetClientLogger()->fatal(__VA_ARGS__)

