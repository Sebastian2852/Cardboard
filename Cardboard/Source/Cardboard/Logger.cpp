#include "Logger.hpp"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Cardboard
{

	std::shared_ptr<spdlog::logger> Logger::s_EngineLogger;
	std::shared_ptr<spdlog::logger> Logger::s_AppLogger;

	void Logger::Init()
	{
		spdlog::set_pattern("%^[%r] [%l] [%n] %v%$");

		s_EngineLogger = spdlog::stderr_color_mt("CARDBOARD");
		s_EngineLogger->set_level(spdlog::level::trace);
		#ifdef CB_DEBUG
				s_EngineLogger->info("Engine logger ready");
		#endif

		s_AppLogger = spdlog::stderr_color_mt("APP");
		s_AppLogger->set_level(spdlog::level::trace);
		#ifdef CB_DEBUG
				s_AppLogger->info("App logger ready");
		#endif
	}

}