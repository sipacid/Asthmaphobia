#pragma once
#include "source/common.h"
#include <mutex>

namespace Asthmaphobia
{
	class Logger
	{
	public:
		enum class Level : uint8_t
		{
			Debug,
			Info,
			Warning,
			Error,
			None
		};

		explicit Logger(Level minLevel = Level::Debug);
		~Logger();

		void Log(Level level, std::string_view message);
		static std::string GetAppDataPath();

	private:
		const Level minLevel;
		bool ConsoleExists;
		HANDLE HConsole;
		std::mutex logMutex;
		std::ofstream FileOut;
		std::string LogFilePath;

		static constexpr std::string_view LevelToString(Level level);
		static constexpr WORD LevelToColor(Level level);
		static std::string GetTimestamp();
		bool InitializeLogDirectory();
	};

	inline Logger* logger;
}

#ifdef _DEBUG
#define LOG_DEBUG(message)    \
	if (Asthmaphobia::logger) \
	Asthmaphobia::logger->Log(Asthmaphobia::Logger::Level::Debug, message)
#else
#define LOG_DEBUG(message)
#endif

#define LOG_INFO(message)     \
	if (Asthmaphobia::logger) \
	Asthmaphobia::logger->Log(Asthmaphobia::Logger::Level::Info, message)
#define LOG_WARN(message)     \
	if (Asthmaphobia::logger) \
	Asthmaphobia::logger->Log(Asthmaphobia::Logger::Level::Warning, message)
#define LOG_ERROR(message)    \
	if (Asthmaphobia::logger) \
	Asthmaphobia::logger->Log(Asthmaphobia::Logger::Level::Error, message)
