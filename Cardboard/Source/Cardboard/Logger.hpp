#pragma once

#include "spdlog/spdlog.h"
#include <memory>

namespace Cardboard
{
	class Logger
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return s_EngineLogger;  }
		inline static std::shared_ptr<spdlog::logger>& GetAppLogger() { return s_AppLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_EngineLogger;
		static std::shared_ptr<spdlog::logger> s_AppLogger;
	};
}

#define CARDBOARD_TRACE(...) ::Cardboard::Logger::GetEngineLogger()->trace(__VA_ARGS__)
#define CARDBOARD_INFO(...) ::Cardboard::Logger::GetEngineLogger()->info(__VA_ARGS__)
#define CARDBOARD_WARN(...) ::Cardboard::Logger::GetEngineLogger()->warn(__VA_ARGS__)
#define CARDBOARD_ERROR(...) ::Cardboard::Logger::GetEngineLogger()->error(__VA_ARGS__)
#define CARDBOARD_CRITICAL(...) ::Cardboard::Logger::GetEngineLogger()->critical(__VA_ARGS__)

#define LOG_TRACE(...) ::Cardboard::Logger::GetAppLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...) ::Cardboard::Logger::GetAppLogger()->info(__VA_ARGS__)
#define LOG_WARN(...) ::Cardboard::Logger::GetAppLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) ::Cardboard::Logger::GetAppLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) ::Cardboard::Logger::GetAppLogger()->critical(__VA_ARGS__)