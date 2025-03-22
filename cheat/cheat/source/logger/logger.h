#pragma once
#include <mutex>
#include <sstream>
#include <fstream>
#include <string>
#include <string_view>
#include <Windows.h>

namespace Asthmaphobia
{
	class Logger
	{
	public:
		enum class Level : uint8_t
		{
			Call,
			Debug,
			Info,
			Warning,
			Error
		};

	private:
		const Level MinLevel;
#ifdef _DEBUG
		bool ConsoleExists;
		HANDLE HConsole;
#endif
		std::mutex LogMutex;
		std::ofstream FileOut;
		std::string LogFilePath;

		static constexpr std::string_view LevelToString(Level level);
		static constexpr WORD LevelToColor(Level level);
		static std::string GetTimestamp();
		bool InitializeLogDirectory();

	public:
		explicit Logger(Level minLevel = Level::Call);
		~Logger();

		template <typename T>
		void Log(const Level level, const T& message)
		{
			std::ostringstream ss;
			ss << message;
			ActualLog(level, ss.str());
		}

		template <typename T, typename... Args>
		void Log(const Level level, const T& first, const Args&... args)
		{
			std::ostringstream ss;
			ss << first;
			((ss << " " << args), ...);
			ActualLog(level, ss.str());
		}

		void ActualLog(Level level, std::string_view message);
		void Cleanup();
	};

	Logger& GetLoggerInstance();
}

#ifdef _DEBUG
#define LOG_DEBUG(...) \
    Asthmaphobia::GetLoggerInstance().Log(Asthmaphobia::Logger::Level::Debug, __VA_ARGS__)
#define LOG_CALL(...) \
    Asthmaphobia::GetLoggerInstance().Log(Asthmaphobia::Logger::Level::Call, __VA_ARGS__)
#else
#define LOG_DEBUG(...)
#define LOG_CALL(...)
#endif

#define LOG_INFO(...) \
    Asthmaphobia::GetLoggerInstance().Log(Asthmaphobia::Logger::Level::Info, __VA_ARGS__)

#define LOG_WARN(...) \
    Asthmaphobia::GetLoggerInstance().Log(Asthmaphobia::Logger::Level::Warning, __VA_ARGS__)

#define LOG_ERROR(...) \
    Asthmaphobia::GetLoggerInstance().Log(Asthmaphobia::Logger::Level::Error, __VA_ARGS__)
