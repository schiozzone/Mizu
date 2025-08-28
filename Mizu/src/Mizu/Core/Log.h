#pragma once

#include "Mizu/Core/Core.h"

#define FMT_DEPRECATED
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Mizu {

	class Log
	{
	public:
		static void Init();

		inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};

}

// LOG MACROS
#define MZ_CORE_TRACE(...)    ::Mizu::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define MZ_CORE_INFO(...)     ::Mizu::Log::GetCoreLogger()->info(__VA_ARGS__)
#define MZ_CORE_WARN(...)     ::Mizu::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define MZ_CORE_ERROR(...)    ::Mizu::Log::GetCoreLogger()->error(__VA_ARGS__)
#define MZ_CORE_CRITICAL(...) ::Mizu::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define MZ_TRACE(...)         ::Mizu::Log::GetClientLogger()->trace(__VA_ARGS__)
#define MZ_INFO(...)          ::Mizu::Log::GetClientLogger()->info(__VA_ARGS__)
#define MZ_WARN(...)          ::Mizu::Log::GetClientLogger()->warn(__VA_ARGS__)
#define MZ_ERROR(...)         ::Mizu::Log::GetClientLogger()->error(__VA_ARGS__)
#define MZ_CRITICAL(...)      ::Mizu::Log::GetClientLogger()->critical(__VA_ARGS__)