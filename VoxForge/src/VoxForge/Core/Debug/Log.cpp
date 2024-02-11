#include "vfpch.hpp"
#include "VoxForge/Core/Debug/Log.hpp"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

#include <filesystem>

namespace VoxForge
{
	Ref<spdlog::logger> Log::s_ForgeLogger;
	Ref<spdlog::logger> Log::s_StudioLogger;

	void Log::Init()
	{
		const std::string logsDir = "logs";
		if (!std::filesystem::exists(logsDir))
			std::filesystem::create_directory(logsDir);

		std::vector<spdlog::sink_ptr> forgeSinks =
		{
			CreateRef<spdlog::sinks::basic_file_sink_mt>("logs/VoxForge.log", true),
			CreateRef<spdlog::sinks::stdout_color_sink_mt>()
		};

		std::vector<spdlog::sink_ptr> studioSinks =
		{
			CreateRef<spdlog::sinks::basic_file_sink_mt>("logs/VoxStudio.log", true),
			CreateRef<spdlog::sinks::stdout_color_sink_mt>()
		};

		forgeSinks[0]->set_pattern("[%T] [%l] %n: %v");
		studioSinks[0]->set_pattern("[%T] [%l] %n: %v");

		forgeSinks[1]->set_pattern("%^[%T] %n: %v%$");
		studioSinks[1]->set_pattern("%^[%T] %n: %v%$");

		s_ForgeLogger = CreateRef<spdlog::logger>("VoxForge", begin(forgeSinks), end(forgeSinks));
		s_ForgeLogger->set_level(spdlog::level::trace);

		s_StudioLogger = CreateRef<spdlog::logger>("VoxStudio", begin(studioSinks), end(studioSinks));
		s_StudioLogger->set_level(spdlog::level::trace);
	}

	void Log::Shutdown()
	{
		s_ForgeLogger.reset();
		s_StudioLogger.reset();

		spdlog::drop_all();
	}

}
