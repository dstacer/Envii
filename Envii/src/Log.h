#pragma once
//#include <memory>
#include "Core.h"
#include "spdlog/spdlog.h"

namespace Envii
{
	class Log
	{
	public:
		static void Init();
		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger;  }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Envii logging macros
#define EV_CORE_TRACE(...) ::Envii::Log::GetCoreLogger()->trace(__VA_ARGS__);
#define EV_CORE_INFO(...)  ::Envii::Log::GetCoreLogger()->info(__VA_ARGS__);
#define EV_CORE_WARN(...)  ::Envii::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define EV_CORE_ERROR(...) ::Envii::Log::GetCoreLogger()->error(__VA_ARGS__);
#define EV_CORE_FATAL(...)  ::Envii::Log::GetCoreLogger()->fatal(__VA_ARGS__);

// Client logging macros
#define EV_APP_TRACE(...)  ::Envii::Log::GetClientLogger()->trace(__VA_ARGS__);
#define EV_APP_INFO(...)   ::Envii::Log::GetClientLogger()->info(__VA_ARGS__);
#define EV_APP_WARN(...)   ::Envii::Log::GetClientLogger()->warn(__VA_ARGS__);
#define EV_APP_ERROR(...)  ::Envii::Log::GetClientLogger()->error(__VA_ARGS__);
#define EV_APP_FATAL(...)  ::Envii::Log::GetClientLogger()->fatal(__VA_ARGS__);

