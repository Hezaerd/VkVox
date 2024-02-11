#pragma once

#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

#include <map>

namespace VoxForge
{
	class Log
	{
	public:
		enum class Type : uint8_t
		{
			Forge = 0, Studio = 1
		};

		enum class Level : uint8_t
		{
			Trace = 0, Info = 1, Warn = 2, Error = 3, Fatal = 4
		};

		struct TagDetail
		{
			bool Enabled = true;
			Level LevelFilter = Level::Trace;
		};

	public:
		static void Init();
		static void Shutdown();

		inline static Ref<spdlog::logger>& GetForgeLogger() { return s_ForgeLogger; }
		inline static Ref<spdlog::logger>& GetStudioLogger() { return s_StudioLogger; }

		inline static bool HasTag(const std::string& pTag) { return s_EnabledTags.contains(pTag); }
		static std::map<std::string, TagDetail>& GetEnabledTags() { return s_EnabledTags; }

		template<typename... Args>
		static void PrintMessage(Log::Type pType, Log::Level pLevel, std::string_view pTag, Args&&... pArgs);

	public:
		static const char* LevelToString(const Level pLevel)
		{
			switch (pLevel)
			{
				case Level::Trace: return "Trace";
				case Level::Info:  return "Info";
				case Level::Warn:  return "Warn";
				case Level::Error: return "Error";
				case Level::Fatal: return "Fatal";
			}
			return "";
		}

		static Level LevelFromString(const std::string& pLevel)
		{
			if (pLevel == "Trace") return Level::Trace;
			if (pLevel == "Info") return Level::Info;
			if (pLevel == "Warn") return Level::Warn;
			if (pLevel == "Error") return Level::Error;
			if (pLevel == "Fatal") return Level::Fatal;

			return Level::Trace;
		}
		
	private:
		static Ref<spdlog::logger> s_ForgeLogger;
		static Ref<spdlog::logger> s_StudioLogger;

		inline static std::map<std::string, TagDetail> s_EnabledTags;
	};
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Tagged logs (prefer these!)                                                                                      //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Forge logging
#define VF_TRACE_TAG(tag, ...) ::VoxForge::Log::PrintMessage(::VoxForge::Log::Type::Forge, ::VoxForge::Log::Level::Trace, tag, __VA_ARGS__)
#define VF_INFO_TAG(tag, ...)  ::VoxForge::Log::PrintMessage(::VoxForge::Log::Type::Forge, ::VoxForge::Log::Level::Info, tag, __VA_ARGS__)
#define VF_WARN_TAG(tag, ...)  ::VoxForge::Log::PrintMessage(::VoxForge::Log::Type::Forge, ::VoxForge::Log::Level::Warn, tag, __VA_ARGS__)
#define VF_ERROR_TAG(tag, ...) ::VoxForge::Log::PrintMessage(::VoxForge::Log::Type::Forge, ::VoxForge::Log::Level::Error, tag, __VA_ARGS__)
#define VF_FATAL_TAG(tag, ...) ::VoxForge::Log::PrintMessage(::VoxForge::Log::Type::Forge, ::VoxForge::Log::Level::Fatal, tag, __VA_ARGS__)

// Studio logging
#define VS_TRACE_TAG(tag, ...) ::VoxForge::Log::PrintMessage(::VoxForge::Log::Type::Studio, ::VoxForge::Log::Level::Trace, tag, __VA_ARGS__)
#define VS_INFO_TAG(tag, ...)  ::VoxForge::Log::PrintMessage(::VoxForge::Log::Type::Studio, ::VoxForge::Log::Level::Info, tag, __VA_ARGS__)
#define VS_WARN_TAG(tag, ...)  ::VoxForge::Log::PrintMessage(::VoxForge::Log::Type::Studio, ::VoxForge::Log::Level::Warn, tag, __VA_ARGS__)
#define VS_ERROR_TAG(tag, ...) ::VoxForge::Log::PrintMessage(::VoxForge::Log::Type::Studio, ::VoxForge::Log::Level::Error, tag, __VA_ARGS__)
#define VS_FATAL_TAG(tag, ...) ::VoxForge::Log::PrintMessage(::VoxForge::Log::Type::Studio, ::VoxForge::Log::Level::Fatal, tag, __VA_ARGS__)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Forge logging
#define VF_TRACE(...) ::VoxForge::Log::PrintMessage(::VoxForge::Log::Type::Forge, ::VoxForge::Log::Level::Trace, "", __VA_ARGS__)
#define VF_INFO(...)  ::VoxForge::Log::PrintMessage(::VoxForge::Log::Type::Forge, ::VoxForge::Log::Level::Info, "", __VA_ARGS__)
#define VF_WARN(...)  ::VoxForge::Log::PrintMessage(::VoxForge::Log::Type::Forge, ::VoxForge::Log::Level::Warn, "", __VA_ARGS__)
#define VF_ERROR(...) ::VoxForge::Log::PrintMessage(::VoxForge::Log::Type::Forge, ::VoxForge::Log::Level::Error, "", __VA_ARGS__)
#define VF_FATAL(...) ::VoxForge::Log::PrintMessage(::VoxForge::Log::Type::Forge, ::VoxForge::Log::Level::Fatal, "", __VA_ARGS__)

// Studio logging
#define VS_TRACE(...) ::VoxForge::Log::PrintMessage(::VoxForge::Log::Type::Studio, ::VoxForge::Log::Level::Trace, "", __VA_ARGS__)
#define VS_INFO(...)  ::VoxForge::Log::PrintMessage(::VoxForge::Log::Type::Studio, ::VoxForge::Log::Level::Info, "", __VA_ARGS__)
#define VS_WARN(...)  ::VoxForge::Log::PrintMessage(::VoxForge::Log::Type::Studio, ::VoxForge::Log::Level::Warn, "", __VA_ARGS__)
#define VS_ERROR(...) ::VoxForge::Log::PrintMessage(::VoxForge::Log::Type::Studio, ::VoxForge::Log::Level::Error, "", __VA_ARGS__)
#define VS_FATAL(...) ::VoxForge::Log::PrintMessage(::VoxForge::Log::Type::Studio, ::VoxForge::Log::Level::Fatal, "", __VA_ARGS__)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace VoxForge
{
	template<typename... Args>
	void Log::PrintMessage(Log::Type pType, Log::Level pLevel, std::string_view pTag, Args&&... pArgs)
	{
		auto detail = s_EnabledTags[std::string(pTag)];
		if (detail.Enabled && detail.LevelFilter <= pLevel)
		{
			auto& logger = (pType == Type::Forge) ? GetForgeLogger() : GetStudioLogger();
			std::string logString = pTag.empty() ? "{0}{1}" : "[{0}] {1}";
			switch(pLevel)
			{
			case Level::Trace:
				logger->trace(logString, pTag, fmt::format(std::forward<Args>(pArgs)...));
				break;
			case Level::Info:
				logger->info(logString, pTag, fmt::format(std::forward<Args>(pArgs)...));
				break;
			case Level::Warn:
				logger->warn(logString, pTag, fmt::format(std::forward<Args>(pArgs)...));
				break;
			case Level::Error:
				logger->error(logString, pTag, fmt::format(std::forward<Args>(pArgs)...));
				break;
			case Level::Fatal:
				logger->critical(logString, pTag, fmt::format(std::forward<Args>(pArgs)...));
				break;
			}
		}
	}

}
