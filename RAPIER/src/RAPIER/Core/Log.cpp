#include "rppch.h"
#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include <spdlog/sinks/basic_file_sink.h>
#include "RAPIER/Editor/EditorConsole/EditorConsoleSink.h"

#include <filesystem>

namespace RAPIER
{

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_EditorConsoleLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		// Create logs directory
		std::string logsDirectory = "logs";
		if (!std::filesystem::exists(logsDirectory))
			std::filesystem::create_directories(logsDirectory);

		std::vector<spdlog::sink_ptr> rapierSinks =
		{
			std::make_shared<spdlog::sinks::stdout_color_sink_mt>(),
			std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/RAPIER.log", true)
		};

		std::vector<spdlog::sink_ptr> editorConsoleSinks =
		{
			std::make_shared<spdlog::sinks::stdout_color_sink_mt>(),
			std::make_shared<EditorConsoleSink>(1)
		};

		std::vector<spdlog::sink_ptr> appSinks =
		{
			std::make_shared<spdlog::sinks::stdout_color_sink_mt>(),
			std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/APP.log", true),
			std::make_shared<EditorConsoleSink>(1)
		};

		rapierSinks[0]->set_pattern("%^[%T] %n: %v%$");
		rapierSinks[1]->set_pattern("[%T] [%l] %n: %v");

		editorConsoleSinks[0]->set_pattern("%^[%T] %n: %v%$");
		editorConsoleSinks[1]->set_pattern("[%T] [%l] %n: %v");

		appSinks[0]->set_pattern("%^[%T] %n: %v%$");
		appSinks[1]->set_pattern("[%T] [%l] %n: %v");
		appSinks[2]->set_pattern("%^[%T] %n: %v%$");

		s_CoreLogger = std::make_shared<spdlog::logger>("RAPIER", rapierSinks.begin(), rapierSinks.end());
		spdlog::register_logger(s_CoreLogger);
		s_CoreLogger->set_level(spdlog::level::trace);
		s_CoreLogger->flush_on(spdlog::level::trace);

		s_EditorConsoleLogger = std::make_shared<spdlog::logger>("Console", editorConsoleSinks.begin(), editorConsoleSinks.end());
		spdlog::register_logger(s_EditorConsoleLogger);
		s_EditorConsoleLogger->set_level(spdlog::level::trace);
		s_EditorConsoleLogger->flush_on(spdlog::level::trace);

		s_ClientLogger = std::make_shared<spdlog::logger>("APP", appSinks.begin(), appSinks.end());
		spdlog::register_logger(s_ClientLogger);
		s_ClientLogger->set_level(spdlog::level::trace);
		s_ClientLogger->flush_on(spdlog::level::trace);
	}

	void Log::Shutdown()
	{
		s_CoreLogger.reset();
		s_EditorConsoleLogger.reset();
		s_ClientLogger.reset();
		spdlog::drop_all();
	}

}	//	END namespace RAPIER

