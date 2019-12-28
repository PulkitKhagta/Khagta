#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Khagta
{
	class  Log
	{
	public:
		static void Init();
		
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger;  }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

//Core Log Macros
#define KG_CORE_TRACE(...)         ::Khagta::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define KG_CORE_INFO(...)          ::Khagta::Log::GetCoreLogger()->info(__VA_ARGS__)
#define KG_CORE_WARN(...)          ::Khagta::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define KG_CORE_ERROR(...)         ::Khagta::Log::GetCoreLogger()->error(__VA_ARGS__)
#define KG_CORE_FATAL(...)         ::Khagta::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Client Log Macros
#define KG_TRACE(...)              ::Khagta::Log::GetClientLogger()->trace(__VA_ARGS__)
#define KG_INFO(...)               ::Khagta::Log::GetClientLogger()->info(__VA_ARGS__)
#define KG_WARN(...)               ::Khagta::Log::GetClientLogger()->warn(__VA_ARGS__)
#define KG_ERROR(...)              ::Khagta::Log::GetClientLogger()->error(__VA_ARGS__)
#define KG_FATAL(...)              ::Khagta::Log::GetClientLogger()->fatal(__VA_ARGS__)